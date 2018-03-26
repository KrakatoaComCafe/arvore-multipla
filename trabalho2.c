#include <string.h>
#include "trabalho2.h"
#include "ui.h"

#define MENU_ANTERIOR "Deseja voltar para o menu anterio?\n"

/**
        Este arquivo e trabalho2.h s�o tem a fun��o de utilizar um arquivo que cont�m uma ou v�rias raizes de diferentes
    �rvores, as raizes servem como indice para recuperar o nome do arquivo que cont�m a �rvore da raiz selecionada.

        A segunda parte do programa oferece algumas op��es, elas s�o(em ordem que aparecem):

        1 - Escolher o nome do arquivo que ser� aberto.
            1.1 - O nome do arquivo deve conter a extens�o.

        2 - Gerar altomaticamente o arquivo indice
            2.1 - O arquivo � gerado utilizando como indice a raiz da �rvore do arquivo arvoreMultipla.bab
            2.2 - Uma vez gerado, essa op��o deixa de ser selecion�vel.
            2.3 - O nome do arquivo indice � atualizado no programa.

        3 - Faz a busca das raizes no arquivo indice selecionado.
            3.1 - Um nome de arquivo deve ser inserido para essa op��o se tornar selecion�vel.
            3.2 - Um segundo menu com todas as raizes do arquivo e a op��o de voltar � exibido se essa op��o for selecionada
                3.2.1 - Ap�s selecionar uma raiz � pedido a confirma��o da raiz selecionada.
                3.2.1 - O nome do arquivo contendo a �rvore � atualizado.

        4 - Retorna para a tela anterior o nome do arquivo que cont�m a �rvore referente a raiz selecionada.
            4.1 - Uma raiz deve ser selecionada para essa op��o se tornar selecion�vel.

        5 - Retorna para a tela anterior do programa, essa op��o pede confirma��o antes de ser executada.
            5.1 - Nenhum valor � retornado se esta op��o for selecionada.
*/

/*
    Menu para escolha do arquivo indice e escolha do arquivo �rvore
*/
char* menuTrabalho2()
{
    char *nomeArquivo = NULL;
    char *raizArquivo = NULL;
    bool indiceGerado = false;
    int opcao;

    do
    {
        trabalho2_menuPrincipalHeader(nomeArquivo, raizArquivo);
        /*
            op��es do menus
        */
        opcao = trabalho2_menuPrincipal(nomeArquivo, raizArquivo, indiceGerado);

        switch(opcao)
        {
        case 'S': //tecla S(que finaliza o programa � trocada de valor se apertado agora
            opcao = 1;
            break;
        case '1': //armazena o nome do arquivo digitado pelo usu�rio
            nomeArquivo = nomearArquivo();
            break;
        case '2': //mostra as raizes dentro do arquivo indice
            if(nomeArquivo)
                raizArquivo = indice_percorreArquivoSequencial(nomeArquivo);
            break;
        case '3': //retorna o nome do arquivo
            if(raizArquivo)
                return raizArquivo;
            break;
        case '9': //gera um arquivo indice
            if(!indiceGerado)
            {
                gerarIndice();
                nomeArquivo = "indiceRaizes.inb";
                indiceGerado = true;
            }
            break;
        case 'Q': //verifica se o usu�rio deseja voltar
            opcao = confirmacaoEncerramentoAtividade(MENU_ANTERIOR);
            break;
        }
    }while(opcao != 'S');

    return raizArquivo;
}

