/*****************************************************************//**
 * \file   Veiculo.h
 * \brief  Projeto EDA
 * \number 18586
 * \author Victor Destefani
 * \date   March 2023
 *********************************************************************/
/*
* Mobilidade Elétrica - Estrutura Veiculos
*/



#include <stdio.h>
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>
#pragma warning( disable : 4996 ) //evita MSG ERROS: _CRT_SECURE_NO_WARNINGS
#define N 200

#pragma region	Struct Veículo

typedef struct Veiculo {
	int cod;
	char tipo[N];
	float bateria;
	float custo;
	char local[N];
	struct Veiculo* next;
}Veiculo;



typedef struct VeiculosFicheiro {
	int cod;
	char tipo[N];
	float bateria;
	float custo;
	char local[N];
}VeiculosFicheiro;


#pragma endregion


#pragma region Funcoes que Tratam dos Veiculos

Veiculo* CriaVeiculo(int cod, char* tipo, float bateria, float custo, char* local, bool* res);
Veiculo* InsertVeiculoInicio(Veiculo* novo, Veiculo* inicio, bool* res);
Veiculo* InsertVeiculoFim(Veiculo* novo, Veiculo* inicio, bool* res);
Veiculo* VerificaVeiculoDuplicado(int cod, char* tipo, Veiculo* inicio, bool* duplicado);
Veiculo* InsertVeiculoLista(Veiculo* novo, Veiculo* inicio, bool* res);
Veiculo* RemoveVeiculo(int cod, char* tipo, Veiculo* inicio, bool* res);
Veiculo* AlteraCampoVeiculo(int cod, char* tipo, float bateria, float custo, char* local, Veiculo* novo, Veiculo* inicio, bool* res);
bool LerDadosVeiculo(char fileName[]);
bool GravarVeiculoBin(char* nomeFicheiro, Veiculo* inicio);
VeiculosFicheiro* LerVeiculoBin(char* nomeFicheiro, bool* res);
#pragma endregion


