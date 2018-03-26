#include <stdlib.h>
#include "ui.h"
#include "arvoreB.h"

//***************************************
//  inicializações

struct noArvoreB **iniciaRaizArvoreB()
{
    struct noArvoreB **raiz = (struct noArvoreB**)malloc(sizeof(struct noArvoreB*));
    *raiz = NULL;

    return raiz;
}

struct noArvoreB *iniciaNoArvoreB(int *elementos[], int numElementos)
{
    int i;
    struct noArvoreB *no = (struct noArvoreB*)malloc(sizeof(struct noArvoreB));

    for(i = 0; i < NUM_ELEMENTOS; i++)
    {
        if(i >= numElementos) no->elementos[i] = 1;
        else no->elementos[i] = (int)elementos[i];
        no->filhos[i] = NULL;
    }
    no->filhos[i] = NULL;
    no->pai = NULL;

    no->numElementos = numElementos;
    no->folha = true;

    return no;
}

struct noArvoreB *iniciaNoArvoreBVazio()
{
    int i;
    struct noArvoreB *no = (struct noArvoreB *)malloc(sizeof(struct noArvoreB));

    for(i = 0; i < NUM_ELEMENTOS; i++)
    {
        no->elementos[i] = 1;
        no->filhos[i] = NULL;
    }
    no->filhos[i] = NULL;
    no->pai = NULL;
    no->numElementos = 0;
    no->folha = true;

    return no;
}

//***************************************
//  inserções

void insereNoArvoreBForcado(struct noArvoreB **raiz, int *elementos[], int numElementos)
{
    if(*raiz == NULL)
    {
        *raiz = iniciaNoArvoreB(elementos, numElementos);
    }
}

struct noArvoreB *trataInsercaoArvoreB(struct noArvoreB **raiz, int elemento)
{
    struct noArvoreB *novaRaiz;         //armazena a nova raiz
    struct noArvoreB *noAtual;          //armazena o nó atual da recursão
    struct noArvoreB *noRecursivo;      //armazena o nó retornado da recursão finalizada, a última posição armazena o elemento "que sobe"
    struct noArvoreB *novo;             //armazena metade do conteudo do nó cheio
    int i;                              //contador de elementos
    int j;                              //contador de ponteiros
    int indiceMeio;                     //posição do elementos que passa para o nó pai
    int indiceInicial;                  //posição do elemento que será passado para o novo nó
    int indiceFinal;                    //posição do elemento que será retirado do nó atual

    if(*raiz == NULL)
    {
        //cria um nó e armazena o elemento nele
        *raiz = iniciaNoArvoreBVazio();
        (*raiz)->elementos[0] = elemento;
        (*raiz)->numElementos = 1;
        return NULL;
    }

    noAtual = *raiz;

    //flag indicando que foi essa é uma nova raiz
    if(noAtual->elementos[0] == -1)
    {
        //pega o nó filho recursivamente e passa o elemento carregado por ele
        noRecursivo = trataInsercaoArvoreB(&(noAtual->filhos[0]), elemento);
        noAtual->elementos[0] = noRecursivo->elementos[NUM_ELEMENTOS-1];
        noAtual->numElementos = 1;
        //arruma o nó recursivo
        noRecursivo->elementos[NUM_ELEMENTOS-1] = 1;
        noRecursivo->pai = noAtual;
        noAtual->filhos[1] = noRecursivo;

        //atualiza os booleanos que indicam nó folha
        noAtual->folha = false;
        noAtual->filhos[0]->folha = isFolha(noAtual->filhos[0]);
        noRecursivo->folha = isFolha(noRecursivo);

        //tratado o problema da geração de uma nova raiz, encerra o método e retorna a nova raiz
        return noAtual;
    }

