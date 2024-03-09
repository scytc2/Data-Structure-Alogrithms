## Implement of BST in C/C++

#### define the node structure

```
typedef struct BstNodes
{
    int data;
    BstNodes* left;
    BstNodes* right;
}BstNode;
```

#### allocate the memory for new node

```
BstNode* GetNewNode(int data) {
    BstNode* newNode = new BstNode;
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}
```

#### insert new node

```
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
```

#### search new node

```
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
```

#### find the min node

````
int findMin(BstNode* rootPtr) {
    if (rootPtr == NULL) {
        cout << "it's an empty tree" << endl;
        return 0;
    }
    else if (rootPtr->left == NULL) {
        return rootPtr->data;
    }
    else {
        return findMin(rootPtr->left);
    }
}
````

#### find the max node

```
int findMax(BstNode* rootPtr) {
    if (rootPtr == NULL) {
        cout << "Error: Tree is empty\n" << endl;
        return 0;
    }
    else if (rootPtr->right == NULL) {
        return rootPtr->data;
    }
    else {
        return findMax(rootPtr->right);
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
```

#### find the height of tree

```
int  findHeight(BstNode* rootPtr) {
    if (rootPtr == NULL) {
        return -1;
    }
    return max(findHeight(rootPtr->left), findHeight(rootPtr->right)) + 1; 
}
```

#### check if a binary tree is a BST

##### - Implement1

```
/*
This implement is to check if left-subtree < node < right-subtree and if both of subtrees are BST.
It's neither effcient nor readable
*/
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
    else if (IsSubtreeLesser(rootptr->left,rootptr->data) && IsSubtreeGreater(rootptr->right,rootptr->data) 
    && IsBST1(rootPtr->left) && IsBST1(rootPtr->right)) {
        return true
    }
    else  {
        return false;
    }
}
```

##### -Implement2

```
/*
This implement is based on left < node < right
more efficence and readable
*/
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
```

##### -Implement3

```
/*
This implement is based on inorder traversal
To my opinon it is most readable and comprehensible
*/
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
```

#### Delete a node in BST

```
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
```

#### find the successor of the node

```
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
```







## Implement of Binary Tree Traversal in C/C++

### Breadth-first(level-order traversal)

```
void LevelOrder(Node *root){
    if (root == NULL) {
        cout << "Error: Tree is empty" << endl;
        return;
    }
    queue<Node*> Q; // STL of queue: #include<queue>
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
```



### Depth-first

- #### Preorder

  ```
  void Preorder(Node* root) {
      if (root == NULL) {
          return;
      }
      cout << root->data << " ";
      Preorder(root->left);
      Preorder(root->right); 
  }
  ```

  

- #### Inorder

  ```
  void Inorder(Node* root) {
      if (root == NULL) {
          return;
      }
      Inorder(root->left);
      cout << root->data << " ";
      Inorder(root->right); 
  }
  ```

  

- #### Postroder

  ```
  void Postorder(Node* root) {
      if (root == NULL) {
          return;
      }
      Postorder(root->left);
      Postorder(root->right);
      cout << root->data << " ";
  }
  ```









