/*****************************************************************//**
 * \file   MainMaster.c
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   May 2023
 *********************************************************************/

#include <stdio.h>
#include <string.h> // para as strings
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include "Veiculo.h"
#include "Cliente.h"
#include "Gestor.h"
#include "Grafo.h"
#include "Adjacencia.h"
#pragma warning( disable : 4996 )

int main()  {
    setlocale(LC_ALL, "Portuguese");	//para escrever caracteres portugueses

    static int tot = 0;					//total de vertices

    //Inicia Lista vazia
    Veiculo* inicioVeiculos = NULL;
    Cliente* inicioClientes = NULL;
    Gestor*  inicioGestores = NULL;
   
    bool res = false;

    char fileNameVeiculos[] = "veiculos.txt";
    char fileNameClientes[] = "clientes.txt";
    char fileNameGestores[] = "gestores.txt";

    bool sucessoV = LerDadosVeiculo(fileNameVeiculos);
    bool sucessoC = LerDadosCliente(fileNameClientes);
    bool sucessoG = LerDadosGestor(fileNameGestores);

    //Cria um novo Veiculo, Cliente e Gestor.
    Veiculo* novoVeiculo = CriaVeiculo(140, "carro", 70.5, 30.0, "Sao Vitor", &res);
    Cliente* novoCliente = CriaCliente(01, "Michael Jackson", 200.45, 284152362, "Rua de Lameichas", &res);
    Gestor* novoGestor = CriaGestor(01, "Lebron James", 596.78, 299655456, "Rua Sebastiao", &res);

    /**/
    // Inserir o novo Veiculo, Cliente e Gestor no início da lista
    inicioVeiculos = InsertVeiculoInicio(novoVeiculo, inicioVeiculos, &res);
    inicioClientes = InsertClienteInicio(novoCliente, inicioClientes, &res);
    inicioGestores = InsertGestorInicio(novoGestor, inicioGestores, &res);
    
    
    // Insere Veiculo, Cliente e Gestor no Fim
    inicioVeiculos = InsertVeiculoFim(novoVeiculo, inicioVeiculos, &res);
    inicioClientes = InsertClienteFim(novoCliente, inicioClientes, &res);
    inicioGestores = InsertGestorFim(novoGestor, inicioGestores, &res);

    // Insere o novo Veiculo, Cliente e Gestor na lista
    inicioVeiculos = InsertVeiculoLista(novoVeiculo, inicioVeiculos, &res);
    inicioClientes = InsertClienteLista(novoCliente, inicioClientes, &res);
    inicioGestores = InsertGestorLista(novoGestor, inicioGestores, &res);

    // Chama a função para alterar o veículo com o código e tipo especificados, cliente e gestor com cod e nif
    inicioVeiculos = AlteraCampoVeiculo(144, "carro", 80.5, 50.0, "Lamacaes", novoVeiculo, inicioVeiculos, &res);
    inicioClientes = AlteraCampoCliente(05, "Mohamedi Ali", 100.52, 322954125, "Rua de Marechal", novoCliente, inicioClientes, &res);
    inicioGestores = AlteraCampoGestor(25, "Bob Marley", 400.20, 420240420, "Rua da Jamaica", novoGestor, inicioGestores, &res);

    /*
    // Remove o Veiculo, Cliente e Gestor com o código e tipo especificados
    inicioVeiculos = RemoveVeiculo(144, "carro", inicioVeiculos, &res);
    inicioClientes = RemoveCliente(05, 322954125, inicioClientes, &res);
    inicioGestores = RemoveGestor(25, 420240420, novoGestor, inicioGestores, &res);
    */

    //Grava Veiculo, Cliente e Gestor em arquivo binário
    char* fileVeiculo = "veiculos.bin";
    bool  saveVeiculo = GravarVeiculoBin(fileVeiculo, inicioVeiculos, &res);

    char* fileCliente = "clientes.bin";
    bool  saveCliente = GravarClienteBin(fileCliente, inicioClientes, &res);
        
    char* fileGestor = "gestores.bin";
    bool  saveGestor = GravarGestorBin(fileGestor, inicioGestores, &res);

    //Lê arquivo binario
    VeiculosFicheiro* listVeiculos = LerVeiculoBin("veiculos.bin", &res);
    ClientesFicheiro* listClientes = LerClienteBin("clientes.bin", &res);
    GestoresFicheiro* listGestores = LerGestorBin("gestores.bin", &res);

#pragma region Grafos (Vertices e Adj)
    /*
    //Vertices
    Vertice* graf = CriarGrafo();

    Vertice* novoVertice = CriaPontoRecolha("Sao Victor", tot);
    if (novoVertice != NULL) {
        graf = InserePontoRecolha(graf, novoVertice, &res);
        tot++;
    }

    novoVertice = CriaPontoRecolha("Lamacaes", tot);
    if (novoVertice != NULL) {
        graf = InserePontoRecolha(graf, novoVertice, &res);
        tot++;
    }

    novoVertice = CriaPontoRecolha("Santa Tecla", tot);
    if (novoVertice != NULL) {
        graf = InserePontoRecolha(graf, novoVertice, &res);
        tot++;
    }

    novoVertice = CriaPontoRecolha("Vila Velha", tot);
    if (novoVertice != NULL) {
        graf = InserePontoRecolha(graf, novoVertice, &res);
        tot++;
    }

    ExibeGrafo(graf); // Recursividade

    //Ligações
    graf = InsLigPontoRecolha(graf, "Sao Vitor", "Lamacaes", 22, &res);
    graf = InsLigPontoRecolha(graf, "Sao Vitor", "Santa Tecla", 30, &res);
    graf = InsLigPontoRecolha(graf, "Santa Tecla", "Lamacaes", 17, &res);
    graf = InsLigPontoRecolha(graf, "Lamacaes", "Vila Velha", 17, &res);

    ExibeGrafo(graf); // Recursividade

#pragma endregion 
*/
    return true;
}

