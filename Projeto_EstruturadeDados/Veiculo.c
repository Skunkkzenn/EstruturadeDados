/*****************************************************************//**
 * \file   Veiculo.c
 * \brief  Projeto EDA
 * \number 18586
 * \author Victor Destefani
 * \date   March 2023
 *********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Veiculo.h"
#pragma warning( disable : 4996 )
#define MAXCHAR 500

#pragma region Métodos Veículos.

//Criar e inicializar um novo veículo com as informações fornecidas
Veiculo* CriaVeiculo(int cod, char* tipo, float bateria, float custo, char* local) {
	// Cria uma variável para armazenar o ponteiro para o novo veículo
	Veiculo* novoVeiculo;

	// Aloca memória para o novo veículo
	novoVeiculo = (Veiculo*)malloc(sizeof(Veiculo));
	// Verifica se a alocação de memória foi bem sucedida
	if (novoVeiculo == NULL)
	{   //printf("Erro ao alocar memória para novo veículo\n");
		return NULL;
	}

	// Inicializa os campos do novo veículo com as informações fornecidas
	novoVeiculo->cod = cod;
	strcpy(novoVeiculo->tipo, tipo);
	novoVeiculo->bateria = bateria;
	novoVeiculo->custo = custo;
	strcpy(novoVeiculo->local, local);
	novoVeiculo->next = NULL;

	return novoVeiculo; //Retorna o o ponteiro para o novo veiculo criado
}

// Insere veiculo no inicio
Veiculo* InsertVeiculoInicio(Veiculo* novo, Veiculo* inicio) {
	/*
		* Se a lista for vazia, vai alocar o veiculo criado e o retorna;
		* No inicio da função verifica-se se sup é nulo
		* Se for nulo, é definido como o novo veículo e é retornado.
	*/

 	if (novo == NULL) { /* Se o ponteiro "novo" apontar para NULL, a função terá um erro e
						   retornará o ponteiro "inicio" original sem modificar a lista.
						   Caso contrário, a função prossegue com a inserção do novo cliente na lista.
						*/
						printf("Erro: novo cliente e nulo\n");
 		return inicio;
	}
	if (inicio == NULL)
	{
		inicio = novo;
	}
	else {
		novo->next = inicio;
		inicio = novo;
	}
	return inicio; //É necessário que ela retorne o ponteiro para o início da lista atualizado após a inserção do novo veículo.
}

// Inserir Maquina Fim da Lista
/* Esse metodo recebe uma maquina nova para
   inserir e recebe o incio da lista onde se vai inserir */
Veiculo* InsertVeiculoFim(Veiculo* novo, Veiculo* inicio) {
	if (inicio == NULL) // Se a lista estiver vazia, o novo nó será a cabeça da lista
	{
		inicio = novo;
	}
	else  // Se a lista não estiver vazia, insere o novo nó no final
	{
		Veiculo* aux = inicio; // Usa-se uma variável auxiliar que fica a apontar para o inicio, pois nao podemos alterar o inicio
		while (aux->next != NULL) {  /* Enquanto o aux campo next nao for nulo
									  ou
									  Enquanto ele estiver a apontar para alguma coisa seguira sempre. */
			aux = aux->next; // aux toma o valor de aux campo next, dessa forma avançamos na lista e quando acabar o fim do ciclo estamos no fim da lista
		}
		aux->next = novo;
	}
	novo->next = NULL; // O campo next do novo nó deve ser nulo
	return inicio;
}

// Insere Veiculo Lista
Veiculo* InsertVeiculoLista(Veiculo* novo, Veiculo* inicio) {

	if (inicio == NULL)
	{
		inicio = novo;
	}
	else
	{
		Veiculo* atual = inicio;
		Veiculo* anterior = NULL;

		//Verificar se já existe repetido
		if (VerificaVeiculoDuplicado(novo->cod, novo->tipo, inicio) == inicio)
			return inicio;

		//procurar a posicao correta, e ordena pelo cod!!!!
		while (atual && atual->cod < novo->cod) {
			anterior = atual;
			atual = atual->next;
		}

		if (anterior == NULL && novo->  cod < inicio->cod) { //Insere no início
			novo->next = inicio;
			inicio = novo;
		}
		else if (anterior == NULL)
		{ //Insere no meio
			novo->next = atual;
			inicio = novo;
		}
		else //Insere no fim
		{
			anterior->next = novo;
			novo->next = atual;
		}
		return inicio;
	}

}

// Verifica Veiculo em duplicado
Veiculo* VerificaVeiculoDuplicado(int cod, char* tipo, Veiculo* inicio) {
	if (inicio == NULL) // Verifica se a lista encadeada está vazia (inicio == NULL), caso esteja retorna NULL, indicando que não há veículos duplicados.
	{
		return NULL; // Caso não encontre nenhum veículo com o mesmo código e tipo, retorna NULL.
	}

	Veiculo* aux = inicio;
	while ((aux != NULL) && (aux->cod != cod) && (strcmp(aux->tipo, tipo) != 0)) // Percorre a lista encadeada, enquanto não chegar ao final da lista (aux != NULL) e não encontrar um veículo com o mesmo código e tipo (aux->cod != cod) && (strcmp(aux->tipo, tipo) != 0). Se encontrar um veículo com o mesmo código e tipo, retorna um ponteiro para esse veículo (aux).
	{
		aux = aux->next;
	}
	return aux;
}

