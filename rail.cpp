#include<iostream>
#include<cmath>
#include<iomanip>
#include<vector>
using namespace std;
#define N 25
#define S 20
#define T 10
class ticket;
class Date;
class Time {
private:
    int hour;
    int minute;
    int p;

public:
    Time(int h = 0, int m = 0) {
        hour = h;
        minute = m;
        p = 0; 
    }

    void normalize() 
    {
        int totalMinutes = hour * 60 + minute;
        totalMinutes %= 1440; 
        hour = totalMinutes / 60;
        minute = totalMinutes % 60;
    }
    bool isInvalid()
    {
    return hour == -1 && minute == -1;
    }

    Time operator+(int m) 
    {
        Time result = *this;
        int start = result.hour * 60 + result.minute;
        int end = start + m;
        result.p += (end / 1440) - (start / 1440);
        result.minute += m;
        result.normalize();
        return result;
    }

    void disp() {
        if(hour==-1 && minute==-1)
         {     cout<<"-----";
               return;
         }
        cout << setfill('0') << setw(2) << hour << ":"
             << setfill('0') << setw(2) << minute;
        
    }

    void resetp() 
    { 
        p = 0;
    }

    int getp() 
    {
        return p;
    }
    friend bool good(const Time &, const Date &, const Time &, const Date &);
};
class Date {
private:
    int day, month, year;

    bool leap(int y)
    {
        return (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
    }

    int check(int m, int y)  
    {
        if (m == 2) return leap(y) ? 29 : 28;
        if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
        return 31;
    }

public:
    Date(int d = 1, int m = 1, int y = 2000) 
    {
        day = d;
        month = m;
        year = y;
    }

    Date operator+(int days) 
    {
        Date result = *this;
        result.day += days;

        while (result.day > result.check(result.month, result.year)) 
        {
            result.day -= result.check(result.month, result.year);
            
        
            result.month++;
            if (result.month > 12) 
            {
                result.month = 1;
                result.year++;
            }
        }
        return result;
    }

    void disp() 
    {
        cout << setfill('0') << setw(2) << day << "/"
             << setfill('0') << setw(2) << month << "/"
             << year ;
            
    }
    friend bool good(const Time &, const Date &, const Time &, const Date &);
    friend int tdays(const Date &);
};
int tdays(const Date &d) 
{
        int days = 0;
        for (int y = 2025; y < d.year; ++y)
            days += (Date(1,1,y).leap(y) ? 366 : 365);

        for (int m = 1; m < d.month; ++m)
            days+=Date(1,m,d.year).check(m, d.year);

        days += d.day;
        days--;
        return days;
};
bool good(const Time &t1, const Date &d1, const Time &t2, const Date &d2)
{
    

    int total1 =tdays(d1)*1440+t1.hour * 60+t1.minute;
    int total2 =tdays(d2)*1440+t2.hour * 60+t2.minute;

    return (abs(total1 - total2)<=30);
}

class train;
class station
{   
    friend class train;
    
    int s_id;  //station id
    string sname; //station name
    int x,y;    //co-ordinates in xy-plane
    int max_plat; //total no. of platforms
    int in;     //no. of trains scheduled to this station,used as index for entering new trains
    
    int trains_id_arr[N]; //id of all the trains in the stations
    string trains[N];    //name of all the trains in the station
    int plat[N];         //platform of all trains ""
    Time s_arr[N];       //arrival time  ""
    Time s_dep[N];       //depature time  ""
    Date s_date[N];      //date  ""
    
    
    public:
    station(int i=0,string w="Null",int a=0,int b=0,int c=0)
    {   
        s_id=i;
        sname=w;
        x=a;
        y=b;
        max_plat=c;
        in=0;
        
        for(int j=0;j<N;j++)
               { trains_id_arr[j]=-1;
                plat[j]=1;
                }
    }
    int getid()
    {
        return s_id;
    }
    string getn()
    {
        return sname;
    }
    int getx()
    {
        return x;
    }
    int gety()
    {
        return y;
    }
    void removetrain(int index) 
    {
    for (int i=index;i<N-1; i++) 
    { 
      if(trains_id_arr[i]==-1)
         {   in--;
             return;
         }
        trains_id_arr[i] = trains_id_arr[i + 1];
        trains[i] = trains[i + 1];
        plat[i] = plat[i + 1];
        s_arr[i] = s_arr[i + 1];
        s_dep[i] = s_dep[i + 1];
        s_date[i] = s_date[i + 1];
        
    }
    }
    
