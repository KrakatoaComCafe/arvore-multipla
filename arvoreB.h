#ifndef __ARVOREB_H_
#define __ARVOREB_H_

#include "filaInfo.h"

struct noArvoreB
{
    int numElementos;
    bool folha;
    int elementos[NUM_ELEMENTOS];
    struct noArvoreB *filhos[NUM_FILHOS];
    struct noArvoreB *pai;
};

struct noArvoreB **iniciaRaizArvoreB();
struct noArvoreB *iniciaNoArvoreB(int *elementos[], int numElementos);
struct noArvoreB *iniciaNoArvoreBVazio();
void insereNoArvoreBForcado(struct noArvoreB **raiz, int *elementos[], int numElementos);
struct noArvoreB *trataInsercaoArvoreB(struct noArvoreB **raiz, int elemento);
struct noArvoreB *insereArvoreB(struct noArvoreB **raiz, int elemento);
void imprimeNoArvoreB(struct noArvoreB *no);
void imprimeArvoreB(struct noArvoreB **raiz);
void imprimeFilhosNoArvoreB(struct noArvoreB *no);
void imprimeIsFolha(struct noArvoreB *no);
bool isFolha(struct noArvoreB *no);
struct noArvoreB **injetaValoresArvoreB();


#endif // __ARVOREB_H_
