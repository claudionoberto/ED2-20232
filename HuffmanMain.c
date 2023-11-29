#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "arvoreHuffman.h"

//ALUNOS: CLAUDIO NOBERTO E KHAWAN FELLIPE

void compressSetup(FILE *fileText) {
    BinaryCode **codeTable;
    List list;
    Node *tree;
    unsigned int frequencyTable[TAM];
    int column;
    
    initTable(frequencyTable);
    fillTable(fileText, frequencyTable);
    fclose(fileText);
    
    init(&list);
    fillList(frequencyTable, &list);
    
    printf("\nTabela de Códigos Binários:\n");
    tree = setUpTree(&list);
    column = treeHeight(tree) + 1;
    codeTable = allocateMatrix(TAM, column);
    generateTable(tree, codeTable, "", column);
    printTable(codeTable);
    
    printf("\n---------------------\n");
    compressFile("PalavrasArvore.txt", "arquivo_comprimido.bin", codeTable);
    printf("Arquivo comprimido com sucesso.\n");
}

int main () {
    setlocale(LC_ALL, "portuguese");
    FILE* inputFile = fopen("PalavrasArvore.txt", "r");
    
    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    } else {
        compressSetup(inputFile);
    }
    
    return 0;
}