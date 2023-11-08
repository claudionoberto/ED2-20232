#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"

bool comparar(void* data1,void* data2) {
    if(strcmp (data1,data2) == 0) {
        return true;
    } else {
        return false;
    }
}

void printHash(void *data) {
    char* string_data = (char*)data;
    if (string_data != NULL) {
        printf("%s ",string_data);
    }
}

int main() {
    HashStruct hashe, hashe2;

    FILE *arquivoHashe;
    char *textoHashe;
    arquivoHashe = fopen ("Palavras.txt","r");
    initHash(&hashe);
    if (arquivoHashe != NULL) {
        textoHashe = (char*)malloc(sizeof(char)*100);
        while (fscanf(arquivoHashe,"%s \n",textoHashe) !=EOF) {
            put(&hashe,textoHashe,textoHashe,comparar);
            textoHashe = (char*)malloc(sizeof(char)*100);
        }
    }
    fclose(arquivoHashe);

    FILE *arquivoHashe2;
    char *textoHashe2;
    arquivoHashe2 = fopen ("Palavras.txt","r");
    initHash(&hashe2);
    if (arquivoHashe2 != NULL) {
        textoHashe2 = (char*)malloc(sizeof(char)*100);
        while (fscanf(arquivoHashe2,"%s \n",textoHashe2) !=EOF) {
            put(&hashe2,textoHashe2,textoHashe2,comparar);
            textoHashe2 = (char*)malloc(sizeof(char)*100);
        }
    }
    fclose(arquivoHashe2);



    initHash(&hashes);
    printf("%d\n",hash("joao.preti@cba.ifmt.edu.br"));
    Cliente *c = (Cliente *)malloc(sizeof(Cliente));
    strcpy(c->nome,"Joao Paulo") ;
    strcpy(c->email,"joao.preti@cba.ifmt.edu.br");
    printf("%d\n",hash(c->email));
    put(&hashes, c->email, c, comparaChaves);
    printf("%d\n",hashes.hashes[hash("joao.preti@cba.ifmt.edu.br")].size);
    printf("%d\n",hashes.size);
    printf("%d\n",containsKey(&hashes, "joao.preti@cba.ifmt.edu.br", comparaChaves));
    Cliente *cliente = (Cliente*)get(&hashes, "joao.preti@cba.ifmt.edu.br", comparaChaves);
    printf("%s\n",cliente->nome);
    c = (Cliente *)malloc(sizeof(Cliente));
    strcpy(c->nome,"Maria") ;
    strcpy(c->email,"maria@email.br");
    put(&hashes, c->email, c, comparaChaves);
    c = (Cliente *)malloc(sizeof(Cliente));
    strcpy(c->nome,"Pedro") ;
    strcpy(c->email,"pedro@email.com.br");
    put(&hashes, c->email, c, comparaChaves);
    c = (Cliente *)malloc(sizeof(Cliente));
    strcpy(c->nome,"Carla") ;
    strcpy(c->email,"carla@gmail.com.br");
    put(&hashes, c->email, c, comparaChaves);
    showHashStruct(&hashes, printCliente);
    return 0;
}