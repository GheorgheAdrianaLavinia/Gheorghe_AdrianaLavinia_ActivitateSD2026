#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Serial Serial;
typedef struct Nod Nod;

struct Serial {
	int id;
	char* nume;
	float rating;
};

struct Nod {
	Serial info;
	Nod* stanga;
	Nod* dreapta;
	int inaltime;
};

/*================ INITIALIZARE =================*/

Serial initializareSerial(
	int id,
	const char* nume,
	float rating) {

	Serial s;

	s.id = id;

	s.nume =
		(char*)malloc(sizeof(char) *
			(strlen(nume) + 1));

	strcpy(s.nume, nume);

	s.rating = rating;

	return s;
}

void afisareSerial(Serial s) {

	printf("Id: %d | Nume: %s | Rating: %.2f\n",
		s.id,
		s.nume,
		s.rating);
}

/*================ HASH TABLE =================*/

int functieHash(int id, int dimensiune) {

	return id % dimensiune;
}

void exempluHashTable() {

	int dimensiune = 5;

	Serial hashTable[5];

	hashTable[0] =
		initializareSerial(
			0,
			"Gol",
			0
		);

	hashTable[1] =
		initializareSerial(
			1,
			"BreakingBad",
			9.90f
		);

	hashTable[2] =
		initializareSerial(
			2,
			"Dark",
			9.50f
		);

	hashTable[3] =
		initializareSerial(
			3,
			"Sherlock",
			9.70f
		);

	hashTable[4] =
		initializareSerial(
			4,
			"TheOffice",
			8.90f
		);

	printf("HashTable simplu:\n\n");

	for (int i = 0; i < dimensiune; i++) {

		afisareSerial(hashTable[i]);
	}

	for (int i = 0; i < dimensiune; i++) {

		free(hashTable[i].nume);
	}
}

/*================ HEAP =================*/

void interschimbare(Serial* a, Serial* b) {

	Serial aux = *a;
	*a = *b;
	*b = aux;
}

void heapify(
	Serial vector[],
	int nrElemente,
	int i) {

	int maxim = i;

	int stanga = 2 * i + 1;
	int dreapta = 2 * i + 2;

	if (stanga < nrElemente &&
		vector[stanga].rating >
		vector[maxim].rating) {

		maxim = stanga;
	}

	if (dreapta < nrElemente &&
		vector[dreapta].rating >
		vector[maxim].rating) {

		maxim = dreapta;
	}

	if (maxim != i) {

		interschimbare(
			&vector[i],
			&vector[maxim]
		);

		heapify(
			vector,
			nrElemente,
			maxim
		);
	}
}

void construireHeap(
	Serial vector[],
	int nrElemente) {

	for (int i = nrElemente / 2 - 1;
		i >= 0;
		i--) {

		heapify(
			vector,
			nrElemente,
			i
		);
	}
}

void afisareVector(
	Serial vector[],
	int nrElemente) {

	for (int i = 0; i < nrElemente; i++) {

		afisareSerial(vector[i]);
	}
}

/*================ ARBORE BINAR =================*/

Nod* creareNod(Serial s) {

	Nod* nou =
		(Nod*)malloc(sizeof(Nod));

	nou->info =
		initializareSerial(
			s.id,
			s.nume,
			s.rating
		);

	nou->stanga = NULL;
	nou->dreapta = NULL;
	nou->inaltime = 1;

	return nou;
}

Nod* inserareABC(
	Nod* radacina,
	Serial s) {

	if (radacina == NULL) {

		return creareNod(s);
	}

	if (s.id < radacina->info.id) {

		radacina->stanga =
			inserareABC(
				radacina->stanga,
				s
			);
	}
	else {

		if (s.id > radacina->info.id) {

			radacina->dreapta =
				inserareABC(
					radacina->dreapta,
					s
				);
		}
	}

	return radacina;
}

void afisareInordine(
	Nod* radacina) {

	if (radacina != NULL) {

		afisareInordine(
			radacina->stanga
		);

		afisareSerial(
			radacina->info
		);

		afisareInordine(
			radacina->dreapta
		);
	}
}

/*================ AVL =================*/

int maxim(int a, int b) {

	if (a > b) {

		return a;
	}
	else {

		return b;
	}
}

