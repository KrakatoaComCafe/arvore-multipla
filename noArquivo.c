#include "noArquivo.h"

//***************************************
//  inicializações

struct noArquivo *iniciaNoArquivo(char *chaves[], int *indices[], bool folha, int nroChavesArm)
{
    int i;
    struct noArquivo *no = (struct noArquivo*) malloc(sizeof(struct noArquivo));

    for(i = 0; i < NUM_ELEMENTOS; i++)
    {
        no->chave[i] = chaves[i];
        no->indice[i] = indices[i];
    }
    no->indice[i] = indices[i];
    no->folha = folha;
    no->nroChavesArm = nroChavesArm;

    return no;
};

//***************************************
//  inserções

//***************************************
//  remoções

//***************************************
//  auxiliares

void imprimeNoArquivo(struct noArquivo *no)
{
    int i;
    if(no == NULL) return;

    printf("No Arquivo: \n");
    printf("NumChavesArm - %d\n", no->nroChavesArm);
    for(i = 0; i < NUM_ELEMENTOS; i++)
    {
        printf("Elemento[%d] - %c\n", i, no->chave[i]);
    }
    for(i = 0; i < NUM_FILHOS; i++)
    {
        printf("Indice[%d] - %d\n",i, no->indice[i]);
    }
    printf("Folha - ");
    if(no->folha) printf("SIM");
    else printf("NAO");
    printf("\n\n");
}

//passa (em arquivo) pela lógica In Order mostrando somente as chaves em ordem alfabetica
void noArquivo_percorreArquivoInOrderChaves(FILE *fp, int indice)
{
    int i;
    int nbytes;
    struct noArquivo aux;
    fseek(fp, indice * sizeof(struct noArquivo), SEEK_SET);
    nbytes = fread(&aux, sizeof(struct noArquivo), 1, fp);
    if(nbytes != 0)
    {
        for(i = 0 ; i < NUM_FILHOS; i++)
        {
            if(aux.indice[i] != 0) noArquivo_percorreArquivoInOrderChaves(fp, aux.indice[i]);

            if(i < NUM_ELEMENTOS && aux.chave[i] >= 'A' && aux.chave[i] <= 'Z') printf("%c", aux.chave[i]);
        }
    }
}

//percorre todos os nós da árvore (pré inseridos em ordem de nível)
void noArquivo_percorreArquivoSequencial(char *nomeArquivo[])
{
    FILE *fp;
    int i;
    int indice;
    int nbytes;
    struct noArquivo aux;

    fp = fopen(nomeArquivo,"rb");
    if(fp != NULL)
    {
        printf("> | Indice | NumChaves | Folha |  Chaves |   Indices   |\n");
        nbytes = 1; //atribui um valor pra passar pelo primeiro for
        for(indice = 0; nbytes != 0; indice++)
        {
            fseek(fp, indice * sizeof(struct noArquivo), SEEK_SET);
            nbytes = fread(&aux, sizeof(struct noArquivo), 1, fp);
            if(nbytes != 0)
            {
                printf("> |   %2d   |     %d     |", indice, aux.nroChavesArm);
                printf("  ");
                if(aux.folha) printf("SIM");
                else printf("NAO");
                printf("  |  ");
                for(i = 0; i < NUM_ELEMENTOS; i++)
                {
                    printf("%c ",aux.chave[i]);
                }
                printf(" | ");
                for(i = 0; i < NUM_FILHOS; i++)
                {
                    printf("%2d ", aux.indice[i]);
                }
                printf("| \n");
            }
        }

        fclose(fp);
    }
    else printf("\nNAO VAI DAR NAO! NAO ABRIU O ARQUIVO!\n");

}

//realiza busca de um elemento chave na árvore em arquivo
int noArquivo_buscaBinariaArquivo(FILE *fp, int chave, int indice)
{
    int i;
    int nbytes;
    struct noArquivo aux;

    if(fp != NULL)
    {
        fseek(fp, indice*sizeof(struct noArquivo), SEEK_SET);
        nbytes = fread(&aux, sizeof(struct noArquivo), 1, fp);
        if(nbytes != 0)
        {
            for(i = 0; i < aux.nroChavesArm; i++)
            {
                if(aux.chave[i] == chave)
                {
                    printf("\nElemento %c Encontrado - No identificado pelo indice[%d]\n", aux.chave[i], indice);
                    return 1;
                }
            }

            for(i = 0; i < aux.nroChavesArm; i++)
            {
                if(chave < aux.chave[i])
                    return noArquivo_buscaBinariaArquivo(fp, chave, aux.indice[i]);
            }
            if(i == aux.nroChavesArm) return noArquivo_buscaBinariaArquivo(fp, chave, aux.indice[i]);
        }
        else return 0;
    }
    else printf("\nDEU MERDA NA BUSCA\n");
}
