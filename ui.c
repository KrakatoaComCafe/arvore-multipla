#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "ui.h"

//#include <stdbool.h>
//#include "arvoreB.h"
//#include "filaInfo.h"

#define GRAU (2)
#define NUM_FILHOS (GRAU * 2)
#define NUM_ELEMENTOS (NUM_FILHOS - 1)

void quebraLinha()
{
    printf("\n\n");
}

void pausarExecucao()
{
    quebraLinha();
    system("pause");
}

char* nomearArquivo()
{
    char* nomeArquivo = (char*) calloc(100,sizeof(char));
    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeArquivo);

    return nomeArquivo;
}

char confirmacaoEncerramentoAtividade(char* aviso)
{
    printf("%s", aviso);
    printf("[S] - Sim\n");
    printf("[N] - Nao\n");
    printf("\nSua escolha: ");
    fflush(stdin);
    char opcao = toupper(getchar());
    fflush(stdin);

    return opcao;
}

//***************************************
//  main.c
//***************************************

void menuPrincipalHeader(char* nomeArquivo)
{
    system("cls");
    printf(">> Arvore Multipla com Grau %d\n", GRAU);
    printf(">> Numero de Elementos: %d\n", NUM_ELEMENTOS);
    printf(">> Numero de Filhos:    %d\n", NUM_FILHOS);
    printf(">> Nome do Arquivo: ");
    if(nomeArquivo == NULL) printf("Nome ainda nao definido\n");
    else printf("%s\n",nomeArquivo);
    quebraLinha();
}

char menuPrincipal(bool isArvoreGerada)
{
    printf("\nEscolha uma opcao: \n");
    printf("[1] - Definir Nome do Arquivo: (necessario determinar extensao)\n");
    printf("[2] - Mostrar Conteudo por Ordem de Insercao no Arquivo\n");
    printf("[3] - Mostrar Elementos em Ordem Alfabetica\n");
    printf("[4] - Buscar Elemento no Arquivo\n");
    printf("[5] - Utilizar Busca por Indice\n");
    if(isArvoreGerada) printf("[X] - ArvoreB ja foi gerada com nome de arquivo arvoreMultipla.bab\n");
    else printf("[9] - Gera e Salva Arvore B mostrada na imagem img_arvore.gif\n");
    printf("[Q] - Sair");

    printf("\n\nSua escolha... ");
    char opcao = toupper(getchar());
    quebraLinha();

    return opcao;
}

char retornaLetraParaBusca()
{
    printf("Digite a letra que deve ser procurada: ");
    fflush(stdin);
    char chave = toupper(getchar());

    return chave;
}

void mensagemAlerta_elementoNaoEncontrado()
{
    printf("\nElemento nao encontrado");
}

void mensagemAlerta_nomeArquivo()
{
    quebraLinha();
    printf(">>Nome do arquivo nao definido, favor definir.");
}

//***************************************
//  trabalho2.c
//***************************************

//header do menu principal de escolhas do trablaho2
void trabalho2_menuPrincipalHeader(char* nomeArquivo, char* raizArquivo)
{
    system("cls");
    printf(">> Nome do arquivo de indices selecionado: ");
    if(nomeArquivo == NULL) printf("Arquivo ainda nao definido\n");
    else printf("%s\n", nomeArquivo);
    printf(">> Nome do arquivo da raiz selecionada:    ");
    if(raizArquivo == NULL) printf("Arquivo contendo arvore ainda nao selecionado\n");
    else printf("%s\n", raizArquivo);
    quebraLinha();
}

