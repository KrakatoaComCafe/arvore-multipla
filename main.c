#include <time.h>
#include "trabalho2.h"

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

    int i;
    struct noArvoreB **r01;

    FILE *fp;
    int opcao;
    int chave;
    bool arvoreGerada = false;
    char *nomeArquivo = NULL;
    do
    {
        system("cls");
        printf(">> Arvore Multipla com Grau %d (grau pode ser alterado em noArquivo.h)\n", GRAU);
        printf(">> Numero de Elementos: %d\n", NUM_ELEMENTOS);
        printf(">> Numero de Filhos:    %d\n", NUM_FILHOS);
        printf(">> Nome do Arquivo: ");
        if(nomeArquivo == NULL) printf("Nome ainda nao definido\n");
        else printf("%s\n",nomeArquivo);
        printf("\n\n");

        printf("\nEscolha uma opcao: \n");
        printf("[1] - Definir Nome do Arquivo: (necessario determinar extensao)\n");
        printf("[2] - Mostrar Conteudo por Ordem de Insercao no Arquivo\n");
        printf("[3] - Mostrar Elementos em Ordem Alfabetica\n");
        printf("[4] - Buscar Elemento no Arquivo\n");
        printf("[5] - Utilizar Busca por Indice\n");
        if(arvoreGerada) printf("[X] - ArvoreB ja foi gerada com nome de arquivo arvoreMultipla.bab\n");
        else printf("[9] - Gera e Salva Arvore B do ultimo slide de arvB-insercao-2.pdf da Aula 09\n");
        printf("[Q] - Sair");

        printf("\n\nSua escolha... ");
        opcao = toupper(getchar());
        printf("\n\n");
        switch(opcao)
        {

        case 'S': //tecla S(que finaliza o programa) � trocada de valor se for apertado agora
            opcao = 1;
            break;
        case '1': //pega o nome do arquivo digitado pelo usu�rio
            nomeArquivo = (char*) malloc(100*sizeof(char));
            printf("Digite o nome do arquivo: ");
            scanf("%s", nomeArquivo);
            break;
        case '2': //mostra o conteudo do arquivo em formato de tabela
            if(nomeArquivo != NULL)
            {
                noArquivo_percorreArquivoSequencial(nomeArquivo);
            }
            else printf("\n\n>>Nome do arquivo nao definido.");
            printf("\n\n");
            system("PAUSE");
            break;
        case '3': //mostra os elementos do arquivo em ordem alfabetica
            if(nomeArquivo != NULL)
            {
                fp = fopen(nomeArquivo,"rb");
                if(fp != NULL)
                {
                    noArquivo_percorreArquivoInOrderChaves(fp, 0);
                    fclose(fp);
                }
                else printf("\n\nErro ao abrir o arquivo!\n\n");
            }
            else printf("\n\n>>Nome do arquivo nao definido.");
            printf("\n\n");
            system("PAUSE");
            break;
        case '4': //busca (em arquivo) a letra passada pelo usu�rio
            if(nomeArquivo != NULL)
            {
                printf("Digite a letra que deve ser procurada: ");
                fflush(stdin);
                chave = toupper(getchar());

                fp = fopen(nomeArquivo,"rb");
                if(fp != NULL)
                {
                    chave = noArquivo_buscaBinariaArquivo(fp, chave, 0);
                    if(chave == 0) printf("\nElemento nao encontrado");
                    fclose(fp);
                }
                else printf("\n\nErro ao abrir o arquivo!\n\n");
            }
            printf("\n\n");
            system("PAUSE");
            break;
        case '5': //utiliza busca de arquivo utilizando um arquivo indice
            nomeArquivo = menuTrabalho2();
            break;
        case '9':
            if(!arvoreGerada)
            {
                r01 = injetaValoresArvoreB();
                nomeArquivo = "arvoreMultipla.bab";
                noArquivo_salvarArvoreB(r01,nomeArquivo);
                //imprimeArvoreB(r01);
                arvoreGerada = true;
                printf("\n\n");
                system("PAUSE");
            }
            break;
        case 'Q': //verifica se o usu�rio deseja sair
            printf("Tem certeza que deseja sair? \n");
            printf("[S] - Sim\n");
            printf("[N] - Nao\n");
            printf("\nSua escolha: ");
            fflush(stdin);
            opcao = toupper(getchar());
            break;
        }
    }while(opcao != 'S');



    printf("\n\nHello world!\n");
    return 0;
}