// Altera Dados do Veiculo
Veiculo* AlteraCampoVeiculo(int cod, char* tipo, float bateria, float custo, char* local, Veiculo* novo, Veiculo* inicio) {
	// Verifica se a lista está vazia
	if (inicio == NULL)
	{
		inicio = novo;
	}

	// Cria um ponteiro auxiliar para percorrer a lista
	Veiculo* aux = inicio;

	// Percorre a lista até encontrar o veículo com o código e tipo informado
	while ((aux != NULL) && (aux->cod != cod) && (strcmp(aux->tipo, tipo) != 0)) { // Percorre a lista encadeada, enquanto não chegar ao final da lista (aux != NULL) e não encontrar um veículo com o mesmo código e tipo (aux->cod != cod) && (strcmp(aux->tipo, tipo) != 0). Se encontrar um veículo com o mesmo código e tipo, retorna um ponteiro para esse veículo (aux).
		aux = aux->next;
	}

	// Se não encontrou o veículo com o código informado, retorna a lista original
	if ((aux == NULL) || aux->cod != cod)
		return inicio;

	// Altera os campos do veículo encontrado com as informações fornecidas
	aux->cod = novo->cod;
	strcpy(aux->tipo, novo->tipo);
	aux->bateria = novo->bateria;
	aux->custo = novo->custo;
	strcpy(aux->local, novo->local);
	// Libera a memória alocada para o veículo novo
	free(novo);
	// Retorna a lista atualizada
	return inicio;
}

// Remove Veiculo da Lista
Veiculo* RemoveVeiculo(int cod, char* tipo, Veiculo* inicio) {
	// Verifica se o início é nulo (lista vazia)
	if (inicio == NULL) {
		return NULL; // Não há nenhum veículo para ser removido
	}

	// Inicializa ponteiros auxiliares
	Veiculo* noAnterior = inicio;
	Veiculo* noAtual = inicio;

	// Verifica se o nó a ser removido é a cabeça da lista
	if ((inicio != NULL) && (inicio->cod == cod)) { // O veículo a ser removido é o primeiro da lista (inicio)
		noAnterior = noAnterior->next; // Atualiza a lista para começar do segundo elemento
		free(inicio); // Libera a memória ocupada pelo veículo removido
		inicio = noAnterior;  // atualiza o início da lista
	}
	else
	{   // Percorre a lista até encontrar o nó a ser removido
		while ((noAtual != NULL) && (noAtual->cod != cod) && (strcmp(noAtual->tipo, tipo) != 0)) { // percorre array enquanto...
			{
				// Procura pelo veículo a ser removido
				noAnterior = noAtual; // avança o ponteiro auxAnt para o próximo nó
				noAtual = noAtual->next; // avança o ponteiro auxProx para o próximo nó
			}
			if ((noAtual == NULL) || (noAnterior->next == NULL) || (noAnterior->cod != cod)) {
				// Não foi encontrado nenhum veículo com o código e tipo especificados
				return inicio; // nao existe a maquina, retorna início
			}
		}
		// Remove o veículo encontrado
		noAnterior->next = noAtual->next; // auxAnt campo next passa a conter o valor de auxProx campo next!
		free(noAtual); // liberta a memória que é removida
	}
	return inicio; // Retorna head
}

bool LerDadosVeiculo(char fileName[])
{
	char row[MAXCHAR];
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror("Problemas na leitura do ficheiro.\n");
		return false;
	}

	while (feof(fp) != true)
	{
		fgets(row, MAXCHAR, fp);
		printf("Veiculos: %s", row);
	}
	fclose(fp);
	return true;
}

bool GravarVeiculoBin(char* nomeFicheiro, VeiculosLista* inicio) {
	FILE* fp;

	if (inicio == NULL) {
		return false;
	}

	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) {
		return false;
	}	

	//grava 1 registo de cada vez no ficheiro
	VeiculosLista* aux = inicio;
	Veiculo* auxVeiculo;	
	while (aux) {		//while(aux!=NULL)
		auxVeiculo = aux->veiculo; 
		fwrite(&auxVeiculo, sizeof(Veiculo), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}

VeiculosLista* LerVeiculosBin(char* nomeFicheiro) {
	FILE* fp;
	VeiculosLista* inicio = NULL;
	Veiculo* aux;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

	//Vai ler o numero de registro no ficheiro
	aux = (Veiculo*)malloc(sizeof(Veiculo));
	while (fread(aux, sizeof(Veiculo), 1, fp)) {
		inicio = InsertVeiculoInicio(inicio, aux);
		aux = (Veiculo*)malloc(sizeof(Veiculo));
	}
	fclose(fp);
	return inicio;
}

#pragma endregion
