#include <stdio.h>
#include <stdlib.h>
#include "ListaEncadeada.h"

#define INVALID_POS "Pos invalida.\n"
#define FULL "Lista lotada.\n"

#define CAPACIDADE 200

#define AVOID_INVALID_POS_ON_OPERATION

struct lista {
	Elemento* inicio;
	int tamanho;
	Elemento* fim;
};

struct elemento {
	int valor;
	Elemento* proximo;
};

Lista * criar()
{
	Lista* l = (Lista*)malloc(sizeof(Lista));	
	l->inicio = NULL;
	l->tamanho = 0;
	l->fim = NULL;

	return l;
}

void destruir(Lista * l)
{
	if (l != NULL) {
		limpar(l);
		free(l);
	}
}

void limpar(Lista * l)
{
	if (l != NULL) {

		Elemento* e = l->inicio;
		Elemento* e2;
		
		for (int a = 0; a < l->tamanho; a++) {
			e2 = e;
			e = e->proximo;
			free(e2);
		}

		l->tamanho = 0;		
	}	
}

int tamanho(Lista * l) {
	if (l != NULL) return l->tamanho;
	return -1;
}

int esta_vazia(Lista * l) {
	if (l != NULL && l->tamanho > 0) return 0;
	return 1;
}

int ler_pos(Lista * l, int p) {
	if (l != NULL) {
		Elemento* e = l->inicio;

		for (int a = 0; a < p; a++) {
			e = e->proximo;
		}

		return e->valor;
	}
	
	return -1;
}

int primeiro(Lista * l) {
	if (l != NULL && l->tamanho > 0) return l->inicio->valor;
	return -1;
}

int ultimo(Lista * l) {
	if (l != NULL && l->tamanho > 0) return l->fim->valor;
	return -1;
}

int buscar(Lista * l, int v) {
	if (l != NULL) {
		Elemento* e = l->inicio;
		int a;
		for (a = 0; a < l->tamanho; a++) {
			if (e->valor == v) return a;
		}	
	}

	return -1;
}

void escrever_pos(Lista * l, int p, int v) {
	if (l != NULL) {
		if (p < 0 || p >= l->tamanho) {
			printf(INVALID_POS);
			return;
		}

		if (l->tamanho == CAPACIDADE) {
			printf(FULL);
			return;
		}

		Elemento* e = l->inicio;

		for (int a = 0; a < p; a++) {
			e = e->proximo;
		}

		e->valor = v;
	}
}

void inserir_pos(Lista * l, int p, int v) {
	if (l != NULL) {

		if (p < 0 || p > l->tamanho) {
			printf(INVALID_POS);
			return;
		}

		if (l->tamanho == CAPACIDADE) {
			printf(FULL);
			return;
		}

		Elemento* e = (Elemento*)malloc(sizeof(Elemento)); e->valor = v;
		Elemento* aux = l->inicio;
		Elemento* aux2 = l->inicio;

		if (p == 0) {
			l->inicio = e;
			l->inicio->proximo = aux;
		}

		else {
			for (int a = 0; a < p - 1; a++) {
				aux = aux->proximo;
			}

			for (int b = 0; b < p; b++) {
				aux2 = aux2->proximo;
			}

			aux->proximo = e;
			e->proximo = aux2;
		}

		l->tamanho++;
	}
}
void inserir_primeiro(Lista * l, int v)
{
	inserir_pos(l, 0, v);
}

void inserir_ultimo(Lista * l, int v)
{
	if (l != NULL)
	{
		inserir_pos(l, l->tamanho, v);
	}
}
int remover(Lista * l, int v);
int remover_primeiro(Lista * l)
{
	int v = -1;

	if (l != NULL)
	{
		v = remover_pos(l, 0);
	}
	
	return v;
}

int remover_ultimo(Lista * l)
{
	int v = -1;

	if (l != NULL)
	{
		Elemento* e = l->inicio;
		int p = 0;

		while (e != NULL){
			e = e->proximo;
			p++;
		}

		remover_pos(l, p-1);		
	}

	return v;
}


int remover_pos(Lista* l, int p)
{
	int valor;

	if (p < 0 || p >= l->tamanho)
	{
		#ifndef AVOID_INVALID_POS_ON_OPERATION
		printf("Pos invalida.\n");
		#endif
		return -1;
	}

	if (l->tamanho == 0)
	{
		printf("Lista vazia.\n");
		return -1;
	}

	Elemento* aux = l->inicio;
	Elemento* aux2 = l->inicio;

	if (p == 0)
	{
		l->inicio = l->inicio->proximo;
	}

	for (int a = 0; a < p - 1; a++)
	{
		aux = aux->proximo;
	}

	for (int a = 0; a < p; a++)
	{
		aux2 = aux->proximo;
	}

	valor = aux2->valor;

	aux->proximo = aux2->proximo;

	l->tamanho--;

	return valor;

}

Lista* clonar(Lista* l)
{
	Lista* r = NULL;

	if (l != NULL)
	{
		r = criar();
		r->inicio = l->inicio;
		
		for (int a = 0; a < l->tamanho; a++)
		{
			inserir_pos(r, a, ler_pos(l, a));
		}
	}
	
	return r;
}

void exibir(Lista* l)
{
	if (l != NULL) {
		Elemento* e = l->inicio;
		printf("[");
		for(int a = 0; a < l->tamanho; a++) {
			printf("%d", e->valor);
			if (e->proximo != NULL) printf(", ");
			e = e->proximo;
						
		}

		printf("]\n");
	}
	else {
		printf("Status: [ Lista Nula ]\n");
	}
}