    friend int index_station_id(station *x,int k)
    {
        for(int i=0;i<S;i++)
           if(x[i].s_id==k)
               return i;
        return -1;
    }
    
    friend void trains_Disp_(station *x)
    {   
        int i;
        cout<<"Enter Station ID: ";
        cin>>i;
        int j=index_station_id(x,i);
        x[j].trains_Disp();
    }

    void trains_Disp()
       
    { 
        cout<<setfill(' ')<<sname<<endl;
        for(int i=0;i<N;i++)
        
          {  if(trains_id_arr[i]==0)
                  continue;
            if(trains_id_arr[i]==-1)
            break;
             
               {cout<<trains_id_arr[i]<<"\t"<<setw(11)<<setfill(' ')<<trains[i]<<"\t";
               cout<<plat[i]<<"\t";
               s_arr[i].disp();
               cout<<"\t";
               s_dep[i].disp();
               cout<<"\t";
               s_date[i].disp();
               cout<<endl;
               }
          }   
    }
    
    friend void admin(train *t,station *s);
    
    
};
class seat
{protected:
    int sl,s2,ac3,ac2,ac1;
    float sl_cost,s2_cost,ac3_cost,ac2_cost,ac1_cost;
    public:
    seat(int sl,int _2s,int _3ac,int _2ac,int _1ac)
    {
        this->sl=sl;
        s2=_2s;
        ac3=_3ac;
        ac2=_2ac;
        ac1=_1ac;
        sl_cost=50;s2_cost=20;ac3_cost=90;ac2_cost=130;ac1_cost=170;
    }
    void normal()
    {
        sl_cost=50;s2_cost=20;ac3_cost=90;ac2_cost=130;ac1_cost=170;
    }
    void updatecost(float d)
    {
        sl_cost=sl_cost*d/10;
        s2_cost=s2_cost*d/10;
        ac3_cost=ac3_cost*d/10;
        ac2_cost=ac2_cost*d/10;
        ac1_cost=ac1_cost*d/10;
    }
    void showsseat()
    {
        cout<<"TYPE     AVAILABLE   COST"<<endl;
        cout<<"            SEATS         "<<endl;
        cout<<"sleeper\t\t"<<sl<<"\t\t\t"<<sl_cost<<endl;
        cout<<"seater \t\t"<<s2<<"\t\t\t"<<s2_cost<<endl;
        cout<<"3-AC  \t \t"<<ac3<<"\t\t\t"<<ac3_cost<<endl;
        cout<<"2-AC  \t \t"<<ac2<<"\t\t\t"<<ac2_cost<<endl;
        cout<<"1-AC  \t \t"<<ac1<<"\t\t\t"<<ac1_cost<<endl;
    }
    friend float calculate(train &tr,seat *se);
    friend void cancellation(train curr,ticket tic);
};
class train
{
    int t_id;   
    string tname;
    
    int speed;
    string start;  //starting station name
    string end;    //ending station name
    
    int s_id_arr[N];   //array of id of stations the train is going
    string stats[N];   //name of stations the train goes
    int plat[N];       //platform ""
    Time t_arr[N];     //arrival time ""
    Time t_dep[N];     //departure time ""
    Date t_date[N];     //date ""
    
   
    
    public:
    friend float calculate(train &tr,seat *se);
    friend void cancellation(train curr,ticket tic);
    seat *seats;
    int get_t_id()
    {
        return t_id;
    }
     train(int x,string y,int sl,int s2,int ac3,int ac2,int ac1,int z,string a,string b)
    {
        t_id=x;
        tname=y;
        seats=new seat(sl,s2,ac3,ac2,ac1);
        speed=z;
        start=a;
        end=b;
        
        for(int i=0;i<N;i++)
             { s_id_arr[i]=-1;
               plat[i]=1;
             }
    }
    train()
    {
        
    }
    
