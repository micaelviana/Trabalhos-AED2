#include "hash.h"

extern unsigned long desloc_atual;
extern unsigned int pos;
extern unsigned int colisoes;

tipoNoHash * tabelaHashCriar(unsigned tam){
	tipoNoHash *tabela = (tipoNoHash *) malloc(sizeof(tipoNoHash) * tam);
	if(tabela == NULL){
		exit(1);
	}

	memset(tabela, -1, sizeof(tipoNoHash) * tam);

	return tabela;

}

unsigned int hash(int id){
	unsigned aux = abs(id - __HASH_CONST);

	return((aux + (aux % 4)) / 2);

}

void tabelaHashInserir(produtoEstoque produto, tipoNoHash *tabela){
	unsigned int aux = hash(produto.id);

	if(tabela[aux].id < 0){
		tabela[aux].id = produto.id;
		tabela[aux].deslocamento = desloc_atual;
	}
	else{
		tabela[pos].id = produto.id;
		tabela[pos].deslocamento = desloc_atual;
		pos++;
		colisoes++;
	}
	desloc_atual++;

}

long tabelaHashBuscar(int chave, tipoNoHash *tabela, unsigned int pos){
	unsigned int index = hash(chave);

	if(tabela[index].id == -1)
		return -1;
	else if(tabela[index].id == chave){
		return tabela[index].deslocamento;
	}
	else{
		index = __HASH_ZONA_COL;
		while(index < pos){
			if(tabela[index].id == chave){
				return tabela[index].deslocamento;
			}
			index++;
		}
		return -1;

	}
	
}

long tabelaHashBuscarAcessar(FILE *arq, int chave, tipoNoHash *tabela, unsigned int pos){
	unsigned int index = hash(chave);
	produtoEstoque aux;

	if(tabela[index].id == -1){
		return -1;
	}
	else if(tabela[index].id == chave){
		fseek(arq, tabela[index].deslocamento, SEEK_SET);
		fread(&aux, sizeof(produtoEstoque), 1, arq);
		return tabela[index].deslocamento;
	}
	else{
		index = __HASH_ZONA_COL;
		while(index < pos){
			if(tabela[index].id == chave){
				fseek(arq, tabela[index].deslocamento, SEEK_SET);
				fread(&aux, sizeof(produtoEstoque), 1, arq);
				return tabela[index].deslocamento;
			}
			index++;
		}
		return -1;

	}

}
