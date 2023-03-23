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
#pragma warning( disable : 4996 ) 
#define M 200


#pragma region Struct Cliente
typedef struct Cliente {
	int cod;
	char nome[M];
	float saldo;
	long int nif;
	char morada[M];
	struct Cliente* next;
}Cliente;
#pragma endregion

#pragma region Funções para Tratar Clientes
Cliente* CriaCliente(int cod, char* nome, float saldo, long int nif, char* morada);
Cliente* InsertClienteLista(Cliente* novo, Cliente* inicio);
Cliente* AlteraCampoCliente(int cod, char* nome, float saldo, long int nif, char* morada, Cliente* novo, Cliente* inicio);
Cliente* RemoveCliente(int cod, long int nif, Cliente* inicio);
Cliente* InsertClienteInicio(Cliente* novo, Cliente* inicio);
Cliente* InsertClienteFim(Cliente* novo, Cliente* inicio);
Cliente* VerificaClienteDuplicado(int cod, int long nif, Cliente* inicio);

#pragma endregion
