/*****************************************************************//**
 * \file   Gestor.c
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   March 2023
 *********************************************************************/

#include <stdio.h>
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "Gestor.h"
#pragma warning( disable : 4996 )
#define MAXCHAR 500

#pragma region M�todos Gestores
 /**
  * @brief Cria Gestor.
  * @author Victor Destefani
  * @param cod
  * @param nome
  * @param saldo
  * @param nif
  * @param morada
  * @return
  */
Gestor* CriaGestor(int cod, char* nome, float saldo, long int nif, char* morada, bool* res) {
	*res = false;

	Gestor* novoGestor;
	novoGestor = (Gestor*)malloc(sizeof(Gestor)); //Cria espa�o de mem�ria

	if (novoGestor == NULL) { //Verifica se a aloca��o de mem�ria foi bem sucedida 
		printf("Erro ao alocar memoria para novo gestor.\n");
		return NULL;
	}
	novoGestor->cod = cod;
	strcpy(novoGestor->nome, nome);
	novoGestor->saldo = saldo;
	novoGestor->nif = nif;
	strcpy(novoGestor->morada, morada);
	novoGestor->next = NULL;
	*res = true;
	return novoGestor;
}

/**
 * @brief Insere Gestor no Inicio.
 * @author Victor Destefani
 * @param novo
 * @param inicio
 * @return
 */
Gestor* InsertGestorInicio(Gestor* novo, Gestor* inicio, bool* res) {
	*res = false;
	if (novo == NULL) /* Verifica se ponteiro para o novo gestor � nulo, logo como n�o h� nada para ser inserido,
					   retorna o ponteiro para o inicio da lista */
	{
		printf("Erro: novo gestor e nulo\n");
		return inicio;
	}
	if (inicio == NULL) // Verifica se a lista est� vazia, se estiver, o novo gestor torna-se o primeiro n� da lista
	{
		inicio = novo;
	}
	else // Caso contr�rio, insere o novo gestor no in�cio da lista
	{
		novo->next = inicio;
		inicio = novo;
		*res = true;
	}
	return inicio; // retorna o ponteiro para o in�cio da lista atualizada.
}

/**
 * @brief Insere Gestor no Fim.
 * @author Victor Destefani
 * @param novo
 * @param inicio
 * @return
 */
Gestor* InsertGestorFim(Gestor* novo, Gestor* inicio, bool* res) {
	*res = false;
	if (inicio == NULL) // Verifica se a lista est� vazia, se estiver, o novo gestor torna-se o primeiro n� da lista
	{
		inicio = novo;
	}
	else
	{
		Gestor* aux = inicio;
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = novo;
		*res = true;
	}
	novo->next = NULL;
	return inicio;
}

/**
 * @brief Verifica Gestor Duplicado.
 * @author Victor Destefani
 * @param cod
 * @param nif
 * @param inicio
 * @param
 * @return
 */
Gestor* VerificaGestorDuplicado(int cod, int long nif, Gestor* inicio, bool* duplicado) {
	*duplicado = false;

	if (inicio == NULL) // Verifica se a lista encadeada est� vazia (inicio == NULL), caso esteja retorna NULL, indicando que n�o h� clientes duplicados.
	{
		return NULL; // Caso n�o encontre nenhum gestor com o mesmo c�digo e nif, retorna NULL.
	}

	Gestor* aux = inicio;
	while ((aux != NULL) && (aux->cod != cod) && (aux->nif != nif)) // percorre a lista para verificar os campos cod e nif e enquanto ele nao encontrar aux toma valor de aux campo next
	{
		aux = aux->next;
	}

	if ((aux != NULL) && (aux->cod == cod) && (aux->nif == nif)) {
		*duplicado = true;
	}
	return aux; // Ao fim retorna o valor de aux
}

/**
 * @brief Insere Gestor na Lista.
 * @author Victor Destefani
 * @param novo
 * @param inicio
 * @param
 * @return
 */
Gestor* InsertGestorLista(Gestor* novo, Gestor* inicio, bool* res) {
	bool gestorDuplicado = false; // vari�vel bool para armazenar se h� gestor duplicado
	*res = false;
	if (inicio == NULL)
	{
		inicio = novo;
	}
	else {
		//Verificar se j� existe repetido
		if (VerificaGestorDuplicado(novo->cod, novo->nif, inicio, &gestorDuplicado) != NULL) {
			return inicio;
		}
		if (!gestorDuplicado) {
			if (inicio == NULL) {
				inicio = novo;
			}
			else {
				Gestor* atual = inicio;
				Gestor* anterior = NULL;

				//procurar a posicao correta, e ordena pelo cod!!!!
				while (atual != NULL && atual->cod < novo->cod) {
					anterior = atual;
					atual = atual->next;
				}
				if (anterior == NULL) {  //Insere no in�cio
					novo->next = inicio;
					inicio = novo;
				}
				else if (atual == NULL) { //Insere no fim
					anterior->next = novo;
					novo->next = NULL;
				}
				else {  //Insere no meio
					anterior->next = novo;
					novo->next = atual;
				}
				*res = true;
			}
		}
		return inicio;
	}
}

/**
 * @brief Altera dados Gestor.
 * @author Victor Destefani
 * @param cod
 * @param nome
 * @param saldo
 * @param nif
 * @param morada
 * @param novo
 * @param inicio
 * @return
 */
