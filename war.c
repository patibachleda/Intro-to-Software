/*
* Author: Patrycja Bachleda, pbachleda2019@my.fit.edu
* Course: CSE 1001, Section 04 Fall 2019
* Filename: war.c
* Description: Simulates a war card game
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h> 

//Function protocols;
void create_deck(int in_deck_p[]);
void shuffle(int in_deck_p[], int n);
void deal_hand(int in_deck_p[], int hand1_p[], int hand2_p[]);
void assign_suit(int hand_p[], char *suit_p);
void assign_number(int hand_p[], int *value_p);
void find_round_winner(int *value1_p, int *value2_p, int *winner_p, int hand1_p[], int hand2_p[], char *suit1_p, char *suit2_p);
void new_hand(int winner_p[], int loser_p[], int count);
int check_hand(int hand_size, int const hand[]);
void war(int *value1_p, int *value2_p, int *winner_p, int hand1_p[], int hand2_p[], char suit1, char suit2);
void print_cards(int value_p, char suit, int player);

int main(void){
	//Declaration of all variables used:
	int in_deck[52], hand1[52], hand2[52];
	char suit1, suit2, play;
	int value1, value2, winner, hand1_size, hand2_size;

	//Beginning prompts and set ups of game
	printf("Welcome to War!\n");
	create_deck(in_deck);
	printf("Shuffling deck...\n");
	shuffle(in_deck, 52);
	printf("Dealing cards...\n\n");
	deal_hand(in_deck, hand1, hand2);
	printf("Would you like to play (p) or exit (e): ");
	scanf(" %c", &play);
	printf("\n");

	//infinite loop to check what input user gave to play or exit. Loop is broken if 'e'.
	while(1==1){
		if(play == 'p'){
				hand1_size = check_hand(52, hand1);
				hand2_size = check_hand(52, hand2);

				if(hand1_size != 0 && hand2_size!=0){
					find_round_winner(&value1, &value2, &winner, hand1, hand2, &suit1, &suit2);
					printf("\nPlayer %d wins the round! Awarding played cards to Player %d\n\n", winner, winner);
					printf("Would you like to play (p) or exit (e): ");
					scanf(" %c", &play);
					printf("\n");
				}

				else if(hand1_size==0){
					printf("Player 1 has all the cards and wins the game!\n");
					break;
				}

				else if(hand2_size==0){
					printf("Player 2 has all the cards and wins the game!\n");
					break;
				}
		}

		//if player wants to exit see who has more cards
		else if(play == 'e'){
			hand1_size = check_hand(52, hand1);
			hand2_size = check_hand(52, hand2);

			if(hand1_size>hand2_size){
				printf("Player 1 wins the game!\n");
			}
			else if(hand1_size<hand2_size){
				printf("Player 2 wins the game!\n");
			}
			else{
				printf("This game is a tie!\n");
			}
			break;
		}

		//If they don't type in e or p prompt them again
		else{
			printf("Incorrect input\n");
			printf("Would you like to play (p) or exit (e): ");
			scanf(" %c", &play);
			printf("\n");
		}	
	}
	printf("Goodbye! Thanks for playing War!");
	return 0;
}


void print_cards(int value, char suit, int player){
	if(value<=10){
		printf("Player %d's card: %d%c \n", player, value, suit); 
	}

	else if(value == 20){
		printf("Player %d's card: %c%c \n", player, 'J', suit); 
	}

	else if(value == 30){
		printf("Player %d's card: %c%c \n", player, 'Q', suit); 
	}

	else if(value == 40){
		printf("Player %d's card: %c%c \n", player, 'K', suit); 
	}

	else if(value == 50){
		printf("Player %d's card: %c%c \n", player, 'A', suit); 
	}
}

//compares the values assigned to see which is greater and then gives the winner winning cards (if war then same concept with extra steps)
void find_round_winner(int *value1_p, int *value2_p, int *winner_p, int hand1_p[], int hand2_p[], char *suit1_p, char *suit2_p){
	assign_suit(hand1_p, suit1_p);
	assign_suit(hand2_p, suit2_p);
	assign_number(hand1_p, value1_p);
	assign_number(hand2_p, value2_p);

	print_cards(*value1_p, *suit1_p, 1);
	print_cards(*value2_p, *suit2_p, 2);
	

	if(*value1_p>*value2_p){
		new_hand(hand1_p, hand2_p, 1);
		*winner_p = 1;
	}
	else if(*value1_p<*value2_p){
		new_hand(hand2_p, hand1_p, 1);
		*winner_p = 2;
	}
	else if(*value1_p==*value2_p){
		int hand1_size = check_hand(52, hand1_p);
		int hand2_size = check_hand(52, hand2_p);

		if(hand1_size>=5 && hand2_size>=5){
				
				int temp1 = hand1_p[0];
				int temp2 = hand2_p[0];
				hand1_p[0]= hand1_p[4];
				hand2_p[0]= hand2_p[4];

				assign_suit(hand1_p, suit1_p);
				assign_suit(hand2_p, suit2_p);
				assign_number(hand1_p, value1_p);
				assign_number(hand2_p, value2_p);
				war(value1_p, value2_p, winner_p, hand1_p, hand2_p, *suit1_p, *suit2_p);
				
				print_cards(*value1_p, *suit1_p, 1);
				print_cards(*value2_p, *suit2_p, 2);

				hand1_p[0]= temp1;
				hand2_p[0]= temp2;
				if (*winner_p==1){
					new_hand(hand1_p, hand2_p, 1);
				}
				else if (*winner_p==2){
					new_hand(hand2_p, hand1_p, 1);
				}
		}

		else if (hand1_size<5){
			printf("\nThe cards match! It's a battle!\n");
			printf("Drawing three cards from each player for battle...\n\n");
			printf("Player 1 does not have enough cards for war!\n");
			*winner_p = 2;
			for(int i = 0; i<52; i++){
				hand1_p[i]=100;
			}
		}
		else{
			printf("\nThe cards match! It's a battle!\n");
			printf("Drawing three cards from each player for battle...\n\n");
			printf("Player 2 does not have enough cards for war!\n");
			*winner_p = 1;
			for(int i = 0; i<52; i++){
				hand2_p[i]=100;
			}
		}
	}
}

//If players cards match then take the value of first element (which was temporarily made the fifth element for W A R WAR cards) and see who wins
//If the values match again then repeat
void war(int *value1_p, int *value2_p, int *winner_p, int hand1_p[], int hand2_p[], char suit1, char suit2){
	printf("\nThe cards match! It's a battle!\n");
	printf("Drawing three cards from each player for battle...\n\n");

		if(*value1_p>*value2_p){
			*winner_p = 1;
			new_hand(hand1_p, hand2_p, 4);
		}
		else if(*value1_p<*value2_p){
			*winner_p = 2;
			new_hand(hand2_p, hand1_p, 4);
		}
		else{
			int temp1 = hand1_p[0];
			int temp2 = hand2_p[0];
			hand1_p[0]= hand1_p[4];
			hand2_p[0]= hand2_p[4];
			assign_number(hand1_p, value1_p);
			assign_number(hand2_p, value2_p);
			find_round_winner(value1_p, value2_p, winner_p, hand1_p, hand2_p, &suit1, &suit2);
			hand1_p[0]= temp1;
			hand2_p[0]= temp2;
			if (*winner_p==1){
				new_hand(hand1_p, hand2_p, 1);
			}
			else if (*winner_p==2){
				new_hand(hand2_p, hand1_p, 1);
			}
		}
}

//MUST HAVE checks how many cards are in the players deck
int check_hand(int hand_size, int const hand[]){
	int count = 0;
	for(int i = 0; i<52; i++){
		if(hand[i]!=100){
			count++;
		}
	}
	return count;
}

//Moves the cards in the array up one and puts the losers and winners played cards to the winner. Repeats either 1 or 4 times depeding on war
void new_hand(int winner_p[], int loser_p[], int count){
		int lastElement1, Lmoving_variable, Wmoving_variable;

		for(int k = 0; k<count; k++){
			Lmoving_variable = loser_p[0];
			Wmoving_variable = winner_p[0];
				for(int i = 0; i<52; i++){
					if(loser_p[i]<52 && loser_p[i]>=0){
						loser_p[i] = loser_p[i+1];
					}

					if(winner_p[i]<52 && winner_p[i]>=0){
						winner_p[i] = winner_p[i+1];
						lastElement1 = i;
					}
				}
			winner_p[lastElement1] = Lmoving_variable;
			winner_p[lastElement1+1] = Wmoving_variable;	
			loser_p[51] = 100;
			winner_p[51] = 100;
		}
}

//Takes the first number in array and assigns it a card value. Jack = 20. Queen = 30. Kind = 40. Ace = 50.
void assign_number(int hand_p[], int *value_p){
	if(hand_p[0]%13>=0 && hand_p[0]%13<=8){
		*value_p = hand_p[0]%13+2;
	}
	else if(hand_p[0]%13 == 9){
		*value_p = 20;
	}
	else if(hand_p[0]%13 == 10){
		*value_p = 30;
	}
	else if(hand_p[0]%13 == 11){
		*value_p = 40;
	}
	else if (hand_p[0]%13 == 12){
		*value_p = 50;
	}
}

//Assigns a suit to the first value in each array for display purposes
void assign_suit(int hand_p[], char *suit_p){
	if(hand_p[0]<=12){
		*suit_p = 'S';
	}
	else if(hand_p[0]>12 && hand_p[0]<=25){
		*suit_p = 'D';
	}
	else if(hand_p[0]>25 && hand_p[0]<=38){
		*suit_p = 'H';
	}
	else if(hand_p[0]>38 && hand_p[0]<=51){
		*suit_p = 'C';
	}
}

//Takes the array of 52 randomly shuffled elements and splits them into two decks 
void deal_hand(int in_deck_p[], int hand1_p[], int hand2_p[]){
 	for (int i = 0; i<52; i++){
 		if(i<26){
 			hand1_p[i] = in_deck_p[i];
 		}	
 		else{
 			hand1_p[i] = 100;
 		}
 	}

	int k = 26;
 	for (int i = 0; i<52; i++){
 		if(i<26){
 			hand2_p[i] = in_deck_p[k];
 			k++;
 		}	
 		else{
 			hand2_p[i] = 100;
 		}
 	}
}

//Creates a deck of 52 cards
void create_deck(int in_deck_p[]){
	for (int i = 0; i < 52; i++){
		in_deck_p[i]=i;
	}
}

//Shuffles the deck of 52 cards (GIVEN BY DR CRAWFORD)
void shuffle(int in_deck_p[], int n){
	srand((unsigned) time(NULL));
	    if (n > 1) {
	        int i, k, t;
	        for (i = 0; i < (n - 1); i++) {
	            k = i + rand() / (RAND_MAX / (n - i) + 1);
	            t = in_deck_p[k];
	            in_deck_p[k] = in_deck_p[i];
	            in_deck_p[i] = t;
	        }
	}
} 
