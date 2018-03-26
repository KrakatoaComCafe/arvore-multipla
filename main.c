//#include <time.h>
//#include <stdbool.h>
#include <string.h>
#include "trabalho2.h"
#include "main.h"
#include "ui.h"

#define ENCERRAR_PROGRAMA "Deseja encerrar o programa?\n"

/**
    Para alterar o grau da �rvore � necess�rio ir at� o arquivo noArquivo.h e alterar o valor que segue a palavra defineda "GRAU".
    Para abrir um arquivo � necess�rio que ele seja colocado na pasta raiz.
    O programa oferece algumas op��es, elas s�o(em ordem que aparecem):

        1 - Escolher o nome do arquivo que ser� aberto.
            1.1 - O nome do arquivo deve conter a extens�o.

        2 - Mostra o conte�do do arquivo na ordem em que foi inserido.
            1.2 - O arquivo � inserido em ordem de n�vel.

        3 - Realiza uma busca em arquivo seguindo a l�gica In Order, mostrando APENAS as chaves em ordem alfabetica.

        4 - Busca (em arquivo) a chave passada pelo usu�rio.

        5 - Cria uma �rvore.
            5.1 - A �rvore criada tem nome definido como "arvoreMultipla.bab", o nome atual do arquivo � atualizado.
            5.2 - O conteudo da �rvore � o mesmo conteudo do �ltimo slide da Aula 09 - arvB-insercao-2.pdf
            5.3 - Uma vez gerada, ela n�o � mais apagada, � poss�vel criar a �rvore, escolher outro arquivo e ent�o, retornar a �rvore criada. (digitando o nome do arquivo)
            5.4 - Assim que for criada, a op��o de gera��o de �rvore ter� o n�mero de escolha substituido por "X", exemplificando que n�o existe sele��o para essa op��o.

        6 - Possibilita a procura do arquivo a ser aberto atrav�s de um segundo arquivo indice contendo a raiz de uma ou mais �rvores
            6.1 - Mais informa��es est�o dispon�veis no arquivo trabalho2.c

        7 - Escolha para sair do programa, essa op��o pede confirma��o antes de ser executada.

*/

/* TODO
    terminar de documentar a segunda parte do trabalho, documenta��o deve ser escrita no arquivo trabalho2.c
*/

int main()
{
    char opcao;
    bool isArvoreGerada = false;
    char *nomeArquivo = NULL;
    do
    {
        menuPrincipalHeader(nomeArquivo);
        opcao = menuPrincipal(isArvoreGerada);
        bool definido_nome_do_arquivo = nomeArquivo != NULL;
        switch(opcao)
        {

        case 'S': //tecla S(que finaliza o programa) � trocada de valor se for apertado agora
            opcao = 1;
            break;
        case '1': //pega o nome do arquivo digitado pelo usu�rio
            resetaNomeDoArquivo(&nomeArquivo);
            nomeArquivo = nomearArquivo();
            break;
        case '2': //mostra o conteudo do arquivo em formato de tabela
            if(definido_nome_do_arquivo)
            {
                noArquivo_percorreArquivoSequencial(nomeArquivo);
            }
            else mensagemAlerta_nomeArquivo();
            pausarExecucao();
            break;
        case '3': //mostra os elementos do arquivo em ordem alfabetica
            if(definido_nome_do_arquivo)
            {
                iniciaOrdemAlphabetica(nomeArquivo);
            }
            else mensagemAlerta_nomeArquivo();
            pausarExecucao();
            break;
        case '4': //busca (em arquivo) a letra passada pelo usu�rio
            if(definido_nome_do_arquivo)
            {
                int chave = retornaLetraParaBusca();

                iniciaBuscaBinaria(nomeArquivo, chave);
            }
            else mensagemAlerta_nomeArquivo();
            pausarExecucao();
            break;
        case '5': //utiliza busca de arquivo utilizando um arquivo indice
            nomeArquivo = menuTrabalho2();
            break;
        case '9':
            if(!isArvoreGerada)
            {
                isArvoreGerada = gerarArvoreB(&nomeArquivo);
            }
            break;
        case 'Q': //verifica se o usu�rio deseja sair
            opcao = confirmacaoEncerramentoAtividade(ENCERRAR_PROGRAMA);
            break;
        }
    }while(opcao != 'S');

    return 0;
}

//*********************************************
void resetaNomeDoArquivo(char** nomeArquivo)
{
    free(*nomeArquivo);
    *nomeArquivo = (char*) calloc(100, sizeof(char));
}

void iniciaOrdemAlphabetica(char* nomeArquivo)
{
    FILE* fp = fopen(nomeArquivo,"rb");
    if(fp != NULL)
    {
        noArquivo_percorreArquivoInOrderChaves(fp, 0);
        fclose(fp);
    }
    else mensagemErro_erroAbrirArquivo(__FILE__);
}

void iniciaBuscaBinaria(char* nomeArquivo, int chave)
{
    FILE* fp = fopen(nomeArquivo,"rb");
    if(fp != NULL)
    {
        chave = noArquivo_buscaBinariaArquivo(fp, chave, 0);
        if(chave == 0) mensagemAlerta_nomeArquivo();
        fclose(fp);
    }
    else mensagemErro_erroBuscarArquivo(__FILE__);
}

bool gerarArvoreB(char** nomeArquivo)
{
    free(*nomeArquivo);
    *nomeArquivo = (char*) calloc(100,sizeof(char));
    struct noArvoreB** raiz = injetaValoresArvoreB();
    //imprimeArvoreB(raiz);
    strcpy(*nomeArquivo, "arvoreMultipla.bab");
    noArquivo_salvarArvoreB(raiz,*nomeArquivo);

    return true;
}
