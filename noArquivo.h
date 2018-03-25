#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GRAU (2)
#define NUM_FILHOS (GRAU * 2)
#define NUM_ELEMENTOS (NUM_FILHOS - 1)

typedef struct noArquivo{
    int nroChavesArm;
    bool folha;
    char chave[NUM_ELEMENTOS];
    int indice[NUM_FILHOS];
	//struct noArquivo *indice[NUM_FILHOS];
} NO_B;

struct noArquivo *iniciaNoArquivo(char *chaves[], int *indices[], bool folha, int nroChavesArm);
void imprimeNoArquivo(struct noArquivo *no);
void noArquivo_percorreArquivoInOrderChaves(FILE *fp, int indice);
void noArquivo_percorreArquivoSequencial(char *nomeArquivo[]);
int noArquivo_buscaBinariaArquivo(FILE *fp, int chave, int indice);
