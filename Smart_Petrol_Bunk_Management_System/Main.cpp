#include <bits/stdc++.h>
using namespace std;

#define PETROL_MAX 10000.0
#define DIESEL_MAX 10000.0
#define DELAY_TIME_MS 5000
#define FILL_ITERATIONS 10
#define DEMAND_WINDOW 10 // number of recent purchases used for prediction

using ll = long long;

// ---------------------- Helper utilities ----------------------
void capitalize(string &str)
{
    for (char &c : str)
        c = tolower(c);
    if (!str.empty())
        str[0] = toupper(str[0]);
}

string now_timestamp()
{
    auto t = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(t);
    string s = ctime(&tt);
    if (!s.empty() && s.back() == '\n')
        s.pop_back();
    return s;
}

// ---------------------- Transaction record types ----------------------
enum class TxType
{
    DEPOSIT,
    PURCHASE
};

struct TransactionRecord
{
    TxType type;
    double amount;  // money amount (for deposit or purchase cost)
    double liters;  // liters involved (0 for deposit)
    char fuel_type; // 'p' or 'd' for purchases, otherwise 'n'
    string timestamp;
    string note;
    TransactionRecord(TxType t = TxType::DEPOSIT, double amt = 0.0, double l = 0.0, char ft = 'n', const string &nt = "")
        : type(t), amount(amt), liters(l), fuel_type(ft), timestamp(now_timestamp()), note(nt) {}
};

// For undo stack: we'll store TransactionRecord plus an indicator whether undoing requires restocking
struct UndoRecord
{
    TransactionRecord tx;
    bool restock_on_undo; // true if undoing this tx should add back liters to stock (purchase)
};

// ---------------------- Customer class ----------------------
// Each customer has:
// - id, name, balance
// - transaction history (linked list)
// - undo stack (to undo recent transactions)
// Note: We will not store loyalty map inside Customer class; PetrolLane holds the loyalty hash map.

class Customer
{
protected:
    static string id_creator; // e.g. "IN0000"
    string id;
    string name;
    double balance;

    list<string> transaction_history; // linked list of readable tx descriptions
    stack<UndoRecord> undo_stack;     // stack to undo recent transactions

public:
    Customer()
    {
        // generate next id
        string temp = id_creator.substr(2);
        int val = stoi(temp);
        val++;
        ostringstream ss;
        ss << "IN" << setw(4) << setfill('0') << val;
        id = ss.str();
        id_creator = id;
        balance = 0.0;
    }
    Customer(const string &nm) : Customer()
    {
        name = nm;
    }

    const string &getId() const { return id; }
    const string &getName() const { return name; }
    double getBalance() const { return balance; }

    void setId(const string &new_id) { id = new_id; }
    void setName(const string &nm) { name = nm; }
    void setBalance(double b) { balance = b; }

    // Add a deposit transaction
    bool deposit(double amt)
    {
        if (amt <= 0)
        {
            cout << "Enter a valid amount > 0\n";
            return false;
        }
        balance += amt;
        // record
        TransactionRecord rec(TxType::DEPOSIT, amt, 0.0, 'n', "Deposit");
        transaction_history.push_back("Deposit: +" + to_string(amt) + " at " + rec.timestamp);
        undo_stack.push({rec, false});
        cout << "Deposit successful. Current balance: " << balance << "\n";
        return true;
    }

    // Purchase fuel: this only adjusts balance and records transaction.
    // Actual stock deduction and loyalty handling are done by Petrol_Lane when calling this method as part of process.
    bool recordPurchase(double amount_money, double liters, char fuel_type)
    {
        if (amount_money <= 0 || liters <= 0)
            return false;
        if (balance < amount_money)
        {
            cout << "Insufficient balance to record purchase.\n";
            return false;
        }
        balance -= amount_money;
        TransactionRecord rec(TxType::PURCHASE, amount_money, liters, fuel_type, "Fuel purchase");
        ostringstream ss;
        ss << "Purchase: -" << amount_money << " for " << liters << "L (" << fuel_type << ") at " << rec.timestamp;
        transaction_history.push_back(ss.str());
        // push undo record: undo of purchase should restock liters and refund amount
        undo_stack.push({rec, true});
        cout << "Purchase recorded. Current balance: " << balance << "\n"<<endl;
        return true;
    }

