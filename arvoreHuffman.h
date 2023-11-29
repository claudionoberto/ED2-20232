#include <stdio.h>
#include <stdlib.h>
#define TAM 256

typedef struct node{
    unsigned char caracter;
    int frequency;
    struct node *left, *right, *next;
}Node;

typedef struct {
    Node *first;
    int size;
}List;

typedef struct {
    char caractere;
    char *code;
}BinaryCode;


void init(List *list);
void enqueue(List *list, Node *node);
void fillList(unsigned int tab[], List *list);
Node *removeBeginning(List *list);
Node *setUpTree(List *list);
int treeHeight(Node *root);
BinaryCode **allocateMatrix(int lines, int columns);
void generateTable(Node *root, BinaryCode **table, char *path, int columns);
void printTable(BinaryCode **table);
void writeTableToFile(FILE *compressedFile, BinaryCode **table);
void writeCompressedData(FILE *compressedFile, FILE *originalFile, BinaryCode **table);
void readTableFromFile(FILE *compressedFile, BinaryCode **table);
void decompressData(FILE *compressedFile, FILE *uncompressedFile, Node *tree);
void compressFile(char *nameOriginalFile, char *nameCompressedFile, BinaryCode **table);
void initTable(unsigned int tab[]);
void fillTable(FILE *file, unsigned int tab[]);