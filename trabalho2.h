#include "filaEnderecos.h"

struct noIndice
{
    struct noArquivo raiz;
    char nomeArquivo[100];
};

char* menuTrabalho2();
void gerarIndice();
char* indice_percorreArquivoSequencial(char *nomeArquivo[]);
char* confirmaEscolhaArquivoNoRaiz(FILE *fp, int opcao);
