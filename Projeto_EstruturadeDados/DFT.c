#include "DFT.h"

/**
 * @brief Conta número de caminhos possíveis entre dois Vértices
 * @author Victor Destefani
 * @param inicio
 * @param ori
 * @param dst
 * @param contaCaminho -> Armazena o nº de caminhos encontrados
 * @param
 * @return
 */
int ContaCaminho(Vertice* inicio, int ori, int dest, int contaCaminho) {
	if (inicio == NULL) return 0; //Se for NULL retorna 0 indicando que não existe caminho
	if (ori == dest) return (++contaCaminho); // Se = caminho foi encontrado, incrementa contaCaminho antes de retornar o seu valor

	else {
		Vertice* headV = ProcuraRecolhaCod(inicio, ori); //Utiliza a função para procurar o vertice cm o cod igual a origem, ponteiro é armazeno em headV
		Adj* hAdj = headV->adjacentes; //Inicia o ponteiro hAdj para percorrer a lista de adj do vertice headV
		while (hAdj) { //enquanto hAdj não for NULL, percorrerá os nós adjacentes ao headV
			Vertice* a = ProcuraRecolhaCod(inicio, hAdj->cod); //Procura o vértice de acordo com o cod armazenado no nó adjacente atual (hAdj), 'a' armazena point do vertice
			contaCaminho = ContaCaminho(inicio, a->cod, dest, contaCaminho); // Explora os caminhos a partir do vertice 'a' em direção ao destino
			hAdj = hAdj->next; // Aponta para o próximo nó da lista
		}
	}
	return contaCaminho; // Acumula o numero total de caminhos encontrados
}


/**
 * @brief Conta número de caminhos possíveis entre dois Vértices de forma recursiva, utilizando os nomes dos vértices e convertendo em códigos
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
														ContaCaminhoVerticesNome, retorna o número de caminhos possíveis entre os vértices de origem e destino */	
}

/**
 * @brief Verifica a Existência de um caminho direto entre Vértices utilizando o cod
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
	aux->visitado = true; // Indica que o vértice foi visitado
	printf(" Vertice: %s : %d\n", aux->cidade, aux->cod); //Imprime o nome da cidade e cod do vértice aux.

	Adj* adj = aux->adjacentes; // Inicializa o ponteiro adj para percorrer a lista de adjacentes
	while (adj) { // Enquanto adj não for nulo
		Vertice* aux = ProcuraRecolhaCod(inicio, adj->cod); // Procura vertice correspondente ao cod, armazenado no no Adj atual, aux armazena o point para esse vertice
		if (aux->visitado == false) // Verifica se o vertice 'aux' foi visitado
		{
			bool existe = CaminhoDiretoCodRecolha(inicio, adj->cod, dest); /* Explora os vértices adjacentes ao vértice 'aux', nova origem é definida como o codigo do vértice
																			adjacente adj->cod e o destino permanece o mesmo												*/
			return existe; // O valor de existe e retornado pela função
		}
		else
			aux = aux->next; // Se aux já foi visitado, avança para o próximo nó adjacente sem realizar nenhuma ação recursiva
	}
	return false; // Qnd nenhum caminho direto é encontrado
}

/**
 * @brief Converte os nomes de Vértices em cód, utilizando ProcuraPontoRecolha; 
          Utiliza CaminhoDiretoCodRecolha para realizar a verificação do caminho direto, com base nos códigos dos vértices.
 * @author Victor Destefani
 * @param inicio
 * @param ori
 * @param dest
 * @return
 */
bool CaminhoDiretoNomeRecolha(Vertice* inicio, char* ori, char* dest) {
	int o = ProcuraPontoRecolha(inicio, ori); // Chama a função para encontrar o vértice com nome de origem, 'o' armazena o resultado
	int d = ProcuraPontoRecolha(inicio, dest); // Chama a função para encontrar o vértice com nome de destino, 'd' armazena o resultado
	return CaminhoDiretoCodRecolha(inicio, o, d); // Essa função verifica se existe um caminho direto entre os vértices de origem e destino com base nos códigos dos vértices.
}
