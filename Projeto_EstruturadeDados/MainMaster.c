/*****************************************************************//**
 * \file   MainMaster.c
 * \brief  TRABALHO EDA
 * \number 18586
 * \author Victor Destefani
 * \date   March 2023
 *********************************************************************/

#include <stdio.h>
#include <string.h> // para as strings
#include <stdbool.h>
#include <stdlib.h>
#include "Veiculo.h"
#include "Cliente.h"
#include "Gestor.h"
#pragma warning( disable : 4996 )


int main(){
	FILE* arquivo_texto = fopen("veiculos.txt", "r"); // arquivo_texto aponta para file veiculos.txt
	FILE* arquivo_binario = fopen("veiculos.bin", "wb");  // arquivo_binario aponta para arquivo_binario

	if (arquivo_binario == NULL || arquivo_texto == NULL) { // se arquivo de arquivo_binario && arquivo_texto forem iguais a NULL vai dar error
		printf("Erro ao abrir os arquivos.\n");
		return 1;
	}

	// Atualiza o arquivo binário com os dados do arquivo texto
	int linhas_lidas = atualiza_arquivo_binario(arquivo_binario, arquivo_texto);
	printf("Foram atualizados %d veiculos no arquivo binario.\n", linhas_lidas);

	// Exibe o conteúdo do arquivo binário na tela
	printf("Conteudo do arquivo binario:\n");
	exibe_conteudo_arquivo(arquivo_binario, arquivo_texto); // mostra o conteúdo

	fclose(arquivo_binario); // fecha binario	
	fclose(arquivo_texto); // fecha txt

	return 0;
}