/*
    Gera um arquivo para servir como indice
    O arquivo gerado possui a raiz da �rvore de outro arquivo
*/
void gerarIndice()
{
    FILE *fpArvoreTrabalho1;
    FILE *fpIndiceTrabalho2;
    struct noArquivo auxArquivo;
    struct noIndice auxIndice;
    int nbytes;
    int i;

    //abre o arquivo que contem a �rvore
    fpArvoreTrabalho1 = fopen("arvoreMultipla.bab","rb");
    if(fpArvoreTrabalho1 != NULL)
    {
        //abre o arquivo indice
        fpIndiceTrabalho2 = fopen("indiceRaizes.inb","wb");
        //l� a raiz da �rvore
        nbytes = fread(&auxArquivo, 1, sizeof(struct noArquivo), fpArvoreTrabalho1);

        //caso seja lido alguma informa��o, ela � passada para o n� a ser salvo
        if(nbytes)
        {
            auxIndice.raiz = auxArquivo;
            auxIndice.raiz.nroChavesArm = auxArquivo.nroChavesArm;
            auxIndice.raiz.folha = auxArquivo.folha;
            for(i = 0; i < NUM_ELEMENTOS; i++)
            {
                auxIndice.raiz.chave[i] = auxArquivo.chave[i];
                auxIndice.raiz.indice[i] = auxArquivo.indice[i];
            }
            auxIndice.raiz.indice[i] = auxArquivo.indice[i];
            strcpy(auxIndice.nomeArquivo, "arvoreMultipla.bab");

            //escreve a raiz no arquivo indice
            fwrite(&auxIndice, sizeof(struct noIndice), 1, fpIndiceTrabalho2);
        }

        fclose(fpIndiceTrabalho2);
    }
    else mensagemErro_erroAbrirArquivo(__FILE__);

    fclose(fpArvoreTrabalho1);
}

/*
        Percorre o arquivo indice e mostra as informa��es de cada raiz
    juntamente com uma op��o para sele��o da razi desejada.
*/
char* indice_percorreArquivoSequencial(char *nomeArquivo) //nomeArquivo � o nome do arquivo que carrega os indices para os arquivos com arvores
{
    FILE* fp;
    char *nomeArquivoRaiz = NULL; //armazena o nome do arquivo que contem a raiz selecionada

    fp = fopen(nomeArquivo, "rb");
    if(fp != NULL)
    {
        char opcao;
        do
        {
            trabalho2_menuIndicesHeader();
            leituraDeArquivo_header();
            //atribui valor ao nbytes para passar pela primeira checagem do "for"
            int nbytes = 1;
            int indice;
            for(indice = 0; nbytes != 0; indice++)
            {
                struct noIndice aux;
                //recupera um n� do arquivo
                fseek(fp, indice *sizeof(struct noIndice), SEEK_SET);
                nbytes = fread(&aux, sizeof(struct noIndice), 1, fp);
                if(nbytes != 0)
                {
                    leituraDeArquivo_corpo((indice + 1), aux.raiz.nroChavesArm, aux.raiz.chave, aux.raiz.indice, aux.raiz.folha);

                }
            }
            opcao = trabalho2_menuIndiceContinuacao();

            /*
                A��es das possiveis escolhas
            */
            bool escolheu_uma_das_raizes = opcao > '0' && opcao <= (indice + '0'); //48 � o valor 0 na tabela ASCII
            if(escolheu_uma_das_raizes) {
                nomeArquivoRaiz = confirmaEscolhaArquivoNoRaiz(fp, opcao);
                fclose(fp);
                return nomeArquivoRaiz;
            }

            switch(opcao)
            {
            case 'S': //tecla S(que finaliza o programa) � trocada de valor se for apertado agora
                opcao = 1;
                break;
            case 'Q':
                opcao = confirmacaoEncerramentoAtividade(MENU_ANTERIOR);
            }
        }while(opcao != 'S');
    }//if(fp != NULL)
    fclose(fp);
    return nomeArquivoRaiz;
}

/*
    Exibe a raiz escolhida e espera o input de confirma��o do usu�rio
*/
//a variavel "opcao" � usada como indice e recebe o input do usu�rio
char* confirmaEscolhaArquivoNoRaiz(FILE *fp, int opcao)
{
    struct noIndice aux;
    char *nomeArquivoRaiz;

    //passa o arquivo para a posi��o do n� selecionado
    rewind(fp);
    fseek(fp, (opcao-49) *sizeof(struct noIndice), SEEK_SET);
    /*int nbytes = */fread(&aux, sizeof(struct noIndice), 1, fp);

    //mostra o n� na tela e espera input do usu�rio
    do
    {
        raizEscolhida_header();
        raizEscolhida_upperBody(aux.raiz.nroChavesArm, &aux.raiz.folha, &(aux.raiz.chave[0]), &(aux.raiz.indice[0]));
        opcao = raizEscolhida_lowerBody(aux.nomeArquivo);

    }
    while( (opcao != 'S') && (opcao != 'N'));

    if(opcao == 'S'){
        //passa o nome do arquivo para o ponteiro e retorna o ponteiro
        insereValorNaString(&nomeArquivoRaiz, &(aux.nomeArquivo[0]));
        return nomeArquivoRaiz;
    }
    else return NULL;
}