    friend void stats_Disp_(train *x)
    {   
        int i;
        cout<<"Enter Train ID: ";
        cin>>i;
        int j=index_train_id(x,i);
        x[j].stats_Disp();
    }
    void stats_Disp()
    {   cout<<setfill(' ')<<tname<<endl;
        
        for(int i=0;i<N;i++)
        
        {   if(s_id_arr[i]==0)
                      continue;
            if(s_id_arr[i]==-1)
                       break;
           
              {  cout<<s_id_arr[i]<<"\t"<<setfill(' ')<<stats[i]<<"\t";
                 cout<<plat[i]<<"\t";
                t_arr[i].disp();
                cout<<"\t";
                t_dep[i].disp();
                cout<<"\t";
                t_date[i].disp();
                cout<<endl;
              }
               
               
          }
        
    }
               
      
   
    
    int plat_assign(station *z,int n,Time t1,Date d1)
    {
        vector<int> t;
        t.push_back(-1);
        for(int i=0;i<N;i++)
         {  
             if(z[n].trains_id_arr[i]==-1)
                 break;
             if(!z[n].s_arr[i].isInvalid())  
               {  if(good(t1,d1,z[n].s_arr[i],z[n].s_date[i]))
                     t.push_back(z[n].plat[i]);
               }
             
             else
              { 
                if(good(t1,d1,z[n].s_dep[i],z[n].s_date[i]))
                      t.push_back(z[n].plat[i]);
              }
          }
        for(int j=1;j<=z[n].max_plat+1;j++)
        {   
             int flag=0;
             for(int k:t)
             
               {  
                  if(k==j)
                  { flag++;
                    break;
                  }
               }
             if(flag==0)
             {  
                if(j==z[n].max_plat+1)
                    return -1;
                return j;
             }
        
         
        }
        return 1;
                     
                    
               
    }
    
