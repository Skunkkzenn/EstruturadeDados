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
		Vertice* headV = ProcuraRecolhaCod(inicio, ori);
		Adj* hAdj = headV->adjacentes;
		while (hAdj) {
			Vertice* a = ProcuraRecolhaCod(inicio, hAdj->cod);
			contaCaminho = ContaCaminho(inicio, a->cod, dest, contaCaminho);
			hAdj = hAdj->next;
		}
	}
	return contaCaminho;
}


/**
 * @brief Conta n�mero de caminhos poss�veis entre dois V�rtices de forma recursiva
 * @author Victor Destefani
 * @param inicio
 * @param ori
 * @param dest
 * @param contaCaminho
 * @return
 */
int ContaCaminhoVerticesNome(Vertice* inicio, char* ori, char* dest, int contaCaminho) {
	int origem = ProcuraPontoRecolha(inicio, ori);
	int destino = ProcuraPontoRecolha(inicio, dest);
	return ContaCaminho(inicio, origem, destino, 0);
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
	int o = ProcuraPontoRecolha(inicio, ori);
	int d = ProcuraPontoRecolha(inicio, dest);
	return CaminhoDiretoCodRecolha(inicio, o, d);
}
