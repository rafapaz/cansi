#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 10

typedef struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
} dictNo;

static dictNo *hashtab[HASHSIZE];
void printHash();
unsigned hash(char *s);
dictNo *lookup(char *s);
dictNo *install(char *name, char *defn);

int main()
{
	int i;
	char *line=NULL, *token=NULL;
	size_t len=0;
	dictNo temp;

	for (i=0;i < HASHSIZE;i++) {
		hashtab[i] = NULL;
	}

	while (getline(&line, &len, stdin) > 0) {
		token = strsep(&line, ":");
		temp.name = strdup(token);
		token = strsep(&line, ":");
		temp.defn = strdup(token);
		
		install(temp.name, temp.defn);
	}

	printHash();
	return 0;
}

void printHash()
{
	int i=0;
	dictNo *p;

	for (i=0;i < HASHSIZE;i++) {
		printf("Hash[%d] -> ",i);
		if (hashtab[i]==NULL) {
			printf("NULL\n");
			continue;
		}
		
		for (p = hashtab[i]; p != NULL; p = p->next)
			printf("%s -> ", p->name);

		printf("NULL\n");
	}
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
dictNo *lookup(char *s)
{
	dictNo *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;

	return NULL; //not found
}

/* install: put (name, defn) in hashtab */
dictNo *install(char *name, char *defn)
{
	dictNo *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) { /* not found */
		np = (dictNo *) malloc(sizeof(*np));
		
		if (np == NULL) return NULL;

		if ((np->name = strdup(name)) == NULL || (np->defn = strdup(defn)) == NULL) {
			free(np);
			return NULL;
		}
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} 

	return np;
}


