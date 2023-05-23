/*****************************************************************//**
 * \file   Cliente.h
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

#pragma region Struct Cliente

typedef struct Cliente {
	int cod;
	char nome[N];
	float saldo;
	long int nif;
	char morada[N];
	struct Cliente* next;
}Cliente;

typedef struct ClientesFicheiro {
	int cod;
	char nome[N];
	float saldo;
	long int nif;
	char morada[N];
}ClientesFicheiro;

#pragma endregion

#pragma region Funcoes para Tratar Clientes

Cliente* CriaCliente(int cod, char* nome, float saldo, long int nif, char* morada, bool* res);
Cliente* ProcuraGestor(Cliente* inicio, int cod, long int nif);
Cliente* InsertClienteLista(Cliente* novo, Cliente* inicio, bool* res);
Cliente* AlteraCampoCliente(int cod, char* nome, float saldo, long int nif, char* morada, Cliente* novo, Cliente* inicio, bool* res);
Cliente* RemoveCliente(int cod, long int nif, Cliente* inicio, bool* res);
Cliente* InsertClienteInicio(Cliente* novo, Cliente* inicio, bool* res);
Cliente* InsertClienteFim(Cliente* novo, Cliente* inicio, bool* res);
Cliente* VerificaClienteDuplicado(int cod, long int nif, Cliente* inicio, bool* duplicado);
bool LerDadosCliente(char fileName[]);
bool GravarClienteBin(char* nomeFicheiro, Cliente* inicio);
Cliente* LerClienteBin(char* nomeFicheiro, bool* res);


#pragma endregion