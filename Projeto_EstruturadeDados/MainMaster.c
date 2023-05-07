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

#pragma region Veiculos
    bool res = false;

    char fileName[] = "veiculos.txt";
    bool sucesso = LerDadosVeiculo(fileName);
    
    //Inicia Lista vazia
    VeiculosLista* inicio = NULL;
    //Cria um novo veiculo
    Veiculo* novoVeiculo = CriaVeiculo(140, "carro", 70.5, 30.0, "SaoVitor");

    // Inserir o novo ve�culo no in�cio da lista
    inicio = InsertVeiculoInicio(novoVeiculo, inicio, &res);

    // Insere Veiculo no Fim
    inicio = InsertVeiculoFim(novoVeiculo, inicio, &res);

    // Insere o novo ve�culo na lista
    inicio = InsertVeiculoLista(novoVeiculo, inicio, &res);

    // Chama a fun��o para alterar o ve�culo com o c�digo e tipo especificados
    inicio = AlteraCampoVeiculo(144, "carro", 80.5, 50.0, "Lamacaes", novoVeiculo, inicio, &res);

    // Remove o ve�culo com o c�digo e tipo especificados
    inicio = RemoveVeiculo(144, "carro", inicio, &res);

#pragma endregion
}
