#include <iostream>
using namespace std;

struct node {
    int data;
    node *left, *right;
    bool color; // 1 -> Red, 0 -> Black
};

// --------------------- Helper Functions ---------------------
node* singleRotateWithLeft(node *root) {
    node *root_left = root->left;
    root->left = root_left->right;
    root_left->right = root;

    // Explicit recoloring
    root_left->color = 0; // new parent black
    root->color = 1;      // child red
    return root_left;
}

node* singleRotateWithRight(node *root) {
    node *root_right = root->right;
    root->right = root_right->left;
    root_right->left = root;

    root_right->color = 0; // new parent black
    root->color = 1;       // child red
    return root_right;
}

node* doubleRotateWithLeft(node *root) {
    root->left = singleRotateWithRight(root->left);
    return singleRotateWithLeft(root);
}

node* doubleRotateWithRight(node *root) {
    root->right = singleRotateWithLeft(root->right);
    return singleRotateWithRight(root);
}

// Flip colors when both children are red
void colorFlip(node *root) {
    root->color = 1;
    if (root->left)  root->left->color = 0;
    if (root->right) root->right->color = 0;
}

// --------------------- Insertion ---------------------
node* insertFunc(node* root, int val) {
    // Standard BST insert
    if (root == nullptr) {
        root = new node{val, nullptr, nullptr, 1}; // new node red
        return root;
    }

    if (val < root->data) {
        root->left = insertFunc(root->left, val);

        if (root->left != nullptr) {
            // Left Left case
            if (root->left->left != nullptr &&
                root->left->color == 1 &&
                root->left->left->color == 1) {
                if (root->right && root->right->color == 1)
                    colorFlip(root);
                else
                    root = singleRotateWithLeft(root);
            }

            // Left Right case
            else if (root->left->right != nullptr &&
                     root->left->color == 1 &&
                     root->left->right->color == 1) {
                if (root->right && root->right->color == 1)
                    colorFlip(root);
                else
                    root = doubleRotateWithLeft(root);
            }
        }
    }

    else if (val > root->data) {
        root->right = insertFunc(root->right, val);

        if (root->right != nullptr) {
            // Right Right case
            if (root->right->right != nullptr &&
                root->right->color == 1 &&
                root->right->right->color == 1) {
                if (root->left && root->left->color == 1)
                    colorFlip(root);
                else
                    root = singleRotateWithRight(root);
            }

            // Right Left case
            else if (root->right->left != nullptr &&
                     root->right->color == 1 &&
                     root->right->left->color == 1) {
                if (root->left && root->left->color == 1)
                    colorFlip(root);
                else
                    root = doubleRotateWithRight(root);
            }
        }
    }

    // Equal values not allowed in BST
    return root;
}

// Wrapper ensures root is always black
node* insert(node *root, int val) {
    root = insertFunc(root, val);
    root->color = 0; // root always black
    return root;
}

// --------------------- Utility: Inorder Print ---------------------
void inorder(node *root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << (root->color ? "(R) " : "(B) ");
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
int main()
{
    node *root = nullptr;
    int arr[] = {10,18,7,15,16,30,25,40,60,2,1,70};
    for(int x : arr)
        root = insert(root,x);
    cout<<"Inorder traversal : ";
    inorder(root);
    cout<<endl;
    cout<<"Pre order traversal : ";
    preorder(root);
    cout<<endl;
    cout<<"Post order traversal : ";
    postorder(root);
    cout<<endl;
}
