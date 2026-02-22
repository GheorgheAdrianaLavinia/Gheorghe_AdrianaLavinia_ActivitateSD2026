#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Student Student;

struct Student {

	int id;
	char* nume;
	float medie;
};

// Functie pentru initializarea unui student
Student initializare(int id, const char* nume, float medie) {

	Student s;

	s.id = id;

	s.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(s.nume, nume);

	s.medie = medie;

	return s;
}

// Functie pentru afisarea unui student
void afisareStudent(Student s) {

	printf("Id: %d\n", s.id);
	printf("Nume: %s\n", s.nume);
	printf("Medie: %.2f\n", s.medie);
	printf("\n");
}

// Functie pentru afisarea vectorului de studenti
void afisareVector(Student* vector, int nrElemente) {

	for (int i = 0; i < nrElemente; i++) {

		afisareStudent(vector[i]);
	}
}

// Functie pentru calcularea mediei generale
float calculMedieGenerala(Student* vector, int nrElemente) {

	float suma = 0;

	for (int i = 0; i < nrElemente; i++) {

		suma += vector[i].medie;
	}

	return suma / nrElemente;
}

// Functie pentru copierea studentilor cu media mai mare decat 8
Student* copiazaStudentiIntegrali(Student* vector,
	int nrElemente,
	int* nrStudentiCopiati) {

	*nrStudentiCopiati = 0;

	for (int i = 0; i < nrElemente; i++) {

		if (vector[i].medie >= 8) {
			(*nrStudentiCopiati)++;
		}
	}

	Student* vectorNou =
		(Student*)malloc(sizeof(Student) * (*nrStudentiCopiati));

	int k = 0;

	for (int i = 0; i < nrElemente; i++) {

		if (vector[i].medie >= 8) {

			vectorNou[k] =
				initializare(
					vector[i].id,
					vector[i].nume,
					vector[i].medie
				);

			k++;
		}
	}

	return vectorNou;
}

// Functie pentru dezalocarea memoriei
void dezalocare(Student** vector, int* nrElemente) {

	for (int i = 0; i < *nrElemente; i++) {

		free((*vector)[i].nume);
	}

	free(*vector);

	*vector = NULL;
	*nrElemente = 0;
}

int main() {

	int nrStudenti = 3;

	Student* vector =
		(Student*)malloc(sizeof(Student) * nrStudenti);

	vector[0] =
		initializare(
			1,
			"Andrei",
			9.50f
		);

	vector[1] =
		initializare(
			2,
			"Maria",
			7.25f
		);

	vector[2] =
		initializare(
			3,
			"Elena",
			8.75f
		);

	printf("Vectorul initial este:\n\n");

	afisareVector(vector, nrStudenti);

	float medieGenerala =
		calculMedieGenerala(vector, nrStudenti);

	printf("Media generala este: %.2f\n\n",
		medieGenerala);

	int nrStudentiIntegrali = 0;

	Student* studentiIntegrali =
		copiazaStudentiIntegrali(
			vector,
			nrStudenti,
			&nrStudentiIntegrali
		);

	printf("Studentii cu media peste 8 sunt:\n\n");

	afisareVector(
		studentiIntegrali,
		nrStudentiIntegrali
	);

	dezalocare(&vector, &nrStudenti);

	dezalocare(
		&studentiIntegrali,
		&nrStudentiIntegrali
	);

	return 0;
}