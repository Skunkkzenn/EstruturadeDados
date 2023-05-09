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
#define MAX 40 // Maximo de Clientes, utilizar mais a frente*


#pragma region Struct Cliente
typedef struct Cliente {
	int cod;
	char nome[N];
	float saldo;
	long int nif;
	char morada[N];
	struct Cliente* next;
}Cliente;

typedef struct ClientesLista {
	Cliente* cliente;
	struct ClientesLista* next;
}ClientesLista;

#pragma endregion

#pragma region Fun��es para Tratar Clientes

Cliente* CriaCliente(int cod, char* nome, float saldo, long int nif, char* morada);
Cliente* InsertClienteLista(Cliente* novo, Cliente* inicio);
Cliente* AlteraCampoCliente(int cod, char* nome, float saldo, long int nif, char* morada, Cliente* novo, Cliente* inicio);
Cliente* RemoveCliente(int cod, long int nif, Cliente* inicio);
Cliente* InsertClienteInicio(Cliente* novo, Cliente* inicio);
Cliente* InsertClienteFim(Cliente* novo, Cliente* inicio);
Cliente* VerificaClienteDuplicado(int cod, int long nif, Cliente* inicio);

#pragma endregion