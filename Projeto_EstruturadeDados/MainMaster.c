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
#include "Vertice.h"
#include "Adjacencia.h"
#include "DFT.h"
#include "AlugaVeiculos.h"

#pragma warning( disable : 4996 )

int main() {
    setlocale(LC_ALL, "Portuguese");	//para escrever caracteres portugueses

    static int tot = 0;					//total de vertices

    //Inicia Lista vazia
    Veiculo* inicioVeiculos = NULL;
    Cliente* inicioClientes = NULL;
    Gestor* inicioGestores = NULL;
    Aluguel* inicioAluguel = NULL;

    bool res = false;

    //char fileNameVeiculos[] = "veiculos.txt";
    //char fileNameClientes[] = "clientes.txt";
    //char fileNameGestores[] = "gestores.txt";

    //bool sucessoV = LerDadosVeiculo(fileNameVeiculos);
    //bool sucessoC = LerDadosCliente(fileNameClientes);
    //bool sucessoG = LerDadosGestor(fileNameGestores);

#pragma region Tratamento dos Métodos | Clientes, Gestores e Veiculos

    Veiculo* novoVeiculo1 = CriaVeiculo(101, "Carro", 70.5, 30.0, "Sao Vitor", &res);
    Veiculo* novoVeiculo2 = CriaVeiculo(301, "Bicicleta", 84.23, 3.42, "Lamacaes", &res);
    Veiculo* novoVeiculo3 = CriaVeiculo(302, "Bicicleta", 32.23, 3.42, "Santa Tecla", &res);
    Veiculo* novoVeiculo4 = CriaVeiculo(201, "Scooter", 55.56, 11.67, "Vila Velha", &res);
    
    Cliente* novoCliente1 = CriaCliente(1, "Ayrton Senna", 1500.36, 284152362, "Sao Vitor", &res);
    Cliente* novoCliente2 = CriaCliente(2, "Beckenbauer", 236.85, 365549562, "Lamacaes", &res);
    Cliente* novoCliente3 = CriaCliente(3, "Lucas Podolski", 80.47, 446523976, "Santa Tecla", &res);
    Cliente* novoCliente4 = CriaCliente(4, "Michael Jackson", 100.78, 752369946, "Vila Velha", &res);

    Gestor* novoGestor1 = CriaGestor(1001, "Lebron James", 10.365, 315986256, "Guarda", &res);
    Gestor* novoGestor5 = CriaGestor(1001, "Lebron James", 10.365, 315986256, "Guarda", &res);
    Gestor* novoGestor2 = CriaGestor(1002, "Tony Hawky", 8997.64, 784632415, "Esposende", &res);
    Gestor* novoGestor3 = CriaGestor(1002, "Holandes Voador", 19.99, 236455687, "Parque Holandinha", &res);

    ///*
    //// Inserir o novo Veiculo, Cliente e Gestor no início da lista
    //inicioVeiculos = InsertVeiculoInicio(inicioVeiculos, novoVeiculo, &res);
    //inicioClientes = InsertClienteInicio(inicioClientes, novoCliente, &res);
    //inicioGestores = InsertGestorInicio(inicioGestores, novoGestor, &res);
    //*/


    //// Insere Cliente no fim da Lista
    //inicioVeiculos = InsertVeiculoFim(inicioVeiculos, novoVeiculo1, &res);
    //inicioVeiculos = InsertVeiculoFim(inicioVeiculos, novoVeiculo2, &res);
    //inicioVeiculos = InsertVeiculoFim(inicioVeiculos, novoVeiculo3, &res);
    //inicioVeiculos = InsertVeiculoFim(inicioVeiculos, novoVeiculo4, &res);
    //inicioGestores = InsertVeiculoFim(inicioGestores, novoVeiculo5, &res);


    //// Insere Gestor no fim da Lista
    //inicioGestores = InsertGestorFim(inicioGestores, novoGestor1, &res);
    //
    //inicioGestores = InsertGestorFim(inicioGestores, novoGestor2, &res);
    //inicioGestores = InsertGestorFim(inicioGestores, novoGestor3, &res);

    ////Insere Cliente no fim da Lista
    //inicioClientes = InsertClienteFim(inicioClientes, novoCliente1, &res);
    //inicioClientes = InsertClienteFim(inicioClientes, novoCliente2, &res);
    //inicioClientes = InsertClienteFim(inicioClientes, novoCliente3, &res);
    //inicioClientes = InsertClienteFim(inicioClientes, novoCliente4, &res);

    
    // Insere o novo Veiculo, Cliente e Gestor na lista ordenadamente 
    inicioVeiculos = InsertVeiculoLista(inicioVeiculos, novoVeiculo1, &res);
    inicioVeiculos = InsertVeiculoLista(inicioVeiculos, novoVeiculo2, &res);
    inicioVeiculos = InsertVeiculoLista(inicioVeiculos, novoVeiculo3, &res);
    inicioVeiculos = InsertVeiculoLista(inicioVeiculos, novoVeiculo4, &res);

    /*inicioClientes = InsertClienteLista(inicioClientes, novoCliente1, &res);
    inicioClientes = InsertClienteLista(inicioClientes, novoCliente2,  &res);
    inicioClientes = InsertClienteLista(inicioClientes, novoCliente3,  &res);
    inicioClientes = InsertClienteLista(inicioClientes, novoCliente4, &res);

    inicioGestores = InsertGestorLista(inicioGestores, novoGestor1,&res);
    inicioGestores = InsertGestorLista(inicioGestores, novoGestor2, &res);*/

    //// Chama a função para alterar o veículo com o código e tipo especificados, cliente e gestor com cod e nif
   /* novoVeiculo1->bateria = 80.5;
    novoVeiculo1->custo = 50.0;
    inicioVeiculos = AlteraCampoVeiculo(inicioVeiculos, novoVeiculo1, 101, "carro", 80.5, 50.0, "Lamacaes", &res);
    inicioClientes = AlteraCampoCliente(inicioClientes, novoCliente1, 05, "Mohamedi Ali", 100.52, 322954125, "Rua de Marechal", &res);
    inicioGestores = AlteraCampoGestor(inicioGestores, novoGestor1, 25, "Bob Marley", 400.20, 420240420, "Rua da Jamaica", &res);*/

    ///*
    //// Remove o Veiculo, Cliente e Gestor com o código e tipo/nif especificados
    //inicioVeiculos = RemoveVeiculo(inicioVeiculos, 144, "carro", &res);
    //inicioClientes = RemoveCliente(inicioClientes, 05, 322954125, &res);
    //inicioGestores = RemoveGestor(inicioGestores, 25, 420240420, novoGestor, &res);
    //*/
 
#pragma endregion 


#pragma region Aluguel de Veículos

    Aluguel* novoAluguel1 = AlugaVeiculo(novoVeiculo1, novoCliente1);
    inicioAluguel = InsereAluguel(inicioAluguel, novoVeiculo1, novoCliente1, 02, "Sao Vitor");
    //inicioAluguel = ProcuraAluguel(inicioAluguel, 02);

#pragma endregion


#pragma region Ficheiros | Clientes, Gestores e Veiculos
   
    //Grava Veiculo, Cliente e Gestor em arquivo binário
    char* fileVeiculo = "veiculos.bin";
    bool  saveVeiculo = GravarVeiculoBin(fileVeiculo, inicioVeiculos, &res);

    char* fileCliente = "clientes.bin";
    bool  saveCliente = GravarClienteBin(fileCliente, inicioClientes, &res);

    char* fileGestor = "gestores.bin";
    bool  saveGestor = GravarGestorBin(fileGestor, inicioGestores, &res);

    char* fileAluguel = "alugueis.bin";
    bool  saveAluguel = GravarAluguelBin(fileAluguel, inicioAluguel, &res);

    //Lê arquivo binario
    Veiculo* listVeiculos = LerVeiculoBin("veiculos.bin", &res);
    Cliente* listClientes = LerClienteBin("clientes.bin", &res);
    Gestor* listGestores = LerGestorBin("gestores.bin", &res);
    Aluguel* listAlugueis = LerAluguelBin("alugueis.bin", &res);

    // Verifica Veiculo Duplicado Manualmente
    //VerificaVeiculoDuplicado(inicioVeiculos, novoVeiculo1->cod, novoVeiculo1->tipo, &res);

#pragma endregion

#pragma region Grafos (Vertices e Adj)

    //Vertices
    Vertice* graf = CriarGrafo();

    Vertice* novoVertice = CriaPontoRecolha("Sao Victor", tot, &res);
    if (novoVertice != NULL) {
        graf = InserePontoRecolha(graf, novoVertice, &res);
        tot++;
    }

    novoVertice = CriaPontoRecolha("Lamacaes", tot, &res);
    if (novoVertice != NULL) {
        graf = InserePontoRecolha(graf, novoVertice, &res);
        tot++;
    }

    novoVertice = CriaPontoRecolha("Santa Tecla", tot, &res);
    if (novoVertice != NULL) {
        graf = InserePontoRecolha(graf, novoVertice, &res);
        tot++;
    }

    novoVertice = CriaPontoRecolha("Vila Velha", tot, &res);
    if (novoVertice != NULL) {
        graf = InserePontoRecolha(graf, novoVertice, &res);
        tot++;
    }

    ExibeGrafo(graf, &res); // Recursividade

    //Ligações
    graf = InsLigPontoRecolha(graf, "Sao Vitor", "Lamacaes", 22, &res);
    graf = InsLigPontoRecolha(graf, "Sao Vitor", "Santa Tecla", 30, &res);
    graf = InsLigPontoRecolha(graf, "Santa Tecla", "Lamacaes", 17, &res);
    graf = InsLigPontoRecolha(graf, "Lamacaes", "Vila Velha", 17, &res);

    ExibeGrafo(graf, &res); // Recursividade

#pragma endregion 


#pragma region DFT

    int contaCaminho = 0;
    int x = ContaCaminho(graf, 0, 1, contaCaminho);
    
    int acrescentaCaminho = 0;
    x = ContaCaminhoVerticesNome(graf, "Sao Vitor", "Lamacaes", acrescentaCaminho);
    x = ContaCaminhoVerticesNome(graf, "Sao Vitor", "Sao Tecla", acrescentaCaminho);

    x = ContaCaminho(graf, 0, 2, 0);

    printf("\nExiste caminho?\n");
    bool existe = CaminhoDiretoCodRecolha(graf, 0, 1);
    printf("Existe caminho entre %d e %d: %s\n", 0, 1, (existe == true ? "Sim" : "Não"));

    graf = LimpaVertices(graf);

    existe = CaminhoDiretoNomeRecolha(graf, "Sao Vitor", "Lamacaes");
    printf("Existe caminho entre %s e %s: %s\n", "Sao Victor", "Lamacaes", (existe == true ? "Sim" : "Não"));

#pragma endregion


#pragma region  Ficheiros Grafos e Adjacencias

    int res1 = GravarGrafo(graf, "Vertices.bin");
    if (res1 > 0) puts("\nGrafo gravado em ficheiro");

    puts("\n Grafo em memória:");
    ExibeGrafo(graf, &res);

    graf = LerGrafoBin(graf, "Vertices.bin", &res);
    if (graf != NULL) puts("\nVertices do Grafo lido no ficheiro\n");
    ExibeGrafo(graf, &res);

    puts("\nLer Adjacencias do grafo de ficheiro\n");
    graf = LerAdjBin(graf, &res);
    ExibeGrafo(graf, &res);

#pragma endregion


    return false;
}

#pragma endregion 