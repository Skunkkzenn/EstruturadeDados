/*****************************************************************//**
 * \file   Veiculo.c
 * \brief  Projeto EDA
 * \number 18586
 * \author Victor Destefani
 * \date   March 2023
 *********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Veiculo.h"
#include "Cliente.h"
#pragma warning( disable : 4996 )


#pragma region Metodos Veículos.

/**
 * @brief Criar e inicializa veiculo com dados fornecidos.
 * @author Victor Destefani
 * @param cod
 * @param tipo
 * @param bateria
 * @param custo
 * @param local
 * @return 
 */
Veiculo* CriaVeiculo(int cod, char* tipo, float bateria, float custo, char* local, bool* res) {
	*res = false;
	Veiculo* novoVeiculo; // Cria uma variável para armazenar o ponteiro para o novo veículo

	novoVeiculo = (Veiculo*)malloc(sizeof(Veiculo));
	
	if (novoVeiculo == NULL) // Verifica se a alocação de memória foi bem sucedida
	{   
	 	printf("Erro ao alocar memória para novo veículo\n");
		return NULL;
	}

	// Inicializa os campos do novo veículo com as informações fornecidas
	novoVeiculo->cod = cod;
	strcpy(novoVeiculo->tipo, tipo);
	novoVeiculo->bateria = bateria;
	novoVeiculo->custo = custo;
	strcpy(novoVeiculo->local, local);
	novoVeiculo->next = NULL;

	*res = true;
	return novoVeiculo; //Retorna o o ponteiro para o novo veiculo criado
}

/**
 * @brief Procura Veiculo pelo Cod. e Tipo.
 * @author Victor Destefani
 * @param inicio
 * @param cod
 * @param tipo
 * @return 
 */
Veiculo* ProcuraVeiculo(Veiculo* inicio, int cod, const char* tipo) {
	Veiculo* veiculo = inicio;

	while (veiculo != NULL) {
		if (veiculo->cod == cod && strcmp(veiculo->tipo, tipo) == 0) {
			return veiculo; // Encontrou o veículo
		}
		veiculo = veiculo->next;
	}

	return NULL; // Veículo não encontrado
}


/**
 * @brief Insere Veiculo no Inicio
 * @author Victor Destefani
 * @param novo
 * @param inicio
 * @param 
 * @return 
 */
Veiculo* InsertVeiculoInicio(Veiculo* novo, Veiculo* inicio, bool* res) {
	*res = false;
	if (novo == NULL) { /* Se o ponteiro "novo" apontar para NULL, a função terá um erro e
						   retornará o ponteiro "inicio" original sem modificar a lista.
						   Caso contrário, a função prossegue com a inserção do novo cliente na lista.
						*/
		printf("Erro: novo cliente e nulo\n");
		return inicio;
	}
	if (inicio == NULL)
	{
		inicio = novo;
	}
	else {
		novo->next = inicio;
		inicio = novo;
		*res = true;
	}
	return inicio; // Retorna o ponteiro para o início da lista atualizada após inserção.
}

/**
 * @brief Insere Veiculo no Fim.
 * @author Victor Destefani
 * @param novo
 * @param inicio
 * @param 
 * @return 
 */
Veiculo* InsertVeiculoFim(Veiculo* novo, Veiculo* inicio, bool* res) {
	*res = false;
	if (inicio == NULL) // Se a lista estiver vazia, o novo nó será a cabeça da lista
	{
		inicio = novo;
	}
	else  // Se a lista não estiver vazia, insere o novo nó no final
	{
		Veiculo* aux = inicio; // Usa-se uma variável auxiliar que fica a apontar para o inicio, pois nao podemos alterar o inicio
		while (aux->next != NULL) {  /* Enquanto o aux campo next nao for nulo
									  ou
									  Enquanto ele estiver a apontar para alguma coisa seguira sempre. */
			aux = aux->next; // aux toma o valor de aux campo next, dessa forma avançamos na lista e quando acabar o fim do ciclo estamos no fim da lista
		}
		aux->next = novo;
		*res = true;
	}
	novo->next = NULL; // O campo next do novo nó deve ser nulo
	return inicio;
}

/**
 * @brief Insere Veiculo Lista.
 * @author Victor Destefani
 * @param novo
 * @param inicio
 * @param 
 * @return 
 */
