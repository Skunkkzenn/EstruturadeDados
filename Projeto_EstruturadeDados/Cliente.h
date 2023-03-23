#pragma once

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#pragma warning( disable : 4996 ) 
#define M 200

typedef struct Cliente {
	int cod;
	char nome[M];
	float saldo;
	long int nif;
	char morada[M];
	struct Cliente* next;
}Cliente;

Cliente* CriaCliente(int cod, char* nome, float saldo, long int nif, char* morada);
Cliente* InsertClienteLista(Cliente* novo, Cliente* inicio);
Cliente* AlteraCampoCliente(int cod, char* nome, float saldo, long int nif, char* morada, Cliente* novo, Cliente* inicio);
Cliente* RemoveCliente(int cod, long int nif, Cliente* inicio);
Cliente* InsertClienteInicio(Cliente* novo, Cliente* inicio);
