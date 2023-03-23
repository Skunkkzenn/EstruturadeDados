/*****************************************************************//**
 * \file   Gestor.h
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   March 2023
 *********************************************************************/

#include <stdio.h>
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>
#pragma warning( disable : 4996 ) //evita MSG ERROS: _CRT_SECURE_NO_WARNINGS
#define N 200
#define MAX 40 // Maximo de Gestores, utilizar mais a frente*

#pragma region Struct Gestor

typedef struct Gestor {
	int cod;
	char nome[N];
	float saldo;
	long int nif;
	char morada[N];
	struct Gestor* next; // temos uma variavel a apontar para o proximo gestor

}Gestor;

#pragma endregion
