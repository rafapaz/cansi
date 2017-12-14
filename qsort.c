#include <stdio.h>
#include "util.h"

typedef struct lno {
	char *word;
	struct lno *prox;
} No;

No *addLista(No *, char*);

int main()
{
	int line;
	char *w;
	No *lista = NULL;
	No *p = NULL;

	lista = (No *) malloc(sizeof(No));
	lista->word = strdup("");
	lista->prox = NULL;
	while ((getword(&w, &line)) != EOF) {
		lista = addLista(lista, w);
	}

	for (p = lista; p->prox != NULL; p = p->prox)
		printf("%s\n", p->word);
	
	return 0;
}

No *addLista(No *lista, char *word)
{
	No *p;
	No *new;

	new = (No *) malloc(sizeof(No));
	new->word = mystrdup(word);
	new->prox = NULL;

	p = lista;
	while (p->prox != NULL)
		p = p->prox;
	p->prox = new;

	return lista;
}
