/*

* Author: Patrycja Bachleda, pbachleda2019@my.fit.edu

* Course: CSE 1001, Section 04 Fall 2019

* Project: ordinal.c

* Description: prints out ordinal numbers up to the user inputted value
*/

#include <stdio.h>

int main(void){

	int inputValue, sum;
	
	//Set a beginning value so the program has a compare value
	printf("Welcome to Ordinal numbers!\n");
	printf("Enter a value between 0 and 65535 (negative value to quit): ");
	scanf("%d", &inputValue);

	while(inputValue>=0){
	//Print the values from 0 - inputValue
		for(int i = 0; i<=inputValue; i++){
			if((inputValue >= 0) && (inputValue <= 65535)){
				if((i<11) || (i>20)){
					if(i%10==1){
						printf("%dst Value\n", i);	
					}
					else if(i%10==2){
						printf("%dnd Value\n", i);	
					}
					else if(i%10==3){
						printf("%drd Value\n", i);	
					}
					else{
						printf("%dth Value\n", i);	
					}
				}

				else{
					printf("%dth Value\n", i);	
				}

			}

			//If value is not in range (greater than) 
			else{
				printf("Input not allowed. Try again.\n");
				break;
			}
		}

		//Calculate sum of only numbers that were valid (entered numbers)
		if((inputValue >= 0) && (inputValue <= 65535)){
			sum = sum + inputValue;
		}
	
		
		//Asks again once the loop has run so the loop can run again if needed
		printf("\n");
		printf("Enter a value between 0 and 65535 (negative value to quit): ");
		scanf("%d", &inputValue);
	}

		printf("\n");
		printf("The sum of all your entered numbers is %d\n", sum);
		printf("Goodbye! Thanks for playing!");
}
