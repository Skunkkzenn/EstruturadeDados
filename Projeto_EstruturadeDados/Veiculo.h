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

#ifndef Veiculos // Indica o nome do ficheio que será trabalhado
#define Veiculos
#include <stdio.h>
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>
#pragma warning( disable : 4996 ) //evita MSG ERROS: _CRT_SECURE_NO_WARNINGS
#define N 200

#define MAX 40 // Maximo de Veiculos, utilizar mais a frente*

#pragma region	Struct Veículo

typedef struct Veiculo {
	int cod;
	char tipo[N];
	float bateria;
	float custo;
	char local[N];
	struct Veiculo* next; /* Campo seguinte do veiculo;
						   guarda a variável no endereço de memoria do proximo veiculo;
						   temos um apontador na memoria para ir para o próximo veículo; */
}Veiculo;



typedef struct VeiculosLista {
	Veiculo* veiculo;
	struct VeiculosLista* next;  //Validar com o professor onde deve permanecer o ponto next
}VeiculosLista;


#pragma endregion


#pragma region Funcoes que Tratam dos Veiculos

Veiculo* CriaVeiculo(int cod, char* tipo, float bateria, float custo, char* local);
Veiculo* InsertVeiculoInicio(Veiculo* novo, Veiculo* inicio, bool* res);
Veiculo* InsertVeiculoFim(Veiculo* novo, Veiculo* inicio, bool* res);
Veiculo* VerificaVeiculoDuplicado(int cod, char* tipo, Veiculo* inicio, bool* duplicado);
Veiculo* InsertVeiculoLista(Veiculo* novo, Veiculo* inicio, bool* res);
Veiculo* RemoveVeiculo(int cod, char* tipo, Veiculo* inicio, bool* res);
Veiculo* AlteraCampoVeiculo(int cod, char* tipo, float bateria, float custo, char* local, Veiculo* novo, Veiculo* inicio, bool* res);
bool LerDadosVeiculo(char fileName[]);
bool GravarVeiculoBin(char* nomeFicheiro, Veiculo* inicio);
VeiculosLista* LerVeiculosBin(char* nomeFicheiro, bool* res);
void DestroiVeiculo(Veiculo* veiculo);
Veiculo* InsertVeiculoInicio(Veiculo* novo, Veiculo* sup);
Veiculo* InsertVeiculoFim(Veiculo* novo, Veiculo* inicio);
Veiculo* VerificaVeiculoDuplicado(int cod, char* tipo, Veiculo* inicio);
Veiculo* AlteraCampoVeiculo(int cod, char* tipo, float bateria, float custo, char* local, Veiculo* novo, Veiculo* inicio);

bool LerDadosVeiculo(char fileName[]);
bool GravarVeiculoBin(char* nomeFicheiro, Veiculo* inicio);
VeiculosLista* lerVeiculosBinario(char* nomeFicheiro);

#pragma endregion


#endif //; !

