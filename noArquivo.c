#include "noArquivo.h"
#include "ui.h"

//***************************************
//  inicializações

struct noArquivo *iniciaNoArquivo(char *chaves, int *indices, bool folha, int nroChavesArm)
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
    if(no == NULL) return;
    mostraNoArquivo(no);
}

//passa (em arquivo) pela lógica In Order mostrando somente as chaves em ordem alfabetica
void noArquivo_percorreArquivoInOrderChaves(FILE *fp, int indice)
{
    int index;
    int nbytes;
    struct noArquivo aux;
    fseek(fp, indice * sizeof(struct noArquivo), SEEK_SET);
    nbytes = fread(&aux, sizeof(struct noArquivo), 1, fp);
    if(nbytes != 0)
    {
        for(index = 0 ; index < NUM_FILHOS; index++)
        {
            if(aux.indice[index] != 0) noArquivo_percorreArquivoInOrderChaves(fp, aux.indice[index]);

            bool dentro_do_no = index < NUM_ELEMENTOS;
            bool chave_eh_uma_letra = aux.chave[index] >= 'A' && aux.chave[index] <= 'Z';

            if(dentro_do_no && chave_eh_uma_letra) mostraChave(aux.chave[index]);;
        }
    }
}

//percorre todos os nós da árvore (pré inseridos em ordem de nível)
void noArquivo_percorreArquivoSequencial(char *nomeArquivo)
{
    FILE *fp;
    int indice;
    int nbytes;
    struct noArquivo aux;

    fp = fopen(nomeArquivo,"rb");
    if(fp != NULL)
    {
        leituraDeArquivo_header();
        nbytes = 1; //atribui um valor pra passar pelo primeiro for
        for(indice = 0; nbytes != 0; indice++)
        {
            fseek(fp, indice * sizeof(struct noArquivo), SEEK_SET);
            nbytes = fread(&aux, sizeof(struct noArquivo), 1, fp);
            if(nbytes != 0)
            {
                leituraDeArquivo_corpo(indice, aux.nroChavesArm, aux.chave, aux.indice, aux.folha);
            }
        }

        fclose(fp);
    }
    else mensagemErro_erroAbrirArquivo(__FILE__);

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
                    mostrarElementoEPosicao(aux.chave[i], indice);
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
    else mensagemErro_erroBuscarArquivo(__FILE__);

    return (int)NULL;
}
