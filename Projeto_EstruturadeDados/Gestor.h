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
Gestor* InsertGestorInicio(Gestor* novo, Gestor* inicio, bool* res);
Gestor* InsertGestorFim(Gestor* novo, Gestor* inicio, bool* res);
Gestor* VerificaGestorDuplicado(int cod, int long nif, Gestor* inicio, bool* duplicado);
Gestor* InsertGestorLista(Gestor* novo, Gestor* inicio, bool* res);
Gestor* AlteraCampoGestor(int cod, char* nome, float saldo, long int nif, char* morada, Gestor* novo, Gestor* inicio, bool* res);
Gestor* RemoveGestor(int cod, long int nif, Gestor* inicio, bool* res);
bool LerDadosGestor(char fileName[]);
bool GravarGestorBin(char* nomeFicheiro, Gestor* inicio);
Gestor* LerGestorBin(char* nomeFicheiro, bool* res);


#pragma endregion