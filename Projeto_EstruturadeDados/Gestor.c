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
#define MAXCHAR 500

#pragma region Métodos Gestores
 /**
  * @brief Cria Gestor.
  * @author Victor Destefani
  * @param cod
  * @param nome
  * @param saldo
  * @param nif
  * @param morada
  * @return
  */
Gestor* CriaGestor(int cod, char* nome, float saldo, long int nif, char* morada, bool* res) {
	*res = false;

	Gestor* novoGestor;
	novoGestor = (Gestor*)malloc(sizeof(Gestor)); //Cria espaço de memória

	if (novoGestor == NULL) { //Verifica se a alocação de memória foi bem sucedida 
		printf("Erro ao alocar memoria para novo gestor.\n");
		return NULL;
	}
	novoGestor->cod = cod;
	strcpy(novoGestor->nome, nome);
	novoGestor->saldo = saldo;
	novoGestor->nif = nif;
	strcpy(novoGestor->morada, morada);
	novoGestor->next = NULL;
	*res = true;
	return novoGestor;
}

/**
 * @brief Insere Gestor no Inicio.
 * @author Victor Destefani
 * @param novo
 * @param inicio
 * @return
 */
Gestor* InsertGestorInicio(Gestor* novo, Gestor* inicio, bool* res) {
	*res = false;
	if (novo == NULL) /* Verifica se ponteiro para o novo gestor é nulo, logo como não há nada para ser inserido,
					   retorna o ponteiro para o inicio da lista */
	{
		printf("Erro: novo gestor e nulo\n");
		return inicio;
	}
	if (inicio == NULL) // Verifica se a lista está vazia, se estiver, o novo gestor torna-se o primeiro nó da lista
	{
		inicio = novo;
	}
	else // Caso contrário, insere o novo gestor no início da lista
	{
		novo->next = inicio;
		inicio = novo;
		*res = true;
	}
	return inicio; // retorna o ponteiro para o início da lista atualizada.
}

/**
 * @brief Insere Gestor no Fim.
 * @author Victor Destefani
 * @param novo
 * @param inicio
 * @return
 */
Gestor* InsertGestorFim(Gestor* novo, Gestor* inicio, bool* res) {
	*res = false;
	if (inicio == NULL) // Verifica se a lista está vazia, se estiver, o novo gestor torna-se o primeiro nó da lista
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
		*res = true;
	}
	novo->next = NULL;
	return inicio;
}

/**
 * @brief Verifica Gestor Duplicado.
 * @author Victor Destefani
 * @param cod
 * @param nif
 * @param inicio
 * @param
 * @return
 */
Gestor* VerificaGestorDuplicado(int cod, int long nif, Gestor* inicio, bool* duplicado) {
	*duplicado = false;

	if (inicio == NULL) // Verifica se a lista encadeada está vazia (inicio == NULL), caso esteja retorna NULL, indicando que não há clientes duplicados.
	{
		return NULL; // Caso não encontre nenhum gestor com o mesmo código e nif, retorna NULL.
	}

	Gestor* aux = inicio;
	while ((aux != NULL) && (aux->cod != cod) && (aux->nif != nif)) // percorre a lista para verificar os campos cod e nif e enquanto ele nao encontrar aux toma valor de aux campo next
	{
		aux = aux->next;
	}

	if ((aux != NULL) && (aux->cod == cod) && (aux->nif == nif)) {
		*duplicado = true;
	}
	return aux; // Ao fim retorna o valor de aux
}

/**
 * @brief Insere Gestor na Lista.
 * @author Victor Destefani
 * @param novo
 * @param inicio
 * @param
 * @return
 */
Gestor* InsertGestorLista(Gestor* novo, Gestor* inicio, bool* res) {
	bool gestorDuplicado = false; // variável bool para armazenar se há gestor duplicado
	*res = false;
	if (inicio == NULL)
	{
		inicio = novo;
	}
	else {
		//Verificar se já existe repetido
		if (VerificaGestorDuplicado(novo->cod, novo->nif, inicio, &gestorDuplicado) != NULL) {
			return inicio;
		}
		if (!gestorDuplicado) {
			if (inicio == NULL) {
				inicio = novo;
			}
			else {
				Gestor* atual = inicio;
				Gestor* anterior = NULL;

				//procurar a posicao correta, e ordena pelo cod!!!!
				while (atual != NULL && atual->cod < novo->cod) {
					anterior = atual;
					atual = atual->next;
				}
				if (anterior == NULL) {  //Insere no início
					novo->next = inicio;
					inicio = novo;
				}
				else if (atual == NULL) { //Insere no fim
					anterior->next = novo;
					novo->next = NULL;
				}
				else {  //Insere no meio
					anterior->next = novo;
					novo->next = atual;
				}
				*res = true;
			}
		}
		return inicio;
	}
}

