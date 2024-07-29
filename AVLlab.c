#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Node* root = NULL;
    Node *inainte=NULL;
    Node *dupa=NULL;

    Elem *lista1=NULL;
    Elem *lista2=NULL;

    float averi[8] = {12, 10, 32, 24, 16, 22, 19, 23};
    float averemax=0.0;


    createList(&lista1);
    createList(&lista2);

    for (int i = 0; i < 8; i++) {
        root = inserare(root, averi[i]);
    }

    printf("Level Order Traversal of the AVL tree:\n");
    levelOrderTraversal(root);

    for(int i=0;i<8;i++)
          averemax=max(averemax,averi[i]);
    
    for(int i=0;i<8;i++)
        if(averi[i]==averemax)
        averi[i]*=0.6;
        else
        averi[i]*=1.05;

    for(int i=0;i<8;i++)
       inainte=inserare(inainte,averi[i]);

       inOrderTraversal(inainte,&lista1);

    for(int i=1;i<8;i++)
       dupa=insertNode(dupa,averi[i]);

     inOrderTraversal(dupa,&lista2);

     if(lista1!=lista2)
        printf("da a fost echil|||||");
     else
       printf("nu a fost echil|||");
    return 0;
}
