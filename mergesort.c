#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

#define MAX 9999999

typedef struct lno {
	char *word;
	struct lno *ant;
	struct lno *prox;
} No;

No *listaInit(No *lista);
No *addLista(No *, char*);
int compNo(const void *n1, const void *n2);
void qsortNo(No *base, int start, int end, int (*compar)(const void *, const void *));

int main()
{
	int line=0, size=0;
	char *w;
	No *lista = NULL;
	No *p = NULL;

	listaInit(lista);

	while ((getword(&w, &line)) != EOF) {
		lista = addLista(lista, w);
		size++;
	}
	lista = lista->prox;

	printf("\nNormal: \n");
	for (i=0, p = lista; p != NULL; p = p->prox, i++) {
		printf("%s\n", p->word);
	}

	mergeSort();

	printf("Ordenado: \n");
	for (p = lista; p != NULL; p = p->prox)
		printf("%s\n", p->word);
	
	return 0;
}

void listaInit(No *lista)
{
	lista = (No *) malloc(sizeof(No));
	lista->word = strdup("");
	lista->ant = lista->prox = NULL;

	return lista;
}


int compNo(const void *n1, const void *n2)
{
	return strcmp(((No*)n1)->word, ((No*)n2)->word);
}

No *addLista(No *lista, char *word)
{
	No *p;
	No *new;

	new = (No *) malloc(sizeof(No));
	new->word = mystrdup(word);
	new->ant = new->prox = NULL;

	p = lista;
	while (p->prox != NULL)
		p = p->prox;
	p->prox = new;
	new->ant = p;

	return lista;
}

