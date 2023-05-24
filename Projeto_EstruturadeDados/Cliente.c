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
#define MAXCHAR 500


#pragma region Métodos Clientes
/**
 * @brief Cria Cliente.
 * @author Victor Destefani
 * @param cod
 * @param nome
 * @param saldo
 * @param nif
 * @param morada
 * @return 
 */
Cliente* CriaCliente(int cod, char* nome, float saldo, long int nif, char* morada, bool* res){
	*res = false;
	
	Cliente* novoCliente;
	novoCliente = (Cliente*)malloc(sizeof(Cliente)); //Cria espaço de memória

	if (novoCliente == NULL) { //Verifica se a alocação de memória foi bem sucedida 
		printf("Erro ao alocar memoria para novo cliente\n");
		return NULL;
	}
	novoCliente->cod = cod;
	strcpy(novoCliente->nome, nome);
	novoCliente->saldo = saldo;
	novoCliente->nif = nif;
	strcpy(novoCliente->morada, morada);
	novoCliente->next = NULL;
	*res = true;
	return novoCliente;
}

/**
 * @brief Procura Cliente pelo Cod. e NIF.
 * @author Victor Destefani
 * @param inicio
 * @param cod
 * @param tipo
 * @return
 */
Cliente* ProcuraGestor(Cliente* inicio, int cod, long int nif) {
	Cliente* cliente = inicio;

	while (cliente != NULL) {
		if (cliente->cod == cod && cliente->nif == nif) {
			return cliente; // Encontrou o cliente
		}
		cliente = cliente->next;
	}

	return NULL; // Cliente não encontrado
}

/**
 * @brief Insere Cliente Inicio.
 * @author Victor Destefani
 * @param novo
 * @param inicio
 * @return 
 */
Cliente* InsertClienteInicio(Cliente* novo, Cliente* inicio, bool* res) {
	*res = false;
	if (novo == NULL) // Verifica se ponteiro para o novo cliente é nulo, logo como não há nada para ser inserido, retorna o ponteiro para o inicio da lista original
	{
		printf("Erro: novo cliente e nulo\n");
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
		*res = true;
	}
	return inicio; // Retorna o ponteiro para o início da lista atualizada após inserção.
}

/**
 * @brief Insere Cliente fim.
 * @author Victor Destefani
 * @param novo
 * @param inicio
 * @param 
 * @return 
 */
Cliente* InsertClienteFim(Cliente* novo, Cliente* inicio, bool* res) {
	*res = false;
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
		*res = true;
	}
	novo->next = NULL;
	return inicio;
}

/**
 * @brief Insere Cliente na lista por ordem de cód.
 * @author Victor Destefani
 * @param novo
 * @param inicio
 * @return 
 */
Cliente* InsertClienteLista(Cliente* novo, Cliente* inicio, bool* res) {
	bool clienteDuplicado = false; // variável bool para armazenar se há cliente duplicado
	*res = false;
	if (inicio == NULL)
	{
		inicio = novo;

	}
	else {
		//Verificar se já existe repetido
	 	if (VerificaClienteDuplicado(novo->cod, novo->nif, inicio, &clienteDuplicado) != NULL) {
			return inicio;

		}

		if (!clienteDuplicado) {
			if (inicio == NULL) {
				inicio = novo;
			}
			else {
				//procurar a posicao correta, e ordena pelo cod!!!!
				Cliente* atual = inicio;
				Cliente* anterior = NULL;

				//procurar a posicao correta, e ordena pelo cod!!!!
				while (atual != NULL && atual->cod < novo->cod) {
					anterior = atual;
					atual = atual->next;

				}

				if (anterior == NULL) { //Insere no início
					novo->next = inicio;
					inicio = novo;
				}
				else if (atual == NULL) { //Insere no fim
					anterior->next = novo;
					novo->next = NULL;
				}
				else { //Insere no meio
					anterior->next = novo;
					novo->next = atual;
				}
				*res = true;
			}
		}
		return inicio; // Retorna o ponteiro de início atualizado
	}
}

/**
 * @brief Verifica Cliente Duplicado.
 * @author Victor Destefani
 * @param cod
 * @param nif
 * @param inicio
 * @param 
 * @return 
 */
