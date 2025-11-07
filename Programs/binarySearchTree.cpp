#include <iostream>
using namespace std;
struct node
{
    int data;
    node *left,*right;
};
void insertElement(node *&root,int value)
{
    if( nullptr == root)
    {
        root = new node;
        root->data = value;
        root->left = root->right = nullptr;
    }
    else if(value < root->data)
    {
        insertElement(root->left,value);
    }
    else if(value > root->data)
    {
        insertElement(root->right,value);
    }
}
void inorderTraversal(node* root)
{
    if(nullptr == root)
        return;
    inorderTraversal(root->left);
    cout<<root->data<<" ";
    inorderTraversal(root->right);
}
int main()
{
    node* head = nullptr;
    insertElement(head,3);
    insertElement(head,4);
    insertElement(head,2);
    insertElement(head,8);
    inorderTraversal(head);
}