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

#pragma region Funções para trabalhar sobre veículos.

//Criar e inicializar um novo veículo com as informações fornecidas
Veiculo* CriaVeiculo(int cod, char* tipo, float bateria, float custo, char* local) {
	// Cria uma variável para armazenar o ponteiro para o novo veículo
	Veiculo* novoVeiculo;

	// Aloca memória para o novo veículo
	novoVeiculo = (Veiculo*)malloc(sizeof(Veiculo));

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
	if (inicio == NULL)
	{
		inicio = novo;
	}
	else {
		novo->next = inicio;
		inicio = novo;
	}
}

// Inserir Maquina Fim da Lista
/* Esse metodo recebe uma maquina nova para
   inserir e recebe o incio da lista onde se vai inserir */
Veiculo* InsertVeiculoFim(Veiculo* novo, Veiculo* inicio) {
	if (inicio == NULL) //se inicio é igual a NULL, a variavel inicio vai ser igual a novo;
	{
		inicio = novo;
	}
	else // se não, vamos procurar o fim
	{
		Veiculo* aux = inicio; // Usa-se uma variável auxiliar que fica a apontar para o inicio, pois nao podemos alterar o inicio
		while (aux->next != NULL)  /* Enquanto o aux campo next nao for nulo
									  ou
									  Enquanto ele estiver a apontar para alguma coisa seguira sempre. */

			aux = aux->next; // aux toma o valor de aux campo next, dessa forma avançamos na lista e quando acabar o fim do ciclo estamos no fim da lista
		aux->next = novo;
		inicio = novo;
	}
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
		Veiculo* aux = inicio;
		Veiculo* auxSup = NULL;

		//Verificar se já existe repetido
		if (VerificaVeiculoDuplicado(novo->bateria, novo->tipo, inicio) == inicio)
			return inicio;

		//procurar a posicao correta, e ordena pelo cod!!!!
		while (aux && aux->cod < novo->cod) {
			auxSup = aux;
			aux = aux->next;
		}

		if (auxSup == NULL && novo->cod < inicio->cod) { //Insere no início
			novo->next = inicio;
			inicio = novo;
		}
		else if (auxSup == NULL)
		{ //Insere no meio
			novo->next = aux;
			inicio = novo;
		}
		else //Insere no fim
		{
			auxSup->next = novo;
			novo->next = aux;
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

#pragma endregion
