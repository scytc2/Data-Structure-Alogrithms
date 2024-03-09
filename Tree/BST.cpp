#include<iostream>
#include <algorithm>
using namespace std;

typedef struct BstNodes
{
    int data;
    BstNodes* left;
    BstNodes* right;
}BstNode;

BstNode* GetNewNode(int data) {
    BstNode* newNode = new BstNode;
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BstNode* Insert(BstNode* rootPtr, int data) { 
    if (rootPtr == NULL) {
        rootPtr = GetNewNode(data); //if it is an empty tree
    }
    else if (rootPtr->data >= data) {
        rootPtr->left = Insert(rootPtr->left, data);
    }
    else {
        rootPtr->right = Insert(rootPtr->right, data);
    }
    return rootPtr;
}

bool Search(BstNode* rootPtr, int data) {
    if (rootPtr == NULL) {
        cout << "no" << endl;
        return false;
    }
    if (rootPtr->data == data) {
        cout << "yes" << endl;
        return true;
    }
    else if (data < rootPtr->data) {
        return Search(rootPtr->left, data);
    }
    else {
        return Search(rootPtr->right, data);
    }
}

int FindMin(BstNode* rootPtr) {
    if (rootPtr == NULL) {
        cout << "it's an empty tree" << endl;
        return 0;
    }
    else if (rootPtr->left == NULL) {
        return rootPtr->data;
    }
    else {
        return FindMin(rootPtr->left);
    }
}

int FindMax(BstNode* rootPtr) {
    if (rootPtr == NULL) {
        cout << "Error: Tree is empty\n" << endl;
        return 0;
    }
    else if (rootPtr->right == NULL) {
        return rootPtr->data;
    }
    else {
        return FindMax(rootPtr->right);
    }

    /*
    using interation (more efficient but less readable)

    if NULL...
    while (rootPtr->right !== NULL) {
        rootPtr = rootPtr->right;
    }
    return rootPtr->data;
    */

}

/*
                    node
    left-subtree            right-subtree

    Height = max(heightLeft, heightRight) + 1
*/
int  FindHeight(BstNode* rootPtr) {
    if (rootPtr == NULL) {
        return -1;
    }
    return max(FindHeight(rootPtr->left), FindHeight(rootPtr->right)) + 1; 
}

bool IsSubtreeLesser(BstNode *rootPtr, int value) {
    if (rootPtr == NULL) {
        return true;
    }
    else if (rootPtr->data < value && IsSubtreeLesser(rootPtr->left, value) && IsSubtreeLesser(rootPtr->right, value)) {
        return true;
    }
    else {
        return false;
    }
}

bool IsSubtreeGreater(BstNode *rootPtr, int value) {
    if (rootPtr == NULL) {
        return true;
    }
    else if (rootPtr->data > value && IsSubtreeGreater(rootPtr->left, value) && IsSubtreeGreater(rootPtr->right, value)) {
        return true;
    }
    else {
        return false;
    }
}

bool IsBST1(BstNode* rootPtr) {
    if (rootPtr == NULL) {
        return true;
    }
    else if (IsSubtreeLesser(rootPtr->left,rootPtr->data) && IsSubtreeGreater(rootPtr->right,rootPtr->data) 
    && IsBST1(rootPtr->left) && IsBST1(rootPtr->right)) {
        return true;
    }
    else  {
        return false;
    }
}

bool IsBstUtil(BstNode* rootPtr, int min, int max) {
    if (rootPtr == NULL) {
        return true;
    }
    else if (rootPtr->data > min && rootPtr->data < max && IsBstUtil(rootPtr->left, min, rootPtr->data) && IsBstUtil(rootPtr->right, rootPtr->data, max)) {
        return true;
    }
    else {
        return false;
    }
}

bool IsBST2(BstNode *root) {
    return  IsBstUtil(root, INT_MIN, INT_MAX);
}


int current = INT_MIN;
bool IsBST3(BstNode *root) {
    if (root == NULL) {
        return true;
    }
    if(!IsBST3(root->left)) {
        return false;
    }
    if(root->data <= current) {
        return false;
    }
    current = root->data;
    if(!IsBST3(root->right)) {
        return false;
    }
    return true;
}

BstNode* Delete(BstNode *root, int data) {
    if (root == NULL) {
        return root;
    }
    else if (data < root->data) {
        root->left = Delete(root->left, data);
    }
    else if (data > root->data) {
        root->right = Delete(root->right, data);
    }
    // find the data needing deleted
    else { 
        // case 1: NO child
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        }
        // case 2: One child
        else if (root->left == NULL) {
            BstNode *temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL) {
        BstNode *temp = root;
        root = root->left;
        delete temp;
        }
        // case 3: Two chilidren
        else {
            int temp = FindMin(root->right);
            root->data = temp;
            root->right = Delete(root->right, temp);
        }
    return root;
} 

BstNode* Find(BstNode *root, int data) {

}

BstNode* GetSuccessor(BstNode *root, int data) {
    // search the node - O(h)
    BstNode *current = Find(root, data);
    if (current == NULL) {
        return NULL:
    }
    // case 1: Node has right subtree
    else if (current->right != NULL) {
        return FindMin(current->right);
    }
    // case 2: Node doesn't has right subtree
    else {
        BstNode *successor = NULL;
        BstNode *ancestor = root;
        while (ancestor != current) {
            if (current->data < ancestor->data) {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else {
                ancestor = ancestor->right;
            }
        }
        return successor;
    }

}

int main() {
    BstNode* rootPtr = NULL;
    rootPtr = Insert(rootPtr, 1);
    rootPtr = Insert(rootPtr, 2);
    rootPtr = Insert(rootPtr, 3);
    rootPtr = Insert(rootPtr, 4);
    // rootPtr = Insert(rootPtr, 6);
    // Search(rootPtr, 4);    
    // cout << FindMin(rootPtr) << endl;
    // cout << FindMax(rootPtr) << endl;
    // cout << FindHeight(rootPtr) << endl;

    if (IsBST3(rootPtr)) {
        cout << "1";
    }
    else {
        cout << "0";
    }


    return 0;
}

