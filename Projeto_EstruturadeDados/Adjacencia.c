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


#pragma region Fun��es Adjac�ncias

 /**
  * @brief Cria novo n� de liga��es.
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
 * @brief Verifica se X liga��o Existe.
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
 * @brief Insere Liga��o
 * @author Victor Destefani
 * @param inicio
 * @param novo
 * @param
 * @return
 */
Adj* InsereLigacao(Adj* inicio, Adj* novo, bool* res) {
	if (novo == NULL) /* Se o novo n� for nulo, retorna lista original,
						 definindo res como falso, indicando que a
						 inser��o n�o foi realizada com sucesso */
	{
		*res = false;
		return inicio;
	}
	if (inicio == NULL || inicio->cod > novo->cod)/* Verifica se a lista esta vazia OU se o novo no deve ser inserido antes da cabe�a da lista.
												 O novo n� ser� inserido na primeira posi��o, res � definido como true confirmando a execu��o
												 da tarefa e a fun��o retorna o ponteiro para o novo no. 	*/

	{
		novo->next = inicio;
		*res = true;
		return novo;
	}
	if (inicio->cod == novo->cod) /* Verifica se o n� que vai ser inserido j� existe na lista.
								   Se sim, a fun��o retorna a lista original e marca res como falso */
	{
		*res = false;
		return inicio;
	}
	inicio->next = InsereLigacao(inicio->next, novo, res); /* Utilizando a recursividade, a fun��o InsereLigacao percorre a lista at� encontrar
														o local correto para inser��o. Quando encntrar, insere o novo n� e retorna o ponteiro
														para a cabe�a da lista. */
	*res = true;
	return inicio;
}

/**
 * @brief Exibe Liga��es
 * @author Victor Destefani
 * @param head
 */
void MostraLigacoes(Adj* head) { /* Verifica se o ponteiro para lista � diferente de NULL, se for,
									devolve as informa��es impressas do n� atual e em seguida chama novamente a propria fun��o,
									passando como par�metro o proximo no da lista, o processo se repete ate que o ponteiro para o n� seja NULL,
									demostrando o final da lista. */
	if (head != NULL) {
		printf("\tAdj: %d - %.0f km\n", head->cod, head->peso);
		MostraLigacoes(head->next);
	}
}

/**
 * @brief Grava Adjac�ncia em bin.
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
	if (fp == NULL) return -1; // aus�ncia de v�rtices no grafo
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
 * @brief L� bin�rio de Adjac�ncias.
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