#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    string word;
    string meaning;
    struct Node *left;
    struct Node *right;
    int height;
};

//function to find height of any node
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

//function to create a new node
Node *newNode(string str, string m)
{
    Node *node = new Node();
    node->word = str;
    node->meaning = m;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *temp = x->right;

    // Perform rotation
    x->right = y;
    y->left = temp;

    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;

    // Return new root
    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *temp = y->left;

    // Perform rotation
    y->left = x;
    x->right = temp;

    // Update heights
    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node *insert(Node *node, string str, string m)
{
    if (node == NULL)
        return (newNode(str, m));

    //comparing the new word with the word at particular node
    int res = str.compare(node->word);

    //If it is lexicographically lesser than go through left subtree else right subtree
    if (res < 0)
        node->left = insert(node->left, str, m);
    else if (res > 0)
        node->right = insert(node->right, str, m);
    else
    {
        cout << "Duplicate entry\n";
        return node;
    }

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && str.compare(node->left->word) < 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && str.compare(node->right->word) > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && str.compare(node->left->word) > 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && str.compare(node->right->word) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

Node *minValueNode(Node *node)
{
    Node *current = node;

    /*finding inorder successor */
    while (current->left != NULL)
        current = current->left;

    return current;
}

Node *deleteNode(Node *root, string str)
{
    if (root == NULL)
    {
        cout << "The dictionary is empty or the word is not found in dictionary\n";
        return root;
    }

    // If the key to be deleted is smaller than the root's key, then it lies in left subtree
    if (str.compare(root->word) < 0)
        root->left = deleteNode(root->left, str);

    // If the key to be deleted is greater than the root's key, then it lies in right subtree
    else if (str.compare(root->word) > 0)
        root->right = deleteNode(root->right, str);

    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            cout << "The word is deleted successfully\n";
            free(temp);
        }
        else
        {
            //inorder successor
            Node *temp = minValueNode(root->right);
            root->word = temp->word;
            root->meaning=temp->meaning;

            // Delete the inorder successor
            root->right = deleteNode(root->right,
                                     temp->word);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left),
                           height(root->right));

    // To check whether this node became unbalanced
    int balance = getBalance(root);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // Left Left Case
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void inOrder(Node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        cout << root->word << "-\t";
        cout << root->meaning << "\n";
        inOrder(root->right);
    }
}

void findele(Node *root, string tofind)
{
    if (root == NULL)
    {
        cout << "Dictionary is empty or word is not in dictionary\n";
        return;
    }
    if (tofind.compare(root->word) < 0)
    {
        findele(root->left, tofind);
    }
    else if (tofind.compare(root->word) > 0)
    {
        findele(root->right, tofind);
    }
    else
    {
        cout << root->word << "-\t" << root->meaning << "\n";
    }
    return;
}

int main()
{
    Node *root = NULL;
    int ch;
    string toadd;
    string men;
    string todelete;
    string tofind;
    cout << "******* Dictionary based on AVL Tree *******\n";
    do
    {
        cout << "\nEnter 1 to insert a word\nEnter 2 to delete a word\nEnter 3 to find a word\nEnter 4 to print dictionary words\nEnter 5 to know AVL tree height\nEnter 0 to exit\n";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Enter word to be entered\n";
            cin >> toadd;
            cout << "Enter its meaning\n";
            cin >> men;
            root = insert(root, toadd, men);
            break;
        case 2:
            cout << "Enter word to be deleted\n";
            cin >> todelete;
            root = deleteNode(root, todelete);
            break;
        case 3:
            cout << "Enter word to find\n";
            cin >> tofind;
            findele(root, tofind);
            break;
        case 4:
            if (root == NULL)
            {
                cout << "The dictionary is empty\n";
                break;
            }
            inOrder(root);
            cout << "\n";
            break;
        case 5:
            if (root == NULL)
            {
                cout << "Dictionary is empty\n";
                break;
            }
            cout << "The height of AVL tree is " << root->height << "\n";
            break;
        case 0:
            exit(0);
        }

    } while (1);
    return 0;
}

/*
******* Dictionary based on AVL Tree *******

Enter 1 to insert a word
Enter 2 to delete a word
Enter 3 to find a word
Enter 4 to print dictionary words
Enter 5 to know AVL tree height
Enter 0 to exit
1
Enter word to be entered
zibra
Enter its meaning
animal

Enter 1 to insert a word
Enter 2 to delete a word
Enter 3 to find a word
Enter 4 to print dictionary words
Enter 5 to know AVL tree height
Enter 0 to exit
1
Enter word to be entered
magic
Enter its meaning
wonder

Enter 1 to insert a word
Enter 2 to delete a word
Enter 3 to find a word
Enter 4 to print dictionary words
Enter 5 to know AVL tree height
Enter 0 to exit
1
Enter word to be entered
luck
Enter its meaning
favour

Enter 1 to insert a word
Enter 2 to delete a word
Enter 3 to find a word
Enter 4 to print dictionary words
Enter 5 to know AVL tree height
Enter 0 to exit
4
luck-   favour
magic-  wonder
zibra-  animal


Enter 1 to insert a word
Enter 2 to delete a word
Enter 3 to find a word
Enter 4 to print dictionary words
Enter 5 to know AVL tree height
Enter 0 to exit
5
The height of AVL tree is 2      //If not avl then height would be 3

Enter 1 to insert a word
Enter 2 to delete a word
Enter 3 to find a word
Enter 4 to print dictionary words
Enter 5 to know AVL tree height
Enter 0 to exit
0
*/
