/*****************************************************************//**
 * \file   Veiculo.h
 * \brief  Projeto EDA
 * \number 18586
 * \author Victor Destefani
 * \date   March 2023
 *********************************************************************/
/*
* Mobilidade El�trica - Estrutura Veiculos
*/

#ifndef Veiculos // Indica o nome do ficheio que ser� trabalhado
#define Veiculos
#include <stdio.h>
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>
#pragma warning( disable : 4996 ) //evita MSG ERROS: _CRT_SECURE_NO_WARNINGS
#define N 50

#define MAX 40 // Maximo de Veiculos, utilizar mais a frente*

#pragma region	Struct Ve�culo

typedef struct Veiculo {
	int cod;
	char tipo[N];
	float bateria;
	float custo;
	char local[N];
	struct Veiculo* next; /* Campo seguinte do veiculo;
						   guarda a vari�vel no endere�o de memoria do proximo veiculo;
						   temos um apontador na memoria para ir para o pr�ximo ve�culo; */
}Veiculo;

#pragma endregion
#endif //; !

