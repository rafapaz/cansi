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
	char *p;
	No *lista = NULL;

	while ((getword(&p, &line)) != EOF) {
		lista = addLista(lista, p);
	}

	if (lista != NULL)
		while (lista->prox != NULL)
			printf("%s\n", lista->word);
	
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
	if (p != NULL) {
		while (p->prox != NULL)
			p = p->prox;
		p->prox = new;
	} else 
		p = new;

	return (lista) ? lista : p;
}
