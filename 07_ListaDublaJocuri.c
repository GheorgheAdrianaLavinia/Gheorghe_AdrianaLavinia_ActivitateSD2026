#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Joc Joc;
typedef struct Nod Nod;

struct Joc {
	int id;
	char* denumire;
	float pret;
	int oreJucate;
};

struct Nod {
	Joc info;
	Nod* next;
	Nod* prev;
};

Joc initializareJoc(int id,
	const char* denumire,
	float pret,
	int oreJucate) {

	Joc j;

	j.id = id;

	j.denumire =
		(char*)malloc(sizeof(char) *
			(strlen(denumire) + 1));

	strcpy(j.denumire, denumire);

	j.pret = pret;
	j.oreJucate = oreJucate;

	return j;
}

void afisareJoc(Joc j) {

	printf("Id: %d\n", j.id);
	printf("Denumire: %s\n", j.denumire);
	printf("Pret: %.2f\n", j.pret);
	printf("Ore jucate: %d\n", j.oreJucate);
	printf("\n");
}

void inserareLaSfarsit(Nod** cap, Joc j) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = j;
	nou->next = NULL;
	nou->prev = NULL;

	if (*cap == NULL) {
		*cap = nou;
	}
	else {

		Nod* temp = *cap;

		while (temp->next != NULL) {
			temp = temp->next;
		}

		temp->next = nou;
		nou->prev = temp;
	}
}

void inserareLaInceput(Nod** cap, Joc j) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = j;
	nou->prev = NULL;
	nou->next = *cap;

	if (*cap != NULL) {
		(*cap)->prev = nou;
	}

	*cap = nou;
}

void afisareDeLaInceput(Nod* cap) {

	while (cap != NULL) {

		afisareJoc(cap->info);

		cap = cap->next;
	}
}

void afisareDeLaSfarsit(Nod* cap) {

	if (cap == NULL) {
		return;
	}

	Nod* temp = cap;

	while (temp->next != NULL) {
		temp = temp->next;
	}

	while (temp != NULL) {

		afisareJoc(temp->info);

		temp = temp->prev;
	}
}

float calculValoareTotala(Nod* cap) {

	float suma = 0;

	while (cap != NULL) {

		suma += cap->info.pret;

		cap = cap->next;
	}

	return suma;
}

void afisareJocuriScumpe(Nod* cap, float pretMinim) {

	while (cap != NULL) {

		if (cap->info.pret >= pretMinim) {

			afisareJoc(cap->info);
		}

		cap = cap->next;
	}
}

void modificarePret(Nod* cap,
	int id,
	float pretNou) {

	while (cap != NULL) {

		if (cap->info.id == id) {

			cap->info.pret = pretNou;
			return;
		}

		cap = cap->next;
	}
}

void stergereJocDupaId(Nod** cap,
	int id) {

	Nod* temp = *cap;

	while (temp != NULL &&
		temp->info.id != id) {

		temp = temp->next;
	}

	if (temp != NULL) {

		if (temp->prev != NULL) {
			temp->prev->next = temp->next;
		}
		else {
			*cap = temp->next;
		}

		if (temp->next != NULL) {
			temp->next->prev = temp->prev;
		}

		free(temp->info.denumire);
		free(temp);
	}
}

void salvareInFisier(Nod* cap,
	const char* numeFisier) {

	FILE* f = fopen(numeFisier, "w");

	if (f != NULL) {

		while (cap != NULL) {

			fprintf(f,
				"%d %s %.2f %d\n",
				cap->info.id,
				cap->info.denumire,
				cap->info.pret,
				cap->info.oreJucate);

			cap = cap->next;
		}

		fclose(f);
	}
}

void dezalocareLista(Nod** cap) {

	while (*cap != NULL) {

		Nod* temp = *cap;

		*cap = (*cap)->next;

		free(temp->info.denumire);
		free(temp);
	}
}

int main() {

	Nod* lista = NULL;

	Joc j1 =
		initializareJoc(
			1,
			"Minecraft",
			120,
			300
		);

	Joc j2 =
		initializareJoc(
			2,
			"GTA5",
			150,
			500
		);

	Joc j3 =
		initializareJoc(
			3,
			"Cyberpunk",
			200,
			120
		);

	Joc j4 =
		initializareJoc(
			4,
			"Valorant",
			0,
			700
		);

	inserareLaSfarsit(&lista, j1);
	inserareLaSfarsit(&lista, j2);
	inserareLaSfarsit(&lista, j3);

	inserareLaInceput(&lista, j4);

	printf("Afisare de la inceput:\n\n");

	afisareDeLaInceput(lista);

	printf("Afisare de la sfarsit:\n\n");

	afisareDeLaSfarsit(lista);

	printf("Valoarea totala este: %.2f\n\n",
		calculValoareTotala(lista));

	printf("Jocuri cu pret peste 100:\n\n");

	afisareJocuriScumpe(lista, 100);

	printf("Modificare pret pentru jocul cu id 2:\n\n");

	modificarePret(lista, 2, 180);

	afisareDeLaInceput(lista);

	printf("Stergere joc cu id 3:\n\n");

	stergereJocDupaId(&lista, 3);

	afisareDeLaInceput(lista);

	salvareInFisier(
		lista,
		"jocuri.txt"
	);

	dezalocareLista(&lista);

	return 0;
}