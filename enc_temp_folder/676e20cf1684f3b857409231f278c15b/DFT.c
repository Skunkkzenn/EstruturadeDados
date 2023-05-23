#include "DFT.h"

/**
 * @brief Conta número de caminhos possíveis entre dois Vértices
 * @author Victor Destefani
 * @param inicio
 * @param ori
 * @param dst
 * @param contaCaminho
 * @param
 * @return
 */
int ContaCaminho(Vertice* inicio, int ori, int dest, int contaCaminho) {
	if (inicio == NULL) return 0;
	if (ori == dest) return (++contaCaminho);

	else {
		Vertice* h = ProcuraRecolhaCod(inicio, ori);
		Adj* hAdj = h->adjacentes;
		while (hAdj) {
			Vertice* a = ProcuraRecolhaCod(inicio, hAdj->cod);
			contaCaminho = ContaCaminho(inicio, a->cod, dest, contaCaminho);
			hAdj = hAdj->next;
		}
	}
	return contaCaminho;
}


/**
 * @brief Conta número de caminhos possíveis entre dois Vértices de forma recursiva
 * @author Victor Destefani
 * @param inicio
 * @param ori
 * @param dest
 * @param contaCaminho
 * @return
 */
int ContaCaminhoVerticesNome(Vertice* inicio, char* ori, char* dest, int contaCaminho) {
	int origem = ProcuraCodPontoRecolha(inicio, ori);
	int destino = ProcuraCodPontoRecolha(inicio, dest);
	return ContaCaminho(inicio, origem, destino, 0, contaCaminho);
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
	if (ori == dest) return true;

	Vertice* aux = ProcuraRecolhaCod(inicio, ori);
	aux->visitado = true;
	printf(" Vertice: %s : %d\n", aux->cidade, aux->cod);

	Adj* adj = aux->adjacentes;
	while (adj) {
		Vertice* aux = ProcuraRecolhaCod(inicio, adj->cod);
		if (aux->visitado == false)
		{
			bool existe = CaminhoDiretoCodRecolha(inicio, adj->cod, dest);
			return existe;
		}
		else
			aux = aux->next;
	}
	return true;
}

bool CaminhoDiretoNomeRecolha(Vertice* inicio, char* ori, char* dest) {
	int o = ProcuraCodPontoRecolha(inicio, ori);
	int d = ProcuraCodPontoRecolha(inicio, dest);
	return CaminhoDiretoCodRecolha(inicio, o, d);
}
