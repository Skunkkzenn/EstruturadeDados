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

Cliente* InsertClienteLista(Cliente* novo, Cliente* inicio) {
	if (novo == NULL) { /* Se o ponteiro "novo" apontar para NULL, a fun��o ter� um erro e
						   retornar� o ponteiro "inicio" original sem modificar a lista.
						   Caso contr�rio, a fun��o prossegue com a inser��o do novo cliente na lista.
						*/
						//printf("Erro: novo cliente e nulo\n");
		return inicio;
	}

	if (inicio == NULL) { /* Se o ponteiro "inicio" da lista estiver apontando para NULL,
							 o novo cliente ser� o primeiro da lista, portanto o ponteiro
							 "inicio" ser� atualizado para apontar para o novo cliente. */
		inicio = novo;
	}
	else // Se o ponteiro "inicio" da lista n�o estiver apontando para NULL, o novo cliente ser� adicionado ao in�cio da lista e o ponteiro "next" do novo cliente ser� atualizado para apontar para o antigo primeiro cliente da lista. Em seguida, o ponteiro "inicio" da lista ser� atualizado para apontar para o novo cliente.
	{
		novo->next = inicio;
		inicio = novo;
	}
	return inicio;
}

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

Cliente* RemoveCliente(int cod, long int nif, Cliente* inicio) {
	// Verifica se o in�cio � nulo (lista vazia)
	if (inicio == NULL) {
		return NULL; // N�o h� nenhum ve�culo para ser removido
	}

	// Inicializa ponteiros auxiliares
	Cliente* auxAnt = inicio;
	Cliente* auxProx = inicio;

	// Verifica se o n� a ser removido � a cabe�a da lista
	if ((inicio != NULL) && (inicio->cod == cod)) {
		auxAnt = auxAnt->next;
		free(inicio);
		inicio = auxAnt;
	}
	else
	{
		while ((auxProx != NULL) && (auxProx->cod != cod) && (auxProx->nif != nif)) {
			auxAnt = auxProx;
			auxProx = auxProx->next;
		}
		if ((auxProx != NULL) && (auxProx->cod != cod) && (auxProx->nif != nif)) {
			// N�o foi encontrado nenhum cliente com o c�digo e nif especificados;
			return NULL; // nao existe cliente, retorna in�cio;
		}
		if (auxProx != NULL) {
			// Remove o ve�culo encontrado
			auxAnt->next = auxProx->next; // auxAnt campo next passa a conter o valor de auxProx campo next;
			free(auxProx);	// liberta a mem�ria que � removida;
		}
	}
	return inicio;	// Retorna o cabe�alho
} /* Na minha avalia��o, a fun��o RemoveCliente parece estar correta agora. A verifica��o inicial de inicio ser nulo para garantir que a lista n�o � vazia e as vari�veis auxiliares auxAnt e auxProx est�o sendo corretamente inicializadas. A condi��o para remover o n� da cabe�a da lista tamb�m parece estar correta.

No loop while, a fun��o verifica se auxProx � nulo antes de acess�-lo e tamb�m verifica se o cod e nif correspondem ao n� atual. Al�m disso, o if que verifica se o n� a ser removido foi encontrado parece estar correto agora.

Na linha problem�tica, adicionando o if antes da atribui��o de auxAnt->next resolve o problema de desreferenciar um ponteiro nulo.

Dito isso, a fun��o RemoveCliente parece estar funcionando corretamente e n�o vejo nenhuma melhoria adicional a ser feita.*/

