/*****************************************************************//**
 * \file   AlugaVeiculos.h
 * \brief  
 * 
 * \author Destefani
 * \date   May 2023
 *********************************************************************/
#ifndef ALUGUEL_H
#define ALUGUEL_H

#include <stdio.h>
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "Cliente.h"
#include "Veiculo.h"
#define N 100


typedef struct Aluguel {
	int cod;
	char cidade[N];
	Veiculo* veiculo;
	Cliente* cliente;
	struct Aluguel* next;
}Aluguel;

typedef struct AluguelFicheiro {
	int cod;
	char cidade[N];
	int codVeiculo;
	int codCliente;
}AluguelFicheiro;


int AlugaVeiculo(Veiculo* veiculo, Cliente* cliente);
Aluguel* ProcuraAluguel(Aluguel* lista, int cod);
Aluguel* InsereAluguel(Aluguel* lista, Veiculo* veiculo, Cliente* cliente, int cod, const char* cidade);
Aluguel* RemoveAluguel(Aluguel* inicio, int cod, long int nif, bool* res);
bool GravarAluguelBin(char* nomeFicheiro, Aluguel* inicio);
Aluguel* LerAluguelBin(char* nomeFicheiro, bool* res);
#pragma once
#endif ALUGUEL_H 