#include <iostream>
#include <conio.h>
#include "Station.h"
#include "User.h"

/*---------------------------DEFINITION OF METHODS---------------------------------------*/
void parse_command_line(int argc, char** argv, Stations *inststations);
void read_input(Stations *inststations);
void plot_gnuplot(Stations *inststations);
void free_instance(Stations *inststations,Users *instusers) {
	free(inststations->xcoords);
	free(inststations->ycoords);
	free(inststations->all_stations);
	free(instusers->all_users);
	free(inststations->critical_station);
}
void generateTraffic(Stations *inststations, Users *instusers);
void createEnv(Stations *inststations,Users *instusers);



int main(int argc, char **argv)
{
	Stations stat;
	Users usrs;
	parse_command_line(argc,argv,&stat);
	read_input(&stat);
	plot_gnuplot(&stat);
	
	const int ns = stat.n_stations;												//n� STAZIONI
	int n_b = 5;																//n� BICI STAZIONE i
	int n_c = 10;																//n� COLONNINE STAZIONE i
	/*-------------------------INSERT BIKES AND COLUMNS IN EVERY STATION---------------------*/
	stat.set_n_bikes_for_stations(n_b);
	stat.set_n_columns_for_station(n_c);
	/*se volessi inserirle random basta fare "rand() % 10" per generare da 0 a 10*/

	/*-----------------------------------INSERT NUMBER OF USERS------------------------------*/
	usrs.n_users = 40;
	stat.set_cash_desk(usrs);
	/*------------------------CREATE THE ENVIROENMENTS(BIKE & USERS)-------------------------*/
	createEnv(&stat,&usrs);
	generateTraffic(&stat,&usrs);																		//GENERO IL TRAFFICO DI UTENTI
		
	free_instance(&stat,&usrs);																		//LIBERO LA MEMORIA OCCUPATA DA stat
	return 0;
}