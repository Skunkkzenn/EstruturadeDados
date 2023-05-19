/*****************************************************************//**
 * \file   Vertice.c
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   May 2023
 *********************************************************************/

#include <stdlib.h>
#include <string.h>
#include "Vertice.h"

#pragma region Funções Vértices

 /**
  * @brief Inicia grafo, sem orientação
  * @author Victor Destefani
  * @return
  */
Vertice* CriarGrafo() {
	return NULL;
}


/**
 * @brief Cria um ponto de recolha dentro do grafo
 * @author Victor Destefani
 * @param cidade
 * @param cod
 * @return ponteiro para o novo ponto de recolha criado.
 */
Vertice* CriaPontoRecolha(char* cidade, int cod, bool* res) {
	*res = false;
	Vertice* novo = (Vertice*)calloc(1, sizeof(Vertice));
	if (novo == NULL) return NULL;
	novo->cod = cod;
	strcpy(novo->cidade, cidade);
	novo->next = NULL;
	*res = true;
	return novo;
}


/**
 * @brief Insere ponto de recolha no grafo
 * @author Victor Destefani
 * @param g
 * @param novo
 * @param
 * @return
 */
Vertice* InserePontoRecolha(Vertice* g, Vertice* novo, bool* res) {
	*res = false;
	if (novo == NULL) {
		return g;
	}

	// Verifica se o ponto de recolha já existe na lista
	bool existe = false;
	Vertice* pontoExistente = ProcuraPontoRecolha(g, novo->cidade, &existe);
	if (existe)
	{
		free(novo); // Libera a memória alocada para o novo ponto de recolha
		return g;
	}

	// Insere o novo ponto de recolha na lista
	if (g == NULL) {
		g = novo;
		*res = true;
	}
	else
	{
		Vertice* aux = g;
		Vertice* ant = aux;
		while (aux && strcmp(aux->cidade, novo->cidade) < 0) {
			ant = aux;
			aux = aux->next;
		}
		if (aux == g)
		{
			novo->next = g;
			g = novo;
		}
		else
		{
			novo->next = aux;
			ant->next = novo;
		}
		*res = true;
	}
	return g;
}


/**
 * @brief Exibe o Grafo
 * @author Victor Destefani
 * @param g
 */
void ExibeGrafo(Vertice* g, bool* res) {
	*res = false;
	if (g == NULL) return;
	printf("Vertice: %d - %s\n", g->cod, g->cidade);
	MostraLigacoes(g->adjacentes);
	ExibeGrafo(g->next, res);
	*res = true;
}


/**
 * @brief Verifica se existe ponto de recolha pela cidade
 * @author Victor Destefani
 * @param g
 * @param cidade
 * @return Cod. da cidade
 */
int ProcuraCodPontoRecolha(Vertice* g, char* cidade, bool* res) {
	*res = false;
	if (g == NULL) return -1;
	if (strcmp(g->cidade, cidade) == 0) {
		*res = true;
		return g->cod;
	}
	return(ProcuraCodPontoRecolha(g->next, cidade, res));
}


/**
 * @brief Verifica se existe ponto de recolha pela cidade
 * @author Victor Destefani
 * @param g
 * @param cidade
 * @return Retorna o ponteiro para o nó que contém o ponto de recolha
 */
Vertice* ProcuraPontoRecolha(Vertice* g, char* cidade, bool* res) {
	*res = false;
	if (g == NULL) return NULL;
	if (strcmp(g->cidade, cidade) == 0) {
		*res = true;
		return g;
	}
	return(ProcuraPontoRecolha(g->next, cidade, res));
}

/**
 * @brief Insere ligação entre pontos de recolha.
 * @author Victor Destefani
 * @param g
 * @param origem
 * @param dest
 * @param peso
 * @return
 */
Vertice* InsLigPontoRecolha(Vertice* g, char* origem, char* dest, float peso, bool* res) {
	*res = false; //inicia sempre como falso
	if (g == NULL) return g;

	Vertice* aux = ProcuraPontoRecolha(g, origem, res); // busca vertice de origem
	int cod = ProcuraCodPontoRecolha(g, dest, res);  // busca vertice de destino

	if (aux == NULL || cod < 0) return g; // Se não foi encontrado o vertice origem e destino, ignora operação

	if (ExisteLigacao(aux->adjacentes, cod)) return g; //Se já foi registrado a ligacação entre os pontos, ignora a operação

	//Insere nova ligacao ao vertice de origem
	Adj* novoAdj = CriaLigacao(cod, peso);
	aux->adjacentes = InsereLigacao(aux->adjacentes, novoAdj, res);

	*res = true; // indica que a operação foi concluída com sucesso
	return g;
}
#pragma endregion