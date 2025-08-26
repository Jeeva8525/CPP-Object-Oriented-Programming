#include <iostream>
using namespace std;
typedef struct binTree
{
        int data;
        struct binTree *left,*right;
}bin;
bin *createNode(int val)
{
        bin* temp = new bin;
        temp->data = val;
        temp->left = temp->right = NULL;
        return temp;
}
void insert(bin *&root,int val)
{
        if(NULL == root)
        {
                root = createNode(val);
                return;
        }
        else if(val < (root)->data)
                insert(root->left,val);
        else if(val > (root)->data)
                insert(root->right,val);
}
void search(bin *&root,int val)
{
        if(NULL == root)
        {
                cout<<"No such element is in the tree"<<endl;
                return;
        }
        if(root->data == val)
        {
                cout<<"Element found"<<endl;
                return;
        }
        else if(val < root->data)
                search(root->left,val);
        else
                search(root->right,val);
}
void printLDR(bin *root)
{
        if(root==NULL)
                return;
        printLDR(root->left);
        cout<<root->data<<" ";
        printLDR(root->right);
}
bin* findMax(bin* root)
{
        if(NULL == root)
        {
                return root;
        }
        while(root->right)
                root = root->right;
        return root;
}
int spaceWidth = 5;
void printTree(bin *root,int space)
{
        if(NULL == root)
        {
                return;
        }
        space += spaceWidth;
        printTree(root->right,space);
        for(int x=0;x<space;x++)
                cout<<" ";
        cout<<root->data<<endl;
        printTree(root->left,space);
}
int main()
{
        bin *root = NULL;
        int ch,val;
        cout<<"1 : add an element\n2 : display the tree\n3 : search for an element\n4 : find the maximum element in the tree"<<endl;

        do{
                cout<<"Enter choice: ";
                cin>>ch;
                switch(ch)
                {
                        case 1:
                                val=0;
                                cout<<"Enter the value: ";
                                cin>>val;
                                insert(root,val);
                                printLDR(root);
                                cout<<endl;
                                break;
                        case 2:
                                cout<<"The elements in the binary search tree are"<<endl;
                                printLDR(root);
                                cout<<endl<<endl;
                                printTree(root,0);
                                break;
                        case 3:
                                cout<<"Enter the element to be searched: ";
                                cin>>val;
                                search(root,val);
                                break;
                        case 4:
                                if(findMax(root)!=NULL)
                                        cout<<"The maximum element in the tree is "<<findMax(root)->data<<endl;
                                break;
                        default:
                                ch = 0;
                }
        }while(ch!=0);
}