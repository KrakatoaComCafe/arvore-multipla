#include "trabalho2.h"

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
        /*
            topo de menu
        */
        system("cls");
        printf(">> Nome do arquivo de indices selecionado: ");
        if(nomeArquivo == NULL) printf("Arquivo ainda nao definido\n");
        else printf("%s\n", nomeArquivo);
        printf(">> Nome do arquivo da raiz selecionada:    ");
        if(raizArquivo == NULL) printf("Arquivo contendo arvore ainda nao selecionado\n");
        else printf("%s\n", raizArquivo);
        printf("\n\n");

        /*
            op��es do menus
        */
        printf("\nEscolha uma opcao: \n");
        printf("[1] - Definir nome do arquivo Indice: (necessario determinar extensao)\n");
        if(nomeArquivo) printf("[2] - Buscar as raizes no arquivo de indices\n");
        if(raizArquivo) printf("[3] - Abrir arquivo contendo a raiz selecionada\n");
        if(indiceGerado)
            printf("[X] - Indice ja gerado com o nome indiceRaizes.inb\n");
        else
            printf("[9] - Gerar arquivo indice utilizando a raiz do arquivo arvoreMultipla.bab\n");
        printf("[Q] - Sair");

        printf("\n\nSua escolha... ");
        opcao = toupper(getchar());
        printf("\n\n");

        switch(opcao)
        {
        case 'S': //tecla S(que finaliza o programa � trocada de valor se apertado agora
            opcao = 1;
            break;
        case '1': //armazena o nome do arquivo digitado pelo usu�rio
            nomeArquivo = (char *) malloc(100*sizeof(char));
            printf("Digite o nome do arquivo: ");
            scanf("%s", nomeArquivo);
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
            printf("Tem certeza que deseja voltar? \n");
            printf("[S] - Sim \n");
            printf("[N] - Nao \n");
            printf("\nSua escolha: ");
            fflush(stdin);
            opcao = toupper(getchar());
            break;
        }
    }while(opcao != 'S');
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
        fclose(fpArvoreTrabalho1);
    }
    else
    {
        printf("\nUM ERRO INESPERADO! SOFRA!\n");
        return;
    }
}

/*
        Percorre o arquivo indice e mostra as informa��es de cada raiz
    juntamente com uma op��o para sele��o da razi desejada.
*/
char* indice_percorreArquivoSequencial(char *nomeArquivo[]) //nomeArquivo � o nome do arquivo que carrega os indices para os arquivos com arvores
{
    FILE *fp;
    int opcao;
    int i;
    int indice;
    int nbytes;
    struct noIndice aux;
    char *nomeArquivoRaiz = NULL; //armazena o nome do arquivo que contem a raiz selecionada

    fp = fopen(nomeArquivo, "rb");
    if(fp != NULL)
    {
        do
        {
            /*
                topo de menu
            */
            system("cls");
            printf("Escolha uma das opcoes abaixo: \n\n");

            /*
                op��es do menu
            */
            printf(" Opcoes | NumChaves | Folha |  Chaves |   Indices   |\n");
            //atribui valor ao nbytes para passar pela primeira checagem do "for"
            nbytes = 1;
            //percorre o arquivo em ordem sequencial e mostra eles na tela
            for(indice = 0; nbytes != 0; indice++)
            {
                //recupera um n� do arquivo
                fseek(fp, indice *sizeof(struct noIndice), SEEK_SET);
                nbytes = fread(&aux, sizeof(struct noIndice), 1, fp);
                if(nbytes != 0)
                {
                    //o monstro de printenstein para exibir o conteudo do n� e as op��es para cada
                    printf("  [%2d]  |     %d     |", indice+1, aux.raiz.nroChavesArm);
                    printf("  ");
                    if(aux.raiz.folha) printf("SIM");
                    else printf("NAO");
                    printf("  |  ");
                    for(i = 0; i < NUM_ELEMENTOS; i++)
                    {
                        printf("%c ",aux.raiz.chave[i]);
                    }
                    printf(" | ");
                    for(i = 0; i < NUM_FILHOS; i++)
                    {
                        printf("%2d ", aux.raiz.indice[i]);
                    }
                    printf("| \n");
                }//if
            }//for
            printf("  [Q] - Voltar\n");

            printf("\n\nSua escolha... ");
            opcao = toupper(getchar());
            printf("\n\n");

            /*
                A��es das possiveis escolhas
            */
            //Caso seja escolhida uma das possiveis raizes dentro das disponiveis
            //(depende da quantidade de raizes no arquivo indice)
            if(opcao > '0' && opcao <= (indice+48)) //48 � o valor 0 na tabela ASCII
            {
                //exibe a op��o escolhida e espera a confirma��o do usu�rio
                nomeArquivoRaiz = confirmaEscolhaArquivoNoRaiz(fp, opcao);
                return nomeArquivoRaiz;
            }

            switch(opcao)
            {
            case 'S': //tecla S(que finaliza o programa) � trocada de valor se for apertado agora
                opcao = 1;
                break;
            case 'Q': //op��o para sair da tela
                fflush(stdin);
                printf("Deseja retornar a tela anterior? \n");
                printf("[S] - Sim\n");
                printf("[N] - Nao\n");
                printf("\n\nSua escolha... ");
                opcao = toupper(getchar());
                printf("\n\n");
            }
        }while(opcao != 'S');
    }//if(fp != NULL)
    return nomeArquivoRaiz;
}

/*
    Exibe a raiz escolhida e espera o input de confirma��o do usu�rio
*/
//a variavel "opcao" � usada como indice e recebe o input do usu�rio
char* confirmaEscolhaArquivoNoRaiz(FILE *fp, int opcao)
{
    struct noIndice aux;
    int nbytes;
    int i;
    char *nomeArquivoRaiz;

    //passa o arquivo para a posi��o do n� selecionado
    rewind(fp);
    fseek(fp, (opcao-49) *sizeof(struct noIndice), SEEK_SET);
    nbytes = fread(&aux, sizeof(struct noIndice), 1, fp);

    //mostra o n� na tela e espera input do usu�rio
    do
    {
        system("cls");
        printf("");
        printf(" NumChaves | Folha |  Chaves |   Indices   |\n");
        printf("     %d     |", aux.raiz.nroChavesArm);
        printf("  ");
        if(aux.raiz.folha) printf("SIM");
        else printf("NAO");
        printf("  |  ");
        for(i = 0; i < NUM_ELEMENTOS; i++)
        {
            printf("%c ",aux.raiz.chave[i]);
        }
        printf(" | ");
        for(i = 0; i < NUM_FILHOS; i++)
        {
            printf("%2d ", aux.raiz.indice[i]);
        }
        printf("| \n");

        //confirma��o se este � o n�
        printf("\n\n");
        printf("Este � a raiz que voce escolheu?\n");
        printf("[S] - Sim\n");
        printf("[N] - Nao\n");

        printf(">>Sua resposta: ");
        fflush(stdin);
        opcao = toupper(getchar());
        printf("\n\n");
        printf("\n%s", aux.nomeArquivo);
    }
    while( (opcao != 'S') && (opcao != 'N'));

    if(opcao == 'S')
    {
        //passa o nome do arquivo para o ponteiro e retorna o ponteiro
        nomeArquivoRaiz = (char*) malloc(100*sizeof(char));
        strcpy(nomeArquivoRaiz, aux.nomeArquivo);
        return nomeArquivoRaiz;
    }
    else return NULL;
}
