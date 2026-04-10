#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Anime Anime;
typedef struct Nod Nod;

struct Anime {
	int id;
	char* denumire;
	int episoade;
	float rating;
};

struct Nod {
	Anime info;
	Nod* next;
	Nod* prev;
};

Anime initializare(int id,
	const char* denumire,
	int episoade,
	float rating) {

	Anime a;

	a.id = id;

	a.denumire =
		(char*)malloc(sizeof(char) *
			(strlen(denumire) + 1));

	strcpy(a.denumire, denumire);

	a.episoade = episoade;

	a.rating = rating;

	return a;
}

void afisareAnime(Anime a) {

	printf("Id: %d | Anime: %s | Episoade: %d | Rating: %.2f\n",
		a.id,
		a.denumire,
		a.episoade,
		a.rating);
}

void inserareFinal(Nod** cap,
	Nod** coada,
	Anime a) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info =
		initializare(
			a.id,
			a.denumire,
			a.episoade,
			a.rating
		);

	nou->next = NULL;
	nou->prev = *coada;

	if (*coada != NULL) {

		(*coada)->next = nou;
	}
	else {

		*cap = nou;
	}

	*coada = nou;
}

void afisareInainte(Nod* cap) {

	while (cap != NULL) {

		afisareAnime(cap->info);

		cap = cap->next;
	}
}

void afisareInvers(Nod* coada) {

	while (coada != NULL) {

		afisareAnime(coada->info);

		coada = coada->prev;
	}
}

float calculRatingMediu(Nod* cap) {

	float suma = 0;
	int nrAnime = 0;

	while (cap != NULL) {

		suma += cap->info.rating;

		nrAnime++;

		cap = cap->next;
	}

	if (nrAnime > 0) {

		return suma / nrAnime;
	}
	else {

		return 0;
	}
}

Anime cautareAnimeDupaNume(
	Nod* cap,
	const char* nume) {

	while (cap != NULL) {

		if (strcmp(cap->info.denumire, nume) == 0) {

			return initializare(
				cap->info.id,
				cap->info.denumire,
				cap->info.episoade,
				cap->info.rating
			);
		}

		cap = cap->next;
	}

	return initializare(-1, "Nu exista", 0, 0);
}

void stergerePrimulNod(
	Nod** cap,
	Nod** coada) {

	if (*cap != NULL) {

		Nod* temp = *cap;

		*cap = (*cap)->next;

		if (*cap != NULL) {

			(*cap)->prev = NULL;
		}
		else {

			*coada = NULL;
		}

		free(temp->info.denumire);
		free(temp);
	}
}

void dezalocareLista(
	Nod** cap,
	Nod** coada) {

	while (*cap != NULL) {

		stergerePrimulNod(cap, coada);
	}
}

int main() {

	Nod* cap = NULL;
	Nod* coada = NULL;

	Anime a1 =
		initializare(
			1,
			"One Piece",
			1100,
			9.90f
		);

	Anime a2 =
		initializare(
			2,
			"Naruto",
			720,
			8.80f
		);

	Anime a3 =
		initializare(
			3,
			"Attack on Titan",
			94,
			9.70f
		);

	Anime a4 =
		initializare(
			4,
			"Demon Slayer",
			55,
			8.90f
		);

	inserareFinal(&cap, &coada, a1);
	inserareFinal(&cap, &coada, a2);
	inserareFinal(&cap, &coada, a3);
	inserareFinal(&cap, &coada, a4);

	free(a1.denumire);
	free(a2.denumire);
	free(a3.denumire);
	free(a4.denumire);

	printf("Lista dubla initiala este:\n\n");

	afisareInainte(cap);

	printf("\nAfisare inversa:\n\n");

	afisareInvers(coada);

	printf("\nRatingul mediu este: %.2f\n",
		calculRatingMediu(cap));

	Anime animeCautat =
		cautareAnimeDupaNume(
			cap,
			"One Piece"
		);

	printf("\nAnime-ul cautat este:\n");

	afisareAnime(animeCautat);

	free(animeCautat.denumire);

	printf("\nSe sterge primul anime din lista.\n\n");

	stergerePrimulNod(&cap, &coada);

	printf("Lista dupa stergere:\n\n");

	afisareInainte(cap);

	dezalocareLista(&cap, &coada);

	return 0;
}