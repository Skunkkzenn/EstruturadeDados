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

/* Inicia grafo pesado, não orientado */
Vertice* CriarGrafo() {
	return NULL;
}


/* Cria um ponto de recolha dentro do grafo */
Vertice* CriaPontoRecolha(char* cidade, int cod) {
	Vertice* novo = (Vertice*)calloc(1, sizeof(Vertice));
	if (novo == NULL) return NULL;
	novo->cod = cod;
	strcpy(novo->cidade, cidade);
	novo->next = NULL;
	return novo;
}


/* Insere ponto de recolha no grafo */
Vertice* InserePontoRecolha(Vertice* g, Vertice* novo, bool* res) {
	if (g == NULL) {
		g = novo;
		*res = true;
		return g;
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


/* Exibe o Grafo */
void ExibeGrafo(Vertice* g) {
	if (g == NULL) return;
	printf("Vertice: %d - %s\n", g->cod, g->cidade);
	MostraLigacoes(g->adjacentes);
	ExibeGrafo(g->next);
}


/* Verifica o ponto de recolha pelo seu cod. */
int ProcuraCodPontoRecolha(Vertice* g, char* cidade) {
	if (g == NULL) return -1;
	if (strcmp(g->cidade, cidade) == 0) return g->cod;
	return(ProcuraCodPontoRecolha(g->next, cidade));
}


/* Procura ponto de recolha */
Vertice* ProcuraPontoRecolha(Vertice* g, char* cidade) {
	if (g == NULL) return NULL;
	if (strcmp(g->cidade, cidade) == 0) return g;
}


Vertice* InsLigPontoRecolha(Vertice* g, char* origem, char* dest, float peso, bool* res) {
	*res = false; //inicia sempre como falso
	if (g == NULL) return g;	
	
	Vertice* aux = ProcuraPontoRecolha(g, origem); // busca vertice de origem
	int cod = ProcuraCodPontoRecolha(g, dest);  // busca vertice de destino
	
	if (aux == NULL || cod < 0) return g; // Se não foi encontrado o vertice origem e destino, ignora operação

	if (ExisteLigacao(aux->adjacentes, cod) == true) return g; //Se já foi registrado a ligacação entre os pontos, ignora a operação

	//Insere nova ligacao ao vertice de origem
	Adj* novoAdj = CriaLigacao(cod, peso);
	aux->adjacentes = InsereLigacao(aux->adjacentes, novoAdj, res);
	return g;
	
}
#pragma endregion