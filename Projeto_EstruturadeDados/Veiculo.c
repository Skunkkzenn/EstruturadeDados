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

#pragma region Fun��es para trabalhar sobre ve�culos.

//Criar e inicializar um novo ve�culo com as informa��es fornecidas
Veiculo* CriaVeiculo(int cod, char* tipo, float bateria, float custo, char* local) {
	// Cria uma vari�vel para armazenar o ponteiro para o novo ve�culo
	Veiculo* novoVeiculo;

	// Aloca mem�ria para o novo ve�culo
	novoVeiculo = (Veiculo*)malloc(sizeof(Veiculo));

	if (novoVeiculo == NULL)
	{   //printf("Erro ao alocar mem�ria para novo ve�culo\n");
		return NULL;
	}

	// Inicializa os campos do novo ve�culo com as informa��es fornecidas
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
		* No inicio da fun��o verifica-se se sup � nulo
		* Se for nulo, � definido como o novo ve�culo e � retornado.
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
	if (inicio == NULL) //se inicio � igual a NULL, a variavel inicio vai ser igual a novo;
	{
		inicio = novo;
	}
	else // se n�o, vamos procurar o fim
	{
		Veiculo* aux = inicio; // Usa-se uma vari�vel auxiliar que fica a apontar para o inicio, pois nao podemos alterar o inicio
		while (aux->next != NULL)  /* Enquanto o aux campo next nao for nulo
									  ou
									  Enquanto ele estiver a apontar para alguma coisa seguira sempre. */

			aux = aux->next; // aux toma o valor de aux campo next, dessa forma avan�amos na lista e quando acabar o fim do ciclo estamos no fim da lista
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

		//Verificar se j� existe repetido
		if (VerificaVeiculoDuplicado(novo->bateria, novo->tipo, inicio) == inicio)
			return inicio;

		//procurar a posicao correta, e ordena pelo cod!!!!
		while (aux && aux->cod < novo->cod) {
			auxSup = aux;
			aux = aux->next;
		}

		if (auxSup == NULL && novo->cod < inicio->cod) { //Insere no in�cio
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
	if (inicio == NULL) // Verifica se a lista encadeada est� vazia (inicio == NULL), caso esteja retorna NULL, indicando que n�o h� ve�culos duplicados.
	{
		return NULL; // Caso n�o encontre nenhum ve�culo com o mesmo c�digo e tipo, retorna NULL.
	}

	Veiculo* aux = inicio;
	while ((aux != NULL) && (aux->cod != cod) && (strcmp(aux->tipo, tipo) != 0)) // Percorre a lista encadeada, enquanto n�o chegar ao final da lista (aux != NULL) e n�o encontrar um ve�culo com o mesmo c�digo e tipo (aux->cod != cod) && (strcmp(aux->tipo, tipo) != 0). Se encontrar um ve�culo com o mesmo c�digo e tipo, retorna um ponteiro para esse ve�culo (aux).
	{
		aux = aux->next;
	}
	return aux;
}

// Altera Dados do Veiculo
Veiculo* AlteraCampoVeiculo(int cod, char* tipo, float bateria, float custo, char* local, Veiculo* novo, Veiculo* inicio) {
	// Verifica se a lista est� vazia
	if (inicio == NULL)
	{
		inicio = novo;
	}

	// Cria um ponteiro auxiliar para percorrer a lista
	Veiculo* aux = inicio;

	// Percorre a lista at� encontrar o ve�culo com o c�digo e tipo informado
	while ((aux != NULL) && (aux->cod != cod) && (strcmp(aux->tipo, tipo) != 0)) { // Percorre a lista encadeada, enquanto n�o chegar ao final da lista (aux != NULL) e n�o encontrar um ve�culo com o mesmo c�digo e tipo (aux->cod != cod) && (strcmp(aux->tipo, tipo) != 0). Se encontrar um ve�culo com o mesmo c�digo e tipo, retorna um ponteiro para esse ve�culo (aux).
		aux = aux->next;
	}

	// Se n�o encontrou o ve�culo com o c�digo informado, retorna a lista original
	if ((aux == NULL) || aux->cod != cod)
		return inicio;

	// Altera os campos do ve�culo encontrado com as informa��es fornecidas
	aux->cod = novo->cod;
	strcpy(aux->tipo, novo->tipo);
	aux->bateria = novo->bateria;
	aux->custo = novo->custo;
	strcpy(aux->local, novo->local);
	// Libera a mem�ria alocada para o ve�culo novo
	free(novo);
	// Retorna a lista atualizada
	return inicio;
}

// Remove Veiculo da Lista
Veiculo* RemoveVeiculo(int cod, char* tipo, Veiculo* inicio) {
	// Verifica se o in�cio � nulo (lista vazia)
	if (inicio == NULL) {
		return NULL; // N�o h� nenhum ve�culo para ser removido
	}

	// Inicializa ponteiros auxiliares
	Veiculo* auxAnt = inicio;
	Veiculo* auxProx = inicio;

	// Verifica se o n� a ser removido � a cabe�a da lista
	if ((inicio != NULL) && (inicio->cod == cod)) { // O ve�culo a ser removido � o primeiro da lista (inicio)
		auxAnt = auxAnt->next; // Atualiza a lista para come�ar do segundo elemento
		free(inicio); // Libera a mem�ria ocupada pelo ve�culo removido
		inicio = auxAnt;  // atualiza o in�cio da lista
	}
	else
	{   // Percorre a lista at� encontrar o n� a ser removido
		while ((auxProx != NULL) && (auxProx->cod != cod) && (strcmp(auxProx->tipo, tipo) != 0)) { // percorre array enquanto...
			{
				// Procura pelo ve�culo a ser removido
				auxAnt = auxProx; // avan�a o ponteiro auxAnt para o pr�ximo n�
				auxProx = auxProx->next; // avan�a o ponteiro auxProx para o pr�ximo n�
			}
			if ((auxProx == NULL) || (auxAnt->next == NULL) || (auxAnt->cod != cod)) {
				// N�o foi encontrado nenhum ve�culo com o c�digo e tipo especificados
				return inicio; // nao existe a maquina, retorna in�cio
			}
		}
		// Remove o ve�culo encontrado
		auxAnt->next = auxProx->next; // auxAnt campo next passa a conter o valor de auxProx campo next!
		free(auxProx); // liberta a mem�ria que � removida
	}
	return inicio; // Retorna head
}


#pragma endregion
