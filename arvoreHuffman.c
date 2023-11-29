#include "arvoreHuffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>


void init(List *list) {
    list->first = NULL;
    list->size = 0;
}


void enqueue(List *list, Node *node) {
    Node *aux;
    if (list->first == NULL) {
        list->first = node;
    } else if (node->frequency < list->first->frequency) {
        node->next = list->first;
        list->first = node;
    } else {
        aux = list->first;
        while (aux->next && aux->next->frequency <= node->frequency)
            aux = aux->next;
        node->next = aux->next;
        aux->next = node;
    }
    list->size++;
}


void fillList(unsigned int tab[], List *list) {
    int i;
    Node *new;
    for (i = 0; i < TAM; i++) {
        if (tab[i] > 0) {
            new = malloc(sizeof(Node));
            if (new) {
                new->caracter = i;
                new->frequency = tab[i];
                new->right = NULL;
                new->left = NULL;
                new->next = NULL;
                
                enqueue(list, new);
            } else {
                printf("\tErro ao alocar memoria\n");
                break;
            }
        }
    }
}

Node *removeBeginning(List *list) {
    Node *aux = NULL;
    if (list->first != NULL) {
        aux = list->first;
        list->first = aux->next;
        aux->next = NULL;
        list->size--;
    }
    return aux;
}

Node *setUpTree(List *list) {
    Node *first, *second, *new;
    while (list->size > 1) {
        first = removeBeginning(list);
        second = removeBeginning(list);
        new = malloc(sizeof(Node));
        
        if (new) {
            new->caracter = '+';
            new->frequency = first->frequency + second->frequency;
            new->left = first;
            new->right = second;
            new->next = NULL;
            
            enqueue(list, new);
        } else {
            printf("\n\tErro ao alocar memoria\n");
            break;
        }
    }
    return list->first;
}

int treeHeight(Node *root) {
    int left, right;
    if (root == NULL) {
        return -1;
    } else {
        left = treeHeight(root->left) + 1;
        right = treeHeight(root->right) + 1;
        
        if (left > right) {
            return left;
        } else {
            return right;
        }
    }
}

BinaryCode **allocateMatrix(int lines, int columns) {
    BinaryCode **matriz;
    int i;
    
    matriz = malloc(sizeof(BinaryCode *) * lines);
    
    for (i = 0; i < lines; i++) {
        matriz[i] = malloc(sizeof(BinaryCode));
        matriz[i]->caractere = '\0';
        matriz[i]->code = NULL;
    }
    
    return matriz;
}


void generateTable(Node *root, BinaryCode **table, char *path, int columns) {
    char left[columns], right[columns];
    
    if (root->left == NULL && root->right == NULL) {
        table[root->caracter]->caractere = root->caracter;
        table[root->caracter]->code = strdup(path);
    } else {
        strcpy(left, path);
        strcpy(right, path);
        
        strcat(left, "0");
        strcat(right, "1");
        
        generateTable(root->left, table, left, columns);
        generateTable(root->right, table, right, columns);
    }
}


void printTable(BinaryCode **table) {
    for (int i = 0; i < TAM; i++) {
        if (table[i]->code) {
            printf("Caractere: %c || Código Binário Correspondente: %s\n", table[i]->caractere, table[i]->code);
        }
    }
}


void writeTableToFile(FILE *compressedFile, BinaryCode **table) {
    for (int i = 0; i < TAM; i++) {
        if (table[i]->code != NULL) {
            fprintf(compressedFile, "%c%s\n", table[i]->caractere, table[i]->code);
        }
    }
}

void writeCompressedData(FILE *compressedFile, FILE *originalFile, BinaryCode **table) {
    int c;
    char buffer[9] = {'\0'};
    int pos = 0;

    while ((c = fgetc(originalFile)) != EOF) {
        const char *code = table[c]->code;
        while (*code != '\0') {
            buffer[pos++] = *code++;
            if (pos == 8) {
                fprintf(compressedFile, "%ld", strtol(buffer, NULL, 2));
                pos = 0;
            }
        }
    }

    if (pos > 0) {
        fprintf(compressedFile, "%ld", strtol(buffer, NULL, 2));
    }
}

void readTableFromFile(FILE *compressedFile, BinaryCode **table) {
    char line[256];
    while (fgets(line, sizeof(line), compressedFile) != NULL) {
        char caractere;
        char *code = strtok(line, "\n");
        
        if (sscanf(code, "%c%s", &caractere, code) == 2) {
            table[(unsigned char)caractere]->code = strdup(code);
        }
    }
}

void decompressData(FILE *compressedFile, FILE *uncompressedFile, Node *tree) {
    int bit;
    Node *current = tree;

    while ((bit = fgetc(compressedFile)) != EOF) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }

        if (current->left == NULL && current->right == NULL) {
            fprintf(uncompressedFile, "%c", current->caracter);
            current = tree;
        }
    }
}


void compressFile(char *nameOriginalFile, char *nameCompressedFile, BinaryCode **table) {
    FILE *originalFile = fopen(nameOriginalFile, "r");
    FILE *compressedFile = fopen(nameCompressedFile, "wb");
    int character;

    if (originalFile == NULL || compressedFile == NULL) {
        fprintf(stderr, "Erro ao abrir arquivos.\n");
        exit(EXIT_FAILURE);
    } else {
        while ((character = fgetc(originalFile)) != EOF) {
            fprintf(compressedFile, "%s", table[(unsigned char)character]->code);
        }

        fclose(compressedFile);
        fclose(originalFile);
    }
}

void initTable(unsigned int tab[]) {
    for (int i = 0; i < TAM; i++) {
        tab[i] = 0;
    }
}

void fillTable(FILE *file, unsigned int tab[]) {
    int c;
    while ((c = fgetc(file)) != EOF) {
        tab[(unsigned char)c]++;
    }
}
