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
#pragma warning( disable : 4996 ) //evita MSG ERROS: _CRT_SECURE_NO_WARNINGS
#define N 200

#pragma region Struct Gestor

typedef struct Gestor {
	int cod;
	char nome[N];
	float saldo;
	long int nif;
	char morada[N];
	struct Gestor* next; // temos uma variavel a apontar para o proximo gestor

}Gestor;

typedef struct GestoresLista {
	Gestor* gestores;
	struct GestoresLista* next;
}GestoresLista;

#pragma endregion

#pragma region Funcoes que Tratam dos Gestores

Gestor* CriaGestor(int cod, char* nome, float saldo, long int nif, char* morada, bool* res);
Gestor* InsertGestorInicio(Gestor* novo, Gestor* inicio, bool* res);
Gestor* InsertGestorFim(Gestor* novo, Gestor* inicio, bool* res);
Gestor* VerificaGestorDuplicado(int cod, int long nif, Gestor* inicio, bool* duplicado);
Gestor* InsertGestorLista(Gestor* novo, Gestor* inicio, bool* res);
Gestor* AlteraCampoGestor(int cod, char* nome, float saldo, long int nif, char* morada, Gestor* novo, Gestor* inicio, bool* res);
Gestor* RemoveGestor(int cod, long int nif, Gestor* inicio, bool* res);
bool LerDadosGestor(char fileName[]);
bool GravarGestorBin(char* nomeFicheiro, Gestor* inicio, bool* res);
GestoresLista* LerGestorBin(char* nomeFicheiro, bool* res);


#pragma endregion