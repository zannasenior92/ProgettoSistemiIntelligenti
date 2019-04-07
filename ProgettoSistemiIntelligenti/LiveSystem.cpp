/*-----------------------------METHODS TO CREATE A LIVE-SYSTEM OF BIKE USERS--------------------------*/

#include "Station.h"
#include "User.h"
#include <Windows.h>
/*-------------------------------VIRTUAL SIMULATOR USERS AND STATIONS---------------------------------*/
void generateTraffic(Stations *inst);
void createEnv(Stations *inst);
	


/*viene passato come argomento l'istanza stazione e in questo modo posso accedere al numero di bici per stazione
al numero di colonnine per stazione e al numero di stazioni da creare*/

/*----------------------CREO ARRAY DI STAZIONI E LO INIZIALIZZO--------------------------*/
void createEnv(Stations *inst)
{
	inst->all_stations = (Station_i*)malloc(inst->n_stations * sizeof(Station_i));
	for (int i = 0; i < inst->n_stations; i++)
	{
		inst->all_stations[i] = Station_i(inst->num_bikes, inst->num_columns);
	}


	/*--------------------PRINT BIKES AND FREE COLUMNS IN EVERY STATIONS-----------------*/
	if (VERBOSE >= 50){
		for (int k = 0; k < inst->n_stations; k++){
			printf("Available Bike Station %d: %d \n", k, inst->all_stations[k].n_bikes());
			printf("Free Columns Station   %d: %d \n", k, inst->all_stations[k].av_columns());
		}
		printf("------------------------------------------------------------------------------\n\n");
	}
}


/*------------------------------------------GENERATE BIKE/USERS TRAFFIC-------------------------------------*/
void generateTraffic(Stations *inst)
{
	int n = 0;
	bool done = true;
	int rand_start;																							//INDEX START'S STATION
	int rand_arrive;																						//INDES END'S STATION

	/*---------------------SIMULATE USERS THAT TAKES BIKE AND DEPOSIT------------------------*/
	while (done)
	{
		
		rand_start = rand() % inst->n_stations;
		rand_arrive = rand() % inst->n_stations;
		/*------------------------------------STAZIONE DI PARTENZA RIMUOVO BICI-----------------------------*/
		printf("User left from station:     %d\n",rand_start);
		inst->all_stations[rand_start].remove_bike();
		printf("Remaining bikes:  %d\n", inst->all_stations[rand_start].n_bikes());
		printf("Free Columns:     %d\n",inst->all_stations[rand_start].av_columns());
		
		/*------------------------------------STAZIONE DI ARRIVO AGGIUNGO BICI-------------------------------*/
		printf("User arrived from stations: %d\n", rand_arrive);
		inst->all_stations[rand_arrive].add_bike();
		printf("Remaining bikes: %d\n", inst->all_stations[rand_arrive].n_bikes());
		printf("Free Columns:    %d\n", inst->all_stations[rand_arrive].av_columns());

		printf("------------------------------------------------------------------------------\n");
		
		Sleep(100);
		if (n > 50)
		{
			done = false;
		}
		n++;
	}

	/*--------------------PRINT BIKES AND FREE COLUMNS IN EVERY STATIONS-----------------*/
	if (VERBOSE >= 50){
		for (int k = 0; k < inst->n_stations; k++){
			printf("Biciclette Presenti Stazione %d: %d \n", k, inst->all_stations[k].n_bikes());
			printf("Colonnine libere Stazione    %d: %d \n", k, inst->all_stations[k].av_columns());
		}
		printf("------------------------------------------------------------------------------\n");
	}
}

