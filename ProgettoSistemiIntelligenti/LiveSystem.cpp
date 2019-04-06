/*-----------------------------METHODS TO CREATE A LIVE-SYSTEM OF BIKE USERS--------------------------*/

#include "Station.h"
#include "User.h"
/*-------------------------------VIRTUAL SIMULATOR USERS AND STATIONS---------------------------------*/
void generateTraffic(Stations *inst);
void createEnv(Stations *inst);
void freeStations(Station_i *inst);
	


/*viene passato come argomento l'istanza stazione e in questo modo posso accedere al numero di bici per stazione
al numero di colonnine per stazione e al numero di stazioni da creare*/

/*----------------------CREO ARRAY DI STAZIONI E LO INIZIALIZZO--------------------------*/
void createEnv(Stations *inst)
{
	Station_i *stations = (Station_i*)malloc(inst->n_stations * sizeof(Station_i));
	for (int i = 0; i < inst->n_stations; i++)
	{
		stations[i] = Station_i(inst->num_bikes, inst->num_columns);
	}
	stations[2].add_bike();
	stations[3].remove_bike();
}

void freeStations(Station_i *inst)													//LIBERO LA MEMORIA OCCUPATA DA stations
{
	free(inst);																				
}


/*------------------------------------------GENERATE BIKE/USERS TRAFFIC-------------------------------------*/
void generateTraffic(Stations *inst)
{
	bool done = true;
	while (done)
	{
		
	}
}

