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

struct noFilaInfo *iniciaNoFilaInfo(int *elementos[], int *indices[], bool folha, int numChavesArm)
{
    int i;
    struct noFilaInfo *no = (struct noFilaInfo*) malloc(sizeof(struct noFilaInfo));

    for(i = 0; i < NUM_ELEMENTOS; i++)
    {
        no->elementos[i] = elementos[i];
        no->indices[i] = indices[i];
    }
    no->numChavesArm = numChavesArm;
    no->indices[i] = indices[i];
    no->folha = folha;
    no->prox = NULL;

    return no;
}

//***************************************
//  inserções

void insereNoFilaInfoFinal(struct filaInfo *f, int *elementos[], int *indices[], bool folha, int numChavesArm)
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
    int i;
    if(no == NULL) return;

    printf("No Fila: \n");
    printf("NumChavesArm - %d\n", no->numChavesArm);
    for(i = 0; i < NUM_ELEMENTOS; i++)
    {
        printf("Elemento[%d] - %c\n", i, no->elementos[i]);
    }
    for(i = 0; i < NUM_FILHOS; i++)
    {
        printf("Indice[%d] - %d\n",i, no->indices[i]);
    }
    printf("Folha - ");
    if(no->folha) printf("SIM");
    else printf("NAO");
    printf("\n\n");
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
    else printf("\nDEU MERDA NA HORA DE SALVAR\n");
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
    int i;
    int indice;
    int nbytes;
    struct noFilaInfo aux;

    fp = fopen("arvoreMultipla.bab","rb");
    if(fp != NULL)
    {
        printf("> | Indice | NumChaves | Folha |  Chaves |   Indices   |\n");
        nbytes = 1; //atribui um valor pra passar pelo primeiro for
        for(indice = 0; nbytes != 0; indice++)
        {
            fseek(fp, indice * sizeof(struct noFilaInfo), SEEK_SET);
            nbytes = fread(&aux, sizeof(struct noFilaInfo), 1, fp);
            if(nbytes != 0)
            {
                printf("> |   %2d   |     %d     |", indice, aux.numChavesArm);
                printf("  ");
                if(aux.folha) printf("SIM");
                else printf("NAO");
                printf("  |  ");
                for(i = 0; i < NUM_ELEMENTOS; i++)
                {
                    printf("%c ",aux.elementos[i]);
                }
                printf(" | ");
                for(i = 0; i < NUM_FILHOS; i++)
                {
                    printf("%2d ", aux.indices[i]);
                }
                printf("| \n");
            }
        }

        fclose(fp);
    }
    else printf("\nNAO VAI DAR NAO! NAO ABRIU O ARQUIVO!\n");

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
                    printf("\nElemento %c Encontrado - No identificado pelo indice[%d]\n", aux.elementos[i], indice);
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
    else printf("\nDEU MERDA NA BUSCA\n");
}
