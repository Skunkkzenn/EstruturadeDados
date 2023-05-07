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


/* Estrutura de Adjac�ncia */
typedef struct Adj {
	int cod;	/* Cod. de Adjac�ncia */
	float peso; /* Peso */
	struct Adj* next;
}Adj;

#pragma region Fun��es/M�todos Liga��es de Vertices

Adj* CriaLigacao(int cod, float peso);
bool ExisteLigacao(Adj* head, int cod);
Adj* InsereLigacao(Adj* head, Adj* novo, bool* res);
void MostraLigacoes(Adj* head);

#pragma endregion
