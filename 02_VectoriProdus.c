#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Produs Produs;

struct Produs {

	int cod;
	char* denumire;
	float pret;
	int stoc;
};

// Functie pentru initializarea unui produs
Produs initializare(int cod,
	const char* denumire,
	float pret,
	int stoc) {

	Produs p;

	p.cod = cod;

	p.denumire =
		(char*)malloc(sizeof(char) *
			(strlen(denumire) + 1));

	strcpy(p.denumire, denumire);

	p.pret = pret;

	p.stoc = stoc;

	return p;
}

// Functie pentru afisarea unui produs
void afisareProdus(Produs p) {

	printf("Cod: %d\n", p.cod);
	printf("Denumire: %s\n", p.denumire);
	printf("Pret: %.2f\n", p.pret);
	printf("Stoc: %d\n", p.stoc);
	printf("\n");
}

// Functie pentru afisarea vectorului
void afisareVector(Produs* vector,
	int nrElemente) {

	for (int i = 0; i < nrElemente; i++) {

		afisareProdus(vector[i]);
	}
}

// Functie pentru calcularea valorii totale
float calculValoareTotala(Produs* vector,
	int nrElemente) {

	float suma = 0;

	for (int i = 0; i < nrElemente; i++) {

		suma +=
			vector[i].pret *
			vector[i].stoc;
	}

	return suma;
}

// Functie pentru copierea produselor
// cu stoc mai mare decat 10
Produs* copiazaProduseStoc(
	Produs* vector,
	int nrElemente,
	int* nrProduseCopiate) {

	*nrProduseCopiate = 0;

	for (int i = 0; i < nrElemente; i++) {

		if (vector[i].stoc > 10) {

			(*nrProduseCopiate)++;
		}
	}

	Produs* vectorNou =
		(Produs*)malloc(sizeof(Produs) *
			(*nrProduseCopiate));

	int k = 0;

	for (int i = 0; i < nrElemente; i++) {

		if (vector[i].stoc > 10) {

			vectorNou[k] =
				initializare(
					vector[i].cod,
					vector[i].denumire,
					vector[i].pret,
					vector[i].stoc
				);

			k++;
		}
	}

	return vectorNou;
}

// Functie pentru dezalocarea memoriei
void dezalocare(
	Produs** vector,
	int* nrElemente) {

	for (int i = 0; i < *nrElemente; i++) {

		free((*vector)[i].denumire);
	}

	free(*vector);

	*vector = NULL;
	*nrElemente = 0;
}

int main() {

	int nrProduse = 3;

	Produs* vector =
		(Produs*)malloc(sizeof(Produs) *
			nrProduse);

	vector[0] =
		initializare(
			1,
			"Laptop",
			3500.50f,
			15
		);

	vector[1] =
		initializare(
			2,
			"Mouse",
			120.99f,
			5
		);

	vector[2] =
		initializare(
			3,
			"Tastatura",
			250.75f,
			20
		);

	printf("Vectorul initial este:\n\n");

	afisareVector(vector, nrProduse);

	float valoareTotala =
		calculValoareTotala(
			vector,
			nrProduse
		);

	printf("Valoarea totala este: %.2f\n\n",
		valoareTotala);

	int nrProduseCopiate = 0;

	Produs* produseStoc =
		copiazaProduseStoc(
			vector,
			nrProduse,
			&nrProduseCopiate
		);

	printf("Produsele cu stoc mai mare decat 10 sunt:\n\n");

	afisareVector(
		produseStoc,
		nrProduseCopiate
	);

	dezalocare(&vector, &nrProduse);

	dezalocare(
		&produseStoc,
		&nrProduseCopiate
	);

	return 0;
}