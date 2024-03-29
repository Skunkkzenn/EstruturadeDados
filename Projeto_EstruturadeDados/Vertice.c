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

#pragma region Fun��es V�rtices

 /**
  * @brief Inicia grafo, sem orienta��o
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

	// Aloca mem�ria para novo objeto do tipo Vertice, calloc serve para alocar mem�ria e inicia-la com zeros
	Vertice* novo = (Vertice*)calloc(1, sizeof(Vertice)); 			
	if (novo == NULL) return NULL;
	novo->cod = cod;
	strcpy(novo->cidade, cidade);
	novo->next = NULL;
	*res = true;
	return novo;
}

/**
 * @brief Insere ponto de recolha no grafo, verificando se o mesmo j� existe na lista
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

	// Verifica se o ponto de recolha j� existe na lista
	bool existe = false;

	//Retorna um ponteiro para o ponto de recolha existente encontrado, caso exista, ou NULL se n�o for encontrado.
	Vertice* pontoExistente = ProcuraPontoRecolha(inicio, novo->cidade, &existe);

	//Se a condi��o 'existe' for verdadeira
	if (existe)
	{
		free(novo); // Libera a mem�ria alocada para o novo ponto de recolha
		return inicio;
	}

	// Insere o novo ponto de recolha na lista
	if (inicio == NULL) {
		inicio = novo; // Se a lista for vazia, o novo ponto de recolha ser� o primeiro elemento da lista
		*res = true;
	}

	//Se a lista n�o estiver vazia
	else 
	{
		Vertice* aux = inicio;

		// 'ant' toma o valor de 'aux', que ir� rastrear o elemento anterior � posi��o onde o novo ponto de recolha ser� inserido.
		Vertice* ant = aux;

		/* Percorre a lista enquanto o ponteiro aux n�o for nulo e o nome da cidade do v�rtice atual(aux->cidade)
		   for menor que o nome da cidade do novo ponto de recolha (novo->cidade). 
		   O strcmp � usado para comparar as strings alfabeticamente. */
		while (aux && strcmp(aux->cidade, novo->cidade) < 0) {
			ant = aux;
			aux = aux->next;
		}

		//Verifica se o novo ponto de recolha deve ser inserido no inicio da lista 
		if (aux == inicio)
		{   //Se for inserido no inicio, o ponteiro next � atualizado para apontar para o primeiro vertice da lista.
			novo->next = inicio; 
			inicio = novo; //Inicio � atualizado para apontar para o novo vertice, que ser� o primeiro da lista
		}

		//Se n�o for inserido no inicio
		else
		{
			//O ponteiro next do novo vertice, aponta para o pr�ximo elemento da lista onde o novo ponto de recolha ser� inserido
			novo->next = aux; 
			ant->next = novo; //Ponteiro next do 'ant' atualiza para apontar para o novo ponto de recolha, inserindo na posi��o correta.
		}
		*res = true;
	}
	return inicio;
}


/**
 * @brief Insere ponto de recolha no grafo com o cod
 * @author Victor Destefani
 * @param codOrigem
 * @param codDestino
 * @param peso
 * @return
 */
Vertice* InsereLigacaoRecolhaCod(Vertice* g, int codOrigem, int codDestino, float peso, bool* res) {
	*res = false;
	if (g == NULL) return g; //se o grafo for vazio, ignora opera��o

	Vertice* o = ProcuraRecolhaCod(g, codOrigem); //Procura vertice origem
	Vertice* d = ProcuraRecolhaCod(g, codDestino); //Procura vertice destino

	if (o == NULL || d == NULL) return g; // Se n�o encontrar origem e destino retorna inicio
	if (ExisteLigacao(o->adjacentes, codDestino) == true) return g; //Se j� foi registado esta adjacencia, ignorar a opera��o

	//Insere nova adjacencia no vertice "Origem"
	Adj* novoAdj = CriaLigacao(codDestino, peso);
	o->adjacentes = InsereLigacao(o->adjacentes, novoAdj, res);
	return g;

}

/**
 * @brief Insere liga��o entre pontos de recolha.
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

	if (aux == NULL || cod < 0) return inicio; // Se n�o foi encontrado o vertice origem e destino, ignora opera��o

	if (ExisteLigacao(aux->adjacentes, cod)) return inicio; //Se j� foi registrado a ligaca��o entre os pontos, ignora a opera��o

	//Insere nova ligacao ao vertice de origem
	Adj* novoAdj = CriaLigacao(cod, peso);
	aux->adjacentes = InsereLigacao(aux->adjacentes, novoAdj, res);

	*res = true; // indica que a opera��o foi conclu�da com sucesso
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
 * @brief Verifica o cod. do V�rtice de X cidade
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
 * @return Retorna o ponteiro para o n� que cont�m o ponto de recolha
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
		fwrite(&auxFile, sizeof(VerticesFicheiro), 1, fp); // Grava v�rtices

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
 * L� Grafo Bin.
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