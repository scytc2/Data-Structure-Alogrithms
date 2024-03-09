#include<iostream>
#include<queue> // STL of queue
using namespace std;

typedef struct Nodes
{
    char data;
    Nodes *left;
    Nodes *right;
}Node;



Node* GetNewNode(char data) {
    Node *newNode = new Node;
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* Insert(Node* root, char data) { 
    if (root == NULL) {
        root = GetNewNode(data); //if it is an empty tree
    }
    else if (root->data >= data) {
        root->left = Insert(root->left, data);
    }
    else {
        root->right = Insert(root->right, data);
    }
    return root;
}

void LevelOrder(Node *root){
    if (root == NULL) {
        cout << "Error: Tree is empty" << endl;
        return;
    }
    queue<Node*> Q;
    Q.push(root);
    //while there is at least one discovere node
    while(!Q.empty()) {
        Node *current = Q.front();
        cout << current->data << " ";
        if(current->left != NULL) {
            Q.push(current->left);
        }
        if(current->right != NULL) {
            Q.push(current->right);
        }
        Q.pop(); // removing the elemnt at front
    }
}

void Preorder(Node* root) {
    if (root == NULL) {
        return;
    }
    cout << root->data << " ";
    Preorder(root->left);
    Preorder(root->right); 
}

void Inorder(Node* root) {
    if (root == NULL) {
        return;
    }
    Inorder(root->left);
    cout << root->data << " ";
    Inorder(root->right); 
}

void Postorder(Node* root) {
    if (root == NULL) {
        return;
    }
    Postorder(root->left);
    Postorder(root->right);
    cout << root->data << " ";
}

void 

int main() {
    Node *root = NULL;
    root = Insert(root,'F');
    root = Insert(root,'D');
    root = Insert(root,'J');
    root = Insert(root,'B');
    root = Insert(root,'E');
    root = Insert(root,'G');
    root = Insert(root,'K');
    root = Insert(root,'A');
    root = Insert(root,'C');
    root = Insert(root,'I');

    LevelOrder(root);
    cout << endl;
    Preorder(root);
    cout << endl;
    Inorder(root);
    cout << endl;
    Postorder(root);

    return 0;
}