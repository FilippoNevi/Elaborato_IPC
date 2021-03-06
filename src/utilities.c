#include "utilities.h"

int ** creaMatrice(int ordine) {
	int **matrice, i;

	matrice = calloc(ordine, sizeof(int *));

	for(i = 0; i < ordine; i++)
		matrice[i] = calloc(ordine, sizeof(int));

	return matrice;
}

void leggiMatrice(int fileMatrice, int ** matrice, int ordine) {

char * buff;					// Buffer su cui salvare il contenuto di ogni riga
int n;							// Numero di byte letti dalla funzione leggiRiga
int i = 0, j = 0, k, x = 0;
char * temp;					// Array temporaneo su cui salvo ogni numero che leggo

	if((buff = malloc(DIM_BUFF * sizeof(char))) == NULL) {
		segnala("Errore: impossibile allocare buffer durante la lettura di una matrice.\n\n");
		exit(1);
	}
	if((temp = malloc(DIM_BUFF * sizeof(char))) == NULL) {
		segnala("Errore: impossibile allocare stringa temporanea durante la lettura di una matrice.\n\n");
	}

	while((n = leggiRiga(fileMatrice, buff)) > 0) {

		buff[n] = '\0';

		printf("\n\nHO APPENA LETTO LA RIGA: %s", buff);

		printf("\n\nSTAMPO BUFF: ");

		for(k = 0; k < strlen(buff) && (buff[k] != '\0'); k++) {
			printf("%d ", buff[k]);
		}

		printf("\n");


		for(k = 0; k < strlen(buff) && (buff[k] != '\0'); k++) {

			if((buff[k] != ' ') && (buff[k] != '\n')) {
				temp[x] = buff[k];
				x++;
				printf("\n\nSONO IN IF\n\n");
			}
			else {
				temp[x] = '\0';
				x = 0;
				matrice[i][j] = atoi(temp);

				printf("\n\nSTAMPA RIGA %d E COLONNA %d: %d\n\n", i, j, matrice[i][j]);

				if(j == ordine - 1) {	// Se sono arrivato a fine riga passo alla successiva
					i++;
					j = 0;
				}
				else {					// Altrimenti vado alla prossima colonna della riga
					j++;
				}
			}
		}
	}

	free(buff);
	free(temp);
}

int leggiRiga(int fileMatrice, char * buff) {
char carattere;											// Carattere su cui salvo ogni byte che leggo dal file
int dim, dimTot = 0;
int i = 0;
	
	if((dim = read(fileMatrice, &carattere, 1)) > 0) {	// Leggo un byte alla volta
		if((carattere == EOF) || (carattere == '\n')){
			return dimTot;
		}
		else {		
			while((carattere != '\n') && (carattere != EOF) && (dim > 0)) {
				buff[i] = carattere;
				i++;
				dim = read(fileMatrice, &carattere, 1);
				dimTot++;
			}

			return dimTot;
		}
	}
	else {
		return dimTot;
	}
}

void segnala(char * bufferOutput) {
	write(STDOUT, bufferOutput, strlen(bufferOutput));
}

void caricaMatrice(int ** matrice, int * matriceCond, int ordine) {
int i, j;

	for(i = 0; i < ordine; i++)
		for(j = 0; j < ordine; j++) {
			matriceCond[(i * ordine) + j] = matrice[i][j];
		}

}

void creaComando(char * buff, int comando, int riga, int colonna, int ordine) {

	if(comando == MOLTIPLICA) {
		sprintf(buff, "%d %d %d %d", comando, riga, colonna, ordine);
	}
	else if(comando == SOMMA) {
		sprintf(buff, "%d %d %d", comando, riga, ordine);
	}
	else if(comando == ESCI) {
		sprintf(buff, "%d", comando);
	}

}

void freeMatrice(int ** matrice, int ordine) {
int i;

	for(i = 0; i < ordine; i++) {
		free(matrice[i]);
	}

	free(matrice);
}