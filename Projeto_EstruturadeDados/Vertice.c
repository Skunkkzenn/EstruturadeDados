/*****************************************************************//**
 * \file   Vertice.c
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   May 2023
 *********************************************************************/

#include <stdlib.h>
#include <string.h>
#include "Vertice.h"

#pragma region Funções Vértices

 /**
  * @brief Inicia grafo, sem orientação
  * @author Victor Destefani
  * @return
  */
Vertice* CriarGrafo() {
	return NULL;
}


/**
 * @brief Cria um ponto de recolha dentro do grafo
 * @author Victor Destefani
 * @param cidade
 * @param cod
 * @return ponteiro para o novo ponto de recolha criado.
 */
Vertice* CriaPontoRecolha(char* cidade, int cod, bool* res) {
	*res = false;
	Vertice* novo = (Vertice*)calloc(1, sizeof(Vertice));
	if (novo == NULL) return NULL;
	novo->cod = cod;
	strcpy(novo->cidade, cidade);
	novo->next = NULL;
	*res = true;
	return novo;
}

/**
 * @brief Insere ponto de recolha no grafo
 * @author Victor Destefani
 * @param inicio
 * @param novo
 * @param
 * @return
 */
Vertice* InserePontoRecolha(Vertice* inicio, Vertice* novo, bool* res) {
	*res = false;
	if (novo == NULL) {
		return inicio;
	}

	// Verifica se o ponto de recolha já existe na lista
	bool existe = false;
	Vertice* pontoExistente = ProcuraPontoRecolha(inicio, novo->cidade, &existe);
	if (existe)
	{
		free(novo); // Libera a memória alocada para o novo ponto de recolha
		return inicio;
	}

	// Insere o novo ponto de recolha na lista
	if (inicio == NULL) {
		inicio = novo;
		*res = true;
	}
	else
	{
		Vertice* aux = inicio;
		Vertice* ant = aux;
		while (aux && strcmp(aux->cidade, novo->cidade) < 0) {
			ant = aux;
			aux = aux->next;
		}
		if (aux == inicio)
		{
			novo->next = inicio;
			inicio = novo;
		}
		else
		{
			novo->next = aux;
			ant->next = novo;
		}
		*res = true;
	}
	return inicio;
}

/**
 * @brief Insere ligação entre pontos de recolha.
 * @author Victor Destefani
 * @param inicio
 * @param origem
 * @param dest
 * @param peso
 * @return
 */
Vertice* InsLigPontoRecolha(Vertice* inicio, char* origem, char* dest, float peso, bool* res) {
	*res = false; //inicia sempre como falso
	if (inicio == NULL) return inicio;

	Vertice* aux = ProcuraPontoRecolha(inicio, origem, res); // busca vertice de origem
	int cod = ProcuraCodPontoRecolha(inicio, dest, res);  // busca vertice de destino

	if (aux == NULL || cod < 0) return inicio; // Se não foi encontrado o vertice origem e destino, ignora operação

	if (ExisteLigacao(aux->adjacentes, cod)) return inicio; //Se já foi registrado a ligacação entre os pontos, ignora a operação

	//Insere nova ligacao ao vertice de origem
	Adj* novoAdj = CriaLigacao(cod, peso);
	aux->adjacentes = InsereLigacao(aux->adjacentes, novoAdj, res);

	*res = true; // indica que a operação foi concluída com sucesso
	return inicio;
}

/**
 * @brief Exibe o Grafo
 * @author Victor Destefani
 * @param inicio
 */
void ExibeGrafo(Vertice* inicio, bool* res) {
	*res = false;
	if (inicio == NULL) return;
	printf("Vertice: %d - %s\n", inicio->cod, inicio->cidade);
	MostraLigacoes(inicio->adjacentes);
	ExibeGrafo(inicio->next, res);
	*res = true;
}

/**
 * @brief Verifica o cod. do Vértice de X cidade
 * @author Victor Destefani
 * @param inicio
 * @param cidade
 * @return Cod. da cidade
 */
int ProcuraCodPontoRecolha(Vertice* inicio, char* cidade) {
	if (inicio == NULL) return -1;
	if (strcmp(inicio->cidade, cidade) > 0) return -2;
	if (strcmp(inicio->cidade, cidade) == 0) return inicio->cod;
	return(ProcuraCodPontoRecolha(inicio->next, cidade));
}

/**
 * @brief Verifica se existe ponto de recolha pela cidade
 * @author Victor Destefani
 * @param g
 * @param cidade
 * @return Retorna o ponteiro para o nó que contém o ponto de recolha
 */
Vertice* ProcuraPontoRecolha(Vertice* inicio, char* cidade) {
	if (inicio == NULL) return NULL;
	if (strcmp(inicio->cidade, cidade) == 0) return inicio;
	return(ProcuraPontoRecolha(inicio->next, cidade));
}

/**
 * @brief
 * @author Victor Destefani
 * @param inicio
 * @param cod
 * @return 
 */
Vertice* ProcuraRecolhaCod(Vertice* inicio, int cod) {
	if (inicio == NULL) return NULL;
	if (inicio->cod == cod) return inicio;
	return(ProcuraRecolhaCod(inicio->next, cod));
}

/**
 * @brief
 * @author Victor Destefani
 * @param inicio
 * @return 
 */
Vertice* LimpaVertices(Vertice* inicio) {
	Vertice* aux = inicio;
	while (aux) {
		aux->visitado = false;
		aux = aux->next;
	}
	return inicio;
}

/**
 * @brief Grava Grafo em ficheiro bin.
 * @author Victor Destefani
 * @param inicio
 * @param nomeFicheiro
 * @return
 */
int GravarGrafo(Vertice* inicio, char* nomeFicheiro) {
	if (inicio == NULL) return -1;
	FILE* fp;
	int res;

	fp = fopen(nomeFicheiro, "wb");
	if (fp == NULL) return -2;

	//grava 1 registo de cada vez no ficheiro
	VerticesFicheiro auxFile;
	Vertice* auxVertice = inicio;
	while (auxVertice != NULL) {
		auxFile.cod = auxVertice->cod;
		strcpy(auxFile.cidade, auxVertice->cidade);
		fwrite(&auxFile, sizeof(VerticesFicheiro), 1, fp); // Grava vértices

		//grava adj em conjunto
		if (auxVertice->adjacentes) {
			res = GravaAdjBin(auxVertice->adjacentes, auxVertice->cidade, auxVertice->cod);
			if (res < 0) break;
		}
		auxVertice = auxVertice->next;
	}
	fclose(fp);
	return 1;
}

/**
 * Lê Grafo Bin.
 * 
 * @param inicio
 * @param fileName
 * @param 
 * @return 
 */
Vertice* LerGrafoBin(Vertice* inicio, char* fileName, bool* res) {
	*res = false;
	FILE* fp = fopen(fileName, "rb");
	if (fp == NULL) return NULL;
	VerticesFicheiro auxFicheiro;
	Vertice* novo;
	while (fread(&auxFicheiro, 1, sizeof(VerticesFicheiro), fp)) {
		novo = CriaPontoRecolha(auxFicheiro.cidade, auxFicheiro.cod, res);
		inicio = InserePontoRecolha(inicio, novo, res);
	}
	fclose(fp);
	return inicio;
}
#pragma endregion