int inaltime(Nod* radacina) {

	if (radacina == NULL) {

		return 0;
	}

	return radacina->inaltime;
}

int factorEchilibru(
	Nod* radacina) {

	if (radacina == NULL) {

		return 0;
	}

	return
		inaltime(radacina->stanga) -
		inaltime(radacina->dreapta);
}

Nod* rotireDreapta(
	Nod* y) {

	Nod* x = y->stanga;
	Nod* T2 = x->dreapta;

	x->dreapta = y;
	y->stanga = T2;

	y->inaltime =
		1 + maxim(
			inaltime(y->stanga),
			inaltime(y->dreapta)
		);

	x->inaltime =
		1 + maxim(
			inaltime(x->stanga),
			inaltime(x->dreapta)
		);

	return x;
}

Nod* rotireStanga(
	Nod* x) {

	Nod* y = x->dreapta;
	Nod* T2 = y->stanga;

	y->stanga = x;
	x->dreapta = T2;

	x->inaltime =
		1 + maxim(
			inaltime(x->stanga),
			inaltime(x->dreapta)
		);

	y->inaltime =
		1 + maxim(
			inaltime(y->stanga),
			inaltime(y->dreapta)
		);

	return y;
}

Nod* inserareAVL(
	Nod* radacina,
	Serial s) {

	if (radacina == NULL) {

		return creareNod(s);
	}

	if (s.id < radacina->info.id) {

		radacina->stanga =
			inserareAVL(
				radacina->stanga,
				s
			);
	}
	else {

		if (s.id > radacina->info.id) {

			radacina->dreapta =
				inserareAVL(
					radacina->dreapta,
					s
				);
		}
		else {

			return radacina;
		}
	}

	radacina->inaltime =
		1 + maxim(
			inaltime(radacina->stanga),
			inaltime(radacina->dreapta)
		);

	int echilibru =
		factorEchilibru(radacina);

	if (echilibru > 1 &&
		s.id < radacina->stanga->info.id) {

		return rotireDreapta(radacina);
	}

	if (echilibru < -1 &&
		s.id > radacina->dreapta->info.id) {

		return rotireStanga(radacina);
	}

	return radacina;
}

/*================ DEZALOCARE =================*/

void dezalocareArbore(
	Nod** radacina) {

	if (*radacina != NULL) {

		dezalocareArbore(
			&((*radacina)->stanga)
		);

		dezalocareArbore(
			&((*radacina)->dreapta)
		);

		free((*radacina)->info.nume);

		free(*radacina);

		*radacina = NULL;
	}
}

/*================ MAIN =================*/

int main() {

	printf("========== HASH TABLE ==========\n\n");

	exempluHashTable();

	printf("\n========== HEAP ==========\n\n");

	Serial vector[4];

	vector[0] =
		initializareSerial(
			1,
			"BreakingBad",
			9.90f
		);

	vector[1] =
		initializareSerial(
			2,
			"Dark",
			9.50f
		);

	vector[2] =
		initializareSerial(
			3,
			"Sherlock",
			9.70f
		);

	vector[3] =
		initializareSerial(
			4,
			"TheOffice",
			8.90f
		);

	construireHeap(
		vector,
		4
	);

	afisareVector(
		vector,
		4
	);

	printf("\n========== ARBORE BINAR ==========\n\n");

	Nod* abc = NULL;

	abc =
		inserareABC(
			abc,
			vector[0]
		);

	abc =
		inserareABC(
			abc,
			vector[1]
		);

	abc =
		inserareABC(
			abc,
			vector[2]
		);

	abc =
		inserareABC(
			abc,
			vector[3]
		);

	afisareInordine(abc);

	printf("\n========== AVL ==========\n\n");

	Nod* avl = NULL;

	avl =
		inserareAVL(
			avl,
			vector[0]
		);

	avl =
		inserareAVL(
			avl,
			vector[1]
		);

	avl =
		inserareAVL(
			avl,
			vector[2]
		);

	avl =
		inserareAVL(
			avl,
			vector[3]
		);

	afisareInordine(avl);

	for (int i = 0; i < 4; i++) {

		free(vector[i].nume);
	}

	dezalocareArbore(&abc);
	dezalocareArbore(&avl);

	return 0;
}