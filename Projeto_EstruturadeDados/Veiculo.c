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

#pragma region M�todos Ve�culos.

//Criar e inicializar um novo ve�culo com as informa��es fornecidas
Veiculo* CriaVeiculo(int cod, char* tipo, float bateria, float custo, char* local) {
	// Cria uma vari�vel para armazenar o ponteiro para o novo ve�culo
	Veiculo* novoVeiculo;

	// Aloca mem�ria para o novo ve�culo
	novoVeiculo = (Veiculo*)malloc(sizeof(Veiculo));
	// Verifica se a aloca��o de mem�ria foi bem sucedida
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

 	if (novo == NULL) { /* Se o ponteiro "novo" apontar para NULL, a fun��o ter� um erro e
						   retornar� o ponteiro "inicio" original sem modificar a lista.
						   Caso contr�rio, a fun��o prossegue com a inser��o do novo cliente na lista.
						*/
						//printf("Erro: novo cliente e nulo\n");
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
	return inicio; //� necess�rio que ela retorne o ponteiro para o in�cio da lista atualizado ap�s a inser��o do novo ve�culo.
}

// Inserir Maquina Fim da Lista
/* Esse metodo recebe uma maquina nova para
   inserir e recebe o incio da lista onde se vai inserir */
Veiculo* InsertVeiculoFim(Veiculo* novo, Veiculo* inicio) {
	if (inicio == NULL) // Se a lista estiver vazia, o novo n� ser� a cabe�a da lista
	{
		inicio = novo;
	}
	else  // Se a lista n�o estiver vazia, insere o novo n� no final
	{
		Veiculo* aux = inicio; // Usa-se uma vari�vel auxiliar que fica a apontar para o inicio, pois nao podemos alterar o inicio
		while (aux->next != NULL) {  /* Enquanto o aux campo next nao for nulo
									  ou
									  Enquanto ele estiver a apontar para alguma coisa seguira sempre. */
			aux = aux->next; // aux toma o valor de aux campo next, dessa forma avan�amos na lista e quando acabar o fim do ciclo estamos no fim da lista
		}
		aux->next = novo;
	}
	novo->next = NULL; // O campo next do novo n� deve ser nulo
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

		//Verificar se j� existe repetido
		if (VerificaVeiculoDuplicado(novo->cod, novo->tipo, inicio) == inicio)
			return inicio;

		//procurar a posicao correta, e ordena pelo cod!!!!
		while (atual && atual->cod < novo->cod) {
			anterior = atual;
			atual = atual->next;
		}

		if (anterior == NULL && novo->cod < inicio->cod) { //Insere no in�cio
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
	Veiculo* noAnterior = inicio;
	Veiculo* noAtual = inicio;

	// Verifica se o n� a ser removido � a cabe�a da lista
	if ((inicio != NULL) && (inicio->cod == cod)) { // O ve�culo a ser removido � o primeiro da lista (inicio)
		noAnterior = noAnterior->next; // Atualiza a lista para come�ar do segundo elemento
		free(inicio); // Libera a mem�ria ocupada pelo ve�culo removido
		inicio = noAnterior;  // atualiza o in�cio da lista
	}
	else
	{   // Percorre a lista at� encontrar o n� a ser removido
		while ((noAtual != NULL) && (noAtual->cod != cod) && (strcmp(noAtual->tipo, tipo) != 0)) { // percorre array enquanto...
			{
				// Procura pelo ve�culo a ser removido
				noAnterior = noAtual; // avan�a o ponteiro auxAnt para o pr�ximo n�
				noAtual = noAtual->next; // avan�a o ponteiro auxProx para o pr�ximo n�
			}
			if ((noAtual == NULL) || (noAnterior->next == NULL) || (noAnterior->cod != cod)) {
				// N�o foi encontrado nenhum ve�culo com o c�digo e tipo especificados
				return inicio; // nao existe a maquina, retorna in�cio
			}
		}
		// Remove o ve�culo encontrado
		noAnterior->next = noAtual->next; // auxAnt campo next passa a conter o valor de auxProx campo next!
		free(noAtual); // liberta a mem�ria que � removida
	}
	return inicio; // Retorna head
}

// Recebe dois ponteiros para um arquivo bin�rio e um arquivo de texto
// L� as informa��es do arquivo bin�rio e exibe o resultado no terminal.
bool exibe_conteudo_arquivo(FILE* arquivo_binario, FILE* arquivo_texto) {
	Veiculo veiculo;
	int linhas_lidas = 0; // armazena o n�mero de ve�culos lidos no arquivo.

	// L� as informa��es do arquivo bin�rio e exibe na tela
	while (fread(&veiculo, sizeof(Veiculo), 1, arquivo_binario) == 1) {
		printf("%d;%s;%f;%f;%s\n", veiculo.cod, veiculo.tipo, veiculo.bateria, veiculo.custo, veiculo.local);
		linhas_lidas++;
		// Escreve as informa��es do ve�culo no arquivo de texto
		fprintf(arquivo_texto, "%d;%s;%f;%f;%s\n", veiculo.cod, veiculo.tipo, veiculo.bateria, veiculo.custo, veiculo.local);
	}
	// Verifica se ocorreu algum erro durante a grava��o do arquivo de texto
	if (ferror(arquivo_texto)) {
		return false;
	}

	return true;
}

// Tamb�m recebe dois ponteiros para um arquivo bin�rio e um arquivo de texto
// L� as informa��es do arquivo de texto e as escreve no bin�rio "cod;tipo;bateria;custo;local". 

bool atualiza_arquivo_binario(FILE* arquivo_binario, FILE* arquivo_texto) {
	Veiculo veiculo;
	int linhas_lidas = 0; // armazena o n�mero de linhas(ve�culos) lidas no arquivo de texto e escritas no arquivo bin�rio.

	memset(&veiculo, 0, sizeof(Veiculo)); // inicializa��o com valores zerados

	fscanf(arquivo_texto, "%*[^\n]"); // Descarta a primeira linha do arquivo de texto

	while (fscanf(arquivo_texto, "%d;%[^;];%f;%f;%[^\n]\n", &veiculo.cod, veiculo.tipo, &veiculo.bateria, &veiculo.custo, veiculo.local) != EOF) {
		fwrite(&veiculo, sizeof(Veiculo), 1, arquivo_binario);
		linhas_lidas++;
	}
	return linhas_lidas;
}
#pragma endregion
