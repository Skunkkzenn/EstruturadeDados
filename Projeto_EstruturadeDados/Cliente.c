/*****************************************************************//**
 * \file   Cliente.c
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   March 2023
 *********************************************************************/


#include <stdio.h>
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "Cliente.h"
#pragma warning( disable : 4996 )

#pragma region M�todos Clientes
/**
 * @brief Cria Cliente.
 * 
 * @param cod
 * @param nome
 * @param saldo
 * @param nif
 * @param morada
 * @return 
 */
Cliente* CriaCliente(int cod, char* nome, float saldo, long int nif, char* morada, bool* res){
	*res = false;
	
	Cliente* novoCliente;
	novoCliente = (Cliente*)malloc(sizeof(Cliente)); //Cria espa�o de mem�ria

	if (novoCliente == NULL) { //Verifica se a aloca��o de mem�ria foi bem sucedida 
		printf("Erro ao alocar memoria para novo cliente\n");
		return NULL;
	}
	novoCliente->cod = cod;
	strcpy(novoCliente->nome, nome);
	novoCliente->saldo = saldo;
	novoCliente->nif = nif;
	strcpy(novoCliente->morada, morada);
	novoCliente->next = NULL;
	*res = true;
	return novoCliente;
}

/**
 * @brief Insere Cliente Inicio.
 * 
 * @param novo
 * @param inicio
 * @return 
 */
Cliente* InsertClienteInicio(Cliente* novo, Cliente* inicio, bool* res) {
	*res = false;
	if (novo == NULL) // Verifica se ponteiro para o novo cliente � nulo, logo como n�o h� nada para ser inserido, retorna o ponteiro para o inicio da lista original
	{
		printf("Erro: novo cliente e nulo\n");
		return inicio;
	}
	if (inicio == NULL) // Verifica se a lista est� vazia, se estiver, o novo cliente se torna o primeiro n� da lista
	{
		inicio = novo;
	}
	else // S� ser� executado se a lista estiver vazia. O campo next do novo cliente esta configurado apra apontar para o in�cio da lista atual, de seguida o ponteiro para o in�cio da lista � atualizado para apontar para o novo n�.
	{
		novo->next = inicio;
		inicio = novo;
		*res = true;
	}
	return inicio; // Retorna o ponteiro para o in�cio da lista atualizada ap�s inser��o.
}

/**
 * @brief Insere Cliente fim.
 * 
 * @param novo
 * @param inicio
 * @param 
 * @return 
 */
Cliente* InsertClienteFim(Cliente* novo, Cliente* inicio, bool* res) {
	*res = false;
	if (inicio == NULL)
	{
		inicio = novo;
	}
	else
	{
		Cliente* aux = inicio;
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
 * @brief Insere Cliente na Lista.
 * 
 * @param novo
 * @param inicio
 * @return 
 */
Cliente* InsertClienteLista(Cliente* novo, Cliente* inicio, bool* res) {
	bool clienteDuplicado = false; // vari�vel bool para armazenar se h� cliente duplicado
	*res = false;
	if (inicio == NULL)
	{
		inicio = novo;

	}
	else {
		//Verificar se j� existe repetido
	 	if (VerificaClienteDuplicado(novo->cod, novo->nif, inicio, &clienteDuplicado) != NULL) {
			return inicio;

		}

		if (!clienteDuplicado) {
			if (inicio == NULL) {
				inicio = novo;
			}
			else {
				//procurar a posicao correta, e ordena pelo cod!!!!
				Cliente* atual = inicio;
				Cliente* anterior = NULL;

				//procurar a posicao correta, e ordena pelo cod!!!!
				while (atual != NULL && atual->cod < novo->cod) {
					anterior = atual;
					atual = atual->next;

				}

				if (anterior == NULL) { //Insere no in�cio
					novo->next = inicio;
					inicio = novo;
				}
				else if (atual == NULL) { //Insere no fim
					anterior->next = novo;
					novo->next = NULL;
				}
				else { //Insere no meio
					anterior->next = novo;
					novo->next = atual;
				}
				*res = true;
			}
		}
		return inicio; // Retorna o ponteiro de in�cio atualizado
	}
}

/**
 * @brief Verifica Cliente Duplicado.
 * 
 * @param cod
 * @param nif
 * @param inicio
 * @param 
 * @return 
 */
Cliente* VerificaClienteDuplicado(int cod, long int nif, Cliente* inicio, bool* duplicado){
	*duplicado = false;
	
	if (inicio == NULL) // Verifica se a lista encadeada est� vazia (inicio == NULL), caso esteja retorna NULL, indicando que n�o h� clientes duplicados.
	{
	return NULL; // Caso n�o encontre nenhum cliente com o mesmo c�digo e nif, retorna NULL.
	}

	Cliente* aux = inicio;
	while ((aux != NULL) && (aux->cod != cod) && (aux->nif != nif)) // percorre a lista para verificar os campos cod e nif e enquanto ele nao encontrar aux toma valor de aux campo next
	{
	aux = aux->next;
	}
	
	if ((aux != NULL) && (aux->cod == cod) && (aux->nif == nif)) {
	 	*duplicado = true;
	}
	return aux;
}

/**
 * @brief Altera dados Cliente.
 * 
 * @param cod
 * @param nome
 * @param saldo
 * @param nif
 * @param morada
 * @param novo
 * @param inicio
 * @param 
 * @return 
 */
Cliente* AlteraCampoCliente(int cod, char* nome, float saldo, long int nif, char* morada, Cliente* novo, Cliente* inicio, bool* res) {
	*res = false;

	// Verifica se a lista est� vazia
	if (inicio == NULL)
	{   
		printf("Erro: lista vazia\n");
		*res = false;
		return NULL;
	}
	// Cria um ponteiro auxiliar para percorrer a lista
	Cliente* aux = inicio;

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
 * @brief Remove Cliente.
 * 
 * @param cod
 * @param nif
 * @param inicio
 * @return 
 */
Cliente* RemoveCliente(int cod, long int nif, Cliente* inicio, bool* res ) {
	*res = false;
	// Verifica se o in�cio � nulo (lista vazia)
	if (inicio == NULL) {
		return NULL; // N�o h� nenhum ve�culo para ser removido
	}

	// Inicializa ponteiros auxiliares
 	Cliente* noAnterior = inicio;
	Cliente* noAtual = inicio;

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

#pragma endregion