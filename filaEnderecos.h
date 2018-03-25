#include "arvoreB.h"

struct filaEndereco
{
    struct noFilaEndereco *inicio;
    struct noFilaEndereco *fim;
};

struct noFilaEndereco
{
    struct noArvoreB *enderecoNoArvore;
    struct noFilaEndereco *prox;
};

struct filaEndereco *iniciaFilaEndereco();
struct noFilaEndereco *iniciaNoFilaEndereco(struct noArvoreB *no);
void insereNoFilaEnderecoFinal(struct filaEndereco *fila, struct noArvoreB *no);
void imprimeNoFilaEndereco(struct noFilaEndereco *no);
struct filaInfo *arvoreB_to_filaInfo(struct noArvoreB **raiz);
void noArquivo_salvarArvoreB(struct noArvoreB **raiz, char *nomeArquivo[]);
