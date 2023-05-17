#include "Vertice.h"
#include "Adjacencia.h"

int ContaCaminho(Vertice* inicio, int ori, int dst, int contaCaminho, bool *res) {
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
