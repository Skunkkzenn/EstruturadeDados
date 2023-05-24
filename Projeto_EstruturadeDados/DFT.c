#include "DFT.h"

/**
 * @brief Conta n�mero de caminhos poss�veis entre dois V�rtices
 * @author Victor Destefani
 * @param inicio
 * @param ori
 * @param dst
 * @param contaCaminho -> Armazena o n� de caminhos encontrados
 * @param
 * @return
 */
int ContaCaminho(Vertice* inicio, int ori, int dest, int contaCaminho) {
	if (inicio == NULL) return 0; //Se for NULL retorna 0 indicando que n�o existe caminho
	if (ori == dest) return (++contaCaminho); // Se = caminho foi encontrado, incrementa contaCaminho antes de retornar o seu valor

	else {
		Vertice* headV = ProcuraRecolhaCod(inicio, ori); //Utiliza a fun��o para procurar o vertice cm o cod igual a origem, ponteiro � armazeno em headV
		Adj* hAdj = headV->adjacentes; //Inicia o ponteiro hAdj para percorrer a lista de adj do vertice headV
		while (hAdj) { //enquanto hAdj n�o for NULL, percorrer� os n�s adjacentes ao headV
			Vertice* a = ProcuraRecolhaCod(inicio, hAdj->cod); //Procura o v�rtice de acordo com o cod armazenado no n� adjacente atual (hAdj), 'a' armazena point do vertice
			contaCaminho = ContaCaminho(inicio, a->cod, dest, contaCaminho); // Explora os caminhos a partir do vertice 'a' em dire��o ao destino
			hAdj = hAdj->next; // Aponta para o pr�ximo n� da lista
		}
	}
	return contaCaminho; // Acumula o numero total de caminhos encontrados
}


/**
 * @brief Conta n�mero de caminhos poss�veis entre dois V�rtices de forma recursiva, utilizando os nomes dos v�rtices e convertendo em c�digos
 * @author Victor Destefani
 * @param inicio
 * @param ori
 * @param dest
 * @param contaCaminho
 * @return
 */
int ContaCaminhoVerticesNome(Vertice* inicio, char* ori, char* dest, int contaCaminho) {
	int origem = ProcuraPontoRecolha(inicio, ori); // Utiliza ProcuraPontoRecolha para encontrar o vertice com o nome de origem
	int destino = ProcuraPontoRecolha(inicio, dest); // Utiliza ProcuraPontoRecolha para encontrar o vertice com o nome de destino
	return ContaCaminho(inicio, origem, destino, 0); /* ContaCaminho recebe o ponteiro para o inicio, os cod de origem, destino e o contador iniciado como 0
														ContaCaminhoVerticesNome, retorna o n�mero de caminhos poss�veis entre os v�rtices de origem e destino */	
}

/**
 * @brief Verifica a Exist�ncia de um caminho direto entre V�rtices utilizando o cod
 * @author Victor Destefani
 * @param inicio
 * @param ori
 * @param dest
 * @return
 */
bool CaminhoDiretoCodRecolha(Vertice* inicio, int ori, int dest)
{
	if (ori == dest) return true; // Se iguais, caminho encontrado

	Vertice* aux = ProcuraRecolhaCod(inicio, ori); //Procura o cod do vertice na lista, aux armazena o ponteiro para o vertice
	aux->visitado = true; // Indica que o v�rtice foi visitado
	printf(" Vertice: %s : %d\n", aux->cidade, aux->cod); //Imprime o nome da cidade e cod do v�rtice aux.

	Adj* adj = aux->adjacentes; // Inicializa o ponteiro adj para percorrer a lista de adjacentes
	while (adj) { // Enquanto adj n�o for nulo
		Vertice* aux = ProcuraRecolhaCod(inicio, adj->cod); // Procura vertice correspondente ao cod, armazenado no no Adj atual, aux armazena o point para esse vertice
		if (aux->visitado == false) // Verifica se o vertice 'aux' foi visitado
		{
			bool existe = CaminhoDiretoCodRecolha(inicio, adj->cod, dest); /* Explora os v�rtices adjacentes ao v�rtice 'aux', nova origem � definida como o codigo do v�rtice
																			adjacente adj->cod e o destino permanece o mesmo												*/
			return existe; // O valor de existe e retornado pela fun��o
		}
		else
			aux = aux->next; // Se aux j� foi visitado, avan�a para o pr�ximo n� adjacente sem realizar nenhuma a��o recursiva
	}
	return false; // Qnd nenhum caminho direto � encontrado
}

/**
 * @brief Converte os nomes de V�rtices em c�d, utilizando ProcuraPontoRecolha; 
          Utiliza CaminhoDiretoCodRecolha para realizar a verifica��o do caminho direto, com base nos c�digos dos v�rtices.
 * @author Victor Destefani
 * @param inicio
 * @param ori
 * @param dest
 * @return
 */
bool CaminhoDiretoNomeRecolha(Vertice* inicio, char* ori, char* dest) {
	int o = ProcuraPontoRecolha(inicio, ori); // Chama a fun��o para encontrar o v�rtice com nome de origem, 'o' armazena o resultado
	int d = ProcuraPontoRecolha(inicio, dest); // Chama a fun��o para encontrar o v�rtice com nome de destino, 'd' armazena o resultado
	return CaminhoDiretoCodRecolha(inicio, o, d); // Essa fun��o verifica se existe um caminho direto entre os v�rtices de origem e destino com base nos c�digos dos v�rtices.
}
