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
	bool visitado;
	struct Vertice* next;
	struct Adj* adjacentes;
}Vertice;

typedef struct VerticesFicheiro {
	int cod;
	char cidade[N];
}VerticesFicheiro;

#pragma region Métodos/Assinaturas para Grafos

Vertice* CriarGrafo();
Vertice* CriaPontoRecolha(char* cidade, int cod, bool* res);
Vertice* InserePontoRecolha(Vertice* inicio, Vertice* novo, bool* res);
Vertice* InsLigPontoRecolha(Vertice* inicio, char* origem, char* dest, float peso, bool* res);
void ExibeGrafo(Vertice* inicio, bool* res);
int ProcuraCodPontoRecolha(Vertice* inicio, char* cidade);
Vertice* ProcuraPontoRecolha(Vertice* inicio, char* cidade);
Vertice* ProcuraRecolhaCod(Vertice* inicio, int cod);
Vertice* LimpaVertices(Vertice* inicio);
int GravarGrafo(Vertice* inicio, char* nomeFicheiro);
Vertice* LerGrafoBin(Vertice* inicio, char* fileName, bool* res);

#pragma endregion