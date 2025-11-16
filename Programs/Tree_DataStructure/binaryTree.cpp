//Implements the full functionality of a Binary Search Tree insertion, deletion, counting (total nodes, leaves, Non terminal), search, max_elt 
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
bin* getSuccessor(bin *root)
{
        root = root->right;
        while(root->left)
                root = root->left;
        return root;
}
void deleteElt(bin *&root,int val)
{
        if(NULL == root)
        {
                cout<<"There is no such element to delete"<<endl;
                return;
        }
        else if(val<root->data)
                deleteElt(root->left,val);
        else if(val>root->data)
                deleteElt(root->right,val);
        else if(root->left && root->right)
        {
                bin *temp = getSuccessor(root);
                root->data = temp->data;
                deleteElt(root->right,temp->data);
        }
        else
        {
                bin *temp = root;
                if(root->left==NULL)
                        root = root->right;
                else if(root->right == NULL)
                        root = root->left;
                free(temp);
        }
}
int countNodes(bin *root)
{
        if(NULL == root)
                return 0;
        return countNodes(root->left) + 1 + countNodes(root->right);
}
int countLeaves(bin *root)
{
        if(NULL == root)
                return 0;
        if(root->right == NULL && root->left == NULL)
        {
                return 1;
        }
        else
        {
                return countLeaves(root->left)+countLeaves(root->right);
        }
}
int countNonTerminalNodes(bin *root)
{
        if(NULL == root || (root->left==NULL && root->right==NULL))
                return 0;
        return countNonTerminalNodes(root->left)+countNonTerminalNodes(root->right)+1;
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
        cout<<"1 : add an element\n2 : delete an element\n3 : display the tree\n4 : search for an element\n5 : count the number of nodes\n6 : count the number of leaf nodes\n7 : count the number of non - terminal nodes\n8 : find the maximum element in the tree"<<endl;

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
                                val=0;
                                cout<<"Enter the element to be deleted: ";
                                cin>>val;
                                deleteElt(root,val);
                                printLDR(root);
                                cout<<endl;
                                break;
                        case 3:
                                cout<<"The elements in the binary search tree are"<<endl;
                                printLDR(root);
                                break;\
                        case 4:
                                cout<<"Enter the element to be searched: ";
                                cin>>val;
                                search(root,val);
                                break;
                        case 5:
                                cout<<"The number of nodes in the binary search tree is "<<countNodes(root)<<endl;
                                break;
                        case 6:
                                cout<<"The number of leaves in the binary search tree is "<<countLeaves(root)<<endl;
                                break;
                        case 7:
                                cout<<"The number of non - terminal nodes in the binary search tree is "<<countNonTerminalNodes(root)<<endl;
                                break;
                        case 8:
                                if(findMax(root)!=NULL)
                                {
                                        cout<<"The maximum element in the tree is "<<findMax(root)->data<<endl;
                                }
                                break;
                        default:
                                ch = 0;
                }
        }while(ch!=0);
        printTree(root,0);
}