/*****************************************************************//**
 * \file   Adjacencia.c
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   May 2023
 *********************************************************************/

#include "Adjacencia.h"
#include "Vertice.h"
#include <stdlib.h>
#include <string.h>


#pragma region Funções Adjacências

 /**
  * @brief Cria novo nó de ligações.
  * @author Victor Destefani
  * @param cod
  * @param peso
  * @return
  */
Adj* CriaLigacao(int cod, float peso) {
	Adj* novo = (Adj*)calloc(1, sizeof(Adj));
	if (novo == NULL) return NULL;
	novo->cod = cod;
	novo->peso = peso;
	novo->next = NULL;
	return novo;
}

/**
 * @brief Verifica se X ligação Existe.
 * @author Victor Destefani
 * @param head
 * @param cod
 * @return
 */
bool ExisteLigacao(Adj* inicio, int cod) {
	while (inicio != NULL)
	{
		if (inicio->cod == cod) return true;
		inicio = inicio->next;
	}
	return false;
}

/**
 * @brief Insere Ligação
 * @author Victor Destefani
 * @param inicio
 * @param novo
 * @param
 * @return
 */
Adj* InsereLigacao(Adj* inicio, Adj* novo, bool* res) {
	if (novo == NULL) /* Se o novo nó for nulo, retorna lista original,
						 definindo res como falso, indicando que a
						 inserção não foi realizada com sucesso */
	{
		*res = false;
		return inicio;
	}
	if (inicio == NULL || inicio->cod > novo->cod)/* Verifica se a lista esta vazia OU se o novo no deve ser inserido antes da cabeça da lista.
												 O novo nó será inserido na primeira posição, res é definido como true confirmando a execução
												 da tarefa e a função retorna o ponteiro para o novo no. 	*/

	{
		novo->next = inicio;
		*res = true;
		return novo;
	}
	if (inicio->cod == novo->cod) /* Verifica se o nó que vai ser inserido já existe na lista.
								   Se sim, a função retorna a lista original e marca res como falso */
	{
		*res = false;
		return inicio;
	}
	inicio->next = InsereLigacao(inicio->next, novo, res); /* Utilizando a recursividade, a função InsereLigacao percorre a lista até encontrar
														o local correto para inserção. Quando encntrar, insere o novo nó e retorna o ponteiro
														para a cabeça da lista. */
	*res = true;
	return inicio;
}

/**
 * @brief Exibe Ligações
 * @author Victor Destefani
 * @param head
 */
void MostraLigacoes(Adj* head) { /* Verifica se o ponteiro para lista é diferente de NULL, se for,
									devolve as informações impressas do nó atual e em seguida chama novamente a propria função,
									passando como parãmetro o proximo no da lista, o processo se repete ate que o ponteiro para o nó seja NULL,
									demostrando o final da lista. */
	if (head != NULL) {
		printf("\tAdj: %d - %.0f km\n", head->cod, head->peso);
		MostraLigacoes(head->next);
	}
}

/**
 * @brief Grava Adjacência em bin.
 * @author Victor Destefani
 * @param inicio
 * @param fileName
 * @param codVerticeOrigem
 * @return
 */
int GravaAdjBin(Adj* inicio, char* fileName, int codVerticeOrigem) {
	FILE* fp;

	if (inicio == NULL) return -2; // falha na abertura do arquivo
	fp = fopen(fileName, "ab");
	if (fp == NULL) return -1; // ausência de vértices no grafo
	Adj* auxAdj = inicio;
	AdjFicheiro auxFileAdj;

	while (auxAdj != NULL) {
		auxFileAdj.codDestino = auxAdj->cod;
		auxFileAdj.codOrigem = codVerticeOrigem;
		auxFileAdj.peso = auxAdj->peso;
		fwrite(&auxFileAdj, 1, sizeof(AdjFicheiro), fp);
		auxAdj = auxAdj->next;
	}
	fclose(fp);
	return 1;
}


/**
 * @brief Lê binário de Adjacências.
 * @author Victor Destefani
 * @param inicio
 * @param 
 * @return 
 */
Adj* LerAdjBin(Adj* inicio, bool* res) {
	*res = false;
	FILE* fp;

	AdjFicheiro auxFicheiro;
	Vertice* auxVertice = inicio;

	while (auxVertice) {
		fp = fopen(auxVertice->cidade, "rb");
		if (fp != NULL) {
			while (fread(&auxFicheiro, 1, sizeof(AdjFicheiro), fp)) {
				inicio = InsereLigacaoRecolhaCod(inicio, auxFicheiro.codDestino, auxFicheiro.codDestino, auxFicheiro.peso, res);
			}
			fclose(fp);
		}
		auxVertice = auxVertice->next;
	}
	return inicio;
}

#pragma endregion