    // Undo last transaction (deposit or purchase)
    // returns UndoRecord if undone, or optional empty if nothing to undo.
    optional<UndoRecord> undoLast()
    {
        if (undo_stack.empty())
        {
            cout << "No transaction to undo for customer " << id << "\n";
            return nullopt;
        }
        UndoRecord ur = undo_stack.top();
        undo_stack.pop();

        TransactionRecord tx = ur.tx;
        if (tx.type == TxType::DEPOSIT)
        {
            // reverse deposit -> subtract amount from balance
            if (balance < tx.amount)
            {
                cout << "Cannot undo deposit: current balance (" << balance
                     << ") is less than the deposit amount (" << tx.amount << ").\n";
                // push back
                undo_stack.push(ur);
                return nullopt;
            }
            balance -= tx.amount;
            transaction_history.push_back("Undo Deposit: -" + to_string(tx.amount) + " at " + now_timestamp());
            cout << "Deposit undone. Current balance: " << balance << "\n";
            return ur;
        }
        else
        { // PURCHASE
            // refund the amount and (optionally) restock liters handled by caller if restock_on_undo == true
            balance += tx.amount;
            transaction_history.push_back("Undo Purchase: +" + to_string(tx.amount) + " at " + now_timestamp());
            cout << "Purchase undone. Current balance: " << balance << "\n";
            return ur;
        }
    }

    const list<string>& getTransactionHistory()
    {
        return transaction_history;
    }


    void showHistory() const
    {
        cout << "Transaction history for " << name << " (" << id << "):\n";
        if (transaction_history.empty())
        {
            cout << "  No transactions yet.\n";
            return;
        }
        for (const auto &s : transaction_history)
        {
            cout << "  " << s << "\n";
        }
    }
};

string Customer::id_creator = "IN0000";

// ---------------------- Customer BST ----------------------
struct CustomerNode
{
    Customer *cust;
    CustomerNode *left, *right;
    CustomerNode(Customer *c = nullptr) : cust(c), left(nullptr), right(nullptr) {}
};

class CustomerBST
{
private:
    CustomerNode *root;

    CustomerNode *insertNode(CustomerNode *node, Customer *cust)
    {
        if (!node)
            return new CustomerNode(cust);
        if (cust->getId() < node->cust->getId())
            node->left = insertNode(node->left, cust);
        else
            node->right = insertNode(node->right, cust);
        return node;
    }

    Customer *searchNode(CustomerNode *node, const string &id) const
    {
        if (!node)
            return nullptr;
        if (id == node->cust->getId())
            return node->cust;
        if (id < node->cust->getId())
            return searchNode(node->left, id);
        return searchNode(node->right, id);
    }

    void inorderNode(CustomerNode *node) const
    {
        if (!node)
            return;
        inorderNode(node->left);
        cout << "  " << node->cust->getId() << " - " << node->cust->getName() << " (Balance: " << node->cust->getBalance() << ")\n";
        inorderNode(node->right);
    }

    void freeNode(CustomerNode *node)
    {
        if (!node)
            return;
        freeNode(node->left);
        freeNode(node->right);
        delete node->cust;
        delete node;
    }

public:
    CustomerBST() : root(nullptr) {}
    ~CustomerBST() { freeNode(root); }

    void insert(Customer *cust)
    {
        root = insertNode(root, cust);
    }

    Customer *search(const string &id) const
    {
        return searchNode(root, id);
    }

    void inorder() const
    {
        if (!root)
        {
            cout << "No customers in BST yet.\n";
            return;
        }
        cout << "Customers (in-order):\n";
        inorderNode(root);
    }
};

// ---------------------- Vehicle + Priority Queue ----------------------
class Vehicle
{
public:
    string reg_no;
    string type_name; // Ambulance, Fire_truck, etc.
    string cust_id;   // "0" if unregistered
    char fuel_type;   // 'p' or 'd'
    int priority;     // higher -> earlier
    double liters_required;

    Vehicle(string reg = "", string t = "", string cid = "0", char ft = 'p', int pr = 1, double liters = 0.0)
        : reg_no(reg), type_name(t), cust_id(cid), fuel_type(ft), priority(pr), liters_required(liters) {}
};