/**
 * @brief Altera dados Gestor.
 * @author Victor Destefani
 * @param cod
 * @param nome
 * @param saldo
 * @param nif
 * @param morada
 * @param novo
 * @param inicio
 * @return
 */
Gestor* AlteraCampoGestor(int cod, char* nome, float saldo, long int nif, char* morada, Gestor* novo, Gestor* inicio, bool* res) {
	*res = false;

	// Verifica se a lista está vazia
	if (inicio == NULL)
	{
		printf("Erro: lista vazia\n");
		*res = false;
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
		*res = false;
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
	*res = true;
	// Retorna a lista atualizada
	return inicio;
}

/**
 * @brief Remove Gestor.
 * @author Victor Destefani
 * @param cod
 * @param nif
 * @param inicio
 * @param
 * @return
 */
Gestor* RemoveGestor(int cod, long int nif, Gestor* inicio, bool* res) {
	*res = false;
	// Verifica se o início é nulo (lista vazia)
	if (inicio == NULL) {
		return NULL; // Não há nenhum veículo para ser removido
	}

	// Inicializa ponteiros auxiliares
	Gestor* noAnterior = inicio;
	Gestor* noAtual = inicio;

	// Verifica se o nó a ser removido é a cabeça da lista
	if ((inicio != NULL) && (inicio->cod == cod)) {
		noAnterior = noAnterior->next;
		free(inicio);
		inicio = noAnterior;
	}
	else
	{
		while ((noAtual != NULL) && (noAtual->cod != cod) && (noAtual->nif != nif)) { // Procura pelo cliente a ser removido
			noAnterior = noAtual; // avança o ponteiro auxAnt para o próximo nó
			noAtual = noAtual->next; // avança o ponteiro auxProx para o próximo nó
		}
		if ((noAtual == NULL) || (noAnterior->next == NULL) || (noAnterior->cod != cod)) { // Não foi encontrado nenhum veículo com o código e tipo especificados
			return inicio;
		}
		// Remove o veículo encontrado
		noAnterior->next = noAtual->next; // auxAnt campo next passa a conter o valor de auxProx campo next!
		free(noAtual); // liberta a memória que é removida
		*res = true;
	}
	return inicio; // Retorna head
}

/**
 * @brief Lê ficheiro gestores.txt.
 * @author Victor Destefani
 * @param fileName
 * @return
 */
bool LerDadosGestor(char fileName[]) {
	char row[MAXCHAR];
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror("Erro ao abrir o arquivo para leitura");
		return false;
	}

	while (fgets(row, MAXCHAR, fp) != NULL) {
		printf("Gestores: %s", row);
	}

	fclose(fp);
	return true;
}

/**
 * @brief Grava ficheiro em binário.
 * @author Victor Destefani
 * @param nomeFicheiro
 * @param inicio
 * @return
 */
bool GravarGestorBin(char* nomeFicheiro, Gestor* inicio, bool* res) {
	FILE* fp;

	if (inicio == NULL) {
		return false;
	}

	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) {
		perror("Erro ao abrir arquivo para escrita");
		return false;
	}

	//grava 1 registo de cada vez no ficheiro
	GestoresFicheiro aux;
	Gestor* auxGestor = inicio;
	while (auxGestor) {
		aux.cod = auxGestor->cod;
		strcpy(aux.nome, auxGestor->nome);
		aux.saldo = auxGestor->saldo;
		aux.nif = auxGestor->nif;
		strcpy(aux.morada, auxGestor->morada);

		fwrite(auxGestor, sizeof(GestoresFicheiro), 1, fp);
		auxGestor = auxGestor->next;
	}
	fclose(fp);
	return true;
}

/**
 * @brief Ler ficheiro bin.
 * @author Victor Destefani
 * @param nomeFicheiro
 * @param 
 * @return 
 */
GestoresFicheiro* LerGestorBin(char* nomeFicheiro, bool* res) {
	FILE* fp;
	GestoresFicheiro* inicio = NULL;
	Gestor* aux;
	*res = false;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

	// garante - se que o ponteiro "aux" já tem um espaço de memória alocado e pode ser utilizado para armazenar os dados
	aux = (Gestor*)malloc(sizeof(Gestor));

	while (fread(aux, sizeof(Gestor), 1, fp)) {
		if (aux != NULL) {
			inicio = InsertGestorInicio(inicio, aux, res);
			aux = (Gestor*)malloc(sizeof(Gestor));
			*res = true;
		}
		else {
			*res = false;
		}
	}
	free(aux);
	fclose(fp);
	return inicio;
}

#pragma endregion