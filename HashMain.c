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

void criarImagemPPM(const HashStruct *hashStruct, const char *filename) {
    FILE *imageFile = fopen(filename, "w");

    if (!imageFile) {
        printf("Erro ao criar o arquivo de imagem PPM.\n");
        return;
    }

    int densidadeMax = 0;

    for (int i = 0; i < MAX; i++) {
        int density = hashStruct->hashes[i].size;
        densidadeMax = (density > densidadeMax) ? density : densidadeMax;
    }

    fprintf(imageFile, "P3\n");
    fprintf(imageFile, "32 32\n");
    fprintf(imageFile, "255\n");   

    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            int density = hashStruct->hashes[i * 32 + j].size;
            int color = (int)((density / (double)densidadeMax) * 255);
            fprintf(imageFile, "42 252 %d ", color);
        }
    }

    fclose(imageFile);
    printf("Imagem PPM criada com sucesso: %s\n", filename);
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
            put2(&hashe2,textoHashe2,textoHashe2,comparar);
            textoHashe2 = (char*)malloc(sizeof(char)*100);
        }
    }
    fclose(arquivoHashe2);

    criarImagemPPM(&hashe, "TabelaHash1.ppm");
    criarImagemPPM(&hashe2, "TabelaHash2.ppm");

    return 0;
}