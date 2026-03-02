#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Student Student;

struct Student {
	int id;
	char* nume;
	float medie;
};

// initializare student
Student initializare(int id, const char* nume, float medie) {

	Student s;

	s.id = id;

	s.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(s.nume, nume);

	s.medie = medie;

	return s;
}

// afisare student
void afisareStudent(Student s) {

	printf("Id: %d | Nume: %s | Medie: %.2f\n",
		s.id, s.nume, s.medie);
}

// afisare matrice de studenti
void afisareMatrice(Student** matrice, int nrLinii, int nrColoane) {

	for (int i = 0; i < nrLinii; i++) {

		printf("\nGrupa %d:\n", i + 1);

		for (int j = 0; j < nrColoane; j++) {

			afisareStudent(matrice[i][j]);
		}
	}
}

// calcul medie pe o linie
float calculMedieGrupa(Student** matrice, int linie, int nrColoane) {

	float suma = 0;

	for (int j = 0; j < nrColoane; j++) {

		suma += matrice[linie][j].medie;
	}

	return suma / nrColoane;
}

// calcul medie generala
float calculMedieGenerala(Student** matrice, int nrLinii, int nrColoane) {

	float suma = 0;
	int nrStudenti = nrLinii * nrColoane;

	for (int i = 0; i < nrLinii; i++) {

		for (int j = 0; j < nrColoane; j++) {

			suma += matrice[i][j].medie;
		}
	}

	return suma / nrStudenti;
}

// cautare student dupa id
Student cautareStudentDupaId(Student** matrice, int nrLinii, int nrColoane, int id) {

	for (int i = 0; i < nrLinii; i++) {

		for (int j = 0; j < nrColoane; j++) {

			if (matrice[i][j].id == id) {

				return matrice[i][j];
			}
		}
	}

	return initializare(-1, "Necunoscut", 0);
}

// copiere studenti cu media peste o valoare data
Student* copiazaStudentiCuMedieMare(Student** matrice,
	int nrLinii,
	int nrColoane,
	float limita,
	int* nrStudentiCopiati) {

	*nrStudentiCopiati = 0;

	for (int i = 0; i < nrLinii; i++) {

		for (int j = 0; j < nrColoane; j++) {

			if (matrice[i][j].medie >= limita) {

				(*nrStudentiCopiati)++;
			}
		}
	}

	Student* vector =
		(Student*)malloc(sizeof(Student) * (*nrStudentiCopiati));

	int k = 0;

	for (int i = 0; i < nrLinii; i++) {

		for (int j = 0; j < nrColoane; j++) {

			if (matrice[i][j].medie >= limita) {

				vector[k] = initializare(
					matrice[i][j].id,
					matrice[i][j].nume,
					matrice[i][j].medie
				);

				k++;
			}
		}
	}

	return vector;
}

// afisare vector de studenti
void afisareVector(Student* vector, int nrElemente) {

	for (int i = 0; i < nrElemente; i++) {

		afisareStudent(vector[i]);
	}
}

// dezalocare vector studenti
void dezalocareVector(Student** vector, int* nrElemente) {

	for (int i = 0; i < *nrElemente; i++) {

		free((*vector)[i].nume);
	}

	free(*vector);

	*vector = NULL;
	*nrElemente = 0;
}

// dezalocare matrice
void dezalocareMatrice(Student*** matrice, int* nrLinii, int* nrColoane) {

	for (int i = 0; i < *nrLinii; i++) {

		for (int j = 0; j < *nrColoane; j++) {

			free((*matrice)[i][j].nume);
		}

		free((*matrice)[i]);
	}

	free(*matrice);

	*matrice = NULL;
	*nrLinii = 0;
	*nrColoane = 0;
}

int main() {

	int nrLinii = 2;
	int nrColoane = 3;

	Student** matrice =
		(Student**)malloc(sizeof(Student*) * nrLinii);

	for (int i = 0; i < nrLinii; i++) {

		matrice[i] =
			(Student*)malloc(sizeof(Student) * nrColoane);
	}

	matrice[0][0] = initializare(1, "Ana", 9.50f);
	matrice[0][1] = initializare(2, "Maria", 8.75f);
	matrice[0][2] = initializare(3, "Ioana", 7.20f);

	matrice[1][0] = initializare(4, "Andrei", 6.80f);
	matrice[1][1] = initializare(5, "Mihai", 9.10f);
	matrice[1][2] = initializare(6, "Elena", 10.00f);

	printf("Matricea initiala de studenti:\n");
	afisareMatrice(matrice, nrLinii, nrColoane);

	printf("\nMedia grupei 1 este: %.2f\n",
		calculMedieGrupa(matrice, 0, nrColoane));

	printf("Media grupei 2 este: %.2f\n",
		calculMedieGrupa(matrice, 1, nrColoane));

	printf("\nMedia generala este: %.2f\n",
		calculMedieGenerala(matrice, nrLinii, nrColoane));

	int idCautat = 5;

	printf("\nStudentul cautat dupa id %d este:\n", idCautat);

	Student studentCautat =
		cautareStudentDupaId(matrice, nrLinii, nrColoane, idCautat);

	afisareStudent(studentCautat);

	int nrStudentiCopiati = 0;

	Student* studentiBuni =
		copiazaStudentiCuMedieMare(
			matrice,
			nrLinii,
			nrColoane,
			8.50f,
			&nrStudentiCopiati
		);

	printf("\nStudentii cu media cel putin 8.50 sunt:\n");

	afisareVector(studentiBuni, nrStudentiCopiati);

	dezalocareVector(&studentiBuni, &nrStudentiCopiati);

	dezalocareMatrice(&matrice, &nrLinii, &nrColoane);

	return 0;
}