#include <iostream>
#include "Station.h"
#include <conio.h>

using Station::Station_i;
int main(int argc, char **argv)
{


	const int n = 10;												//n° STAZIONI
	int n_b = 5;													//n° BICI STAZIONE i
	int n_c = 10;													//n° COLONNINE STAZIONE i
	/*se volessi inserirle random basta fare "rand() % 10" per generare da 0 a 10*/

	/*----------------------CREO ARRAY DI STAZIONI E LO INIZIALIZZO--------------------------*/
	Station::Station_i *stations[n];
	for (int i = 0; i < n; i++)
	{
		stations[i] = new Station_i(n_b,n_c);
	}
	stations[2]->add_bike();
	stations[3]->remove_bike();

	/*--------------------PRINT BIKES AND FREE COLUMNS IN EVERY STATIONS---------------------*/
	if (VERBOSE >= 50)
	{
		for (int k = 0; k < n; k++)
		{
			printf("Biciclette Presenti Stazione %d: %d \n",k, stations[k]->n_bikes());
			printf("Colonnine libere Stazione    %d: %d \n",k ,stations[k]->av_columns());
		}

	}



	


	
	getchar();

	return 0;
}