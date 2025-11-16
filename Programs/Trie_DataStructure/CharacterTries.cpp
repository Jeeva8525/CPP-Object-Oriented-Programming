#include <iostream>
#include <algorithm>
#define num_of_chars 26
using namespace std;
class TrieNode
{
public: 
    TrieNode *next[num_of_chars];
    bool isComplete;
    TrieNode(){
        fill(next,next+num_of_chars,nullptr);
        isComplete = false;
    }
};
class BinaryTrie
{
    private:
        TrieNode *root;
    public:
        BinaryTrie()
        {
            root = new TrieNode();
        }
        void insert(string s)
        {
            TrieNode *cur = root;
            for(char c : s)
            {
                if(cur->next[c-'a'] == nullptr) cur->next[c-'a'] = new TrieNode;
                cur = cur->next[c-'a']; 
            }
            cur->isComplete = true;
        }
        void suggestion(string s)
        {
            TrieNode *cur = root;
            for(char c : s)
            {
                if(cur->next[c-'a']==nullptr)
                {
                    cout<<"No suggestions found!"<<endl;
                    return;
                }
                cur = cur->next[c-'a'];
            }
            cout<<"Suggestions are "<<endl;
            displayAll(cur,s);
        }

        void display()
        {
            string temp = "";
            displayAll(root,temp);
        }
        void displayAll(TrieNode *cur,string temp)
        {
            if(cur == nullptr)
                return;
            if(cur->isComplete)
                cout<<temp<<endl;
            for(int x=0;x<num_of_chars;x++)
                if(cur->next[x])
                    displayAll(cur->next[x],temp+char('a'+x));
        }
};
int main()
{
    BinaryTrie t;
    int ch;
    cout<<"1 : Insert a word\n2 : search\n0 : Exit"<<endl;
    string inp;
    do
    {
        cout<<"Enter choice: ";
        cin>>ch;
        switch(ch)
        {
            case 1:
                cout<<"Enter the string to insert: ";
                cin>>inp;
                t.insert(inp);
                break;
            case 2:
                cout<<"Enter the search string: ";
                cin>>inp;
                t.suggestion(inp);
                break;
            case 0:
                cout<<"Exited";
                break;
            default:
                cout<<"Enter a valid choice"<<endl;
        }

    }while(ch!=0);
}