struct VehicleComparator
{
    bool operator()(const Vehicle *a, const Vehicle *b) const
    {
        // higher priority first; if equal, FIFO by pointer (not ideal), but could add timestamp.
        if (a->priority == b->priority)
            return a > b; // older pointers lower? (approx)
        return a->priority < b->priority;
    }
};

// ---------------------- Petrol Lane (main system) ----------------------
class PetrolLane
{
private:
    CustomerBST bst;                                // BST storing pointers owned by BST nodes
    unordered_map<string, Customer *> customer_map; // quick lookup by id (same pointers as in BST)
    unordered_map<string, int> loyalty_points;      // hash map: customer id -> points

    priority_queue<Vehicle *, vector<Vehicle *>, VehicleComparator> vehicle_queue;

    double petrol_stock;
    double diesel_stock;
    double emergency_petrol_reserve;
    double emergency_diesel_reserve;

    // predictive demand: store recent liters of purchases (sum of liters)
    deque<double> recent_demands;

    const double price_per_liter = 100.0; // fixed price, can be made variable

public:
    PetrolLane()
    {
        petrol_stock = diesel_stock = 0.0;
        // reserve 5% by default
        emergency_petrol_reserve = PETROL_MAX * 0.05;
        emergency_diesel_reserve = DIESEL_MAX * 0.05;
    }

    // ---- Customer management ----
    Customer *createCustomer(const string &name)
    {
        Customer *c = new Customer(name);
        bst.insert(c);
        customer_map[c->getId()] = c;
        loyalty_points[c->getId()] = 0;
        cout << "Customer created: " << c->getId() << " - " << c->getName() << "\n";
        return c;
    }

    Customer *getCustomer(const string &id)
    {
        if (id == "0")
            return nullptr;
        auto it = customer_map.find(id);
        if (it != customer_map.end())
            return it->second;
        // fallback search in BST (shouldn't be necessary if maintained correctly)
        Customer *c = bst.search(id);
        if (c)
            customer_map[id] = c;
        return c;
    }

    void listCustomersSorted() const
    {
        bst.inorder();
    }

    void showCustomerDetails(const string &id)
    {
        Customer *c = getCustomer(id);
        if (!c)
        {
            cout << "Customer not found.\n";
            return;
        }
        cout << "Customer: " << c->getId() << " - " << c->getName() << "\n";
        cout << "Balance: " << c->getBalance() << "\n";
        cout << "Loyalty Points: " << loyalty_points.at(c->getId()) << "\n";
        c->showHistory();
    }

    // deposit to customer account
    bool depositToCustomer(const string &cust_id, double amt)
    {
        Customer *c = getCustomer(cust_id);
        if (!c)
        {
            cout << "Customer ID not found.\n";
            return false;
        }
        return c->deposit(amt);
    }

    // undo last transaction for customer
    void undoLastForCustomer(const string &cust_id)
    {
        Customer *c = getCustomer(cust_id);
        if (!c)
        {
            cout << "Customer ID not found.\n";
            return;
        }
        auto optur = c->undoLast();
        if (!optur.has_value())
        {
            cout << "Nothing was undone.\n";
            return;
        }
        UndoRecord ur = optur.value();
        // if it was a purchase and restock_on_undo true, attempt restock
        if (ur.restock_on_undo)
        {
            char ft = ur.tx.fuel_type;
            double liters = ur.tx.liters;
            if (ft == 'p')
            {
                if (petrol_stock + liters > PETROL_MAX)
                {
                    cout << "Cannot undo purchase fully: petrol stock would exceed max. Partial undo not supported.\n";
                    // (We reversed balance already; we could push back the undo record - skipping for simplicity)
                }
                else
                {
                    petrol_stock += liters;
                    cout << "Restocked " << liters << "L petrol due to undo.\n";
                }
            }
            else if (ft == 'd')
            {
                if (diesel_stock + liters > DIESEL_MAX)
                {
                    cout << "Cannot undo purchase fully: diesel stock would exceed max.\n";
                }
                else
                {
                    diesel_stock += liters;
                    cout << "Restocked " << liters << "L diesel due to undo.\n";
                }
            }
            // adjust loyalty points (remove points granted by that purchase)
            string cid = cust_id;
            int points_deduct = static_cast<int>(ur.tx.amount / 100.0);
            if (loyalty_points.find(cid) != loyalty_points.end())
            {
                loyalty_points[cid] = max(0, loyalty_points[cid] - points_deduct);
                cout << "Loyalty points adjusted: -" << points_deduct << "\n";
            }
        }
        else
        {
            // deposit undo: nothing stock-related; loyalty unaffected
        }
    }