Gestor* AlteraCampoGestor(int cod, char* nome, float saldo, long int nif, char* morada, Gestor* novo, Gestor* inicio, bool* res) {
	*res = false;

	// Verifica se a lista est� vazia
	if (inicio == NULL)
	{
		printf("Erro: lista vazia\n");
		*res = false;
		return NULL;
	}
	// Cria um ponteiro auxiliar para percorrer a lista
	Gestor* aux = inicio;

	// Percorre a lista at� encontrar o ve�culo com o c�digo e tipo informado
	while ((aux != NULL) && (aux->cod != cod) && (aux->nif != nif))
	{
		aux = aux->next;
	}

	// Se n�o encontrou o cliente com o c�digo informado, retorna a lista original
	if ((aux == NULL) || (aux->nif != nif)) {
		*res = false;
		return inicio;
	}

	// Altera os campos do ve�culo encontrado com as informa��es fornecidas
	aux->cod = novo->cod;
	strcpy(aux->nome, novo->nome);
	aux->saldo = novo->saldo;
	aux->nif = novo->nif;
	strcpy(aux->morada, novo->morada);

	// Libera a mem�ria alocada para o cliente novo
	free(novo);
	*res = true;
	// Retorna a lista atualizada
	return inicio;
}

/**
 * @brief Remove Gestor.
 * @author Victor Destefani
 * @param cod
 * @param nif
 * @param inicio
 * @param
 * @return
 */
Gestor* RemoveGestor(int cod, long int nif, Gestor* inicio, bool* res) {
	*res = false;
	// Verifica se o in�cio � nulo (lista vazia)
	if (inicio == NULL) {
		return NULL; // N�o h� nenhum ve�culo para ser removido
	}

	// Inicializa ponteiros auxiliares
	Gestor* noAnterior = inicio;
	Gestor* noAtual = inicio;

	// Verifica se o n� a ser removido � a cabe�a da lista
	if ((inicio != NULL) && (inicio->cod == cod)) {
		noAnterior = noAnterior->next;
		free(inicio);
		inicio = noAnterior;
	}
	else
	{
		while ((noAtual != NULL) && (noAtual->cod != cod) && (noAtual->nif != nif)) { // Procura pelo cliente a ser removido
			noAnterior = noAtual; // avan�a o ponteiro auxAnt para o pr�ximo n�
			noAtual = noAtual->next; // avan�a o ponteiro auxProx para o pr�ximo n�
		}
		if ((noAtual == NULL) || (noAnterior->next == NULL) || (noAnterior->cod != cod)) { // N�o foi encontrado nenhum ve�culo com o c�digo e tipo especificados
			return inicio;
		}
		// Remove o ve�culo encontrado
		noAnterior->next = noAtual->next; // auxAnt campo next passa a conter o valor de auxProx campo next!
		free(noAtual); // liberta a mem�ria que � removida
		*res = true;
	}
	return inicio; // Retorna head
}

/**
 * @brief L� ficheiro gestores.txt.
 * @author Victor Destefani
 * @param fileName
 * @return
 */
bool LerDadosGestor(char fileName[]) {
	char row[MAXCHAR];
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror("Erro ao abrir o arquivo para leitura");
		return false;
	}

	while (fgets(row, MAXCHAR, fp) != NULL) {
		printf("Gestores: %s", row);
	}

	fclose(fp);
	return true;
}

/**
 * @brief Grava ficheiro em bin�rio.
 * @author Victor Destefani
 * @param nomeFicheiro
 * @param inicio
 * @return
 */
bool GravarGestorBin(char* nomeFicheiro, Gestor* inicio, bool* res) {
	FILE* fp;

	if (inicio == NULL) {
		return false;
	}

	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) {
		perror("Erro ao abrir arquivo para escrita");
		return false;
	}

	//grava 1 registo de cada vez no ficheiro
	GestoresFicheiro aux;
	Gestor* auxGestor = inicio;
	while (auxGestor) {
		aux.cod = auxGestor->cod;
		strcpy(aux.nome, auxGestor->nome);
		aux.saldo = auxGestor->saldo;
		aux.nif = auxGestor->nif;
		strcpy(aux.morada, auxGestor->morada);

		fwrite(auxGestor, sizeof(GestoresFicheiro), 1, fp);
		auxGestor = auxGestor->next;
	}
	fclose(fp);
	return true;
}

/**
 * @brief Ler ficheiro bin.
 * @author Victor Destefani
 * @param nomeFicheiro
 * @param 
 * @return 
 */
GestoresFicheiro* LerGestorBin(char* nomeFicheiro, bool* res) {
	FILE* fp;
	GestoresFicheiro* inicio = NULL;
	Gestor* aux;
	*res = false;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

	// garante - se que o ponteiro "aux" j� tem um espa�o de mem�ria alocado e pode ser utilizado para armazenar os dados
	aux = (Gestor*)malloc(sizeof(Gestor));

	while (fread(aux, sizeof(Gestor), 1, fp)) {
		if (aux != NULL) {
			inicio = InsertGestorInicio(inicio, aux, res);
			aux = (Gestor*)malloc(sizeof(Gestor));
			*res = true;
		}
		else {
			*res = false;
		}
	}
	free(aux);
	fclose(fp);
	return inicio;
}

#pragma endregion