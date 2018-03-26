//#include <time.h>
//#include <stdbool.h>
#include <string.h>
#include "trabalho2.h"
#include "main.h"
#include "ui.h"

#define ENCERRAR_PROGRAMA "Deseja encerrar o programa?\n"

/**
    Para alterar o grau da árvore é necessário ir até o arquivo noArquivo.h e alterar o valor que segue a palavra defineda "GRAU".
    Para abrir um arquivo é necessário que ele seja colocado na pasta raiz.
    O programa oferece algumas opções, elas são(em ordem que aparecem):

        1 - Escolher o nome do arquivo que será aberto.
            1.1 - O nome do arquivo deve conter a extensão.

        2 - Mostra o conteúdo do arquivo na ordem em que foi inserido.
            1.2 - O arquivo é inserido em ordem de nível.

        3 - Realiza uma busca em arquivo seguindo a lógica In Order, mostrando APENAS as chaves em ordem alfabetica.

        4 - Busca (em arquivo) a chave passada pelo usuário.

        5 - Cria uma árvore.
            5.1 - A árvore criada tem nome definido como "arvoreMultipla.bab", o nome atual do arquivo é atualizado.
            5.2 - O conteudo da árvore é o mesmo conteudo do último slide da Aula 09 - arvB-insercao-2.pdf
            5.3 - Uma vez gerada, ela não é mais apagada, é possível criar a árvore, escolher outro arquivo e então, retornar a árvore criada. (digitando o nome do arquivo)
            5.4 - Assim que for criada, a opção de geração de árvore terá o número de escolha substituido por "X", exemplificando que não existe seleção para essa opção.

        6 - Possibilita a procura do arquivo a ser aberto através de um segundo arquivo indice contendo a raiz de uma ou mais árvores
            6.1 - Mais informações estão disponíveis no arquivo trabalho2.c

        7 - Escolha para sair do programa, essa opção pede confirmação antes de ser executada.

*/

/* TODO
    terminar de documentar a segunda parte do trabalho, documentação deve ser escrita no arquivo trabalho2.c
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

        case 'S': //tecla S(que finaliza o programa) é trocada de valor se for apertado agora
            opcao = 1;
            break;
        case '1': //pega o nome do arquivo digitado pelo usuário
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
        case '4': //busca (em arquivo) a letra passada pelo usuário
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
        case 'Q': //verifica se o usuário deseja sair
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
