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
	{   // printf("Erro: lista vazia\n");
		return NULL;
	}
	// Cria um ponteiro auxiliar para percorrer a lista
	Cliente* aux = inicio;

	// Percorre a lista até encontrar o veículo com o código e tipo informado
	while ((aux != NULL) && (aux->cod != cod) && (aux->nif != nif))
	{
		aux = aux->next;
	}

	// Se não encontrou o cliente com o código informado, retorna a lista original
	if ((aux == NULL) || (aux->nif != nif)) {
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

Cliente* RemoveCliente(int cod, long int nif, Cliente* inicio) {
	// Verifica se o início é nulo (lista vazia)
	if (inicio == NULL) {
		return NULL; // Não há nenhum veículo para ser removido
	}

	// Inicializa ponteiros auxiliares
	Cliente* auxAnt = inicio;
	Cliente* auxProx = inicio;

	// Verifica se o nó a ser removido é a cabeça da lista
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
			// Não foi encontrado nenhum cliente com o código e nif especificados;
			return NULL; // nao existe cliente, retorna início;
		}
		if (auxProx != NULL) {
			// Remove o veículo encontrado
			auxAnt->next = auxProx->next; // auxAnt campo next passa a conter o valor de auxProx campo next;
			free(auxProx);	// liberta a memória que é removida;
		}
	}
	return inicio;	// Retorna o cabeçalho
} /* Na minha avaliação, a função RemoveCliente parece estar correta agora. A verificação inicial de inicio ser nulo para garantir que a lista não é vazia e as variáveis auxiliares auxAnt e auxProx estão sendo corretamente inicializadas. A condição para remover o nó da cabeça da lista também parece estar correta.

No loop while, a função verifica se auxProx é nulo antes de acessá-lo e também verifica se o cod e nif correspondem ao nó atual. Além disso, o if que verifica se o nó a ser removido foi encontrado parece estar correto agora.

Na linha problemática, adicionando o if antes da atribuição de auxAnt->next resolve o problema de desreferenciar um ponteiro nulo.

Dito isso, a função RemoveCliente parece estar funcionando corretamente e não vejo nenhuma melhoria adicional a ser feita.*/

