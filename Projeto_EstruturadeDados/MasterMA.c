/*****************************************************************//**
 * \file   MainMaster.c
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   March 2023
 *********************************************************************/

#include <stdio.h>
#include <string.h> // para as strings
#include <stdbool.h>
#include <stdlib.h>
#include "Veiculo.h"
#include "Cliente.h"
#include "Gestor.h"
#include "GrafoMA.h"
#pragma warning( disable : 4996 )

#define VERT 15

int main() {
    /* Veiculos Leitura e Gravação em ficheiro Binário */
    char fileName[] = "veiculos.txt";
    bool sucesso = LerDadosVeiculo(fileName);



    /* Vertices */
    //Conjunto de Vertices
    Vertice vertices[MAX];

    //Matriz de Adjacência
    float ma[MAX][MAX];

    bool aux = CriaGrafo(VERT, ma);

    //numero da corrente de vertices
    int totVertices = 0;

    aux = InsereVertice(vertices, &totVertices, "Sao Vitor");
    aux = InsereVertice(vertices, &totVertices, "Lamacaes");
    aux = InsereVertice(vertices, &totVertices, "Santa Tecla");

    //Criar o grafo
    aux = InsereAresta(ma, VERT, vertices, totVertices, "Sao Victor", "Lamacaes", 15);
    aux = InsereAresta(ma, 5, vertices, totVertices, "Lamacaes", "Santa Tecla", 20);
    aux = InsereAresta(ma, 5, vertices, totVertices, "Santa Tecla", "Sao Victor", 35);
}
