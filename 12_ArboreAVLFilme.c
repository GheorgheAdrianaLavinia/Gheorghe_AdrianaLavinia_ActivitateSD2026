#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Film Film;
typedef struct Nod Nod;

struct Film {
	int idFilm;
	char* titlu;
	float rating;
};

struct Nod {
	Film info;
	Nod* stanga;
	Nod* dreapta;
	int inaltime;
};

Film initializareFilm(int idFilm, const char* titlu, float rating) {
	Film f;

	f.idFilm = idFilm;

	f.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(f.titlu, titlu);

	f.rating = rating;

	return f;
}

void afisareFilm(Film f) {
	printf("Id: %d | Titlu: %s | Rating: %.2f\n",
		f.idFilm, f.titlu, f.rating);
}

int maxim(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

int inaltimeNod(Nod* radacina) {
	if (radacina == NULL) {
		return 0;
	}

	return radacina->inaltime;
}

Nod* creareNod(Film f) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = initializareFilm(
		f.idFilm,
		f.titlu,
		f.rating
	);

	nou->stanga = NULL;
	nou->dreapta = NULL;
	nou->inaltime = 1;

	return nou;
}

int factorEchilibru(Nod* radacina) {
	if (radacina == NULL) {
		return 0;
	}

	return inaltimeNod(radacina->stanga) -
		inaltimeNod(radacina->dreapta);
}

Nod* rotireDreapta(Nod* y) {
	Nod* x = y->stanga;
	Nod* T2 = x->dreapta;

	x->dreapta = y;
	y->stanga = T2;

	y->inaltime =
		1 + maxim(
			inaltimeNod(y->stanga),
			inaltimeNod(y->dreapta)
		);

	x->inaltime =
		1 + maxim(
			inaltimeNod(x->stanga),
			inaltimeNod(x->dreapta)
		);

	return x;
}

Nod* rotireStanga(Nod* x) {
	Nod* y = x->dreapta;
	Nod* T2 = y->stanga;

	y->stanga = x;
	x->dreapta = T2;

	x->inaltime =
		1 + maxim(
			inaltimeNod(x->stanga),
			inaltimeNod(x->dreapta)
		);

	y->inaltime =
		1 + maxim(
			inaltimeNod(y->stanga),
			inaltimeNod(y->dreapta)
		);

	return y;
}

Nod* inserareAVL(Nod* radacina, Film f) {
	if (radacina == NULL) {
		return creareNod(f);
	}

	if (f.idFilm < radacina->info.idFilm) {
		radacina->stanga =
			inserareAVL(radacina->stanga, f);
	}
	else {
		if (f.idFilm > radacina->info.idFilm) {
			radacina->dreapta =
				inserareAVL(radacina->dreapta, f);
		}
		else {
			return radacina;
		}
	}

	radacina->inaltime =
		1 + maxim(
			inaltimeNod(radacina->stanga),
			inaltimeNod(radacina->dreapta)
		);

	int echilibru = factorEchilibru(radacina);

	if (echilibru > 1 &&
		f.idFilm < radacina->stanga->info.idFilm) {

		return rotireDreapta(radacina);
	}

	if (echilibru < -1 &&
		f.idFilm > radacina->dreapta->info.idFilm) {

		return rotireStanga(radacina);
	}

	if (echilibru > 1 &&
		f.idFilm > radacina->stanga->info.idFilm) {

		radacina->stanga =
			rotireStanga(radacina->stanga);

		return rotireDreapta(radacina);
	}

	if (echilibru < -1 &&
		f.idFilm < radacina->dreapta->info.idFilm) {

		radacina->dreapta =
			rotireDreapta(radacina->dreapta);

		return rotireStanga(radacina);
	}

	return radacina;
}

void afisareInordine(Nod* radacina) {
	if (radacina != NULL) {
		afisareInordine(radacina->stanga);

		afisareFilm(radacina->info);

		afisareInordine(radacina->dreapta);
	}
}

