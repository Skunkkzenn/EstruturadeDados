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

#pragma region Métodos Gestores

	//Criar e inicializar um novo gestor com as informações fornecidas
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

	//Insere Gestor no Inicio
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

	//Insere Gestor no fim
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

	//Verifica Gestor duplicado
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
	
	//Insere Gestor na Lista
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

	//Altera dados do Gestor
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

	//Remove Gestor
Gestor* RemoveGestor(int cod, long int nif, Gestor* inicio) {
	// Verifica se o início é nulo (lista vazia)
	if (inicio == NULL) {
		return NULL; // Não há nenhum veículo para ser removido
	}

	// Inicializa ponteiros auxiliares
	Gestor*	noAnterior = inicio;
	Gestor* noAtual = inicio;

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
			// Não foi encontrado nenhum gestor com o código e nif especificados;
			return NULL; // nao existe gestor, retorna início;
		}
		if (noAtual != NULL) {
			// Remove o gestor encontrado
			noAnterior->next = noAtual->next; // noAnterior campo next passa a conter o valor de noAtual campo next;
			free(noAtual);	// liberta a memória que é removida;
		}
	}
	return inicio;	// Retorna o cabeçalho
}

#pragma endregion