    // ---- Stock management ----
    bool refillStock(double petrol, double diesel)
    {
        if (petrol < 0 || diesel < 0)
        {
            cout << "Invalid stock amounts.\n";
            return false;
        }
        if (petrol_stock + petrol > PETROL_MAX || diesel_stock + diesel > DIESEL_MAX)
        {
            cout << "Refill would exceed max capacity.\n";
            return false;
        }
        petrol_stock += petrol;
        diesel_stock += diesel;
        cout << "Refilled stocks. Petrol: " << petrol_stock << ", Diesel: " << diesel_stock << "\n";
        return true;
    }

    void showStock() const
    {
        if (petrol_stock < 0.1 * PETROL_MAX)
            cout << "Warning: Petrol stock below 10% of capacity.\n";
        if (diesel_stock < 0.1 * DIESEL_MAX)
            cout << "Warning: Diesel stock below 10% of capacity.\n";
        cout << "Petrol stock: " << petrol_stock << " L (reserve: " << emergency_petrol_reserve << " L)\n";
        cout << "Diesel stock: " << diesel_stock << " L (reserve: " << emergency_diesel_reserve << " L)\n";
    }

    void setEmergencyReserve(double petrol_reserve, double diesel_reserve)
    {
        if (petrol_reserve < 0 || diesel_reserve < 0)
        {
            cout << "Invalid reserves.\n";
            return;
        }
        emergency_petrol_reserve = petrol_reserve;
        emergency_diesel_reserve = diesel_reserve;
        cout << "Emergency reserves updated.\n";
    }

    // ---- Vehicles / Queue management ----
    void addVehicleToQueue()
    {
        string reg, type_name, cust_id;
        char fuel_type;
        double liters;
        cout << "Enter Vehicle Registration Number: ";
        cin >> reg;
        cout << "Enter Vehicle Type (Ambulance/Fire_truck/Police_Car/Bus/Truck/Car): ";
        cin >> type_name;
        capitalize(type_name);
        cout << "Enter Customer ID if registered (0 if unregistered): ";
        cin >> cust_id;
        if (cust_id != "0" && getCustomer(cust_id) == nullptr)
        {
            cout << "Customer ID not found. Please register the customer first.\n";
            return;
        }
        cout << "Enter Fuel Type (p for Petrol / d for Diesel): ";
        cin >> fuel_type;
        if (fuel_type != 'p' && fuel_type != 'd')
        {
            cout << "Invalid fuel type.\n";
            return;
        }
        cout << "Enter liters required: ";
        cin >> liters;
        int priority = 1;
        if (type_name == "Ambulance")
            priority = 5;
        else if (type_name == "Fire_truck")
            priority = 4;
        else if (type_name == "Police_car")
            priority = 3;
        else if (type_name == "Bus" || type_name == "Truck")
            priority = 2;
        else
            priority = 1;

        Vehicle *v = new Vehicle(reg, type_name, cust_id, fuel_type, priority, liters);
        vehicle_queue.push(v);
        cout << type_name << " (" << reg << ") added to queue with priority " << priority << ".\n";
    }

