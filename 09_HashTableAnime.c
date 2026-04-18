#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Anime Anime;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Anime {
	int id;
	char* denumire;
	int episoade;
	float rating;
};

struct Nod {
	Anime info;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int dimensiune;
};

Anime initializare(int id, const char* denumire, int episoade, float rating) {
	Anime a;

	a.id = id;

	a.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(a.denumire, denumire);

	a.episoade = episoade;
	a.rating = rating;

	return a;
}

void afisareAnime(Anime a) {
	printf("Id: %d | Anime: %s | Episoade: %d | Rating: %.2f\n",
		a.id, a.denumire, a.episoade, a.rating);
}

int functieHash(int id, int dimensiune) {
	return id % dimensiune;
}

HashTable initializareHashTable(int dimensiune) {
	HashTable ht;

	ht.dimensiune = dimensiune;
	ht.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);

	for (int i = 0; i < dimensiune; i++) {
		ht.vector[i] = NULL;
	}

	return ht;
}

void inserareHashTable(HashTable ht, Anime a) {
	int pozitie = functieHash(a.id, ht.dimensiune);

	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = initializare(
		a.id,
		a.denumire,
		a.episoade,
		a.rating
	);

	nou->next = ht.vector[pozitie];

	ht.vector[pozitie] = nou;
}

void afisareHashTable(HashTable ht) {
	for (int i = 0; i < ht.dimensiune; i++) {
		printf("\nPozitia %d:\n", i);

		Nod* temp = ht.vector[i];

		if (temp == NULL) {
			printf("Nu exista elemente.\n");
		}

		while (temp != NULL) {
			afisareAnime(temp->info);
			temp = temp->next;
		}
	}
}

Anime cautareAnimeDupaId(HashTable ht, int id) {
	int pozitie = functieHash(id, ht.dimensiune);

	Nod* temp = ht.vector[pozitie];

	while (temp != NULL) {
		if (temp->info.id == id) {
			return initializare(
				temp->info.id,
				temp->info.denumire,
				temp->info.episoade,
				temp->info.rating
			);
		}

		temp = temp->next;
	}

	return initializare(-1, "Nu exista", 0, 0);
}

void stergereAnimeDupaId(HashTable ht, int id) {
	int pozitie = functieHash(id, ht.dimensiune);

	Nod* temp = ht.vector[pozitie];
	Nod* anterior = NULL;

	while (temp != NULL) {
		if (temp->info.id == id) {
			if (anterior == NULL) {
				ht.vector[pozitie] = temp->next;
			}
			else {
				anterior->next = temp->next;
			}

			free(temp->info.denumire);
			free(temp);

			return;
		}

		anterior = temp;
		temp = temp->next;
	}
}

float calculRatingMediu(HashTable ht) {
	float suma = 0;
	int nrAnime = 0;

	for (int i = 0; i < ht.dimensiune; i++) {
		Nod* temp = ht.vector[i];

		while (temp != NULL) {
			suma += temp->info.rating;
			nrAnime++;

			temp = temp->next;
		}
	}

	if (nrAnime > 0) {
		return suma / nrAnime;
	}

	return 0;
}

void dezalocareHashTable(HashTable* ht) {
	for (int i = 0; i < ht->dimensiune; i++) {
		Nod* temp = ht->vector[i];

		while (temp != NULL) {
			Nod* aux = temp;

			temp = temp->next;

			free(aux->info.denumire);
			free(aux);
		}

		ht->vector[i] = NULL;
	}

	free(ht->vector);
	ht->vector = NULL;
	ht->dimensiune = 0;
}

int main() {
	HashTable ht = initializareHashTable(5);

	Anime a1 = initializare(1, "One Piece", 1100, 9.90f);
	Anime a2 = initializare(2, "Naruto", 720, 8.80f);
	Anime a3 = initializare(6, "Attack on Titan", 94, 9.70f);
	Anime a4 = initializare(7, "Demon Slayer", 55, 8.90f);
	Anime a5 = initializare(11, "Death Note", 37, 9.40f);

	inserareHashTable(ht, a1);
	inserareHashTable(ht, a2);
	inserareHashTable(ht, a3);
	inserareHashTable(ht, a4);
	inserareHashTable(ht, a5);

	free(a1.denumire);
	free(a2.denumire);
	free(a3.denumire);
	free(a4.denumire);
	free(a5.denumire);

	printf("Tabela de dispersie initiala:\n");
	afisareHashTable(ht);

	printf("\nRatingul mediu este: %.2f\n", calculRatingMediu(ht));

	Anime animeCautat = cautareAnimeDupaId(ht, 1);

	printf("\nAnime cautat dupa id:\n");
	afisareAnime(animeCautat);

	free(animeCautat.denumire);

	printf("\nSe sterge anime-ul cu id 6.\n");
	stergereAnimeDupaId(ht, 6);

	printf("\nTabela dupa stergere:\n");
	afisareHashTable(ht);

	dezalocareHashTable(&ht);

	return 0;
}