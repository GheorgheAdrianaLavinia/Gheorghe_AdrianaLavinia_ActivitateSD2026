#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Produs Produs;

struct Produs {
	int cod;
	char* denumire;
	float pret;
	int cantitate;
};

Produs initializare(int cod, const char* denumire, float pret, int cantitate) {
	Produs p;

	p.cod = cod;

	p.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(p.denumire, denumire);

	p.pret = pret;
	p.cantitate = cantitate;

	return p;
}

void afisareProdus(Produs p) {
	printf("Cod: %d | Denumire: %s | Pret: %.2f | Cantitate: %d\n",
		p.cod, p.denumire, p.pret, p.cantitate);
}

void afisareVector(Produs* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisareProdus(vector[i]);
	}
}

void afisareMatrice(Produs** matrice, int nrLinii, int nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		printf("\nRaftul %d:\n", i + 1);

		for (int j = 0; j < nrColoane; j++) {
			afisareProdus(matrice[i][j]);
		}
	}
}

float valoareProdus(Produs p) {
	return p.pret * p.cantitate;
}

float valoareTotalaVector(Produs* vector, int nrElemente) {
	float suma = 0;

	for (int i = 0; i < nrElemente; i++) {
		suma += valoareProdus(vector[i]);
	}

	return suma;
}

float valoareTotalaMatrice(Produs** matrice, int nrLinii, int nrColoane) {
	float suma = 0;

	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			suma += valoareProdus(matrice[i][j]);
		}
	}

	return suma;
}

Produs* copiazaDinMatriceInVector(
	Produs** matrice,
	int nrLinii,
	int nrColoane,
	int* nrProduseCopiate) {

	*nrProduseCopiate = nrLinii * nrColoane;

	Produs* vector = (Produs*)malloc(sizeof(Produs) * (*nrProduseCopiate));

	int k = 0;

	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			vector[k] = initializare(
				matrice[i][j].cod,
				matrice[i][j].denumire,
				matrice[i][j].pret,
				matrice[i][j].cantitate
			);

			k++;
		}
	}

	return vector;
}

Produs** copiazaDinVectorInMatrice(
	Produs* vector,
	int nrElemente,
	int nrLinii,
	int nrColoane) {

	if (nrElemente != nrLinii * nrColoane) {
		return NULL;
	}

	Produs** matrice = (Produs**)malloc(sizeof(Produs*) * nrLinii);

	for (int i = 0; i < nrLinii; i++) {
		matrice[i] = (Produs*)malloc(sizeof(Produs) * nrColoane);
	}

	int k = 0;

	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			matrice[i][j] = initializare(
				vector[k].cod,
				vector[k].denumire,
				vector[k].pret,
				vector[k].cantitate
			);

			k++;
		}
	}

	return matrice;
}

Produs cautareProdusVector(Produs* vector, int nrElemente, int cod) {
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].cod == cod) {
			return initializare(
				vector[i].cod,
				vector[i].denumire,
				vector[i].pret,
				vector[i].cantitate
			);
		}
	}

	return initializare(-1, "Nu exista", 0, 0);
}

void modificaPretInMatrice(Produs** matrice,
	int nrLinii,
	int nrColoane,
	int cod,
	float pretNou) {

	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			if (matrice[i][j].cod == cod) {
				matrice[i][j].pret = pretNou;
			}
		}
	}
}

void dezalocareVector(Produs** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++) {
		free((*vector)[i].denumire);
	}

	free(*vector);

	*vector = NULL;
	*nrElemente = 0;
}

void dezalocareMatrice(Produs*** matrice, int* nrLinii, int* nrColoane) {
	for (int i = 0; i < *nrLinii; i++) {
		for (int j = 0; j < *nrColoane; j++) {
			free((*matrice)[i][j].denumire);
		}

		free((*matrice)[i]);
	}

	free(*matrice);

	*matrice = NULL;
	*nrLinii = 0;
	*nrColoane = 0;
}

int main() {
	int nrProduse = 4;

	Produs* vector = (Produs*)malloc(sizeof(Produs) * nrProduse);

	vector[0] = initializare(1, "Cafea", 25.50f, 10);
	vector[1] = initializare(2, "Ceai", 15.00f, 8);
	vector[2] = initializare(3, "Zahar", 6.50f, 20);
	vector[3] = initializare(4, "Lapte", 9.99f, 12);

	printf("Vectorul initial de produse:\n\n");
	afisareVector(vector, nrProduse);

	printf("\nValoarea totala a vectorului este: %.2f lei\n",
		valoareTotalaVector(vector, nrProduse));

	int nrLinii = 2;
	int nrColoane = 2;

	Produs** matrice = copiazaDinVectorInMatrice(
		vector,
		nrProduse,
		nrLinii,
		nrColoane
	);

	printf("\nMatricea obtinuta din vector:\n");
	afisareMatrice(matrice, nrLinii, nrColoane);

	printf("\nValoarea totala a matricei este: %.2f lei\n",
		valoareTotalaMatrice(matrice, nrLinii, nrColoane));

	modificaPretInMatrice(matrice, nrLinii, nrColoane, 1, 30.00f);

	printf("\nMatricea dupa modificarea pretului produsului cu codul 1:\n");
	afisareMatrice(matrice, nrLinii, nrColoane);

	int nrProduseCopiate = 0;

	Produs* vectorCopiat = copiazaDinMatriceInVector(
		matrice,
		nrLinii,
		nrColoane,
		&nrProduseCopiate
	);

	printf("\nVectorul copiat inapoi din matrice:\n\n");
	afisareVector(vectorCopiat, nrProduseCopiate);

	Produs produsCautat = cautareProdusVector(vectorCopiat, nrProduseCopiate, 3);

	printf("\nProdusul cautat dupa cod este:\n");
	afisareProdus(produsCautat);

	free(produsCautat.denumire);

	dezalocareVector(&vector, &nrProduse);
	dezalocareMatrice(&matrice, &nrLinii, &nrColoane);
	dezalocareVector(&vectorCopiat, &nrProduseCopiate);

	return 0;
}