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
	//Cria espaço de memória
	novoGestor = (Gestor*)malloc(sizeof(Gestor));

	//Verifica se a alocação de memória foi bem sucedida 
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
	if (novo == NULL) // Verifica se ponteiro para o novo gestor é nulo, logo como não há nada para ser inserido, retorna o ponteiro para o inicio da lista original
	{
		return inicio;
	}
	if (inicio == NULL) // Verifica se a lista está vazia, se estiver, o novo gestor torna-se o primeiro nó da lista
	{
		inicio = novo;
	}
	else // Só será executado se a lista estiver vazia. O campo next do novo gestor esta configurado apra apontar para o início da lista atual, de seguida o ponteiro para o início da lista é atualizado para apontar para o novo nó.
	{
		novo->next = inicio;
		inicio = novo;
	}
	return inicio; // retorna o ponteiro para o início da lista atualizada.
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

	if (inicio == NULL) // Verifica se a lista encadeada está vazia (inicio == NULL), caso esteja retorna NULL, indicando que não há clientes duplicados.
	{
		return NULL; // Caso não encontre nenhum gestor com o mesmo código e nif, retorna NULL.
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

		// Verifica se já existe gestor com mesmo código e nif
		if (VerificaGestorDuplicado(novo->cod, novo->nif, inicio) != NULL)
			return inicio; // Cliente já existe, retorna a lista original

		//procurar a posicao correta, e ordena pelo cod!!!!
		while (atual && atual->cod < novo->cod) {
			anterior = atual;
			atual = atual->next;
		}

		// Insere no início
		if (anterior == NULL && novo->cod < inicio->cod) { //Insere no início
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