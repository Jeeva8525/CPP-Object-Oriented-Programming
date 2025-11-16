#include <iostream>
using namespace std;
struct node{
    int data;
    node *left,*right;
    int height;
};
int Height(node* root)
{
    return nullptr == root?-1:root->height;
}
node* singleRotateWithLeft(node* root){
    node* leftOfRoot = root->left;
    root->left = leftOfRoot->right;
    leftOfRoot->right = root;

    root->height = max(Height(root->left),Height(root->right)) + 1;
    leftOfRoot->height = max(Height(leftOfRoot->left),root->height) + 1;
    return leftOfRoot;
}
node* singleRotateWithRight(node* root){
    node* rightOfRoot = root->right;
    root->right = rightOfRoot->left;
    rightOfRoot->left = root;

    root->height = max(Height(root->left),Height(root->right)) + 1;
    rightOfRoot->height = max(root->height,Height(rightOfRoot->right)) + 1;
    return rightOfRoot;
}
node* doubleRotateWithLeft(node *root)
{
    root->left = singleRotateWithRight(root->left);
    return singleRotateWithLeft(root);
}
node* doubleRotateWithRight(node *root)
{
    root->right = singleRotateWithLeft(root->right);
    return singleRotateWithRight(root);
}
node* insertAVL(node* root,int val){
    if(nullptr == root){
        root = new node;
        root->data = val;
        root->left = root->right = nullptr;
        root->height = 0;
    }
    else if(val < root->data)
    {
        root->left = insertAVL(root->left,val);
        if(Height(root->left) - Height(root->right) == 2)
        {
            if(val < root->left->data)
            {
                root = singleRotateWithLeft(root);
            }
            else if(val > root->left->data)
            {
                root = doubleRotateWithLeft(root);
            }
        }
    }
    else if(val > root->data)
    {
        root->right = insertAVL(root->right,val);
        if(Height(root->right) - Height(root->left) == 2)
        {
            if(val > root->right->data)
            {
                root = singleRotateWithRight(root);
            }
            else if(val < root->right->data)
            {
                root = doubleRotateWithRight(root);
            }
        }
    }
    root->height = max(Height(root->left),Height(root->right)) + 1;
    return root;
    
}
void inorder(node* tree)
{
    if(nullptr == tree)
    {
        return;
    }
    inorder(tree->left);
    cout<<tree->data<<" ";
    inorder(tree->right);
}
void preorder(node* tree)
{
    if(nullptr == tree)
    {
        return;
    }
    cout<<tree->data<<" ";
    preorder(tree->left);
    preorder(tree->right);
}
void postorder(node* tree)
{
    if(nullptr == tree)
    {
        return;
    }
    postorder(tree->left);
    postorder(tree->right);
    cout<<tree->data<<" ";
}
int main()
{
    node* head = nullptr;

    int arr[] = { 50, 20, 70, 10, 25, 40, 5};
    for(int x : arr)
    {
        head = insertAVL(head,x);
    }
    
    inorder(head);
    cout<<endl;
    preorder(head);
    cout<<endl;
    postorder(head);
    cout<<endl;
}