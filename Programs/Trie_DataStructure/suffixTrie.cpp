#include <iostream>
#include <unordered_map>
using namespace std;
struct node 
{
    unordered_map<char,node*> next;
    bool isComplete;
    node()
    {
        isComplete = false;
    }
};
class SuffixTrie
{
    private: 
        node* root = new node;
    public:
        SuffixTrie()
        {

        }
        SuffixTrie(string s)
        {
            buildSuffixTrie(s);
        }
        void buildSuffixTrie(string s)
        {
            for(int x=0;x<s.length();x++)
            {
                insertString(s.substr(x));
            }
        }
        void insertString(string s)
        {
            node *cur = root;
            for(char c : s)
            {
                if(cur->next.find(c) == cur->next.end())
                {
                    cur->next[c] = new node; 
                }
                cur = cur->next[c];
            }
            cur->isComplete = true;
        }
        void display()
        {
            node *cur = root;
            string word = "";
            displayAll(root,word);
        }
        void displayAll(node *cur,string word)
        {
            if(nullptr == cur)
                return;

            if(cur->isComplete)
                cout<<word+" ("<<word.length()<<")"<<endl;
            for(auto key : cur->next)
            {
                displayAll(cur->next[key.first],word+(key.first));    
                // displayAll(key.second,word+(key.first));    
            }
            
        }
        void findPattern(string s)
        {
            node *cur = root;
            for(char c : s)
            {
                if(cur->next.find(c)==cur->next.end())
                {
                    cout<<"No such pattern in the trie"<<endl;
                    return;
                }
                cur = cur->next[c];
            }
            cout<<"Pattern found"<<endl;
        }

};
int main()
{
    SuffixTrie s("malayalam");
    cout<<"Suffixes of the word are " <<endl;
    s.display();
    s.findPattern("ala");
    s.findPattern("alam");
    s.findPattern("aly");
    s.findPattern("laym");
}