#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Comanda Comanda;
typedef struct Nod Nod;

struct Comanda {
	int id;
	char* client;
	float valoare;
};

struct Nod {
	Comanda info;
	Nod* next;
};

Comanda initializare(int id,
	const char* client,
	float valoare) {

	Comanda c;

	c.id = id;

	c.client =
		(char*)malloc(sizeof(char) *
			(strlen(client) + 1));

	strcpy(c.client, client);

	c.valoare = valoare;

	return c;
}

void afisareComanda(Comanda c) {

	printf("Id: %d | Client: %s | Valoare: %.2f\n",
		c.id,
		c.client,
		c.valoare);
}

void enqueue(
	Nod** prim,
	Nod** ultim,
	Comanda c) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info =
		initializare(
			c.id,
			c.client,
			c.valoare
		);

	nou->next = NULL;

	if (*ultim != NULL) {

		(*ultim)->next = nou;
	}
	else {

		*prim = nou;
	}

	*ultim = nou;
}

Comanda dequeue(
	Nod** prim,
	Nod** ultim) {

	if (*prim != NULL) {

		Nod* temp = *prim;

		Comanda c =
			initializare(
				temp->info.id,
				temp->info.client,
				temp->info.valoare
			);

		*prim = (*prim)->next;

		if (*prim == NULL) {

			*ultim = NULL;
		}

		free(temp->info.client);
		free(temp);

		return c;
	}
	else {

		return initializare(-1,
			"Coada goala",
			0);
	}
}

void afisareCoada(Nod* prim) {

	while (prim != NULL) {

		afisareComanda(prim->info);

		prim = prim->next;
	}
}

float calculValoareTotala(Nod* prim) {

	float suma = 0;

	while (prim != NULL) {

		suma += prim->info.valoare;

		prim = prim->next;
	}

	return suma;
}

int numarareComenzi(Nod* prim) {

	int contor = 0;

	while (prim != NULL) {

		contor++;

		prim = prim->next;
	}

	return contor;
}

Comanda cautareComanda(
	Nod* prim,
	int id) {

	while (prim != NULL) {

		if (prim->info.id == id) {

			return initializare(
				prim->info.id,
				prim->info.client,
				prim->info.valoare
			);
		}

		prim = prim->next;
	}

	return initializare(-1,
		"Nu exista",
		0);
}

void dezalocareCoada(
	Nod** prim,
	Nod** ultim) {

	while (*prim != NULL) {

		Nod* temp = *prim;

		*prim = (*prim)->next;

		free(temp->info.client);
		free(temp);
	}

	*ultim = NULL;
}

int main() {

	Nod* prim = NULL;
	Nod* ultim = NULL;

	Comanda c1 =
		initializare(
			1,
			"Maria",
			120.50f
		);

	Comanda c2 =
		initializare(
			2,
			"Andrei",
			250.75f
		);

	Comanda c3 =
		initializare(
			3,
			"Elena",
			89.99f
		);

	Comanda c4 =
		initializare(
			4,
			"Alex",
			310.40f
		);

	enqueue(&prim, &ultim, c1);
	enqueue(&prim, &ultim, c2);
	enqueue(&prim, &ultim, c3);
	enqueue(&prim, &ultim, c4);

	free(c1.client);
	free(c2.client);
	free(c3.client);
	free(c4.client);

	printf("Coada initiala este:\n\n");

	afisareCoada(prim);

	printf("\nNumarul de comenzi este: %d\n",
		numarareComenzi(prim));

	printf("Valoarea totala este: %.2f\n",
		calculValoareTotala(prim));

	Comanda comandaCautata =
		cautareComanda(prim, 3);

	printf("\nComanda cautata este:\n");

	afisareComanda(comandaCautata);

	free(comandaCautata.client);

	printf("\nSe extrage prima comanda din coada:\n\n");

	Comanda extrasa =
		dequeue(&prim, &ultim);

	afisareComanda(extrasa);

	free(extrasa.client);

	printf("\nCoada dupa dequeue este:\n\n");

	afisareCoada(prim);

	dezalocareCoada(&prim, &ultim);

	return 0;
}