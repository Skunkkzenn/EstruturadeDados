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

Gestor* CriaGestor(int cod, char* nome, float saldo, long int nif, char* morada) {
	Gestor* novoGestor;
	//Cria espa�o de mem�ria
	novoGestor = (Gestor*)malloc(sizeof(Gestor));

	//Verifica se a aloca��o de mem�ria foi bem sucedida 
	if (novoGestor == NULL) {
		//printf("Erro ao alocar memoria para novo cliente\n");
		return NULL;
	}
	novoGestor->cod = cod;
	strcpy(novoGestor->nome, nome);
	novoGestor->saldo = saldo;
	novoGestor->nif = nif;
	strcpy(novoGestor->morada, morada);
	novoGestor->next = NULL;
	return novoGestor;

}

Gestor* InsertGestorInicio(Gestor* novo, Gestor* inicio) {
	if (novo == NULL) // Verifica se ponteiro para o novo gestor � nulo, logo como n�o h� nada para ser inserido, retorna o ponteiro para o inicio da lista original
	{
		return inicio;
	}
	if (inicio == NULL) // Verifica se a lista est� vazia, se estiver, o novo gestor torna-se o primeiro n� da lista
	{
		inicio = novo;
	}
	else // S� ser� executado se a lista estiver vazia. O campo next do novo gestor esta configurado apra apontar para o in�cio da lista atual, de seguida o ponteiro para o in�cio da lista � atualizado para apontar para o novo n�.
	{
		novo->next = inicio;
		inicio = novo;
	}
	return inicio; // retorna o ponteiro para o in�cio da lista atualizada.
} /* Sim, o c�digo parece estar correto.
  A fun��o "InsertGestorInicio" parece ser respons�vel por inserir um novo n� (representado pela estrutura "Gestor") no in�cio de uma lista encadeada. O primeiro argumento "novo" � o ponteiro para o novo n� a ser inserido e o segundo argumento "inicio" � o ponteiro para o primeiro n� da lista atual.
  O primeiro "if" verifica se o ponteiro "novo" � nulo, o que indica que n�o h� nada para ser inserido na lista. Nesse caso, a fun��o simplesmente retorna o ponteiro para o in�cio da lista original.
  O segundo "if" verifica se a lista est� vazia (ou seja, se o ponteiro "inicio" � nulo). Se estiver vazia, o novo n� � definido como o primeiro n� da lista, e a fun��o retorna o ponteiro para o novo in�cio da lista.
  Se a lista n�o estiver vazia, o novo n� � inserido no in�cio da lista. Primeiro, o campo "next" do novo n� � definido como o ponteiro para o n� anteriormente no in�cio da lista (ou seja, o "inicio" atual). Em seguida, o ponteiro "inicio" � atualizado para apontar para o novo n�, tornando-o o novo in�cio da lista. A fun��o retorna o ponteiro para o novo in�cio da lista atualizada.
  Tenha em mente que, assim como qualquer fun��o que manipula ponteiros em uma lista encadeada, � importante garantir que os ponteiros estejam configurados corretamente e que n�o haja vazamentos de mem�ria ao inserir ou excluir n�s da lista.*/

Gestor* InsertGestorFim(Gestor* novo, Gestor* inicio) {
	if (inicio == NULL)
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
	}
	novo->next = NULL;
	return inicio;
}

Gestor* VerificaGestorDuplicado(int cod, int long nif, Gestor* inicio) {

	if (inicio == NULL) // Verifica se a lista encadeada est� vazia (inicio == NULL), caso esteja retorna NULL, indicando que n�o h� clientes duplicados.
	{
		return NULL; // Caso n�o encontre nenhum gestor com o mesmo c�digo e nif, retorna NULL.
	}

	Gestor* aux = inicio;
	while ((aux != NULL) && (aux->cod != cod) && (aux->nif != nif)) // percorre a lista para verificar os campos cod e nif e enquanto ele nao encontrar aux toma valor de aux campo next
	{
		aux = aux->next;
	}
	return aux; // Ao fim retorna o valor de aux
}

Gestor* InsertGestorLista(Gestor* novo, Gestor* inicio) {
	if (inicio == NULL)
	{
		inicio = novo;
	}
	else
	{
		Gestor* atual = inicio;
		Gestor* anterior = NULL;

		// Verifica se j� existe gestor com mesmo c�digo e nif
		if (VerificaGestorDuplicado(novo->cod, novo->nif, inicio) != NULL)
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

Gestor* AlteraCampoGestor(int cod, char* nome, float saldo, long int nif, char* morada, Gestor* novo, Gestor* inicio) {
	// Verifica se a lista est� vazia
	if (inicio == NULL)
	{   // printf("Erro: lista vazia\n");
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

Gestor* RemoveCliente(int cod, long int nif, Gestor* inicio) {
	// Verifica se o in�cio � nulo (lista vazia)
	if (inicio == NULL) {
		return NULL; // N�o h� nenhum ve�culo para ser removido
	}

	// Inicializa ponteiros auxiliares
	Gestor* auxAnt = inicio;
	Gestor* auxProx = inicio;

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
			// N�o foi encontrado nenhum gestor com o c�digo e nif especificados;
			return NULL; // nao existe gestor, retorna in�cio;
		}
		if (auxProx != NULL) {
			// Remove o ve�culo encontrado
			auxAnt->next = auxProx->next; // auxAnt campo next passa a conter o valor de auxProx campo next;
			free(auxProx);	// liberta a mem�ria que � removida;
		}
	}
	return inicio;	// Retorna o cabe�alho
}