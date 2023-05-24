/*****************************************************************//**
 * \file   AlugaVeiculos.c
 * \brief  
 * 
 * \author Destefani
 * \date   May 2023
 *********************************************************************/

#include "AlugaVeiculos.h"

#pragma region Funcoes para Alugar Veiculo

/**
 * @brief Associa Cliente ao Veiculo
 * @author Victor Destefani
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
		printf("ERROR: Veiculo já foi reservado.\n");
		return -1; // Indica que a reserva falhou devido ao veículo já estar reservado
	}

	//Abate o valor do custo no valor do saldo
	cliente->saldo -= veiculo->custo;

	// Atualizar o local do veículo para "Reservado"
	strcpy(veiculo->local, "Reservado");

return 1;

}

/**
 * @brief Procura o aluguel do veiculo pelo cod.
 * @author Victor Destefani.
 * @param lista
 * @param cod
 * @return 
 */
Aluguel* ProcuraAluguel(Aluguel* lista, int cod) {
	Aluguel* aluguel = lista;

	while (aluguel != NULL) {
		if (aluguel->cod == cod) {
			return aluguel; // Encontrou o aluguel
		}
		aluguel = aluguel->next;
	}

	return NULL; // Aluguel não encontrado
}

/**
 * @brief Grava aluguel em ficheiro binario.
 * @author Victor Destefani
 * @param nomeFicheiro
 * @param inicio
 * @return
 */


//bool GravarAluguelBin(char* nomeFicheiro, Aluguel* inicio) {
//	FILE* fp;
//
//	if (inicio == NULL) {
//		return false;
//	}
//
//	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) {
//		perror("Erro ao abrir arquivo para escrita");
//		return false;
//	}
//
//	//grava 1 registo de cada vez no ficheiro
//	AluguelFicheiro aux;
//	Aluguel* auxAluguel = inicio;
//	while (auxAluguel) {
//		aux.cod = auxAluguel->cod;
//		strcpy(aux.cidade, auxAluguel->cidade);
//		
//		fwrite(auxAluguel, sizeof(AluguelFicheiro), 1, fp);
//		auxAluguel = auxAluguel->next;
//	}
//	fclose(fp);
//	return true;
//}

/**
 * Lê arquivo bin dos Aluguéis.
 * 
 * @param nomeFicheiro
 * @param 
 * @return 
// */
//Aluguel* LerAluguelBin(char* nomeFicheiro, bool* res) {
//	FILE* fp;
//	Aluguel* inicio = NULL;
//	AluguelFicheiro aux;
//	*res = false;
//
//	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;
//
//	while (fread(&aux, sizeof(AluguelFicheiro), 1, fp)) {
//		Aluguel* novo = (Aluguel*)malloc(sizeof(Aluguel));
//		if (novo == NULL) {
//			*res = false;
//			break;
//		}
//
//		novo->cod = aux.cod;
//		strcpy(novo->cidade, aux.cidade);
//	
//		novo->next = NULL;
//
//		if (inicio == NULL) {
//			inicio = novo;
//		}
//		else {
//	 		Aluguel* temp = inicio;
//			while (temp->next != NULL) {
//				temp = temp->next;
//			}
//			temp->next = novo;
//		}
//
//		// Imprime os dados do registro lido
//		printf("Aluguel registrado: cod=%d, tipo=%s\n", novo->cod, novo->cidade);
//
//		*res = true;
//	}
//
//	fclose(fp);
//
//	return inicio;
//}

/**
 * @brief Remove os alugueis.
 * @author Victor Destefani
 * @param inicio
 * @param cod
 * @param nif
 * @param 
 * @return 
 */
Aluguel* RemoveAluguel(Aluguel* inicio, int cod, long int nif, bool* res) {
	*res = false;
	// Verifica se o início é nulo (lista vazia)
	if (inicio == NULL) {
		return NULL; // Não há nenhum veículo para ser removido
	}

	// Inicializa ponteiros auxiliares
	Aluguel* noAnterior = inicio;
	Aluguel* noAtual = inicio;

	// Verifica se o nó a ser removido é a cabeça da lista
	if ((inicio != NULL) && (inicio->cod == cod)) {
		noAnterior = noAnterior->next;
		free(inicio);
		inicio = noAnterior;
	}
	else
	{
		while ((noAtual != NULL) && (noAtual->cod != cod)) { // Procura pelo aluguel a ser removido
			noAnterior = noAtual; // avança o ponteiro auxAnt para o próximo nó
			noAtual = noAtual->next; // avança o ponteiro auxProx para o próximo nó
		}
		if ((noAtual == NULL) || (noAnterior->next == NULL) || (noAnterior->cod != cod)) { // Não foi encontrado nenhum aluguel com o código e tipo especificados
			return inicio;
		}
		// Remove o aluguel encontrado
		noAnterior->next = noAtual->next; // auxAnt campo next passa a conter o valor de auxProx campo next!
		free(noAtual); // liberta a memória que é removida
		*res = true;
	}
	return inicio; // Retorna head

	return 1;

}


#pragma endregion