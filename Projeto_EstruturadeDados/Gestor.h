/*****************************************************************//**
 * \file   Gestor.h
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   March 2023
 *********************************************************************/

#include <stdio.h>
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>
#pragma warning( disable : 4996 ) 
#define N 200

#pragma region Struct Gestor

typedef struct Gestor {
	int cod;
	char nome[N];
	float saldo;
	long int nif;
	char morada[N];
	struct Gestor* next; 
}Gestor;

typedef struct GestoresFicheiro {
	int cod;
	char nome[N];
	float saldo;
	long int nif;
	char morada[N];
}GestoresFicheiro;

#pragma endregion

#pragma region Funcoes que Tratam dos Gestores

Gestor* CriaGestor(int cod, char* nome, float saldo, long int nif, char* morada, bool* res);
Gestor* ProcuraGestor(Gestor* inicio, int cod, long int nif);
Gestor* InsertGestorInicio(Gestor* inicio, Gestor* novo, bool* res);
Gestor* InsertGestorFim(Gestor* inicio, Gestor* novo, bool* res);
Gestor* VerificaGestorDuplicado(Gestor* inicio, int cod, int long nif, bool* res);
Gestor* InsertGestorLista(Gestor* inicio, Gestor* novo, bool* res);
Gestor* AlteraCampoGestor(Gestor* inicio, Gestor* novo, int cod, char* nome, float saldo, long int nif, char* morada, bool* res);
Gestor* RemoveGestor(Gestor* inicio, int cod, long int nif, bool* res);
bool LerDadosGestor(char fileName[]);
bool GravarGestorBin(char* nomeFicheiro, Gestor* inicio);
Gestor* LerGestorBin(char* nomeFicheiro, bool* res);


#pragma endregion