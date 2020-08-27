/***************************************************************************** 
* Author: Patrycja Bachleda 
* Program: memory.c 
* Description: Recreate a memory card game using command line
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h> 
#include<time.h>

void print_board(int board_size, char in_board[][board_size]);
void fill_board(int board_size, char in_board[][board_size]);
void compare(int board_size, char in_board[][board_size], char in_board2[][board_size], int *points_p);


int main(void){
	char choice, board1[4][4], board2[4][4]; 
	int points =0, row1, row2, col1, col2, flip =0;

	//Initialize the shown board to all "$"
	for(int row = 0; row<4; row++){
		for(int col = 0; col<4; col++){
			board2[row][col] = '$';
		}
	}

	//Prompts
	printf("Welcome to Memory! Read Player One... \n\n");
	fill_board(4, board1);

	printf("Here's the board: \n");
	print_board(4, board2);

	printf("\nChoose an option: \n");
	printf("(F) Find a match\n(Q) Quit \nChoice: ");
	scanf(" %c", &choice);

//Checking the choices until the user wants to quit
while(1==1){
	if(choice == 'F' || choice == 'f'){
		compare(4, board1, board2, &points);

		if(points == 8){
			printf("\nYou win!\n");
			break;
		}

		printf("\nChoose an option: \n");
		printf("(F) Find a match\n(Q) Quit \nChoice: ");
		scanf(" %c", &choice);
	}

	else if(choice == 'Q' || choice == 'q'){
		break;
	}

	else{
		printf("Incorrect input: try again!");
		printf("\nChoose an option: \n");
		printf("(F) Find a match\n(Q) Quit \nChoice: ");
		scanf(" %c", &choice);
	}
}

printf("Your total points: %d. Goodbye!", points);

	return 0; 
}

void compare(int board_size, char in_board1[][board_size], char in_board2[][board_size], int *points_p){
	int row1, row2, col1, col2;

	printf("Pick first card (row, column): ");
	scanf("%d,%d", &row1, &col1);
	printf("Pick second card (row, column): ");
	scanf("%d,%d", &row2, &col2);

//If all requirements are met then assign the flipped cards to the shown grid. Depeding on if the cards match or not reset the grid for next round
//Check if the entered positions are within the grid
	if((row1 < 4 && row1>-1) && (col1 < 4 && col1>-1) && (row2 < 4 && row2>-1) && (col2 < 4 && col2>-1)){
		//Check if the entered positions are the same place
		if(row1 == row2 && col1 == col2){
			printf("\nSame position: enter two different card positions!\n");
			print_board(4, in_board2);
		}

		//If they aren't the same make sure the card wasn't already flipped over
		else if(in_board2[row1][col1] == '$'  && in_board2[row2][col2] == '$'){
			//Code for if the cards match
			if(in_board1[row1][col1] == in_board1[row2][col2]){
				*points_p = *points_p + 1;
				printf("\nCards match! You get a point!\n");
				printf("Your current points: %d\n", *points_p);
				in_board2[row1][col1] = in_board1[row1][col1];
				in_board2[row2][col2] = in_board1[row2][col2];

				printf("\nHere's the board: \n\n");
				print_board(4, in_board2);
			}
			//Code for if the cards don't match
			else {
				printf("\nCards do not match! Try again!\n");
				in_board2[row1][col1] = in_board1[row1][col1];
				in_board2[row2][col2] = in_board1[row2][col2];
				
				printf("\nHere's the board: \n\n");
				print_board(4, in_board2);

				in_board2[row1][col1] = '$';
				in_board2[row2][col2] = '$';
			}
		}
		//If it is flipped
		else{
			printf("\nYou already flipped one of these cards: try again!\n");
			printf("\nHere's the board: \n\n");
			print_board(4, in_board2);
		}
	}

	//If positions are not on grid
	else{
		printf("\nPositions entered not on grid: Enter values between 0-3\n");
	}
	
}

void print_board(int board_size, char in_board[][board_size]){
	printf("    0   1   2   3");
	for(int row = 0; row<board_size; row++){
		printf("\n%d", row);
		for(int col = 0; col<board_size; col++){
			printf(" | %c", in_board[row][col]);
		}
		printf("\n------------------");
	}
}

void fill_board(int board_size, char in_board[][board_size]){
	int count[8] = {0, 0, 0, 0, 0, 0, 0, 0}, rand_alp[26], letters[8], final[26], playing[16];

	//initializes an array 0-25 (to represent the alphabet)
    for (int i = 0; i < 26; i++) {
    	final[i] = i;
    } 

    //Mix the "alphabet" represented by 0-25 up
	srand((unsigned) time(NULL));
	int i, k, t;
	
	for (i = 0; i < 26; i++) {
		k = i + rand() / (RAND_MAX / (26 - i) + 1);
	    t = final[k];
	    final[k] = final[i];
	    final[i] = t;
	}

	//Take the first 8 randomized letters and add 65 to them so they are ASCII values
	for(int i = 0; i<8; i++){
		letters[i]=final[i]+65;
	}

	//Put the random characters into an array twice {0-8} {0-8}
	for(int k = 0; k<8; k++){
		playing[k] = letters[k];
	}

	for(int i = 0; i<8; i++){
		playing[i+8] = letters[i];
	}

	//Again mix those letters up
	for (i = 0; i < 16; i++) {
		k = i + rand() / (RAND_MAX / (16 - i) + 1);
	    t = playing[k];
	    playing[k] = playing[i];
	    playing[i] = t;
	}

	//Assign the randomlized 1D array to a 2D array
	int num = -1;
	for(int row = 0; row<4; row++){
		for(int col = 0; col<4; col++){
			num++;
			in_board[row][col] = playing[num];
		}
	}

}