    // Process only the next vehicle (top of priority queue)
    void processNextVehicle()
    {
        if (vehicle_queue.empty())
        {
            cout << "No vehicles in queue.\n";
            return;
        }
        Vehicle *v = vehicle_queue.top();
        vehicle_queue.pop();

        // Check stock vs emergency reserve
        if (v->fuel_type == 'p')
        {
            if (petrol_stock - v->liters_required < emergency_petrol_reserve)
            {
                cout << "Cannot serve vehicle " << v->reg_no << ": petrol would drop below emergency reserve.\n";
                // If we want, we could requeue or discard. Here we discard and inform.
                delete v;
                return;
            }
        }
        else
        {
            if (diesel_stock - v->liters_required < emergency_diesel_reserve)
            {
                cout << "Cannot serve vehicle " << v->reg_no << ": diesel would drop below emergency reserve.\n";
                delete v;
                return;
            }
        }

        double cost = v->liters_required * price_per_liter;

        // If customer registered, check balance and deduct
        if (v->cust_id != "0")
        {
            Customer *c = getCustomer(v->cust_id);
            if (!c)
            {
                cout << "Associated customer id not found; proceed as unregistered cash sale.\n";
            }
            else
            {
                if (c->getBalance() < cost)
                {
                    cout << "Insufficient balance for customer " << c->getName() << ". Cannot service.\n";
                    delete v;
                    return;
                }
                // Deduct balance and record purchase in customer record
                bool ok = c->recordPurchase(cost, v->liters_required, v->fuel_type);
                if (!ok)
                {
                    cout << "Failed to record purchase for customer.\n";
                    delete v;
                    return;
                }
                // Update loyalty points: e.g., 1 point per 100 rupees spent
                int points = static_cast<int>(cost / 100.0);
                loyalty_points[v->cust_id] += points;
                cout << "Loyalty points awarded: " << points << " (Total: " << loyalty_points[v->cust_id] << ")\n";
            }
        }
        else
        {
            // Unregistered -> cash sale: we don't maintain cash register; simply proceed and record demand.
            cout << "\nUnregistered vehicle paying cash. Amount: " << cost << "\n";
            // Optionally we could keep a cash register.
        }

        // Deduct stock
        if (v->fuel_type == 'p')
            petrol_stock -= v->liters_required;
        else
            diesel_stock -= v->liters_required;

        // Add to recent demands for prediction
        double liters_for_demand = v->liters_required;
        recent_demands.push_back(liters_for_demand);
        if (recent_demands.size() > DEMAND_WINDOW)
            recent_demands.pop_front();

        // Simulate fueling with progress
        cout << v->type_name << " (" << v->reg_no << ") is fueling " << v->liters_required << " L. " << endl;
        // cout << "\r" << string(20,' ') << "\r";
        for (int x = 1; x <= FILL_ITERATIONS; ++x)
        {
            cout << "\rLitres filling : " << (int)(v->liters_required * ((double)x / FILL_ITERATIONS)) << " L";
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(DELAY_TIME_MS / FILL_ITERATIONS));
        }
        cout << "   \n";
        cout << v->type_name << " (" << v->reg_no << ") fueled " << v->liters_required
             << " liters. Total cost: " << cost << "\n";

