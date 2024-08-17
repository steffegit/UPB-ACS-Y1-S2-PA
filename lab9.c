#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    char *cuvant;
    uint16_t hash;
    struct Node *next;
} Node;

void stackCreate(Node **List) {
    *List = NULL;
}

uint16_t sum_hash(const uint8_t *str) {
    uint16_t hash = 0;
    while (*str) {
        hash += *str;
        str++;
    }
    return hash % 65536;
}

uint16_t DJB2_hash ( const uint8_t *str) {
uint16_t hash = 5381;
uint8_t c;
while ((c = *str ++))
hash = (( hash << 5) + hash ) + c; /* hash * 33 + c */
return hash ;
}

void addAtTheEnd(Node **head, char *v) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->cuvant = (char*)malloc(strlen(v) + 1);
    strcpy(newNode->cuvant, v);
    newNode->hash = sum_hash((uint8_t*)v);
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *aux = *head;
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = newNode;
    }
}

void addAtTheEndDJBS(Node **head, char *v) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->cuvant = (char*)malloc(strlen(v) + 1);
    strcpy(newNode->cuvant, v);
    newNode->hash = DJB2_hash((uint8_t*)v);
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *aux = *head;
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = newNode;
    }
}

void printList(Node *head) {
    Node *aux = head;
    while (aux != NULL) {
        printf("%s\n", aux->cuvant);
        aux = aux->next;
    }
}

void freeList(Node **head) {
    Node *aux;
    while (*head != NULL) {
        aux = *head;
        *head = (*head)->next;
        free(aux->cuvant);
        free(aux);
    }
}

void procentColiziuni(int coliziuni) {
    printf("Procent coliziuni: %.2f%%\n", (float)coliziuni /370105 * 100);
}

int main() {
    Node *Hash_Table[65536];
    int bucketsize[65536] = {0};
    FILE *input = fopen("words_alpha.txt", "r");

    if (input == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    for (int i = 0; i < 65536; i++) {
        stackCreate(&Hash_Table[i]);
    }

    char cuvant[100];
    int coliziuni = 0;

    // First pass to count collisions and store words
    while (fscanf(input, "%s", cuvant) != EOF) {
        uint16_t hash = sum_hash((uint8_t*)cuvant);
        bucketsize[hash]++;
        if (bucketsize[hash] == 2) {  // Count collisions when a bucket has exactly 2 items
            coliziuni++;
        } else if (bucketsize[hash] > 2) {  // Increment collision count for subsequent items
            coliziuni++;
        }
        addAtTheEnd(&Hash_Table[hash], cuvant);
        
    }

    procentColiziuni(coliziuni);

    // Free existing lists
    for (int i = 0; i < 65536; i++) {
        freeList(&Hash_Table[i]);
    }

    // Reinitialize hash table
    for (int i = 0; i < 65536; i++) {
        stackCreate(&Hash_Table[i]);
    }

    // Reset file pointer to the beginning
    fseek(input, 0, SEEK_SET);

    int coliziuni100 = 0;
    int bucketsize100[65536] = {0};
    int totalWords = 0;

    // Second pass to count collisions in the first 100 words
    while (fscanf(input, "%s", cuvant) != EOF && totalWords < 100) {
        uint16_t hash = sum_hash((uint8_t*)cuvant);
        bucketsize100[hash]++;
        if (bucketsize100[hash] == 2) {  // Count collisions when a bucket has exactly 2 items
            coliziuni100++;
        } else if (bucketsize100[hash] > 2) {  // Increment collision count for subsequent items
            coliziuni100++;
        }
        addAtTheEnd(&Hash_Table[hash], cuvant);
        totalWords++;
    }

    printf("\nNumar coliziuni pentru primele 100 de cuvinte: %d\n", coliziuni100);

    // Clean up
    for (int i = 0; i < 65536; i++) {
        freeList(&Hash_Table[i]);
    }

    //DJBSHASH

    for (int i = 0; i < 65536; i++) {
        stackCreate(&Hash_Table[i]);
    }

    totalWords = 0;
    coliziuni = 0;

    for(int i=0; i<65536; i++) {
        bucketsize[i] = 0;
    }

    // First pass to count collisions and store words
    while (fscanf(input, "%s", cuvant) != EOF) {
        uint16_t hash = DJB2_hash((uint8_t*)cuvant);
        bucketsize[hash]++;
        if (bucketsize[hash] == 2) {  // Count collisions when a bucket has exactly 2 items
            coliziuni++;
        } else if (bucketsize[hash] > 2) {  // Increment collision count for subsequent items
            coliziuni++;
        }
        addAtTheEndDJBS(&Hash_Table[hash], cuvant);
    }

     printf("DUPA DJB2\n");
    procentColiziuni(coliziuni);

    // Free existing lists
    for (int i = 0; i < 65536; i++) {
        freeList(&Hash_Table[i]);
    }

    // Reinitialize hash table
    for (int i = 0; i < 65536; i++) {
        stackCreate(&Hash_Table[i]);
    }

    // Reset file pointer to the beginning
    fseek(input, 0, SEEK_SET);

    coliziuni100 = 0;
    totalWords = 0;

    for(int i = 0; i < 65536; i++) {
        bucketsize100[i] = 0;
    }

    // Second pass to count collisions in the first 100 words
    while (fscanf(input, "%s", cuvant) != EOF && totalWords < 100) {
        uint16_t hash = DJB2_hash((uint8_t*)cuvant);
        bucketsize100[hash]++;
        if (bucketsize100[hash] == 2) {  // Count collisions when a bucket has exactly 2 items
            coliziuni100++;
        } else if (bucketsize100[hash] > 2) {  // Increment collision count for subsequent items
            coliziuni100++;
        }
        addAtTheEndDJBS(&Hash_Table[hash], cuvant);
        totalWords++;
    }

    printf("\nNumar coliziuni pentru primele 100 de cuvinte: %d\n", coliziuni100);

    // Clean up
    for (int i = 0; i < 65536; i++) {
        freeList(&Hash_Table[i]);
    }

    fclose(input);
    return 0;
}