//corpo do menu principal de escolhas do trabalho2
char trabalho2_menuPrincipal(char* nomeArquivo, char* raizArquivo, bool indiceGerado)
{
    bool arquivo_foi_aberto = nomeArquivo != NULL;
    bool arquivo_com_a_raiz_foi_aberto = raizArquivo != NULL;

    printf("\nEscolha uma opcao: \n");
    printf("[1] - Definir nome do arquivo Indice: (necessario determinar extensao)\n");
    if(arquivo_foi_aberto) printf("[2] - Buscar as raizes no arquivo de indices\n");
    if(arquivo_com_a_raiz_foi_aberto) printf("[3] - Abrir arquivo contendo a raiz selecionada\n");

    if(indiceGerado)
        printf("[X] - Indice ja gerado com o nome indiceRaizes.inb\n");
    else
        printf("[9] - Gerar arquivo indice utilizando a raiz do arquivo arvoreMultipla.bab\n");
    printf("[Q] - Sair");

    printf("\n\nSua escolha... ");
    char opcao = toupper(getchar());
    quebraLinha();

    return opcao;
}

//header do menu de escolha de raizes
void trabalho2_menuIndicesHeader()
{
    system("cls");
    printf("  *****************************************************\n");
    printf("  *                                                   *\n");
    printf("  *           ESCOLHA UMA DAS OPCOES ABAIXO:          *\n");
    printf("  *                                                   *\n");
    printf("  *****************************************************\n");
    quebraLinha();
}
//parte inferior do menu de escolha de raizes
char trabalho2_menuIndiceContinuacao()
{
    printf("  [Q] - Voltar\n");

    printf("\n\nSua escolha... ");
    char opcao = toupper(getchar());
    quebraLinha();

    return opcao;
}

void raizEscolhida_header()
{
    system("cls");
    printf(" NumChaves | Folha |  Chaves |   Indices   |\n");
}

//parte superior do corpo do menu de confirmação de escolha de raizes
void raizEscolhida_upperBody(int numChaves, bool* isFolha, char* chaves, int* indices)
{
    printf("     %d     |", numChaves);
    printf("  ");
    if(isFolha) printf("SIM");
    else printf("NAO");
    printf("  |  ");
    int index;
    for(index = 0; index < NUM_ELEMENTOS; index++)
    {
        printf("%c ",chaves[index]);
    }
    printf(" | ");
    for(index = 0; index < NUM_FILHOS; index++)
    {
        printf("%2d ", indices[index]);
    }
    printf("| \n");
    quebraLinha();
}

//parte inferior do corpo do menu de confirmação de escolha de raizes
char raizEscolhida_lowerBody(char* nomeArquivo)
{
        printf("Este é a raiz que voce escolheu?\n");
        printf("[S] - Sim\n");
        printf("[N] - Nao\n");

        printf(">>Sua resposta: ");
        fflush(stdin);
        char opcao = toupper(getchar());
        fflush(stdin);
        quebraLinha();
        printf("\n%s", nomeArquivo);

        return opcao;
}

//reserva espaço para uma string e passa um valor para ela
void insereValorNaString(char** nomeDestino, char* nomeFonte)
{
    free(*nomeDestino);
    *nomeDestino = (char*) calloc(100,sizeof(char));
    strcpy(*nomeDestino, nomeFonte);
}

//***************************************
//  arvoreB.c
//***************************************

void mostraConteudoNoArvoreB(struct noArvoreB *no)
{
    int index;
    printf("Inicio do No: \n");
    for(index = 0; index < NUM_ELEMENTOS; index++)
    {
        printf("| Elem[%d] - %c |",index ,no->elementos[index]);
    }
    printf("\nFinal do No\n");
}

void mostraFilhosNoArvoreB(struct noArvoreB* no)
{
    int index;
    printf("\nNo Filhos\n");
    for(index = 0; index < NUM_FILHOS; index++)
    {
        printf("Filho[%d] - ",index );
        if(no->filhos[index] != NULL) printf("NAO ");
        printf("NULO\n");
    }
}

void mostraNoFolhaArvoreB(struct noArvoreB* no)
{
    if(no->folha) printf("\nNo Folha\n");
    else printf("\nNo NAO Folha\n");
}

//***************************************
//  filaEnderecos.c
//***************************************

void informaTipoStruct_NoFilaEndereco()
{
    printf("\nNo Lista Endereco: \n");
}

void informaTipoStruct_ListaEndereco()
{
    printf("\nLISTA DE ENDERECOS\n");
}

void mensagemErro_filaEndereco_erroArquivo()
{
    printf("\nErro ao tentar abrir arquivo para salvar noArquivo\n");
}

