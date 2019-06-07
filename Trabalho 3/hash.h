#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma once
#include "arquivo.h"

#define __HASH_CONST 38000
#define __HASH_SIZE 22000
#define __HASH_ZONA_COL 19010

typedef struct tipoNoHash{
	int id;
	long deslocamento;
} tipoNoHash;

tipoNoHash * tabelaHashCriar(unsigned int tam);
unsigned int hash(int id);
unsigned int tabelaHashdeArquivo(FILE *arq, tipoNoHash *tabela);
void tabelaHashInserir(produtoEstoque produto, tipoNoHash *tabela);
long tabelaHashBuscar(int chave, tipoNoHash *tabela, unsigned int pos);
long tabelaHashBuscarAcessar(FILE *arq, int chave, tipoNoHash *tabela, unsigned int pos);

