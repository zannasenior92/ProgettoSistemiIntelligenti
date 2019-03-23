#include <iostream>
#include "Station.h"

using Station::Station_i;
int main()
{


	const int n = 10;												//n° STAZIONI
	int n_b = 5;													//n° BICI STAZIONE i
	int n_c = 10;													//n° COLONNINE STAZIONE i
	/*se volessi inserirle random basta fare "rand() % 10" per generare da 0 a 10*/
	Station::Station_i *stations[n];
	for (int i = 0; i < n; i++)
	{
		stations[i] = new Station_i(n_b,n_c);
	}



	



	return 0;
}