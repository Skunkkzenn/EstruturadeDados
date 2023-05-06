/*****************************************************************//**
 * \file   MainMaster.c
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   March 2023
 *********************************************************************/

#include <stdio.h>
#include <string.h> // para as strings
#include <stdbool.h>
#include <stdlib.h>
#include "Veiculo.h"
#include "Cliente.h"
#include "Gestor.h"
#include "Grafo.h"
#pragma warning( disable : 4996 )

#define VERT 15

int main()  {
    /* Veiculos */
    char fileName[] = "veiculos.txt";
    bool sucesso = LerDadosVeiculo(fileName);
}