//***************************************
//  filaInfo.c
//***************************************

void mostraNoFilaInfo(struct noFilaInfo* no)
{
    int index;

    printf("No Fila: \n");
    printf("NumChavesArm - %d\n", no->numChavesArm);
    for(index = 0; index < NUM_ELEMENTOS; index++)
    {
        printf("Elemento[%d] - %c\n", index, no->elementos[index]);
    }
    for(index = 0; index < NUM_FILHOS; index++)
    {
        printf("Indice[%d] - %d\n",index, no->indices[index]);
    }
    printf("Folha - ");
    if(no->folha) printf("SIM");
    else printf("NAO");
    quebraLinha();
}

void mensagemErro_filaInfo_erroSalvarArquivo()
{
    printf("\nDEU MERDA NA HORA DE SALVAR - filaInfo.c\n");
}

void leituraDeArquivo_corpo_noFilaInfo(int indice, struct noFilaInfo* no)
{
    printf("> |   %2d   |     %d     |", indice, no->numChavesArm);
    printf("  ");
    if(no->folha) printf("SIM");
    else printf("NAO");
    printf("  |  ");
    int nodeIndex;
    for(nodeIndex = 0; nodeIndex < NUM_ELEMENTOS; nodeIndex++)
    {
        printf("%c ",no->elementos[nodeIndex]);
    }
    printf(" | ");
    for(nodeIndex = 0; nodeIndex < NUM_FILHOS; nodeIndex++)
    {
        printf("%2d ", no->indices[nodeIndex]);
    }
    printf("| \n");
}

//***************************************
//  noArquivo.c
//***************************************

void mostraNoArquivo(struct noArquivo* no)
{
    int index;
    printf("No Arquivo: \n");
    printf("NumChavesArm - %d\n", no->nroChavesArm);
    for(index = 0; index < NUM_ELEMENTOS; index++)
    {
        printf("Elemento[%d] - %c\n", index, no->chave[index]);
    }
    for(index = 0; index < NUM_FILHOS; index++)
    {
        printf("Indice[%d] - %d\n",index, no->indice[index]);
    }
    printf("Folha - ");
    if(no->folha) printf("SIM");
    else printf("NAO");
    quebraLinha();
}

void mostraChave(char chave)
{
    printf("%c", chave);
}

//***************************************
//  mais de um arquivo
//***************************************

void leituraDeArquivo_corpo(int indice, int numChaves, char chaves[NUM_ELEMENTOS], int filhos[NUM_FILHOS], bool isFolha)
{
    printf("> |   %2d   |     %d     |", indice, numChaves);
    printf("  ");
    if(isFolha) printf("SIM");
    else printf("NAO");
    printf("  |  ");
    int nodeIndex;
    for(nodeIndex = 0; nodeIndex < NUM_ELEMENTOS; nodeIndex++)
    {
        bool mostra_valor = chaves[nodeIndex] != 1;
        if(mostra_valor) printf("%c ",chaves[nodeIndex]);
        else printf("  ");
    }
    printf(" | ");
    for(nodeIndex = 0; nodeIndex < NUM_FILHOS; nodeIndex++)
    {
        bool mostra_valor = filhos[nodeIndex] != -1;
        if(mostra_valor) printf("%2d ", filhos[nodeIndex]);
        else printf(" . ");
    }
    printf("| \n");
}

void leituraDeArquivo_header()
{
    printf("> | Indice | NumChaves | Folha |  Chaves |   Indices   |\n");
}

void mostrarElementoEPosicao(int elemento, int index)
{
    printf("\nElemento %c Encontrado - No identificado pelo indice[%d]\n", elemento, index);
}

void mensagemErro_erroBuscarArquivo(char* arquivoC)
{
    printf("\nDEU MERDA NA BUSCA - %s\n", arquivoC);
}

void mensagemErro_erroAbrirArquivo(char* arquivoC)
{
    printf("\nNAO VAI DAR NAO! NAO ABRIU O ARQUIVO! - %s \n", arquivoC);
}