Cliente* VerificaClienteDuplicado(int cod, long int nif, Cliente* inicio, bool* duplicado){
	*duplicado = false;
	
	if (inicio == NULL) // Verifica se a lista encadeada está vazia (inicio == NULL), caso esteja retorna NULL, indicando que não há clientes duplicados.
	{
	return NULL; // Caso não encontre nenhum cliente com o mesmo código e nif, retorna NULL.
	}

	Cliente* aux = inicio;
	while ((aux != NULL) && (aux->cod != cod) && (aux->nif != nif)) // percorre a lista para verificar os campos cod e nif e enquanto ele nao encontrar aux toma valor de aux campo next
	{
	aux = aux->next;
	}
	
	if ((aux != NULL) && (aux->cod == cod) && (aux->nif == nif)) {
	 	*duplicado = true;
	}
	return aux;
}

/**
 * @brief Altera dados Cliente.
 * @author Victor Destefani
 * @param cod
 * @param nome
 * @param saldo
 * @param nif
 * @param morada
 * @param novo
 * @param inicio
 * @param 
 * @return 
 */
Cliente* AlteraCampoCliente(int cod, char* nome, float saldo, long int nif, char* morada, Cliente* novo, Cliente* inicio, bool* res) {
	*res = false;

	// Verifica se a lista está vazia
	if (inicio == NULL)
	{   
		printf("Erro: lista vazia\n");
		*res = false;
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
 * @brief Remove Cliente.
 * @author Victor Destefani
 * @param cod
 * @param nif
 * @param inicio
 * @return 
 */
Cliente* RemoveCliente(int cod, long int nif, Cliente* inicio, bool* res ) {
	*res = false;
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
 * @brief Ler ficheiro clientes.txt.
 * @author Victor Destefani
 * @param fileName
 * @return
 */
bool LerDadosCliente(char fileName[]) {
	char row[MAXCHAR];
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror("Erro ao abrir o arquivo para leitura");
		return false;
	}

	while (fgets(row, MAXCHAR, fp) != NULL) {
		printf("Clientes: %s", row);
	}

	fclose(fp);
	return true;
}


/**
 * @brief Grava clientes em ficheiro binario.
 *
 * @param nomeFicheiro
 * @param inicio
 * @return
 */
bool GravarClienteBin(char* nomeFicheiro, Cliente* inicio) {
	FILE* fp;

	if (inicio == NULL) {
		return false;
	}

	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) {
		perror("Erro ao abrir arquivo para escrita");
		return false;
	}

	//grava 1 registo de cada vez no ficheiro
	ClientesFicheiro aux;
 	Cliente* auxCliente = inicio;
	while (auxCliente) {
		aux.cod = auxCliente->cod;
		strcpy(aux.nome, auxCliente->nome);
		aux.saldo = auxCliente->saldo;
		aux.nif = auxCliente->nif;
		strcpy(aux.morada, auxCliente->morada);

		fwrite(auxCliente, sizeof(ClientesFicheiro), 1, fp);
		auxCliente = auxCliente->next;
	}
	fclose(fp);
	return true;
}

/**
 * @brief Grava cliente em binario.
 * @author Victor Destefani
 * \param nomeFicheiro
 * \param
 * \return
 */
Cliente* LerClienteBin(char* nomeFicheiro, bool* res) {
	FILE* fp;
	Cliente* inicio = NULL;
	ClientesFicheiro aux;
	*res = false;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

	while (fread(&aux, sizeof(ClientesFicheiro), 1, fp)) {
		Cliente* novo = (Cliente*)malloc(sizeof(Cliente));
 		if (novo == NULL) {
			*res = false;
			break;
		}

	 	novo->cod = aux.cod;
		strcpy(novo->nome, aux.nome);
		novo->saldo = aux.saldo;
		novo->nif = aux.nif;
		strcpy(novo->morada, aux.morada);
		novo->next = NULL;

		if (inicio == NULL) {
			inicio = novo;
		}
		else {
			Cliente* temp = inicio;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = novo;
		}

		// Imprime os dados do registro lido
		printf("Registro lido: cod=%d, nome=%s, saldo=%.2f, nif=%d, local=%s\n",
			novo->cod, novo->nome, novo->saldo, novo->nif, novo->morada);

		*res = true;
	}

	fclose(fp);

	return inicio;
}


#pragma endregion