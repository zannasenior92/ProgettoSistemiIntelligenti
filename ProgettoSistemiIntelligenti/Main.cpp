#include <iostream>
#include "Station.h"
#include <conio.h>

/*---------------------------DEFINITION OF METHODS---------------------------------------*/
void parse_command_line(int argc, char** argv, Stations *inst);
void read_input(Stations *inst);
void plot_gnuplot(Stations *inst);
void free_instance(Stations *inst) {
	free(inst->xcoords);
	free(inst->ycoords);
}



int main(int argc, char **argv)
{
	Stations stat;
	parse_command_line(argc,argv,&stat);
	read_input(&stat);
	plot_gnuplot(&stat);
	

	const int n = 10;												//n° STAZIONI
	int n_b = 5;													//n° BICI STAZIONE i
	int n_c = 10;													//n° COLONNINE STAZIONE i
	/*se volessi inserirle random basta fare "rand() % 10" per generare da 0 a 10*/

	/*----------------------CREO ARRAY DI STAZIONI E LO INIZIALIZZO--------------------------*/
	Station_i *stations[n];
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
	free_instance(&stat);
	return 0;
}