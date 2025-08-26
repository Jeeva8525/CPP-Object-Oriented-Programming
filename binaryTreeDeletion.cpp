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
void printLDR(bin *root)
{
        if(root==NULL)
                return;
        printLDR(root->left);
        cout<<root->data<<" ";
        printLDR(root->right);
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
        cout<<"1 : add an element\n2 : delete an element\n3 : display the tree\n"<<endl;

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
                                cout<<endl<<endl;
                                printTree(root,0);
                                break;
                        default:
                                ch = 0;
                }
        }while(ch!=0);
}