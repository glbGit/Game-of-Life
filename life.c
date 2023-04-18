#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LENGTH 50
#define numberOfGenerations 1000
#define numberOfGames 5
#define c 0.02f // chance of mutation
#define T 20000 // latency (micro seconds)

// initialize grid with an R-pentomino
void initialize_board(int **cell) {
	
	int i,j;
	for (i = 0; i < LENGTH; i++) for (j = 0; j < LENGTH; j++) {
		cell[i][j] = 0;
		if (
			   (j==(LENGTH/2-1) && i==(LENGTH/2)) 
			|| (j==(LENGTH/2) && i==(LENGTH/2-1)) 
			|| (j==(LENGTH/2) && i==(LENGTH/2)) 
			|| (j==(LENGTH/2) && i==(LENGTH/2+1)) 
			|| (j==(LENGTH/2+1) && i==(LENGTH/2-1))
		) 
		{
			cell[i][j] = 1;
		}
	
	}
	
}

// print current generation
void print(int **cell) {
	
	int i,j;
	for (i = 0; i < LENGTH; i++) {
		for (j = 0; j < LENGTH; j++) {
			printf("%c ",cell[i][j] ? '@' : ' ');
		}
		printf("\n");
	}

	
}

// print every last generation to file
void print_file(int **cell,FILE *fp) {
	
	int i,j;
	for (i = 0; i < LENGTH; i++) {
		for (j = 0; j < LENGTH; j++) {
			fprintf(fp,"%c ",cell[i][j] ? '@' : ' ');
		}
		fprintf(fp,"\n");
	}
	
	fprintf(fp,"________________________________________________________________________________\n\n");
	
}

// calculate sigma live neighbors of (i*j)-th cell
int neighbors(int i, int j, int **cell) {
	 
	 int sigma = 0;
	 
	 if (i>0 && j>0) 
	 	if (cell[i-1][j-1]) sigma++;
	 if (j>0) 
	 	if (cell[i][j-1]) sigma++;
	 if (j>0 && i<(LENGTH-1)) 
	 	if (cell[i+1][j-1]) sigma++;
	 if (i>0) 
	 	if (cell[i-1][j]) sigma++;
	 if (i<(LENGTH-1)) 
	 	if (cell[i+1][j]) sigma++;
	 if (i>0 && j<LENGTH-1) 
	 	if (cell[i-1][j+1]) sigma++;
	 if (j<(LENGTH-1)) 
	 	if (cell[i][j+1]) sigma++;
	 if (i<(LENGTH-1) && j<(LENGTH-1)) 
	 	if (cell[i+1][j+1]) sigma++;
	 
	 return sigma;

}
	
// game
void play_life(int **cell) {

	int a,i,j, newcell[LENGTH][LENGTH];
	double r;
	
	for (i = 0; i < LENGTH; i++) for(j = 0; j < LENGTH; j++) {
		a = neighbors(i,j,cell);
		r = (double) rand()/RAND_MAX*100.;
		if (a == 2) {
			if (r > c) {
				newcell[i][j] = cell[i][j];
			} else {
				newcell[i][j] = cell[i][j] ? 0 : 1;
			} 
		}
		if (a == 3) { 
			if (r > c) {
				newcell[i][j] = 1;
			} else {
				newcell[i][j] = 0;
			} 
		}
		if (a < 2 || a > 3) {
			if (r > c) {
				newcell[i][j] = 0;
			} else {
				newcell[i][j] = 1;
			} 
		}
	}
	
	for (i = 0; i < LENGTH; i++) for(j = 0; j < LENGTH; j++)
		cell[i][j] = newcell[i][j];
	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

int main(void) {
	
	// 2D grid 
	int **cell, i, k;
	// output stream
	FILE *fp;
	if ((fp = fopen("life.dat", "w+")) == NULL) {
		printf("Errore durante l'apertura del file Life.dat\n");
		exit(EXIT_FAILURE);
	}
	// dynamic memory alloc
	cell = (int **) malloc(LENGTH * sizeof(int*));
	for (i = 0;i < LENGTH; i++) 
		cell[i] = (int *) malloc(LENGTH * sizeof(int));
	
	for (k = 0; k < numberOfGames; k++) {	 
		initialize_board(cell);
		
		// play numberOfGenerations games
		for (i = 0; i < numberOfGenerations; i++) {
			system("clear");
			print(cell);
			play_life(cell);
			printf("\n");
			// print last configuration to file
			if (i == numberOfGenerations-1) print_file(cell,fp);
			usleep(T);
		}
	}
	// free memory
	for(i = 0; i < LENGTH; i++)
		free(cell[i]);
	free(cell);
	
	return 0;
	
}




