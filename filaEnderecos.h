#ifndef __FILAENDERECOS_H_
#define __FILAENDERECOS_H_
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

//inicialização
struct filaEndereco *iniciaFilaEndereco();
struct noFilaEndereco *iniciaNoFilaEndereco(struct noArvoreB *no);
//inserção
void insereNoFilaEnderecoFinal(struct filaEndereco *fila, struct noArvoreB *no);
//imprime
void imprimeNoFilaEndereco(struct noFilaEndereco *no);
void imprimeFilaEndereco(struct filaEndereco *fila);
//arquivo
struct filaInfo *arvoreB_to_filaInfo(struct noArvoreB **raiz);
void noArquivo_salvarArvoreB(struct noArvoreB **raiz, char *nomeArquivo);


#endif // __FILAENDERECOS_H_
