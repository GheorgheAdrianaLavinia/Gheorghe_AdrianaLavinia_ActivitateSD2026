#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Student Student;
typedef struct Nod Nod;

struct Student {
	int id;
	char* nume;
	float medie;
	int an;
};

struct Nod {
	Student info;
	Nod* next;
};

Student initializareStudent(int id, const char* nume, float medie, int an) {
	Student s;

	s.id = id;
	s.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(s.nume, nume);
	s.medie = medie;
	s.an = an;

	return s;
}

void afisareStudent(Student s) {
	printf("Id: %d | Nume: %s | Medie: %.2f | An: %d\n",
		s.id, s.nume, s.medie, s.an);
}

void inserareLaInceput(Nod** cap, Student s) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = s;
	nou->next = *cap;

	*cap = nou;
}

void inserareLaSfarsit(Nod** cap, Student s) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = s;
	nou->next = NULL;

	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		Nod* temp = *cap;

		while (temp->next != NULL) {
			temp = temp->next;
		}

		temp->next = nou;
	}
}

void afisareLista(Nod* cap) {
	while (cap != NULL) {
		afisareStudent(cap->info);
		cap = cap->next;
	}
}

int numaraStudenti(Nod* cap) {
	int nr = 0;

	while (cap != NULL) {
		nr++;
		cap = cap->next;
	}

	return nr;
}

float calculMedieGenerala(Nod* cap) {
	float suma = 0;
	int nr = 0;

	while (cap != NULL) {
		suma = suma + cap->info.medie;
		nr++;

		cap = cap->next;
	}

	if (nr == 0) {
		return 0;
	}

	return suma / nr;
}

Student cautareStudentDupaId(Nod* cap, int id) {
	while (cap != NULL) {
		if (cap->info.id == id) {
			return cap->info;
		}

		cap = cap->next;
	}

	return initializareStudent(0, "Necunoscut", 0, 0);
}

void afisareStudentiCuMediaPeste(Nod* cap, float medieMinima) {
	while (cap != NULL) {
		if (cap->info.medie >= medieMinima) {
			afisareStudent(cap->info);
		}

		cap = cap->next;
	}
}

void modificareMedieDupaId(Nod* cap, int id, float medieNoua) {
	while (cap != NULL) {
		if (cap->info.id == id) {
			cap->info.medie = medieNoua;
			return;
		}

		cap = cap->next;
	}
}

void stergereStudentDupaId(Nod** cap, int id) {
	if (*cap == NULL) {
		return;
	}

	if ((*cap)->info.id == id) {
		Nod* temp = *cap;
		*cap = (*cap)->next;

		free(temp->info.nume);
		free(temp);

		return;
	}

	Nod* temp = *cap;

	while (temp->next != NULL && temp->next->info.id != id) {
		temp = temp->next;
	}

	if (temp->next != NULL) {
		Nod* nodSters = temp->next;
		temp->next = nodSters->next;

		free(nodSters->info.nume);
		free(nodSters);
	}
}

void salvareInFisierText(Nod* cap, const char* numeFisier) {
	FILE* f = fopen(numeFisier, "w");

	if (f != NULL) {
		while (cap != NULL) {
			fprintf(f, "%d %s %.2f %d\n",
				cap->info.id,
				cap->info.nume,
				cap->info.medie,
				cap->info.an);

			cap = cap->next;
		}

		fclose(f);
	}
	else {
		printf("Fisierul nu s-a putut deschide.\n");
	}
}

Nod* citireDinFisierText(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");

	Nod* cap = NULL;

	if (f != NULL) {
		int id;
		char nume[50];
		float medie;
		int an;

		while (fscanf(f, "%d %s %f %d", &id, nume, &medie, &an) == 4) {
			Student s = initializareStudent(id, nume, medie, an);
			inserareLaSfarsit(&cap, s);
		}

		fclose(f);
	}
	else {
		printf("Fisierul nu exista sau nu poate fi citit.\n");
	}

	return cap;
}

void raportStudentiAn(Nod* cap, int anCautat, const char* numeFisier) {
	FILE* f = fopen(numeFisier, "w");

	if (f != NULL) {
		while (cap != NULL) {
			if (cap->info.an == anCautat) {
				fprintf(f, "%d %s %.2f %d\n",
					cap->info.id,
					cap->info.nume,
					cap->info.medie,
					cap->info.an);
			}

			cap = cap->next;
		}

		fclose(f);
	}
}

void dezalocareLista(Nod** cap) {
	while (*cap != NULL) {
		Nod* temp = *cap;

		*cap = (*cap)->next;

		free(temp->info.nume);
		free(temp);
	}
}

int main() {
	Nod* lista = NULL;

	Student s1 = initializareStudent(1, "Andrei", 9.50f, 2);
	Student s2 = initializareStudent(2, "Maria", 8.25f, 1);
	Student s3 = initializareStudent(3, "Elena", 7.80f, 2);
	Student s4 = initializareStudent(4, "Ioana", 9.80f, 3);
	Student s5 = initializareStudent(5, "Vlad", 6.90f, 1);

	inserareLaSfarsit(&lista, s1);
	inserareLaSfarsit(&lista, s2);
	inserareLaSfarsit(&lista, s3);
	inserareLaSfarsit(&lista, s4);
	inserareLaSfarsit(&lista, s5);

	printf("Lista initiala:\n");
	afisareLista(lista);

	printf("\nNumar studenti: %d\n", numaraStudenti(lista));

	printf("Media generala: %.2f\n", calculMedieGenerala(lista));

	printf("\nStudentii cu media peste 8:\n");
	afisareStudentiCuMediaPeste(lista, 8);

	printf("\nCautare student cu id 3:\n");
	Student cautat = cautareStudentDupaId(lista, 3);
	afisareStudent(cautat);

	printf("\nModificare medie pentru studentul cu id 5:\n");
	modificareMedieDupaId(lista, 5, 7.50f);
	afisareLista(lista);

	printf("\nStergere student cu id 2:\n");
	stergereStudentDupaId(&lista, 2);
	afisareLista(lista);

	salvareInFisierText(lista, "studenti.txt");

	raportStudentiAn(lista, 2, "raport_an_2.txt");

	dezalocareLista(&lista);

	printf("\nLista citita din fisier:\n");

	Nod* listaCitita = citireDinFisierText("studenti.txt");
	afisareLista(listaCitita);

	dezalocareLista(&listaCitita);

	return 0;
}