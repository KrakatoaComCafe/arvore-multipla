#include <stdlib.h>
#include "ui.h"
#include "filaInfo.h"

//***************************************
//  inicializações

struct filaInfo *iniciaFilaInfo()
{
    struct filaInfo *novaFila = (struct filaInfo* )malloc(sizeof(struct filaInfo));
    novaFila->inicio = NULL;
    novaFila->fim = NULL;

    return novaFila;
}

struct noFilaInfo *iniciaNoFilaInfo(int *elementos, int *indices, bool folha, int numChavesArm)
{
    int i;
    struct noFilaInfo *no = (struct noFilaInfo*) malloc(sizeof(struct noFilaInfo));

    for(i = 0; i < NUM_ELEMENTOS; i++)
    {
        no->elementos[i] = (int)elementos[i];
        no->indices[i] = (int)indices[i];
    }
    no->numChavesArm = numChavesArm;
    no->indices[i] = (int)indices[i];
    no->folha = folha;
    no->prox = NULL;

    return no;
}

//***************************************
//  inserções

void insereNoFilaInfoFinal(struct filaInfo *f, int *elementos, int *indices, bool folha, int numChavesArm)
{
    struct noFilaInfo *novo = iniciaNoFilaInfo(elementos, indices, folha, numChavesArm);
    if(f->inicio == NULL)
    {
        f->inicio = novo;
        f->fim = novo;
        return;
    }

    f->fim->prox = novo;
    f->fim = novo;
}

void insereNoFilaInfoFinalStruct(struct filaInfo *fila, struct noFilaInfo *novoNo)
{
    if(fila->inicio == NULL)
    {
        fila->inicio = novoNo;
        fila->fim = novoNo;
        return;
    }

    fila->fim->prox = novoNo;
    fila->fim = novoNo;
}

//***************************************
//  remoções

//***************************************
//  auxiliares

//mostra todo o conteudo da do nó da fila
void imprimeNoFilaInfo(struct noFilaInfo *no)
{
    if(no == NULL) return;
    mostraNoFilaInfo(no);
}

//mostra todo o conteudo da fila
void imprimeFilaInfo(struct filaInfo *f)
{
    struct noFilaInfo *aux;
    if(f->inicio == NULL) return;

    aux = f->inicio;
    while(aux != NULL)
    {
        imprimeNoFilaInfo(aux);
        aux = aux->prox;
    }
}

//salva o conteudo da fila
void salvaArquivo(struct filaInfo *fila)
{
    struct noFilaInfo *aux;
    FILE *fp;

    if(fila->inicio == NULL) return;

    fp = fopen("arvoreMultipla.bab","wb");
    if(fp)
    {
        aux = fila->inicio;

        while(aux != NULL)
        {
            fwrite(aux, sizeof(struct noFilaInfo), 1, fp);
            aux = aux->prox;
        }

        fclose(fp);
    }
    else mensagemErro_filaInfo_erroSalvarArquivo();
}

//percorre a árvore em arquivo, mostrando os elementos em ordem alfabetica
void percorreArquivoInOrderElementos(FILE *fp, int indice)
{
    int i;
    int nbytes;
    struct noFilaInfo aux;
    fseek(fp, indice * sizeof(struct noFilaInfo), SEEK_SET);
    nbytes = fread(&aux, sizeof(struct noFilaInfo), 1, fp);
    if(nbytes != 0)
    {
        for(i = 0 ; i < NUM_FILHOS; i++)
        {
            if(aux.indices[i] != 0) percorreArquivoInOrderElementos(fp, aux.indices[i]);

            if(i < NUM_ELEMENTOS && aux.elementos[i] != 1) printf("%c", aux.elementos[i]);
        }
    }
}

void percorreArquivoSequencial()
{
    FILE *fp;
    int indice;
    int nbytes;
    struct noFilaInfo aux;

    fp = fopen("arvoreMultipla.bab","rb");
    if(fp != NULL)
    {
        leituraDeArquivo_header();
        nbytes = 1; //atribui um valor pra passar pelo primeiro for
        for(indice = 0; nbytes != 0; indice++)
        {
            fseek(fp, indice * sizeof(struct noFilaInfo), SEEK_SET);
            nbytes = fread(&aux, sizeof(struct noFilaInfo), 1, fp);
            if(nbytes != 0)
            {
                char* charArray = (char*)aux.elementos;
                leituraDeArquivo_corpo(indice, aux.numChavesArm, charArray, aux.indices, aux.folha);
                //leituraDeArquivo_corpo_noFilaInfo(indice, &aux);
            }
        }

        fclose(fp);
    }
    else mensagemErro_erroAbrirArquivo(__FILE__);

}

//procura a chave em uma arvore em aquivo
int buscaBinariaArquivo(FILE *fp, int chave, int indice)
{
    int i;
    int nbytes;
    struct noFilaInfo aux;

    if(fp != NULL)
    {
        fseek(fp, indice*sizeof(struct noFilaInfo), SEEK_SET);
        nbytes = fread(&aux, sizeof(struct noFilaInfo), 1, fp);
        if(nbytes != 0)
        {
            for(i = 0; i < aux.numChavesArm; i++)
            {
                if(aux.elementos[i] == chave)
                {
                    mostrarElementoEPosicao(aux.elementos[i], indice);
                    //printf("\nElemento %c Encontrado - No identificado pelo indice[%d]\n", aux.elementos[i], indice);
                    return 1;
                }
            }

            for(i = 0; i < aux.numChavesArm; i++)
            {
                if(chave < aux.elementos[i])
                    return buscaBinariaArquivo(fp, chave, aux.indices[i]);
            }
            if(i == aux.numChavesArm) return buscaBinariaArquivo(fp, chave, aux.indices[i]);
        }
        else return 0;
    }
    else mensagemErro_erroBuscarArquivo(__FILE__);

    return (int)NULL;
}
