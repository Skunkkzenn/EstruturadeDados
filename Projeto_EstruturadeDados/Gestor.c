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
} /* Sim, o código parece estar correto.
  A função "InsertGestorInicio" parece ser responsável por inserir um novo nó (representado pela estrutura "Gestor") no início de uma lista encadeada. O primeiro argumento "novo" é o ponteiro para o novo nó a ser inserido e o segundo argumento "inicio" é o ponteiro para o primeiro nó da lista atual.
  O primeiro "if" verifica se o ponteiro "novo" é nulo, o que indica que não há nada para ser inserido na lista. Nesse caso, a função simplesmente retorna o ponteiro para o início da lista original.
  O segundo "if" verifica se a lista está vazia (ou seja, se o ponteiro "inicio" é nulo). Se estiver vazia, o novo nó é definido como o primeiro nó da lista, e a função retorna o ponteiro para o novo início da lista.
  Se a lista não estiver vazia, o novo nó é inserido no início da lista. Primeiro, o campo "next" do novo nó é definido como o ponteiro para o nó anteriormente no início da lista (ou seja, o "inicio" atual). Em seguida, o ponteiro "inicio" é atualizado para apontar para o novo nó, tornando-o o novo início da lista. A função retorna o ponteiro para o novo início da lista atualizada.
  Tenha em mente que, assim como qualquer função que manipula ponteiros em uma lista encadeada, é importante garantir que os ponteiros estejam configurados corretamente e que não haja vazamentos de memória ao inserir ou excluir nós da lista.*/

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

Gestor* AlteraCampoGestor(int cod, char* nome, float saldo, long int nif, char* morada, Gestor* novo, Gestor* inicio) {
	// Verifica se a lista está vazia
	if (inicio == NULL)
	{   // printf("Erro: lista vazia\n");
		return NULL;
	}
	// Cria um ponteiro auxiliar para percorrer a lista
	Gestor* aux = inicio;

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

Gestor* RemoveCliente(int cod, long int nif, Gestor* inicio) {
	// Verifica se o início é nulo (lista vazia)
	if (inicio == NULL) {
		return NULL; // Não há nenhum veículo para ser removido
	}

	// Inicializa ponteiros auxiliares
	Gestor* auxAnt = inicio;
	Gestor* auxProx = inicio;

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
			// Não foi encontrado nenhum gestor com o código e nif especificados;
			return NULL; // nao existe gestor, retorna início;
		}
		if (auxProx != NULL) {
			// Remove o veículo encontrado
			auxAnt->next = auxProx->next; // auxAnt campo next passa a conter o valor de auxProx campo next;
			free(auxProx);	// liberta a memória que é removida;
		}
	}
	return inicio;	// Retorna o cabeçalho
}