    //nó cheio
    if(noAtual->numElementos == NUM_ELEMENTOS)
    {
        //nó raiz cheio
        if(noAtual->pai == NULL)
        {
            //cria a nova raiz e trata os ponteiros
            novaRaiz = iniciaNoArvoreBVazio();
            noAtual->pai = novaRaiz;
            novaRaiz->filhos[0] = noAtual;

            //flag indicando que uma nova raiz foi criada
            novaRaiz->elementos[0] = -1;

            return trataInsercaoArvoreB(&(novaRaiz), elemento);
        }

        //atribui os valores para os indices
        novo = iniciaNoArvoreBVazio();
        indiceMeio = NUM_ELEMENTOS/2;
        indiceInicial = 0;
        indiceFinal = indiceMeio + 1;

        //armazena o elemento que vai ser passado para o nó pai
        novo->elementos[NUM_ELEMENTOS-1] = noAtual->elementos[indiceMeio];
        noAtual->elementos[indiceMeio] = 1;
        noAtual->numElementos--;

        //divide os elementos entre os nós
        while(indiceFinal < NUM_ELEMENTOS && indiceInicial < indiceMeio)
        {
            novo->elementos[indiceInicial] = noAtual->elementos[indiceFinal];
            noAtual->elementos[indiceFinal] = 1;
            noAtual->numElementos--;
            novo->numElementos++;
            indiceFinal++;
            indiceInicial++;
        }

        //caso o nó não seja folha, divide os ponteiros dos filhos
        if(!noAtual->folha)
        {
            //prepara os indices
            indiceFinal = indiceMeio+1;
            indiceInicial = 0;

            //divide os ponteiros entre os nós
            while(indiceFinal < NUM_FILHOS)
            {
                novo->filhos[indiceInicial] = noAtual->filhos[indiceFinal];
                noAtual->filhos[indiceFinal] = NULL;
                indiceFinal++;
                indiceInicial++;
            }
        }

        return novo;
    }//fim nó cheio
    else//nó com espaço
    {
        //nó folha
        if(noAtual->folha)
        {
            //procura a posição para inserção do novo elemento
            for(i = 0; i < NUM_ELEMENTOS; i++)
            {
                if(noAtual->elementos[i] > elemento || noAtual->elementos[i] == 1)
                    break;
            }

            //desloca os elementos para a direita
            if(noAtual->elementos[i] != 1 )
                for(j = noAtual->numElementos-1; j >= i; j--)
                {
                    noAtual->elementos[j+1] = noAtual->elementos[j];
                }

            //insere o elemento
            noAtual->elementos[i] = elemento;
            noAtual->numElementos++;
        }//fim nó folha
        else //nó interno
        {
            for(i = 0; i < NUM_ELEMENTOS; i++)
            {
                if(noAtual->elementos[i] > elemento || noAtual->elementos[i] == 1)
                    break;
            }

            //verifica se o nó abaixo mandou um elemento
            noRecursivo = trataInsercaoArvoreB(&(noAtual->filhos[i]), elemento);
            if(noRecursivo != NULL)
            {
                //desloca os valores do nó
                if(noAtual->elementos[i] != 1)
                    for(j = noAtual->numElementos; j >= i; j--)
                    {
                        noAtual->elementos[j+1] = noAtual->elementos[j];
                        noAtual->filhos[j+2] = noAtual->filhos[j+1];
                    }

                //atribui o valor carregado pelo nó vindo da recursão
                noAtual->elementos[i] = noRecursivo->elementos[NUM_ELEMENTOS-1];
                noAtual->filhos[i+1] = noRecursivo;
                noAtual->numElementos++;
                //trata do nó vindo da recursão
                noRecursivo->elementos[NUM_ELEMENTOS-1] = 1;
                noRecursivo->pai = noAtual;

                //verifica qual nó será visitado a partir do novo elemento inserido
                if(noAtual->elementos[i] > elemento)
                    trataInsercaoArvoreB(&(noAtual->filhos[i]), elemento);
                else trataInsercaoArvoreB(&(noAtual->filhos[i+1]), elemento);
            }//nó recursivo retornado
        }//fim nó interno
    }//fim nó com espaço
    return NULL;
}

//inicia a inserção na árvore
struct noArvoreB *insereArvoreB(struct noArvoreB **raiz, int elemento)
{
    struct noArvoreB *arrumaBagunca;
    arrumaBagunca = trataInsercaoArvoreB(raiz, elemento);

    //árvore não aumentou de tamanho
    if(arrumaBagunca == NULL) return *raiz;

    //árvore aumentou de tamanho, a nova raiz é atualizada e a inserção é chamada novamente
    *raiz = arrumaBagunca;
    return insereArvoreB(raiz, elemento);
}

//***************************************
//  remoções

//***************************************
//  auxiliares

//mostra o conteudo do nó
void imprimeNoArvoreB(struct noArvoreB *no)
{
    if(no == NULL) return;
    mostraConteudoNoArvoreB(no);
}

//mostra o conteudo da árvore
void imprimeArvoreB(struct noArvoreB **raiz)
{
    int i;
    if(*raiz == NULL) return;

    for(i = 0; i < NUM_FILHOS; i++)
    {
        if((*raiz)->filhos[i] != NULL) imprimeArvoreB(&(*raiz)->filhos[i]);
        if((*raiz)->elementos[i] != 1 && i < NUM_ELEMENTOS) printf("%c", (*raiz)->elementos[i]);
    }
}

//mostra se existe conteudo em cada filho do nó
void imprimeFilhosNoArvoreB(struct noArvoreB *no)
{
    if(no == NULL) return;
    mostraFilhosNoArvoreB(no);
}

//mostra se o nó é folha ou não
void imprimeIsFolha(struct noArvoreB *no)
{
    if(no == NULL) return;
    mostraNoFolhaArvoreB(no);
}

//retorna um booleano com a resposta se o nó é folha
bool isFolha(struct noArvoreB *no)
{
    int index;
    if(no == NULL) return false;

    for(index = 0; index < NUM_FILHOS; index++)
    {
        if(no->filhos[index] != NULL) return false;
    }
    return true;
}

//cria uma nova arvoreB e alimenta com valores pre determinados
//retorna o ponteiro p/ ponteiro da raiz
struct noArvoreB** injetaValoresArvoreB()
{
    struct noArvoreB **r02 = iniciaRaizArvoreB();

    *r02 = insereArvoreB(r02, 'F');
    *r02 = insereArvoreB(r02, 'S');
    *r02 = insereArvoreB(r02, 'Q');
    *r02 = insereArvoreB(r02, 'K');
    *r02 = insereArvoreB(r02, 'C');
    *r02 = insereArvoreB(r02, 'L');
    *r02 = insereArvoreB(r02, 'H');
    *r02 = insereArvoreB(r02, 'T');
    *r02 = insereArvoreB(r02, 'V');
    *r02 = insereArvoreB(r02, 'W');
    *r02 = insereArvoreB(r02, 'M');
    *r02 = insereArvoreB(r02, 'R');
    *r02 = insereArvoreB(r02, 'N');
    *r02 = insereArvoreB(r02, 'P');
    *r02 = insereArvoreB(r02, 'A');
    *r02 = insereArvoreB(r02, 'B');
    *r02 = insereArvoreB(r02, 'X');
    *r02 = insereArvoreB(r02, 'Y');
    *r02 = insereArvoreB(r02, 'D');
    *r02 = insereArvoreB(r02, 'Z');
    *r02 = insereArvoreB(r02, 'E');

    return r02;
}