Veiculo* InsertVeiculoLista(Veiculo* novo, Veiculo* inicio, bool* res) {
	bool veiculoDuplicado = false; // variável bool para armazenar se há veículo duplicado
	*res = false;
	
	if (inicio == NULL)
	{
		inicio = novo;

	}
	else {
		//Verificar se já existe repetido
		if (VerificaVeiculoDuplicado(novo->cod, novo->tipo, inicio, &veiculoDuplicado) != NULL) {
			return inicio;

		}

		if (!veiculoDuplicado) {
			if (inicio == NULL) {
				inicio = novo;
			}
			else {
				//procurar a posicao correta, e ordena pelo cod!!!!
				Veiculo* atual = inicio;
				Veiculo* anterior = NULL;

				//procurar a posicao correta, e ordena pelo cod!!!!
				while (atual != NULL && atual->cod < novo->cod) {
					anterior = atual;
					atual = atual->next;

				}

				if (anterior == NULL) { //Insere no início
					novo->next = inicio;
					inicio = novo;
				}
				else if (atual == NULL) { //Insere no fim
					anterior->next = novo;
					novo->next = NULL;
				}
				else { //Insere no meio
					anterior->next = novo;
					novo->next = atual;
				}
				
			} 
		}
		*res = true;
	}
}

/**
 * @brief Verifica Veiculo em duplicado.
 * @author Victor Destefani
 * @param cod
 * @param tipo
 * @param inicio
 * @param 
 * @return 
 */
Veiculo* VerificaVeiculoDuplicado(int cod,char* tipo , Veiculo* inicio, bool* duplicado) {
	*duplicado = false;
	
	if (inicio == NULL) // Verifica se a lista encadeada está vazia (inicio == NULL), caso esteja retorna NULL, indicando que não há veículos duplicados.
	{
		return NULL; // Caso não encontre nenhum veículo com o mesmo código e tipo, retorna NULL.
	}

	Veiculo* aux = inicio;
	while ((aux != NULL) && (aux->cod != cod) && (strcmp(aux->tipo, tipo) != 0)) // Percorre a lista encadeada, enquanto não chegar ao final da lista (aux != NULL) e não encontrar um veículo com o mesmo código e tipo (aux->cod != cod) && (strcmp(aux->tipo, tipo) != 0). Se encontrar um veículo com o mesmo código e tipo, retorna um ponteiro para esse veículo (aux).
	{
		aux = aux->next;
	}

	if (aux != NULL && aux->cod == cod && strcmp(aux->tipo, tipo) == 0) { // Verifica se foi encontrado um veículo duplicado
	 	*duplicado = true;
	}

	if (*duplicado) {
		printf("Erro: Veículo duplicado encontrado. Código: %d, Tipo: %s\n", aux->cod, aux->tipo);
	}
	
	return aux;
}

/**
 * @brief Altera Dados do Veiculo.
 * @author Victor Destefani
 * @param cod
 * @param tipo
 * @param bateria
 * @param custo
 * @param local
 * @param novo
 * @param inicio
 * @param 
 * @return 
 */
Veiculo* AlteraCampoVeiculo(int cod, char* tipo, float bateria, float custo, char* local, Veiculo* novo, Veiculo* inicio, bool* res) {
	*res = false;
	
	// Verifica se a lista está vazia
	if (inicio == NULL)
	{
		printf("Erro: lista vazia\n");
		*res = false;
		return NULL;
	}

	// Cria um ponteiro auxiliar para percorrer a lista
	Veiculo* aux = inicio;

	// Percorre a lista até encontrar o veículo com o código e tipo informado
	while ((aux != NULL) && (aux->cod != cod) && (strcmp(aux->tipo, tipo) != 0)) { // Percorre a lista encadeada, enquanto não chegar ao final da lista (aux != NULL) e não encontrar um veículo com o mesmo código e tipo (aux->cod != cod) && (strcmp(aux->tipo, tipo) != 0). Se encontrar um veículo com o mesmo código e tipo, retorna um ponteiro para esse veículo (aux).
		aux = aux->next;
	}

	// Se não encontrou o veículo com o código informado, retorna a lista original
	if ((aux == NULL) || aux->cod != cod) {
		*res = false;
		return inicio;
	}
	// Altera os campos do veículo encontrado com as informações fornecidas
	aux->cod = novo->cod;
	strcpy(aux->tipo, novo->tipo);
	aux->bateria = novo->bateria;
	aux->custo = novo->custo;
	strcpy(aux->local, novo->local);
	// Libera a memória alocada para o veículo novo
	free(novo);

 	*res = true;
	// Retorna a lista atualizada
	return inicio;
}

/**
 * @brief Remove Veiculo da Lista.
 * @author Victor Destefani
 * @param cod
 * @param tipo
 * @param inicio
 * @param 
 * @return 
 */
