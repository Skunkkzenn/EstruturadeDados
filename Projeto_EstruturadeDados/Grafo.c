/*****************************************************************//**
 * \file   Grafo.c
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   April 2023
 *********************************************************************/
#include "Grafo.h"

/**
 * \brief Cria Grafo
 * 
 * \param numVertices
 * \param mat
 * \return 
 * \author	Victor Destefani	
 */
bool CriaGrafo(int numVertices, float mat[][MAX]){
	if (numVertices > MAX || numVertices < 0) return false;
	for (int i = 0; i < numVertices; i++)
		for (int j = 0; j < numVertices; j++)
		{
			mat[i][j] = -1;
		}
	return true;
}

/**
 * \brief Insere Vertice no Grafo
 * 
 * \param v
 * \param numVert
 * \param local
 * \return 
 * \author Victor Destefani
 * 
 */
bool InsereVertice(Vertice v[], int* numVert, char* local) {
	if (*numVert > MAX)
		return false;
	v[*numVert].valor = *numVert;
	strcpy(v[*numVert].nome, local);
	(*numVert)++;
	return true;
}


/**
 * \brief Insere Arestas e pesos.
 * 
 * \param ma
 * \param totVertices
 * \param v
 * \param numVertices
 * \param origem
 * \param destino
 * \param p
 * \return 
 */
bool InsereAresta(float ma[][MAX], int totVertices, Vertice v[], int numVertices, char* origem, char* destino, float p) {

	int vOrigem = -1;
	int vDestino = -1;

	//procurar o vertice origem
	for (int i = 0; i < numVertices; i++) {
		if (strcmp(v[i].nome, origem) == 0) {
			vOrigem = i;
			continue;
		}

		if (strcmp(v[i].nome, destino) == 0) {
			vDestino = i;
			continue;
		}
	}
	if (vOrigem == -1 || vDestino == -1) return false;

	//Registar pesos
	ma[vOrigem][vDestino] = p;
	ma[vDestino][vOrigem] = p;
	return true;
}