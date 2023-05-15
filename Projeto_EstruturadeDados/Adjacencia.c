/*****************************************************************//**
 * \file   Adjacencia.c
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   May 2023
 *********************************************************************/

#include "Adjacencia.h"
#include <stdlib.h>
#include <string.h>


#pragma region

 /**
  * @brief Cria novo nó de ligações.
  * @author Victor Destefani
  * @param cod
  * @param peso
  * @return
  */
Adj* CriaLigacao(int cod, float peso) {
	Adj* novo = (Adj*)calloc(1, sizeof(Adj));
	if (novo == NULL) return NULL;
	novo->cod = cod;
	novo->peso = peso;
	novo->next = NULL;
	return novo;
}


/**
 * @brief Verifica se X ligação Existe.
 * @author Victor Destefani
 * @param head
 * @param cod
 * @return
 */
bool ExisteLigacao(Adj* head, int cod) {
	while (head != NULL)
	{
		if (head->cod == cod) return true;
		head = head->next;
	}
	return false;
}

/**
 * @brief
 * @author Victor Destefani
 * @param head
 * @param novo
 * @param
 * @return
 */
Adj* InsereLigacao(Adj* head, Adj* novo, bool* res) {
	if (novo == NULL) /* Se o novo nó for nulo, retorna lista original,
						 definindo res como falso, indicando que a
						 inserção não foi realizada com sucesso */
	{
		*res = false;
		return head;
	}
	if (head == NULL || head->cod > novo->cod)/* Verifica se a lista esta vazia OU se o novo no deve ser inserido antes da cabeça da lista.
												 O novo nó será inserido na primeira posição, res é definido como true confirmando a execução
												 da tarefa e a função retorna o ponteiro para o novo no. 	*/

	{
		novo->next = head;
		*res = true;
		return novo;
	}
	if (head->cod == novo->cod) /* Verifica se o nó que vai ser inserido já existe na lista.
								   Se sim, a função retorna a lista original e marca res como falso */
	{
		*res = false;
		return head;
	}
	head->next = InsereLigacao(head->next, novo, res); /* Utilizando a recursividade, a função InsereLigacao percorre a lista até encontrar
														o local correto para inserção. Quando encntrar, insere o novo nó e retorna o ponteiro
														para a cabeça da lista. */
	*res = true;
	return head;
}


/**
 * @brief
 * @author Victor Destefani
 * @param head
 */
void MostraLigacoes(Adj* head) { /* Verifica se o ponteiro para lista é diferente de NULL, se for,
									devolve as informações impressas do nó atual e em seguida chama novamente a propria função,
									passando como parãmetro o proximo no da lista, o processo se repete ate que o ponteiro para o nó seja NULL,
									demostrando o final da lista. */
	if (head != NULL) {
		printf("\tAdj: %d - (%.0f)\n", head->cod, head->peso);
		MostraLigacoes(head->next);
	}
}

#pragma endregion