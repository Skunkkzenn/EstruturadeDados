/*****************************************************************//**
 * \file   Adjacencia.h
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   May 2023
 *********************************************************************/

#pragma once
#include <stdio.h>
#include <stdbool.h>
#pragma warning (disable: 4996)


typedef struct Adj {
	int cod;	
	float peso; 
	struct Adj* next;
}Adj;


typedef struct AdjFicheiro {
	int codOrigem;
	int codDestino;
	float peso;
}AdjFicheiro;

#pragma region Funções/Métodos Ligações de Vertices

Adj* CriaLigacao(int cod, float peso);
bool ExisteLigacao(Adj* inicio, int cod);
Adj* InsereLigacao(Adj* inicio, Adj* novo, bool* res);
void MostraLigacoes(Adj* head);
int GravaAdjBin(Adj* inicio, char* fileName, int codVerticeOrigem);
Adj* LerAdjBin(Adj* inicio, bool* res);

#pragma endregion

