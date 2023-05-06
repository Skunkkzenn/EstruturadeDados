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


/* Estrutura de Adjacência */
typedef struct Adj {
	int cod;	/* Cod. de Adjacência */
	float peso; /* Peso */
	struct Adj* next;
}Adj;