/*****************************************************************//**
 * \file   AlugaVeiculos.c
 * \brief  
 * 
 * \author Destefani
 * \date   May 2023
 *********************************************************************/

#include "AlugaVeiculos.h"


/**
 * @brief Associa Cliente ao Veiculo
 *
 * @param veiculo
 * @param cliente
 * @return
 */
int AlugaVeiculo(Veiculo* veiculo, Cliente* cliente) {
	//Verifica se o cliente tem saldo suficiente
	if (veiculo->custo > cliente->saldo) {
		return 0; // Indica que a reserva falhou devido a saldo insuficiente
	}

	if (strcmp(veiculo->local, "Reservado") == 0) {
		return -1; // Indica que a reserva falhou devido ao veículo já estar reservado
	}

	//Abate o valor do custo no valor do saldo
	cliente->saldo -= veiculo->custo;

	// Atualizar o local do veículo para "Reservado"
	strcpy(veiculo->local, "Reservado");

	return 1;

}