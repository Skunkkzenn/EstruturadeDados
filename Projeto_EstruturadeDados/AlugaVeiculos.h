/*****************************************************************//**
 * \file   AlugaVeiculos.h
 * \brief  
 * 
 * \author Destefani
 * \date   May 2023
 *********************************************************************/

#include "Cliente.h"
#include "Veiculo.h"
#include <stdio.h>
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>

typedef struct Aluguel {
	int cod;
	char cidade;
	Veiculo* veiculo;
	Cliente* aluguel;
	struct Aluguel* next;
}Aluguel;

typedef struct AluguelFicheiro {
	int cod;
	char cidade;
	int codVeiculo;
	int codAluguel;
}AluguelFicheiro;


int AlugaVeiculo(Veiculo* veiculo, Cliente* cliente);
Aluguel* ProcuraAluguel(Aluguel* lista, int cod);

#pragma once