Veiculo* RemoveVeiculo(int cod, char* tipo, Veiculo* inicio, bool* res) {
	*res = false;
	
	// Verifica se o início é nulo (lista vazia)
	if (inicio == NULL) {
		return NULL; // Não há nenhum veículo para ser removido
	}

	// Inicializa ponteiros auxiliares
	Veiculo* noAnterior = inicio;
	Veiculo* noAtual = inicio;

	// Verifica se o nó a ser removido é a cabeça da lista
	if ((inicio != NULL) && (inicio->cod == cod)) { // O veículo a ser removido é o primeiro da lista (inicio)
		noAnterior = noAnterior->next; // Atualiza a lista para começar do segundo elemento
		free(inicio); // Libera a memória ocupada pelo veículo removido
		inicio = noAnterior;  // atualiza o início da lista
	}
	else
	{   // Percorre a lista até encontrar o nó a ser removido
		while ((noAtual != NULL) && (noAtual->cod != cod) && (strcmp(noAtual->tipo, tipo) != 0)) { // percorre array enquanto...
			{
				// Procura pelo veículo a ser removido
				noAnterior = noAtual; // avança o ponteiro auxAnt para o próximo nó
				noAtual = noAtual->next; // avança o ponteiro auxProx para o próximo nó
			}
			if ((noAtual == NULL) || (noAnterior->next == NULL) || (noAnterior->cod != cod)) {
				// Não foi encontrado nenhum veículo com o código e tipo especificados
				return inicio; // nao existe a veiculo, retorna início
			}
		}
		// Remove o veículo encontrado
		noAnterior->next = noAtual->next; // auxAnt campo next passa a conter o valor de auxProx campo next!
		free(noAtual); // liberta a memória que é removida
		*res = true;
	}
	return inicio; // Retorna head
}

/**
 * @brief Ler dados ficheiro veiculos.txt.
 * @author Victor Destefani
 * @param fileName
 * @return 
 */
bool LerDadosVeiculo(char fileName[])
{
	char row[MAXCHAR];
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror("Problemas na leitura do ficheiro.\n");
		return false;
	}

	while (feof(fp) != true)
	{
		fgets(row, MAXCHAR, fp);
		printf("Veiculos: %s", row);
	}
	fclose(fp);
	return true;
}

/**
 * @brief Grava dados do Veiculo em Binário.
 * @author Victor Destefani
 * @param nomeFicheiro
 * @param inicio
 * @return 
 */
bool GravarVeiculoBin(char* nomeFicheiro, Veiculo* inicio) {
	FILE* fp;

	if (inicio == NULL) {
		return false;
	}

	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) {
		perror("Erro ao abrir arquivo para escrita");
		return false;
	}

	//grava 1 registo de cada vez no ficheiro
 	VeiculosFicheiro aux;
	Veiculo* auxVeiculo = inicio;
 	while (auxVeiculo) {
		aux.cod = auxVeiculo->cod;
		strcpy(aux.tipo, auxVeiculo->tipo);
		aux.bateria = auxVeiculo->bateria;
		aux.custo = auxVeiculo->custo;
		strcpy(aux.local, auxVeiculo->local);

		fwrite(&aux, sizeof(VeiculosFicheiro), 1, fp);
 		auxVeiculo = auxVeiculo->next;
	}
 	fclose(fp);
	return true;
}

/**
 * @brief Lê dados do ficheiro binário criado.
 * @author Victor Destefani
 * @param nomeFicheiro
 * @param 
 * @return 
 */
Veiculo* LerVeiculoBin(char* nomeFicheiro, bool* res) {
	FILE* fp;
	Veiculo* inicio = NULL;
	VeiculosFicheiro aux;
	*res = false;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;
	
	while (fread(&aux, sizeof(VeiculosFicheiro), 1, fp)) {
		Veiculo* novo = (Veiculo*)malloc(sizeof(Veiculo));
		if (novo == NULL) {
			*res = false;
			break;
		}

		novo->cod = aux.cod;
		strcpy(novo->tipo, aux.tipo);
		novo->bateria = aux.bateria;
		novo->custo = aux.custo;
		strcpy(novo->local, aux.local);
		novo->next = NULL;

		if (inicio == NULL) {
			inicio = novo;
		}
		else {
			Veiculo* temp = inicio;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = novo;
		}

		// Imprime os dados do registro lido
		printf("Registro lido: cod=%d, tipo=%s, bateria=%.2f, custo=%.2f, local=%s\n",
			novo->cod, novo->tipo, novo->bateria, novo->custo, novo->local);

		*res = true;
	}

	fclose(fp);

	return inicio;
}

#pragma endregion
