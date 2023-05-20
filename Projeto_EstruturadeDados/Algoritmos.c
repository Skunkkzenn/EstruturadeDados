#include "Vertice.h"
#include "Adjacencia.h"

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
int ContaCaminhoVertices(Vertice* inicio, int ori, int dst, int contaCaminho, bool *res) {
	*res = false;
	if (inicio == NULL) *res = false;

	if (ori == dst) return (++contaCaminho);

	else { 
		Vertice* aux = (inicio, ori);
		Adj* hAdj = aux->adjacentes;
		while (hAdj) {
			Vertice* v = ProcuraCodPontoRecolha(inicio, hAdj->cod, &res);
			contaCaminho = ContaCaminho(inicio, v->cod, dst, contaCaminho, &res);
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
	bool res = false;
	int origem = ProcuraCodPontoRecolha(inicio, ori, &res);
	int destino = ProcuraCodPontoRecolha(inicio, dest, &res);
	return CountPaths(inicio, origem, destino, 0);
}


/**
 * @brief Verifica a Existência de um caminho direto entre Vértices
 * 
 * @param inicio
 * @param ori
 * @param dest
 * @return 
 */
bool CaminhoDiretoVertices(Vertice* inicio, int ori, int dest)
{	
	bool res = false;
	int a;

	if (ori == dest) return true;

	Vertice* aux = ProcuraCodPontoRecolha(inicio, ori, &res);
	aux->visitado = true;
	printf(" Vertice: %s : %d\n", aux->cidade, aux->cod);

	Adj* adj = aux->adjacentes;
	while (adj) {
		Vertice* aux = ProcuraCodPontoRecolha(inicio, adj->cod, &res);
		if (aux->visitado == false)
		{
			bool existe = CaminhoDiretoVertices(inicio, adj->cod, dest);
			return existe;
		}
		else
			aux = aux->next;
	}
}
