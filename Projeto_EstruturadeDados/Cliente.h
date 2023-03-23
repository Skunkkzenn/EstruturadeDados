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

