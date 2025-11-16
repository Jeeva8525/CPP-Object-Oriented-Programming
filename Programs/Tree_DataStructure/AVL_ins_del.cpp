#include <iostream>
using namespace std;
struct node
{
    int data;
    node *left,*right;
    int height;
};
int Height(node *root)
{
    return nullptr == root? -1 : root->height;
}
void singleRotateWithLeft(node *&root)
{
    node* k1 = root->left;
    root->left = k1->right;
    k1->right = root;
    root->height = max(Height(root->left),Height(root->right))+1;
    k1->height = max(Height(k1->left),root->height)+1;
    root = k1;
}
void singleRotateWithRight(node *&root)
{
    node* k1 = root->right;
    root->right = k1->left;
    k1->left = root;
    root->height = max(Height(root->left),Height(root->right))+1;
    k1->height = max(root->height,Height(k1->right))+1;
    root = k1;
}
void doubleRotateWithLeft(node *&root)
{
    singleRotateWithRight(root->left);
    singleRotateWithLeft(root);
}
void doubleRotateWithRight(node *&root)
{
    singleRotateWithLeft(root->right);
    singleRotateWithRight(root);
}
void insertElement(node *&root,int value)
{
    if(nullptr == root)
    {
        root = new node;
        root->data = value;
        root->left = root->right = nullptr;
        root->height = 0;
        return;
    }
    if(value < root->data)
    {
        insertElement(root->left,value);
        if(Height(root->left) - Height(root->right) == 2)
        {
            if(value < root->left->data)
                singleRotateWithLeft(root);
            else
                doubleRotateWithLeft(root);
        }
    }
    else if(value > root->data)
    {
        insertElement(root->right,value);
        if(Height(root->right) - Height(root->left) == 2)
        {
            if(value > root->right->data)
                singleRotateWithRight(root);
            else
                doubleRotateWithRight(root);
        }
    }
    else 
        cout<<"Such element already exists"<<endl;
    root->height = max(Height(root->left),Height(root->right))+1;
}
void inorder(node *root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}void preorder(node *root)
{
    if(nullptr == root)
        return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}
void postorder(node *root)
{
    if(nullptr == root)
        return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}
void printTree(node* root, int space = 0, int COUNT = 5) {
    if (!root) return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    printTree(root->right, space);

    // Print current node after space
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->data << "\n";

    // Process left child
    printTree(root->left, space);
}
void deleteElement(node *&root,int target)
{
    if(!root)
        return;
    if(target < root->data)
    {
        deleteElement(root->left,target);
    }
    else if(target > root->data)
    {
        deleteElement(root->right,target);
    }
    else if( root->left && root->right)
    {
        node *temp = root->right;
        while(temp->left)
            temp = temp->left;
        root->data = temp->data;
        deleteElement(root->right,temp->data);
    }
    else
    {
        node *temp = root;
        if(root->left == nullptr)
            root = root->right;
        else if(root->right == nullptr)
            root = root->left;
        delete temp;
    
    }

    if (!root) return;
    root->height = max(Height(root->left), Height(root->right)) + 1;
    int balance = Height(root->left) - Height(root->right);
    if (balance > 1) {
        if (Height(root->left->left) >= Height(root->left->right))
            singleRotateWithLeft(root);
        else
            doubleRotateWithLeft(root);
    }
    else if (balance < -1) {
        if (Height(root->right->right) >= Height(root->right->left))
            singleRotateWithRight(root);
        else
            doubleRotateWithRight(root);
    }
}
int main()
{
    node *head = nullptr;
    // insertElement(head,6);
    // insertElement(head,3);
    // insertElement(head,5);
    // insertElement(head,9);
    // insertElement(head,8);
    
    int temp;
    do{
        cout<<"Enter the element: ";
        cin>>temp;
        if(temp!=-999)
            insertElement(head,temp);
        printTree(head);
    }while(temp!=-999);

    /* cout<<"Pre order : ";
    preorder(head);
    cout<<endl;

    cout<<"In order : ";
    inorder(head);
    cout<<endl;

    cout<<"Post order : ";
    postorder(head);
    cout<<endl; */

    cout<<" ----------- FINAL TREE --------------"<<endl;
    printTree(head);

    do{
        cout<<"Enter the element to delete: ";
        cin>>temp;
        if(temp!=-999)
            deleteElement(head,temp);
        printTree(head);
    }while(temp!=-999);

}
