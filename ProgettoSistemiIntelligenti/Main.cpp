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
	free(inst->all_stations);
}
void generateTraffic(Stations *inst);
void createEnv(Stations *inst);



int main(int argc, char **argv)
{
	Stations stat;
	parse_command_line(argc,argv,&stat);
	read_input(&stat);
	plot_gnuplot(&stat);
	
	const int n = stat.n_stations;												//n° STAZIONI
	int n_b = 5;																//n° BICI STAZIONE i
	int n_c = 10;																//n° COLONNINE STAZIONE i
	/*-------------------------INSERT BIKES AND COLUMNS IN EVERY STATION---------------------*/
	stat.set_n_bikes_for_stations(n_b);
	stat.set_n_columns_for_station(n_c);
	/*se volessi inserirle random basta fare "rand() % 10" per generare da 0 a 10*/

	
	/*------------------------CREATE THE ENVIROENMENTS(BIKE & USERS)-------------------------*/
	createEnv(&stat);
	generateTraffic(&stat);																		//GENERO IL TRAFFICO DI UTENTI
	
	
	
	free_instance(&stat);																		//LIBERO LA MEMORIA OCCUPATA DA stat
	return 0;
}