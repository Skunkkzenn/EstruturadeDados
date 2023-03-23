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
}

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