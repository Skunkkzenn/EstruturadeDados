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
	//Cria espaço de memória
	novoCliente = (Cliente*)malloc(sizeof(Cliente));

	//Verifica se a alocação de memória foi bem sucedida 
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
	if (novo == NULL) { /* Se o ponteiro "novo" apontar para NULL, a função terá um erro e
						   retornará o ponteiro "inicio" original sem modificar a lista. 
						   Caso contrário, a função prossegue com a inserção do novo cliente na lista. 
					    */
		//printf("Erro: novo cliente e nulo\n");
		return inicio; 
	}
		
	if (inicio == NULL) { /* Se o ponteiro "inicio" da lista estiver apontando para NULL, 
							 o novo cliente será o primeiro da lista, portanto o ponteiro
							 "inicio" será atualizado para apontar para o novo cliente. */
		inicio = novo;
	}
	else // Se o ponteiro "inicio" da lista não estiver apontando para NULL, o novo cliente será adicionado ao início da lista e o ponteiro "next" do novo cliente será atualizado para apontar para o antigo primeiro cliente da lista. Em seguida, o ponteiro "inicio" da lista será atualizado para apontar para o novo cliente.
	{
		novo->next = inicio;
		inicio = novo;
	}
	return inicio;
}

Cliente* AlteraCampoCliente(int cod, char* nome, float saldo, long int nif, char* morada, Cliente* novo, Cliente* inicio) {
		// Verifica se a lista está vazia
		if (inicio == NULL)
	{
		inicio = novo;
	}
		// Cria um ponteiro auxiliar para percorrer a lista
		Cliente* aux = inicio;

		// Percorre a lista até encontrar o veículo com o código e tipo informado
		while ((aux != NULL) && (aux->cod != cod) && (strcmp(aux->nif, nif) != 0)) {

	}

		// Se não encontrou o cliente com o código informado, retorna a lista original
		if ((aux != NULL) || (aux->nif != nif)) {
		return inicio;
	}

		// Altera os campos do veículo encontrado com as informações fornecidas
	 	aux->cod = novo->cod;
	 	strcpy(aux->nome, novo->nome);
	 	aux->saldo = novo->saldo;
	 	aux->nif = novo->nif;
		strcpy(aux->morada, novo->morada);
		// Libera a memória alocada para o cliente novo
		free(novo);
		// Retorna a lista atualizada
		return inicio;

}