        delete v;
        // cout<<endl;
    }

    // Show queue summary
    void showQueueSummary()
    {
        cout << "Vehicles in queue: " << vehicle_queue.size() << "\n";
        // Can't easily traverse priority_queue; optionally copy to temporary container to show top few.
        auto copyq = vehicle_queue;
        int c = 0;
        while (!copyq.empty() && c++ < 10)
        {
            Vehicle *v = copyq.top();
            copyq.pop();
            cout << "  " << v->type_name << " (" << v->reg_no << ") - priority " << v->priority
                 << " - " << v->liters_required << " L - customer " << v->cust_id << "\n";
        }
    }

    // ---- Predictive analysis ----
    double predictNextDemand() const
    {
        if (recent_demands.empty())
            return 0.0;
        double sum = 0;
        for (double d : recent_demands)
            sum += d;
        return sum / recent_demands.size();
    }

    void showPrediction() const
    {
        double pred = predictNextDemand();
        cout << "Predicted next demand (moving average of last " << recent_demands.size()
             << " purchases): " << pred << " L\n";
    }

    // Show loyalty points top N
    void showTopLoyalCustomers(int topN = 5) const
    {
        vector<pair<int, string>> vec;
        for (auto &p : loyalty_points)
        {
            vec.push_back({p.second, p.first});
        }
        sort(vec.begin(), vec.end(), greater<>());
        cout << "Top loyalty customers:\n";
        for (int i = 0; i < (int)vec.size() && i < topN; ++i)
        {
            cout << "  " << vec[i].second << " -> " << vec[i].first << " points\n";
        }
    }
    // ---- Process all vehicles ----
    void processAllVehicles()
    {
        if (vehicle_queue.empty())
        {
            cout << "No vehicles in queue.\n";
            return;
        }
        cout << "Processing all vehicles in queue...\n";
        int count = 0;
        while (!vehicle_queue.empty())
        {
            processNextVehicle();
            ++count;
        }
        cout << count << " vehicle(s) processed.\n";
    }

    // ---- Save & Load data ----
    void saveData()
{
    // ---- Save stock ----
    ofstream stock("stock.txt");
    if (stock)
    {
        stock << petrol_stock << " " << diesel_stock << "\n";
    }

    // ---- Save customers ----
    ofstream cust("customers.txt");
    for (auto &p : customer_map)
    {
        Customer *c = p.second;
        cust << c->getId() << " " << c->getName() << " "
             << c->getBalance() << " " << loyalty_points[p.first] << "\n";

        // ---- Save transactions ----
        ofstream tx("transactions_" + c->getId() + ".txt");
        if (tx)
        {
            for (const auto &entry : c->getTransactionHistory())
            {
                tx << entry << "\n";
            }
        }
    }

    cout << "Data saved successfully.\n";
}


    void loadData()
    {
        // load stock
        ifstream stock("stock.txt");
        if (stock)
            stock >> petrol_stock >> diesel_stock;

        ifstream cust("customers.txt");
        string id, name;
        double bal;
        int points;

        while (cust >> id >> name >> bal >> points)
        {
            Customer *c = new Customer(name);
            c->setId(id);
            c->setBalance(bal);
            customer_map[id] = c;
            bst.insert(c);

            cout << "Data loaded successfully.\n";
        }
    }
};

// ---------------------- UI / Menu ----------------------
void showMenu()
{
    cout << "\n===== Smart Petrol Station Menu =====\n";
    cout << "1. Create Customer\n";
    cout << "2. Deposit to Customer\n";
    cout << "3. Show Customer Details\n";
    cout << "4. Add Vehicle to Queue\n";
    cout << "5. Process Next Vehicle\n";
    cout << "6. Refill Stock\n";
    cout << "7. Show Stock\n";
    cout << "8. Undo Last Transaction (Customer)\n";
    cout << "9. Show Customers (Sorted by ID)\n";
    cout << "10. Show Queue Summary\n";
    cout << "11. Show Predictive Demand\n";
    cout << "12. Show Top Loyalty Customers\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    PetrolLane system;
    system.loadData();

    // For demo convenience, prefill some stock
    // system.refillStock(2000.0, 3000.0);

    while (true)
    {
        showMenu();
        int ch;
        if (!(cin >> ch))
        {
            cout << "Invalid input. Exiting.\n";
            break;
        }
        switch (ch)
        {
        case 1:
        {
            string name;
            cout << "Enter full name: ";
            cin >> ws;
            getline(cin, name);
            capitalize(name);
            system.createCustomer(name);
            break;
        }
        case 2:
        {
            string id;
            double amt;
            cout << "Enter customer ID: ";
            cin >> id;
            cout << "Enter amount to deposit: ";
            cin >> amt;
            system.depositToCustomer(id, amt);
            break;
        }
        case 3:
        {
            string id;
            cout << "Enter customer ID: ";
            cin >> id;
            system.showCustomerDetails(id);
            break;
        }
        case 4:
            system.addVehicleToQueue();
            break;
        case 5:
            system.processAllVehicles();
            break;
        case 6:
        {
            double p, d;
            cout << "Enter petrol liters to add: ";
            cin >> p;
            cout << "Enter diesel liters to add: ";
            cin >> d;
            system.refillStock(p, d);
            break;
        }
        case 7:
            system.showStock();
            break;
        case 8:
        {
            string id;
            cout << "Enter customer ID to undo last transaction: ";
            cin >> id;
            system.undoLastForCustomer(id);
            break;
        }
        case 9:
            system.listCustomersSorted();
            break;
        case 10:
            system.showQueueSummary();
            break;
        case 11:
            system.showPrediction();
            break;
        case 12:
            system.showTopLoyalCustomers();
            break;
        case 0:
            cout << "Saving data before exiting...\n";
            system.saveData();
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}
