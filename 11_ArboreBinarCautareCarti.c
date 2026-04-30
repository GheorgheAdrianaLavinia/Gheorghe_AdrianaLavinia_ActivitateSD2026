#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Carte Carte;
typedef struct Nod Nod;

struct Carte {
	int idCarte;
	char* titlu;
	char* autor;
	int nrPagini;
};

struct Nod {
	Carte info;
	Nod* stanga;
	Nod* dreapta;
};

// Functie pentru initializarea unei carti
Carte initializareCarte(
	int idCarte,
	const char* titlu,
	const char* autor,
	int nrPagini) {

	Carte c;

	c.idCarte = idCarte;

	c.titlu =
		(char*)malloc(sizeof(char) *
			(strlen(titlu) + 1));

	strcpy(c.titlu, titlu);

	c.autor =
		(char*)malloc(sizeof(char) *
			(strlen(autor) + 1));

	strcpy(c.autor, autor);

	c.nrPagini = nrPagini;

	return c;
}

// Functie pentru afisarea unei carti
void afisareCarte(Carte c) {

	printf("Id: %d | Titlu: %s | Autor: %s | Pagini: %d\n",
		c.idCarte,
		c.titlu,
		c.autor,
		c.nrPagini);
}

// Creare nod
Nod* creareNod(Carte c) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info =
		initializareCarte(
			c.idCarte,
			c.titlu,
			c.autor,
			c.nrPagini
		);

	nou->stanga = NULL;
	nou->dreapta = NULL;

	return nou;
}

// Inserare nod in arbore
Nod* inserareNod(Nod* radacina, Carte c) {

	if (radacina == NULL) {

		return creareNod(c);
	}

	if (c.idCarte < radacina->info.idCarte) {

		radacina->stanga =
			inserareNod(
				radacina->stanga,
				c
			);
	}
	else {

		if (c.idCarte > radacina->info.idCarte) {

			radacina->dreapta =
				inserareNod(
					radacina->dreapta,
					c
				);
		}
	}

	return radacina;
}

// Afisare inordine
void afisareInordine(Nod* radacina) {

	if (radacina != NULL) {

		afisareInordine(radacina->stanga);

		afisareCarte(radacina->info);

		afisareInordine(radacina->dreapta);
	}
}

// Afisare preordine
void afisarePreordine(Nod* radacina) {

	if (radacina != NULL) {

		afisareCarte(radacina->info);

		afisarePreordine(radacina->stanga);

		afisarePreordine(radacina->dreapta);
	}
}

// Afisare postordine
void afisarePostordine(Nod* radacina) {

	if (radacina != NULL) {

		afisarePostordine(radacina->stanga);

		afisarePostordine(radacina->dreapta);

		afisareCarte(radacina->info);
	}
}

// Numarare noduri
int numarareNoduri(Nod* radacina) {

	if (radacina == NULL) {

		return 0;
	}

	return 1 +
		numarareNoduri(radacina->stanga) +
		numarareNoduri(radacina->dreapta);
}

// Calcul total pagini
int calculTotalPagini(Nod* radacina) {

	if (radacina == NULL) {

		return 0;
	}

	return radacina->info.nrPagini +
		calculTotalPagini(radacina->stanga) +
		calculTotalPagini(radacina->dreapta);
}

// Cautare carte dupa id
Carte cautareCarte(Nod* radacina, int idCautat) {

	if (radacina == NULL) {

		return initializareCarte(
			-1,
			"Nu exista",
			"Necunoscut",
			0
		);
	}

	if (radacina->info.idCarte == idCautat) {

		return initializareCarte(
			radacina->info.idCarte,
			radacina->info.titlu,
			radacina->info.autor,
			radacina->info.nrPagini
		);
	}

	if (idCautat < radacina->info.idCarte) {

		return cautareCarte(
			radacina->stanga,
			idCautat
		);
	}
	else {

		return cautareCarte(
			radacina->dreapta,
			idCautat
		);
	}
}

// Afisare carti cu peste 400 pagini
void afisareCartiMari(Nod* radacina) {

	if (radacina != NULL) {

		afisareCartiMari(radacina->stanga);

		if (radacina->info.nrPagini > 400) {

			afisareCarte(radacina->info);
		}

		afisareCartiMari(radacina->dreapta);
	}
}

// Calcul inaltime arbore
int inaltimeArbore(Nod* radacina) {

	if (radacina == NULL) {

		return 0;
	}

	int stanga =
		inaltimeArbore(radacina->stanga);

	int dreapta =
		inaltimeArbore(radacina->dreapta);

	if (stanga > dreapta) {

		return 1 + stanga;
	}
	else {

		return 1 + dreapta;
	}
}

// Dezalocare arbore
void dezalocareArbore(Nod** radacina) {

	if (*radacina != NULL) {

		dezalocareArbore(
			&((*radacina)->stanga)
		);

		dezalocareArbore(
			&((*radacina)->dreapta)
		);

		free((*radacina)->info.titlu);
		free((*radacina)->info.autor);

		free(*radacina);

		*radacina = NULL;
	}
}

int main() {

	Nod* radacina = NULL;

	Carte c1 =
		initializareCarte(
			50,
			"Atomic Habits",
			"James Clear",
			320
		);

	Carte c2 =
		initializareCarte(
			30,
			"Harry Potter",
			"J.K. Rowling",
			500
		);

	Carte c3 =
		initializareCarte(
			70,
			"The Hobbit",
			"Tolkien",
			450
		);

	Carte c4 =
		initializareCarte(
			20,
			"1984",
			"George Orwell",
			350
		);

	Carte c5 =
		initializareCarte(
			40,
			"Clean Code",
			"Robert Martin",
			464
		);

	radacina =
		inserareNod(radacina, c1);

	radacina =
		inserareNod(radacina, c2);

	radacina =
		inserareNod(radacina, c3);

	radacina =
		inserareNod(radacina, c4);

	radacina =
		inserareNod(radacina, c5);

	free(c1.titlu);
	free(c1.autor);

	free(c2.titlu);
	free(c2.autor);

	free(c3.titlu);
	free(c3.autor);

	free(c4.titlu);
	free(c4.autor);

	free(c5.titlu);
	free(c5.autor);

	printf("Afisare inordine:\n\n");

	afisareInordine(radacina);

	printf("\nAfisare preordine:\n\n");

	afisarePreordine(radacina);

	printf("\nAfisare postordine:\n\n");

	afisarePostordine(radacina);

	printf("\nNumar total de carti: %d\n",
		numarareNoduri(radacina));

	printf("Total pagini: %d\n",
		calculTotalPagini(radacina));

	printf("Inaltime arbore: %d\n",
		inaltimeArbore(radacina));

	int idCautat = 40;

	printf("\nCartea cautata este:\n");

	Carte carteGasita =
		cautareCarte(
			radacina,
			idCautat
		);

	afisareCarte(carteGasita);

	free(carteGasita.titlu);
	free(carteGasita.autor);

	printf("\nCartile cu peste 400 pagini sunt:\n\n");

	afisareCartiMari(radacina);

	dezalocareArbore(&radacina);

	return 0;
}