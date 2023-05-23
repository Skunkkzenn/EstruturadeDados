/*****************************************************************//**
 * \file   DFT.h
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   May 2023
 *********************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include "Vertice.h"
#include "Adjacencia.h"

int ContaCaminho(Vertice* inicio, int ori, int dest, int contaCaminho);
int ContaCaminhoVerticesNome(Vertice* inicio, char* ori, char* dest, int contaCaminho);
bool CaminhoDiretoCodRecolha(Vertice* inicio, int ori, int dest);
bool CaminhoDiretoNomeRecolha(Vertice* inicio, char* ori, char* dest);

#pragma once
