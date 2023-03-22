/*****************************************************************//**
 * \file   Cliente.c
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   March 2023
 *********************************************************************/

#include <stdio.h>
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "Cliente.h"
#pragma warning( disable : 4996 )

Cliente* CriaCliente(int cod, char* nome, float saldo, long int nif, char* morada) {
	Cliente* novoCliente;

	//Cria espaço de memória
	novoCliente = (Cliente*)malloc(sizeof(Cliente));
	novoCliente->cod = cod;
	strcpy(novoCliente->nome, nome);
	novoCliente->saldo = saldo;
	strcpy(novoCliente->morada, morada);
	novoCliente->next = NULL;
	return novoCliente;
	
}

