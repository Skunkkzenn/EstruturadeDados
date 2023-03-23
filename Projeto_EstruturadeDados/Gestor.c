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
}
