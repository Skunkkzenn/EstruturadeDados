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

#pragma region Métodos Clientes
//Cria cliente
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

//Insere Cliente Inicio
Cliente* InsertClienteInicio(Cliente* novo, Cliente* inicio) {
	if (novo == NULL) // Verifica se ponteiro para o novo cliente é nulo, logo como não há nada para ser inserido, retorna o ponteiro para o inicio da lista original
	{
		return inicio;
	}
	if (inicio == NULL) // Verifica se a lista está vazia, se estiver, o novo cliente se torna o primeiro nó da lista
	{
		inicio = novo;
	}
	else // Só será executado se a lista estiver vazia. O campo next do novo cliente esta configurado apra apontar para o início da lista atual, de seguida o ponteiro para o início da lista é atualizado para apontar para o novo nó.
	{
		novo->next = inicio;
		inicio = novo;
	}
	return inicio; // retorna o ponteiro para o início da lista atualizada.
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

		// Verifica se já existe cliente com mesmo código e nif
		if (VerificaClienteDuplicado(novo->cod, novo->nif, inicio) != NULL)
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

//Verifica Cliente Duplicado
Cliente* VerificaClienteDuplicado(int cod, int long nif, Cliente* inicio){

	if (inicio == NULL) // Verifica se a lista encadeada está vazia (inicio == NULL), caso esteja retorna NULL, indicando que não há clientes duplicados.
{
	return NULL; // Caso não encontre nenhum cliente com o mesmo código e nif, retorna NULL.
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

//Remove Cliente
Cliente* RemoveCliente(int cod, long int nif, Cliente* inicio) {
	// Verifica se o início é nulo (lista vazia)
	if (inicio == NULL) {
		return NULL; // Não há nenhum veículo para ser removido
	}

	// Inicializa ponteiros auxiliares
	Cliente* noAnterior = inicio;
	Cliente* noAtual = inicio;

	// Verifica se o nó a ser removido é a cabeça da lista
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
			// Não foi encontrado nenhum cliente com o código e nif especificados;
			return NULL; // nao existe cliente, retorna início;
		}
		if (noAtual != NULL) {
			// Remove o veículo encontrado
			noAnterior->next = noAtual->next; // auxAnt campo next passa a conter o valor de auxProx campo next;
			free(noAtual);	// liberta a memória que é removida;
		}
	}
	return inicio;	// Retorna o cabeçalho
}
/* Na minha avaliação, a função RemoveCliente parece estar correta agora. A verificação inicial de inicio ser nulo para garantir que a lista não é vazia e as variáveis auxiliares auxAnt e auxProx estão sendo corretamente inicializadas. A condição para remover o nó da cabeça da lista também parece estar correta.

No loop while, a função verifica se auxProx é nulo antes de acessá-lo e também verifica se o cod e nif correspondem ao nó atual. Além disso, o if que verifica se o nó a ser removido foi encontrado parece estar correto agora.

Na linha problemática, adicionando o if antes da atribuição de auxAnt->next resolve o problema de desreferenciar um ponteiro nulo.

Dito isso, a função RemoveCliente parece estar funcionando corretamente e não vejo nenhuma melhoria adicional a ser feita.*/

#pragma endregion