void afisarePreordine(Nod* radacina) {
	if (radacina != NULL) {
		afisareFilm(radacina->info);

		afisarePreordine(radacina->stanga);

		afisarePreordine(radacina->dreapta);
	}
}

Film cautareFilm(Nod* radacina, int idFilm) {
	if (radacina == NULL) {
		return initializareFilm(-1, "Nu exista", 0);
	}

	if (radacina->info.idFilm == idFilm) {
		return initializareFilm(
			radacina->info.idFilm,
			radacina->info.titlu,
			radacina->info.rating
		);
	}

	if (idFilm < radacina->info.idFilm) {
		return cautareFilm(radacina->stanga, idFilm);
	}
	else {
		return cautareFilm(radacina->dreapta, idFilm);
	}
}

int numarareFilme(Nod* radacina) {
	if (radacina == NULL) {
		return 0;
	}

	return 1 +
		numarareFilme(radacina->stanga) +
		numarareFilme(radacina->dreapta);
}

float sumaRatinguri(Nod* radacina) {
	if (radacina == NULL) {
		return 0;
	}

	return radacina->info.rating +
		sumaRatinguri(radacina->stanga) +
		sumaRatinguri(radacina->dreapta);
}

float calculRatingMediu(Nod* radacina) {
	int nrFilme = numarareFilme(radacina);

	if (nrFilme == 0) {
		return 0;
	}

	return sumaRatinguri(radacina) / nrFilme;
}

void afisareFilmeCuRatingMare(Nod* radacina, float limita) {
	if (radacina != NULL) {
		afisareFilmeCuRatingMare(radacina->stanga, limita);

		if (radacina->info.rating >= limita) {
			afisareFilm(radacina->info);
		}

		afisareFilmeCuRatingMare(radacina->dreapta, limita);
	}
}

void dezalocareArbore(Nod** radacina) {
	if (*radacina != NULL) {
		dezalocareArbore(&((*radacina)->stanga));

		dezalocareArbore(&((*radacina)->dreapta));

		free((*radacina)->info.titlu);
		free(*radacina);

		*radacina = NULL;
	}
}

int main() {
	Nod* radacina = NULL;

	Film f1 = initializareFilm(30, "Interstellar", 9.70f);
	Film f2 = initializareFilm(20, "Inception", 9.50f);
	Film f3 = initializareFilm(10, "Avatar", 8.80f);
	Film f4 = initializareFilm(40, "Titanic", 8.90f);
	Film f5 = initializareFilm(50, "Joker", 9.10f);
	Film f6 = initializareFilm(25, "Dune", 9.00f);

	radacina = inserareAVL(radacina, f1);
	radacina = inserareAVL(radacina, f2);
	radacina = inserareAVL(radacina, f3);
	radacina = inserareAVL(radacina, f4);
	radacina = inserareAVL(radacina, f5);
	radacina = inserareAVL(radacina, f6);

	free(f1.titlu);
	free(f2.titlu);
	free(f3.titlu);
	free(f4.titlu);
	free(f5.titlu);
	free(f6.titlu);

	printf("Afisare inordine AVL:\n\n");
	afisareInordine(radacina);

	printf("\nAfisare preordine AVL:\n\n");
	afisarePreordine(radacina);

	printf("\nNumar filme: %d\n",
		numarareFilme(radacina));

	printf("Rating mediu: %.2f\n",
		calculRatingMediu(radacina));

	printf("Inaltime arbore AVL: %d\n",
		inaltimeNod(radacina));

	int idCautat = 25;

	printf("\nFilmul cautat este:\n");

	Film filmGasit =
		cautareFilm(radacina, idCautat);

	afisareFilm(filmGasit);

	free(filmGasit.titlu);

	printf("\nFilmele cu rating peste 9 sunt:\n\n");

	afisareFilmeCuRatingMare(radacina, 9.00f);

	dezalocareArbore(&radacina);

	return 0;
}