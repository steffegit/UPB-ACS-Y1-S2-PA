#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>

Node *createNewNode(float val) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->height = 1;
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int nodeHeight(Node *root) {
    if (root == NULL) return 0;
    return root->height;
}

int height(Node *root) {
    int hs, hd;
    if (root == NULL) return 0;
    hs = height(root->left);
    hd = height(root->right);
    return 1 + ((hs > hd) ? hs : hd);
}

Node* inserare(Node* root, float val) {
  if (root == NULL)
    return createNewNode(val);
  if (val < root->val)
    root->left = inserare(root->left, val);
  else if (val > root->val)
    root->right = inserare(root->right, val);
  return root;
}

void printLevel(Node *root, int level) {
    if (root == NULL) return;
    if (level == 1) printf("%f ", root->val);
    else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

void levelOrderTraversal(Node *root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printLevel(root, i);
        printf("\n");
    }
}

int max(float a, float b) {
    return (a > b) ? a : b;
}

Elem * inOrderTraversal(Node* root,Elem **head) {
    if (root != NULL) {
        inOrderTraversal(root->left,head);  // Vizitează subarborele stâng
           addAtBeginning(head,root->val); // Vizitează nodul curent
        inOrderTraversal(root->right,head); // Vizitează subarborele drept
    }
   else return *head;
}
// Function to create a new linked list element
Elem* createElem(float data) {
    Elem* newNode = (Elem*)malloc(sizeof(Elem));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the linked list
void createList(Elem** list) {
    *list = NULL;
}

// Function to add an element to the beginning of the list
void addAtBeginning(Elem** head, float data) {
    Elem* newNode = createElem(data);
    newNode->next = *head;
    *head = newNode;
}

void stackPrint(Elem** list) {
    Elem* current = *list;
    printf("Lista este: ");
    while (current != NULL) {
        printf("%f ",current->data);
        current = current->next;
    }
    printf("\n");
}

Node *leftRotation(Node *z) {
    Node *y = z->right;
    Node *T2 = y->left;
    y->left = z;
    z->right = T2;
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}

Node *rightRotation(Node *z) {
    Node *y = z->left;
    Node *T3 = y->right;
    y->right = z;
    z->left = T3;
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}

Node *LRRotation(Node *z) {
    z->left = leftRotation(z->left);
    return rightRotation(z);
}

Node *RLRotation(Node *z) {
    z->right = rightRotation(z->right);
    return leftRotation(z);
}

Node *insertNode(Node *node, float key) {
    if (node == NULL) return createNewNode(key);

    if (key < node->val)
        node->left = insertNode(node->left, key);
    else if (key > node->val)
        node->right = insertNode(node->right, key);
    else
        return node;

    node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));

    int balance = nodeHeight(node->left) - nodeHeight(node->right);

    if (balance > 1 && key < node->left->val)
        return rightRotation(node);

    if (balance < -1 && key > node->right->val)
        return leftRotation(node);

    if (balance > 1 && key > node->left->val)
        return LRRotation(node);

    if (balance < -1 && key < node->right->val)
        return RLRotation(node);

    return node;
}
Node* search(Node* root, float val) {
  if (root == NULL || root->val == val)
    return root;
  if (root->val < val)
    return search(root->right, val);
  return search(root->left, val);
}
