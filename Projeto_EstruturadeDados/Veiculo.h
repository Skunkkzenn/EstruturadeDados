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
#pragma warning( disable : 4996 ) 
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
Veiculo* ProcuraVeiculo(Veiculo* inicio, int cod, const char* tipo);
Veiculo* InsertVeiculoInicio(Veiculo* inicio, Veiculo* novo, bool* res);
Veiculo* InsertVeiculoFim(Veiculo* inicio, Veiculo* novo, bool* res);
Veiculo* VerificaVeiculoDuplicado(Veiculo* inicio, int cod, char* tipo, bool* res);
Veiculo* InsertVeiculoLista(Veiculo* inicio, Veiculo* novo, bool* res);
Veiculo* RemoveVeiculo(Veiculo* inicio, int cod, char* tipo,bool* res);
Veiculo* AlteraCampoVeiculo(Veiculo* inicio, Veiculo* novo, int cod, char* tipo, float bateria, float custo, char* local, bool* res);
bool LerDadosVeiculo(char fileName[]);
bool GravarVeiculoBin(char* nomeFicheiro, Veiculo* inicio);
Veiculo* LerVeiculoBin(char* nomeFicheiro, bool* res);

#pragma endregion


