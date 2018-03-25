#include "filaEnderecos.h"

//***************************************
//  inicializações

struct filaEndereco *iniciaFilaEndereco()
{
    struct filaEndereco *fila = (struct filaEndereco*) malloc(sizeof(struct filaEndereco));
    fila->inicio = NULL;
    fila->fim = NULL;

    return fila;
}

struct noFilaEndereco *iniciaNoFilaEndereco(struct noArvoreB *no)
{
    struct noFilaEndereco *noEndereco = (struct noFilaEndereco*) malloc(sizeof(struct noFilaEndereco));
    noEndereco->enderecoNoArvore = no;
    noEndereco->prox = NULL;

    return noEndereco;
}

//***************************************
//  inserções

void insereNoFilaEnderecoFinal(struct filaEndereco *fila, struct noArvoreB *no)
{
    struct noFilaEndereco *novoNo = iniciaNoFilaEndereco(no);

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

void imprimeNoFilaEndereco(struct noFilaEndereco *no)
{
    if(no == NULL) return;

    printf("\nNo Lista Endereco: \n");
    imprimeNoArvoreB(no);
}

void imprimeFilaEndereco(struct filaEndereco *fila)
{
    struct noFilaEndereco *aux;
    if(fila->inicio == NULL) return;

    aux = fila->inicio;
    printf("\nLISTA DE ENDERECOS\n");
    //percorre a fila
    while(aux != NULL)
    {
        imprimeNoFilaEndereco(aux);
        aux = aux->prox;
    }
}

struct filaInfo *arvoreB_to_filaInfo(struct noArvoreB **raiz)
{
    struct filaInfo *fInfo;
    struct filaEndereco *fEndereco;
    struct noArvoreB *auxArvoreB;
    struct noFilaInfo *auxInfo;
    struct noFilaEndereco *auxEndereco;
    int i;
    int elementos[NUM_ELEMENTOS];
    int indices[NUM_FILHOS];
    int contagemIndice;

    if(*raiz == NULL) return NULL;

    contagemIndice = 1;
    fInfo = iniciaFilaInfo();
    fEndereco = iniciaFilaEndereco();

    //insere a raiz na fila de endereços
    auxArvoreB = *raiz;
    insereNoFilaEnderecoFinal(fEndereco, auxArvoreB);

    //percorre a fila enquanto insere novos elementos nela
    auxEndereco = fEndereco->inicio;
    while(auxEndereco != NULL)
    {
        auxArvoreB = auxEndereco->enderecoNoArvore;
        //percorre os filhos do nó
        for(i = 0; i < NUM_FILHOS; i++)
        {
            //nó possui filho na i-ésima posição
            if(auxArvoreB->filhos[i] != NULL)
            {
                //insere o endereço do nó filho na lista de próximos nós da árvore a serem visitados
                insereNoFilaEnderecoFinal(fEndereco, auxArvoreB->filhos[i]);
                indices[i] = contagemIndice++;
            }
            else
            {
                indices[i] = -1;
            }

            if(i < NUM_ELEMENTOS) elementos[i] = auxArvoreB->elementos[i];
        }

        //insere o nó na fila de informação para ser salvo
        insereNoFilaInfoFinal(fInfo, &elementos, &indices, auxArvoreB->folha, auxArvoreB->numElementos);
        auxEndereco = auxEndereco->prox;
    }

    return fInfo;
}

void noArquivo_salvarArvoreB(struct noArvoreB **raiz, char *nomeArquivo[])
{
    FILE *fp;
    struct noArquivo *auxArquivo;
    struct filaEndereco *fEndereco;
    struct noArvoreB *auxArvoreB;
    struct noFilaEndereco *auxEndereco;
    int i;
    int chave[NUM_ELEMENTOS];
    int indice[NUM_FILHOS];
    int contagemIndice;

    if(*raiz == NULL) return;

    fp = fopen(nomeArquivo, "wb");
    if(fp != NULL)
    {
        contagemIndice = 1;
        //fInfo = iniciaFilaInfo();
        fEndereco = iniciaFilaEndereco();

        //insere a raiz na fila de endereços
        auxArvoreB = *raiz;
        insereNoFilaEnderecoFinal(fEndereco, auxArvoreB);

        //percorre a fila enquanto insere novos elementos nela
        auxEndereco = fEndereco->inicio;

        while(auxEndereco != NULL)
        {
            auxArvoreB = auxEndereco->enderecoNoArvore;
            //percorre os filhos do nó
            for(i = 0; i < NUM_FILHOS; i++)
            {
                //nó possui filho na i-ésima posição
                if(auxArvoreB->filhos[i] != NULL)
                {
                    //insere o endereço do nó filho na lista de próximos nós da árvore a serem visitados
                    insereNoFilaEnderecoFinal(fEndereco, auxArvoreB->filhos[i]);
                    indice[i] = contagemIndice++;
                }
                else
                {
                    indice[i] = -1;
                }

                if(i < NUM_ELEMENTOS) chave[i] = auxArvoreB->elementos[i];
            }

            //atribui valor ao nó que vai ser salvo e salva no arquivo
            auxArquivo = iniciaNoArquivo(&chave, &indice, auxArvoreB->folha, auxArvoreB->numElementos);
            imprimeNoArquivo(auxArquivo);
            fwrite(auxArquivo, sizeof(struct noArquivo), 1, fp);
            //pega o próximo nó da árvore
            auxEndereco = auxEndereco->prox;
        }//while
        fclose(fp);
    }//abre arquivo
    else printf("\nErro ao tentar abrir arquivo para salvar noArquivo\n");
}
