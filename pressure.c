/*
* Author: Patrycja Bachleda, pbachleda2019@my.fit.edu
* Course: CSE 1001, Section 04  Fall 2019
* Project: pressure.c
* Description: calculate pressure
*/

#include <stdio.h>
#include <math.h>

#define SEA_PRESSURE 101325
#define LAPSE_RATE .00976
#define SEA_TEMP 288.16
#define GRAVITY 9.80665
#define MOLAR_MASS .02896968
#define GAS_CONSTANT 8.314462618

int main(void){

	double first, second, third;

	printf("Enter first alititude: ");
	scanf("%lf", &first);
	printf("Enter second alititude: ");
	scanf("%lf", &second);
	printf("Enter third alititude: ");
	scanf("%lf", &third);

	double pascals1, pascals2, pascals3;

	pascals1 = SEA_PRESSURE*(pow((1-(LAPSE_RATE*first)/SEA_TEMP), (GRAVITY*MOLAR_MASS)/(GAS_CONSTANT*LAPSE_RATE)));
	pascals2 = SEA_PRESSURE*(pow((1-(LAPSE_RATE*second)/SEA_TEMP), (GRAVITY*MOLAR_MASS)/(GAS_CONSTANT*LAPSE_RATE)));
	pascals3 = SEA_PRESSURE*(pow((1-(LAPSE_RATE*third)/SEA_TEMP), (GRAVITY*MOLAR_MASS)/(GAS_CONSTANT*LAPSE_RATE)));

	printf("%17s%17s%17s%17s\n", "Altitude (m)", "Pressure (Pa)", "Pressure(mbar)", "Pressure (atm)" );
	printf("%17.2lf%17.2lf%17.2lf%17.2lf\n", first, pascals1, (pascals1*.01), pascals1/(1.01325e5));
	printf("%17.2lf%17.2lf%17.2lf%17.2lf\n", second, pascals2, pascals2*.01, pascals2/(1.01325e5));
	printf("%17.2lf%17.2lf%17.2lf%17.2lf", third, pascals3, pascals3*.01, pascals3/(1.01325e5));
	return 0;
}
