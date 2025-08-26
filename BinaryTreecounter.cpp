#include <iostream>
using namespace std;
typedef struct binTree
{
        int data;
        struct binTree *left, *right;
} bin;
bin *createNode(int val)
{
        bin *temp = new bin;
        temp->data = val;
        temp->left = temp->right = NULL;
        return temp;
}
void insert(bin *&root, int val)
{
        if (NULL == root)
        {
                root = createNode(val);
                return;
        }
        else if (val < (root)->data)
                insert(root->left, val);
        else if (val > (root)->data)
                insert(root->right, val);
}
int countNodes(bin *root)
{
        if (NULL == root)
                return 0;
        return countNodes(root->left) + 1 + countNodes(root->right);
}
int countLeaves(bin *root)
{
        if (NULL == root)
                return 0;
        if (root->right == NULL && root->left == NULL)
        {
                return 1;
        }
        else
        {
                return countLeaves(root->left) + countLeaves(root->right);
        }
}
int countNonTerminalNodes(bin *root)
{
        if (NULL == root || (root->left == NULL && root->right == NULL))
                return 0;
        return countNonTerminalNodes(root->left) + countNonTerminalNodes(root->right) + 1;
}
void printLDR(bin *root)
{
        if (root == NULL)
                return;
        printLDR(root->left);
        cout << root->data << " ";
        printLDR(root->right);
}
int spaceWidth = 5;
void printTree(bin *root, int space)
{
        if (NULL == root)
                return;
        space += spaceWidth;
        printTree(root->right, space);
        for (int x = 0; x < space; x++)
                cout << " ";
        cout << root->data << endl;
        printTree(root->left, space);
}
int main()
{
        bin *root = NULL;
        int ch, val;
        cout << "1 : add an element\n2 : display the tree\n3 : count the number of nodes\n4 : count the number of leaf nodes\n5 : count the number of non - terminal nodes"<< endl;

        do
        {
                cout << "Enter choice: ";
                cin >> ch;
                switch (ch)
                {
                case 1:
                        val = 0;
                        cout << "Enter the value: ";
                        cin >> val;
                        insert(root, val);
                        printLDR(root);
                        cout << endl;
                        break;
                case 2:
                        cout << "The elements in the binary search tree are" << endl;
                        printLDR(root);
                        cout<<endl;
                        printTree(root, 0);
                        break;
                        case 3:
                        cout << "The number of nodes in the binary search tree is " << countNodes(root) << endl;
                        break;
                case 4:
                        cout << "The number of leaves in the binary search tree is " << countLeaves(root) << endl;
                        break;
                case 5:
                        cout << "The number of non - terminal nodes in the binary search tree is " << countNonTerminalNodes(root) << endl;
                        break;
                default:
                        ch = 0;
                }
        } while (ch != 0);
}