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
//Cria cliente
Cliente* CriaCliente(int cod, char* nome, float saldo, long int nif, char* morada) {
	Cliente* novoCliente;
	//Cria espa�o de mem�ria
	novoCliente = (Cliente*)malloc(sizeof(Cliente));

	//Verifica se a aloca��o de mem�ria foi bem sucedida 
	if (novoCliente == NULL) {
		//printf("Erro ao alocar memoria para novo cliente\n");
		return NULL;
	}
	novoCliente->cod = cod;
	strcpy(novoCliente->nome, nome);
	novoCliente->saldo = saldo;
	novoCliente->nif = nif;
	strcpy(novoCliente->morada, morada);
	novoCliente->next = NULL;
	return novoCliente;

}

//Insere Cliente Inicio
Cliente* InsertClienteInicio(Cliente* novo, Cliente* inicio) {
	if (novo == NULL) // Verifica se ponteiro para o novo cliente � nulo, logo como n�o h� nada para ser inserido, retorna o ponteiro para o inicio da lista original
	{
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
	}
	return inicio; // retorna o ponteiro para o in�cio da lista atualizada.
}

//Insere Cliente fim
Cliente* InsertClienteFim(Cliente* novo, Cliente* inicio) {
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
	}
	novo->next = NULL;
	return inicio;
}

//Insere Cliente na Lista
Cliente* InsertClienteLista(Cliente* novo, Cliente* inicio) {
	if (inicio == NULL)
	{
		inicio = novo;
	}
	else
	{
		Cliente* atual = inicio;
		Cliente* anterior = NULL;

		// Verifica se j� existe cliente com mesmo c�digo e nif
		if (VerificaClienteDuplicado(novo->cod, novo->nif, inicio) != NULL)
			return inicio; // Cliente j� existe, retorna a lista original

		//procurar a posicao correta, e ordena pelo cod!!!!
		while (atual && atual->cod < novo->cod) {
			anterior = atual;
			atual = atual->next;
		}

		// Insere no in�cio
		if (anterior == NULL && novo->cod < inicio->cod) { //Insere no in�cio
			novo->next = inicio;
			inicio = novo;
		}
		//Insere no meio
		else if (anterior == NULL)
		{ 
			novo->next = atual;
			inicio = novo;
		}
		//Insere no fim
		else 
		{
			anterior->next = novo;
			novo->next = atual;
		}
		return inicio;
	}

}

//Verifica Cliente Duplicado
Cliente* VerificaClienteDuplicado(int cod, int long nif, Cliente* inicio){

	if (inicio == NULL) // Verifica se a lista encadeada est� vazia (inicio == NULL), caso esteja retorna NULL, indicando que n�o h� clientes duplicados.
{
	return NULL; // Caso n�o encontre nenhum cliente com o mesmo c�digo e nif, retorna NULL.
}

	Cliente* aux = inicio;
	while ((aux != NULL) && (aux->cod != cod) && (aux->nif != nif)) // percorre a lista para verificar os campos cod e nif e enquanto ele nao encontrar aux toma valor de aux campo next
{
	aux = aux->next;
}
	return aux; // Ao fim retorna o valor de aux
}

//Altera dados Cliente
Cliente* AlteraCampoCliente(int cod, char* nome, float saldo, long int nif, char* morada, Cliente* novo, Cliente* inicio) {
	// Verifica se a lista est� vazia
	if (inicio == NULL)
	{   // printf("Erro: lista vazia\n");
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
	// Retorna a lista atualizada
	return inicio;
}

//Remove Cliente
Cliente* RemoveCliente(int cod, long int nif, Cliente* inicio) {
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
		while ((noAtual != NULL) && (noAtual->cod != cod) && (noAtual->nif != nif)) {
			noAnterior = noAtual;
			noAtual = noAtual->next;
		}
		if ((noAtual != NULL) && (noAtual->cod != cod) && (noAtual->nif != nif)) {
			// N�o foi encontrado nenhum cliente com o c�digo e nif especificados;
			return NULL; // nao existe cliente, retorna in�cio;
		}
		if (noAtual != NULL) {
			// Remove o ve�culo encontrado
			noAnterior->next = noAtual->next; // auxAnt campo next passa a conter o valor de auxProx campo next;
			free(noAtual);	// liberta a mem�ria que � removida;
		}
	}
	return inicio;	// Retorna o cabe�alho
}
/* Na minha avalia��o, a fun��o RemoveCliente parece estar correta agora. A verifica��o inicial de inicio ser nulo para garantir que a lista n�o � vazia e as vari�veis auxiliares auxAnt e auxProx est�o sendo corretamente inicializadas. A condi��o para remover o n� da cabe�a da lista tamb�m parece estar correta.

No loop while, a fun��o verifica se auxProx � nulo antes de acess�-lo e tamb�m verifica se o cod e nif correspondem ao n� atual. Al�m disso, o if que verifica se o n� a ser removido foi encontrado parece estar correto agora.

Na linha problem�tica, adicionando o if antes da atribui��o de auxAnt->next resolve o problema de desreferenciar um ponteiro nulo.

Dito isso, a fun��o RemoveCliente parece estar funcionando corretamente e n�o vejo nenhuma melhoria adicional a ser feita.*/

#pragma endregion