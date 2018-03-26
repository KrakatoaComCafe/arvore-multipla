#ifndef __UI_H_
#define __UI_H_

#include <stdbool.h>
#include "arvoreB.h"
#include "filaInfo.h"

void quebraLinha();
void pausarExecucao();
char* nomearArquivo();
char confirmacaoEncerramentoAtividade(char* aviso);

//main.c
void menuPrincipalHeader(char* nomeArquivo);
char menuPrincipal(bool isArvoreGerada);
char retornaLetraParaBusca();
void mensagemAlerta_elementoNaoEncontrado();
void mensagemAlerta_nomeArquivo();

//trabalho2.c
void trabalho2_menuPrincipalHeader(char* nomeArquivo, char* raizArquivo);
char trabalho2_menuPrincipal(char* nomeArquivo, char* raizArquivo, bool indiceGerado);
void trabalho2_menuIndicesHeader();
char trabalho2_menuIndiceContinuacao();
void raizEscolhida_header();
void raizEscolhida_upperBody(int numChaves, bool* isFolha, char* chaves, int* indices);
char raizEscolhida_lowerBody(char* nomeArquivo);
void insereValorNaString(char** nomeDestino, char* nomeFonte);

//arvoreB.c
void mostraConteudoNoArvoreB(struct noArvoreB *no);
void mostraFilhosNoArvoreB(struct noArvoreB* no);
void mostraNoFolhaArvoreB(struct noArvoreB* no);

//filaEnderecos.c
void informaTipoStruct_NoFilaEndereco();
void informaTipoStruct_ListaEndereco();
void mensagemErro_filaEndereco_erroArquivo();

//filaInfo.c
void mostraNoFilaInfo(struct noFilaInfo* no);
void mensagemErro_filaInfo_erroSalvarArquivo();

//noArquivo.c
void mostraNoArquivo(struct noArquivo *no);
void mostraChave(char chave);

//fileInfo.c e noArquivo.c
void leituraDeArquivo_header();
void leituraDeArquivo_corpo(int indice, int numChaves, char chaves[NUM_ELEMENTOS], int filhos[NUM_FILHOS], bool isFolha);
void mostrarElementoEPosicao(int elemento, int index);
void mensagemErro_erroAbrirArquivo(char* arquivoC);
void mensagemErro_erroBuscarArquivo(char* arquivoC);
#endif // __UI_H_
