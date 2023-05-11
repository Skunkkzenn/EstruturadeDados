/*****************************************************************//**
 * \file   Grafo.h
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   April 2023
 *********************************************************************/
#pragma once

#include <stdbool.h>
#define MAX 10
#define N 20

typedef struct Vertice {
	int valor;
	char nome[N];
}Vertice;


bool CriaGrafo(int numVertices, float mat[][MAX]);
bool InsereVertice(Vertice v[], int* numVert, char* local);
bool InsereAresta(float ma[][MAX], int totVertices, Vertice v[], int numVertices, char* origem, char* destino, float p);
