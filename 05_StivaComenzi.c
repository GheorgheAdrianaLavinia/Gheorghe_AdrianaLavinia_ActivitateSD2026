#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Comanda Comanda;
typedef struct Nod Nod;

struct Comanda {
	int id;
	char* numeClient;
	float valoare;
};

struct Nod {
	Comanda info;
	Nod* next;
};

Comanda initializare(int id, const char* numeClient, float valoare) {
	Comanda c;

	c.id = id;

	c.numeClient = (char*)malloc(sizeof(char) * (strlen(numeClient) + 1));
	strcpy(c.numeClient, numeClient);

	c.valoare = valoare;

	return c;
}

void afisareComanda(Comanda c) {
	printf("Id comanda: %d | Client: %s | Valoare: %.2f lei\n",
		c.id, c.numeClient, c.valoare);
}

void push(Nod** varf, Comanda c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = initializare(c.id, c.numeClient, c.valoare);
	nou->next = *varf;

	*varf = nou;
}

Comanda pop(Nod** varf) {
	if (*varf != NULL) {
		Nod* temp = *varf;

		Comanda c = initializare(
			temp->info.id,
			temp->info.numeClient,
			temp->info.valoare
		);

		*varf = (*varf)->next;

		free(temp->info.numeClient);
		free(temp);

		return c;
	}
	else {
		return initializare(-1, "Stiva goala", 0);
	}
}

void afisareStiva(Nod* varf) {
	while (varf != NULL) {
		afisareComanda(varf->info);
		varf = varf->next;
	}
}

int numarareComenzi(Nod* varf) {
	int contor = 0;

	while (varf != NULL) {
		contor++;
		varf = varf->next;
	}

	return contor;
}

float calculValoareTotala(Nod* varf) {
	float suma = 0;

	while (varf != NULL) {
		suma += varf->info.valoare;
		varf = varf->next;
	}

	return suma;
}

Comanda cautareComandaDupaId(Nod* varf, int id) {
	while (varf != NULL) {
		if (varf->info.id == id) {
			return initializare(
				varf->info.id,
				varf->info.numeClient,
				varf->info.valoare
			);
		}

		varf = varf->next;
	}

	return initializare(-1, "Nu exista", 0);
}

void dezalocareStiva(Nod** varf) {
	while (*varf != NULL) {
		Nod* temp = *varf;

		*varf = (*varf)->next;

		free(temp->info.numeClient);
		free(temp);
	}
}

int main() {
	Nod* stiva = NULL;

	Comanda c1 = initializare(101, "Ana", 120.50f);
	Comanda c2 = initializare(102, "Mihai", 89.99f);
	Comanda c3 = initializare(103, "Elena", 250.00f);
	Comanda c4 = initializare(104, "Andrei", 45.75f);

	push(&stiva, c1);
	push(&stiva, c2);
	push(&stiva, c3);
	push(&stiva, c4);

	free(c1.numeClient);
	free(c2.numeClient);
	free(c3.numeClient);
	free(c4.numeClient);

	printf("Stiva initiala de comenzi este:\n\n");
	afisareStiva(stiva);

	printf("\nNumarul de comenzi este: %d\n",
		numarareComenzi(stiva));

	printf("Valoarea totala a comenzilor este: %.2f lei\n",
		calculValoareTotala(stiva));

	int idCautat = 102;

	printf("\nComanda cautata cu id %d este:\n", idCautat);

	Comanda comandaCautata =
		cautareComandaDupaId(stiva, idCautat);

	afisareComanda(comandaCautata);
	free(comandaCautata.numeClient);

	printf("\nSe scoate ultima comanda introdusa in stiva:\n");

	Comanda comandaScoasa = pop(&stiva);

	afisareComanda(comandaScoasa);
	free(comandaScoasa.numeClient);

	printf("\nStiva dupa operatia pop este:\n\n");
	afisareStiva(stiva);

	dezalocareStiva(&stiva);

	return 0;
}