    station s_name(station *z,string n)
    {
        station t(0,"Null");
        for (int i = 0; i < S; i++)
            if (z[i].sname == n)
                return z[i];
        return t;
    }
    int findi(station arr[],station t) 
    {
    for (int i = 0;i<S; i++) 
    {
        if (arr[i].sname == t.sname) 
        { 
            return i;  
        }
    }
    return -1;  
    }
    friend int index_train_id(train *x,int k)
    {
        for(int i=0;i<T;i++)
           if(x[i].t_id==k)
               return i;
        return -1;
    }
    int notfound(int element, int size, int arr[])
    {
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == element)
            return 0; 
    }
    return 1; 
    }
    int is_name(station *z,string n)
    {
       
        for (int i = 0; i < S; i++)
            if (z[i].sname == n)
                return i;
        return -1;
    }
    float dist(station &s1, station &s2)
    {
        return sqrt(pow(s2.x - s1.x, 2) + pow(s2.y - s1.y, 2));
    }
    friend void map_(train *x,station *y)
    {   
        int i,a,b,c,d,e;
        
        cout<<"Enter Train ID: ";
        cin>>i;
        cout<<"Enter Departure Time (hh:mm): ";
        scanf("%d:%d",&a,&b);
        Time t(a,b);
        cout<<"Enter Date (dd/mm/yyyy): ";
        scanf("%d/%d/%d",&c,&d,&e);
        Date f(c,d,e);
        int j=index_train_id(x,i);
        x[j].map(y,t,f);
    }
    
    void map(station *z, Time x ,Date y1)
    {  
       if(s_id_arr[0]!=-1)
            return;
       int index=0,q=0;
       int o=1;
       
       int arr[S];
       stats[0]=start;
        
       t_arr[0]=Time(-1,-1);
       t_dep[0]=x;
       t_date[0]=y1;
       
       station temp=s_name(z,start);
       int u1=is_name(z,start);
       s_id_arr[0]=z[u1].s_id;
       plat[0]=plat_assign(z,u1,x,y1);
       if(plat[0]==-1)
          {  
              demap(z);
              return;
          }
       
       z[u1].trains_id_arr[z[u1].in]=t_id;
       z[u1].trains[z[u1].in]=tname;
       
       z[u1].s_arr[z[u1].in]=Time(-1,-1);
       z[u1].s_dep[z[u1].in]=x;
       z[u1].s_date[z[u1].in]=y1;
       z[u1].plat[z[u1].in]=plat[0];
       z[u1].in++;
       
      
           
       int y=findi(z,temp);
       arr[index++]=y;
       
        while(1)
        { int min=1000000;
          bool df=false;
          station e=s_name(z,start);
          for(int i=0;i<S;i++)
          {
            if(min>dist(temp,z[i]) && notfound(i,index,arr))
                 { 
                     min=dist(temp,z[i]);
                     q=i;
                 }
           }
           arr[index++]=q;
           station r=s_name(z,z[q].sname);
           stats[o]=z[q].sname;
           s_id_arr[o]=z[q].s_id;
           
           int tt = min*60/speed; 
           t_arr[o]=t_dep[o-1]+tt;
            
           if(t_arr[o].getp()!=0)
            {
                  y1=y1+t_arr[o].getp();
                  t_arr[o].resetp();
                  
            }
           t_dep[o]=t_arr[o]+3;
           t_date[o]=y1;
           plat[o]=plat_assign(z,q,t_arr[o],t_date[o]);
           if(plat[o]==-1)
               {  
                  demap(z);
                  return;
               }
                 
           
           int u=is_name(z,stats[o]);
           
           z[u].trains[z[u].in]=tname;
           z[u].s_arr[z[u].in]=t_arr[o];
           z[u].s_dep[z[u].in]=t_dep[o];
           z[u].s_date[z[u].in]=t_date[o];
           z[u].trains_id_arr[z[u].in]=t_id;
           z[u].plat[z[u].in]=plat[o];
           z[u].in++;
           
          
           
           o++;
           
           if(r.sname==end)
           { 
               s_id_arr[o]=-1;
               t_dep[o-1]=Time(-1,-1);
               z[u].s_dep[z[u].in-1]=Time(-1,-1);
               z[u].trains_id_arr[z[u].in]=-1;
               return;
           }
           temp=z[q];
           }
           
           
           
    }
    friend void demap_(train *x,station *y)
    {   
        int i;
        cout<<"Enter Train ID: ";
        cin>>i;
        int j=index_train_id(x,i);
        x[j].demap(y);
        
        
    }
    void demap(station *z)
    {
        s_id_arr[0]=-1;
        for(int i=0;i<S;i++)
            for(int j=0;j<N;j++)
            {
              if(z[i].trains_id_arr[j]==-1)
                       break;
              if(z[i].trains_id_arr[j]==t_id)
                  z[i].removetrain(j);
                       
                  
                 
            }
    }
    friend void admin(train *t,station *s);
    
};
void admin(train *t,station *s)
{
   
    int ch;
    cout << "\n===== Menu =====\n";
    cout << "1. Schedule Train\n";
    cout << "2. Cancel Train\n";
    cout << "3. View Train Schedule\n";
    cout << "4. View Station Schedule\n";
    cout << "-1. Exit\n";
    do {
        
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) 
        {
            case 1:
                map_(t,s);
                break;
            case 2:
                demap_(t,s);
                break;
            case 3:
                stats_Disp_(t);
                break;
            case 4:
                trains_Disp_(s);
                break;
            case -1:
                cout << "Exiting menu...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (ch!=-1);
}
station s[S]=
    {
        station(201, "Station 01", 15, 24, 2),
        station(202, "Station 02", 89, 12, 2),
        station(203, "Station 03", 33, 76, 4),
        station(204, "Station 04", 120, 35, 5),
        station(205, "Station 05", 65, 49, 2),
        station(206, "Station 06", 174, 60, 3),
        station(207, "Station 07", 10, 90, 4),
        station(208, "Station 08", 141, 15, 2),
        station(209, "Station 09", 87, 99, 3),
        station(210, "Station 10", 55, 32, 2),
        station(211, "Station 11", 180, 85, 4),
        station(212, "Station 12", 24, 17, 3),
        station(213, "Station 13", 99, 66, 5),
        station(214, "Station 14", 43, 21, 2),
        station(215, "Station 15", 136, 70, 3),
        station(216, "Station 16", 77, 38, 4),
        station(217, "Station 17", 158, 25, 2),
        station(218, "Station 18", 110, 81, 1),
        station(219, "Station 19", 48, 50, 3),
        station(220, "Station 20", 199, 97, 4)

    };
train t[T]=
    {
        train(101,"Express A",200,170,80,50,25,90,s[0].getn(),s[10].getn()),
        train(102,"Express B",250,200,100,60,20,100,s[0].getn(),s[6].getn()),
        train(103,"Superfast A",300,200,70,50,20,110,s[0].getn(),s[2].getn()),
        train(104,"Local A",100,250,0,0,0,60,s[3].getn(),s[14].getn()),
        train(105,"Local B",120,300,0,0,0,65,s[4].getn(),s[18].getn()),
        train(106,"Intercity A",180,130,100,80,50,95,s[5].getn(),s[17].getn()),
        train(107,"Superfast B",220,200,150,100,70,105,s[6].getn(),s[16].getn()),
        train(108,"Express C",230,200,100,50,50,90,s[7].getn(),s[19].getn()),
        train(109,"Local C",110,200,0,0,0,55,s[8].getn(),s[13].getn()),
        train(110,"Express D",240,200,130,100,40,100,s[0].getn(),s[18].getn())
    };
class ticket:public train,public station
{   protected:
    long long id;
    int fromid;
    int toid;
    float distance;
    seat *se;
    train tr;
    station st;
    public:
    ticket()
    {
        id=0;
    }
    int gettrain()
    {
        return tr.get_t_id();
    }
    long long getid()
    {   srand(time(NULL));
        id=rand();
        return id;
    }
    void calcdist(station s[])
    {   int fromx=0,fromy=0,tox=0,toy;
        for(int i=0;i<S;i++)
        {
            if(fromid==s[i].getid())
            {
                fromx=s[i].getx();
                fromy=s[i].gety();
                st=s[i];
            }
            if(toid==s[i].getid())
            {
                tox=s[i].getx();
                toy=s[i].gety();
            }
            if(fromx!=0 && tox!=0)
            break;
        }
        distance=sqrt((fromx-tox)*(fromx-tox)+(fromy-toy)*(fromy-toy));
    }
    seat* selectseat()
    {   cout<<"enter seats required"<<endl;
        int sl,s2,ac3,ac2,ac1;
        cout<<"enter number of sleeper: ";
        cin>>sl;
        cout<<"enter number of seater: ";
        cin>>s2;
        cout<<"enter number of 3ac: ";
        cin>>ac3;
         cout<<"enter number of 2ac: ";
        cin>>ac2;
         cout<<"enter number of 1ac: ";
        cin>>ac1;
        seat*sea=new seat(sl,s2,ac3,ac2,ac1);
        return sea;

    }
    friend float calculate(train &tr,seat *se)
    {
        float tot=0;
        tot+=tr.seats->sl_cost*se->sl;
        tot+=tr.seats->s2_cost*se->s2;
        tot+=tr.seats->ac3_cost*se->ac3;
        tot+=tr.seats->ac2_cost*se->ac2;
        tot+=tr.seats->ac1_cost*se->ac1;
        tr.seats->sl-=se->sl;
        tr.seats->s2-=se->s2;
        tr.seats->ac3-=se->ac3;
        tr.seats->ac2-=se->ac2;
        tr.seats->ac1-=se->ac1;
        return tot;
    }
    friend void cancellation(train curr,ticket tic)
    {
        for(int i=0;i<T;i++)
        {
            if(curr.get_t_id()==t[i].get_t_id())
            {
                t[i].seats->sl+=tic.se->sl;
                t[i].seats->s2+=tic.se->s2;
                t[i].seats->ac3+=tic.se->ac3;
                t[i].seats->ac2+=tic.se->ac2;
                t[i].seats->ac1+=tic.se->ac1;
            }
        }
    }
    void book()
    {
        cout<<"enter from station id :";
        cin>>fromid;
        cout<<"enter to station id :";
        cin>>toid;
        calcdist(s);
        st.trains_Disp();
        cout<<"Enter TRain id ";
        cin>>id;
        for(int i=0;i<T;i++)
        if(id==t[i].get_t_id())
        {
            tr=t[i];
        break;
        }
        else
        {
            cout<<"Invalid train id"<<endl;
            goto x;
            
        }
        tr.seats->updatecost(distance);
        tr.seats->showsseat();
        se=selectseat();
        cout<<"Total cost= "<<calculate(tr,se);
        for(int i=0;i<T;i++)
        if(tr.get_t_id()==t[i].get_t_id())
        {   tr.seats->normal();
            t[i]=tr;
            
            break;
        }
        
        x:
    }
};
ticket ticketlist[N];
void booking()
{ int i=0;
    ticket *tic;
    int ch=1;
    while(ch==1 ||ch==2)
    {
        cout<<"Enter your choice:\n1.Book ticket\n2.cancel  ticket\n3.Exit\n  ";
    cin>>ch;
    switch(ch)
    {   case 1:
        tic=new ticket;
        tic->book();
        cout<<"\n...........Redirecting  to payment............."<<endl;
        cout<<"ticket booked successfullly ;) \n";
        cout<<"Ticket id : "<<tic->getid()<<endl;
        ticketlist[i++]=*(tic);
        break;
        case 2:
        long long cancelid;
        cout<<"Enter your ticket id to cancel : ";
        cin>>cancelid;
        for(int i=0;i<N;i++)
        {
            if(cancelid==ticketlist[i].getid())
            {   
                for(int j=0;j<N;j++)
                {
                    if(t[j].get_t_id()==ticketlist[i].gettrain())
                    cancellation(t[j],ticketlist[i]);
                }
                for(int j=i;j<N-i-1;j++)
                ticketlist[j]=ticketlist[j+1];
                cout<<"Ticket cancelled successfully\n";
                break;
            }
            if(ticketlist[i].getid()==0)
            {
                cout<<"ticket not found"<<endl;
                break;
            }
            
            break;
        }
        break;
        default:
        cout<<"Exiting............"<<endl;
        break;
    }  
    }
    
}

int main()
{
    
    
    admin(t,s);
   booking();
    return 0;
}
    
