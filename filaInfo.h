#include "noArquivo.h"

struct noFilaInfo
{
    int elementos[NUM_ELEMENTOS];
    int indices[NUM_FILHOS];
    bool folha;
    int numChavesArm;
    struct noFilaInfo *prox;
};

struct filaInfo
{
    struct noFilaInfo *inicio;
    struct noFilaInfo *fim;
};

struct filaInfo *iniciaFilaInfo();
struct noFilaInfo *iniciaNoFilaInfo(int *elementos[], int *indices[], bool folha, int numChavesArm);
void insereNoFilaInfoFinal(struct filaInfo *f, int *elementos[], int *indices[], bool folha, int numChavesArm);
void insereNoFilaInfoFinalStruct(struct filaInfo *fila, struct noFilaInfo *novoNo);
void imprimeNoFilaInfo(struct noFilaInfo *no);
void imprimeFilaInfo(struct filaInfo *f);
void salvaArquivo(struct filaInfo *fila);
void percorreArquivoInOrderElementos(FILE *fp, int indice);
void percorreArquivoSequencial();
int buscaBinariaArquivo(FILE *fp, int chave, int indice);
