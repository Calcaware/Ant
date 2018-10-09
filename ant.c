#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


int run(unsigned long dims, unsigned long iterations, unsigned int randomize) {
	unsigned long counter = 0;
	unsigned int board[dims][dims];
	unsigned long x = 0;
	unsigned long y = 0;
	unsigned int random = 0;
	unsigned int direction = 0; // 0 = Up, 1 = Right, 2 = Down, 3 = Left
	
	while (y != dims) { // Initialize Board
		x = 0;
		while (x != dims) {
			if (randomize == 0) { board[x][y] = '0'; } else { random = rand() % 100; if (random == 0) { board[x][y] = '1'; } else { board[x][y] = '0'; } }
			x++;
		}
		y++;
	}
	
	// Start from Center-ish
	x = dims/2;
	y = dims/2;
	while ((x != dims) && (y != dims) && (counter != iterations)) {
	
		if (board[x][y] == '0') { // Turn Right
			board[x][y] = '1';
			if (direction < 3) { direction++; } else { direction = 0; }
			if (direction == 0) { y--; } else if (direction == 1) { x++; } else if (direction == 2) { y++; } else if (direction == 3) { x--; }
		}
		
		else if (board[x][y] == '1') { // Turn Left
			board[x][y] = '0';
			if (direction > 0) { direction--; } else { direction = 3; }
			if (direction == 0) { y--; } else if (direction == 1) { x++; } else if (direction == 2) { y++; } else if (direction == 3) { x--; }
		}
		
		counter++;
	}
	
	
	// OUTPUT THE IMAGE
	printf("P1 %d %d\n",dims,dims);
	y = 0; while (y != dims) { x = 0; while (x != dims) { printf("%c",board[x][y]); x++; } printf("\n"); y++; }
	
	return 0;
}



int usage() {
	printf("Usage: ant [dimensions (Int)] [iterations (Int)] [randomize (Bool)] [seed (Int)]\n");
	return 1;
}


int main (int argc, char* args[]) {
	if (argc < 4) { return usage(); }
	unsigned long dims = atoi(args[1]);
	if ((dims > 1024) || (dims < 32)) {
		printf("Error: Dimensions must be between 32 and 1024 (Inclusive).\n");
		return 1;
	}
	unsigned long iterations = atoi(args[2]);
	if ((iterations > 1000000000) || (iterations < 1)) {
		printf("Error: Iterations must be between 1 and 1000000000 (Inclusive).\n");
		return 1;
	}
	unsigned int randomize = 0;
	if (strcmp(args[3],"true") == 0) { randomize = 1; }
	else if (strcmp(args[3],"false") == 0) { randomize = 0; }
	else { return usage(); }
	
	unsigned int seed = 0;
	if (args[4] != NULL) { srand(atoi(args[4])); } else { srand(time(NULL)); }
	
	run(dims, iterations, randomize);
	return 0;
}

