#ifndef AVL_H
#define AVL_H

typedef struct Node {
    int height; 
    float val;    
    struct Node *left;  
    struct Node *right; 
} Node;

typedef struct E {
    float data;
    struct E *next;
} Elem;

// Function declarations
Node *createNewNode(float val);
int nodeHeight(Node *root);
int height(Node *root);
void printLevel(Node *root, int level);
void levelOrderTraversal(Node *root);
int max(float a, float b);
Node *leftRotation(Node *z);
Node *rightRotation(Node *z);
Node *LRRotation(Node *z);
Node *RLRotation(Node *z);
Node *insertNode(Node *node, float key);
Node *inserare(Node *root,float val);
Node* search(Node* root, float val);
Elem * inOrderTraversal(Node* root,Elem **head);
Elem* createelem(float data);
void createList(Elem **List);
void addAtBeginning(Elem **head,float data);
void stackPrint(Elem **List);

#endif // AVL_H
