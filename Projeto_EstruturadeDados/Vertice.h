/*****************************************************************//**
 * \file   Vertice.h
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   May 2023
 *********************************************************************/
#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "Adjacencia.h"
#pragma warning (disable: 4996)

#define N 50

/* Vertice em Grafo */
typedef struct Vertice {
	int cod;
	char cidade[N];
	struct Vertice* next;
	struct Adj* adjacentes;
}Vertice;

#pragma region Métodos/Assinaturas para Grafos

Vertice* CriarGrafo();
Vertice* CriaPontoRecolha(char* cidade, int cod);
Vertice* InserePontoRecolha(Vertice* g, Vertice* novo, bool* res);
void ExibeGrafo(Vertice* g);
int ProcuraCodPontoRecolha(Vertice* g, char* cidade);
Vertice* ProcuraPontoRecolha(Vertice* g, char* cidade);
Vertice* InsLigPontoRecolha(Vertice* g, char* origem, char* dest, float peso, bool* res);

#pragma endregion