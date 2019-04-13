/*-----------------------------METHODS TO CREATE A LIVE-SYSTEM OF BIKE USERS--------------------------*/

#include "Station.h"
#include "User.h"
#include <Windows.h>
/*-------------------------------VIRTUAL SIMULATOR USERS AND STATIONS---------------------------------*/
void generateTraffic(Stations *inststations, Users *instusers);
void createEnv(Stations *inststations,Users *instusers);
	


/*viene passato come argomento l'istanza stazione e in questo modo posso accedere al numero di bici per stazione
al numero di colonnine per stazione e al numero di stazioni da creare*/

/*----------------------CREO ARRAY DI STAZIONI E UTENTI E LO INIZIALIZZO--------------------------*/
void createEnv(Stations *inststations, Users *users)
{
	inststations->all_stations = (Station_i*)malloc(inststations->n_stations * sizeof(Station_i));
	for (int i = 0; i < inststations->n_stations; i++)
	{
		inststations->all_stations[i] = Station_i(inststations->num_bikes, inststations->num_columns);
	}


	/*--------------------PRINT BIKES AND FREE COLUMNS IN EVERY STATIONS-----------------*/
	if (VERBOSE >= 50){
		for (int k = 0; k < inststations->n_stations; k++){
			printf("Available Bike Station %d: %d \n", k, inststations->all_stations[k].n_bikes());
			printf("Free Columns Station   %d: %d \n", k, inststations->all_stations[k].av_columns());
			printf("\n");
		}
		printf("------------------------------------------------------------------------------\n\n");
	}

	users->all_users = (User_i*)malloc(users->n_users * sizeof(User_i));
	for (int j = 0; j < users->n_users; j++)
	{
		users->all_users[j] = User_i(0, inststations->n_stations);
	}
}


/*------------------------------------------GENERATE BIKE/USERS TRAFFIC-------------------------------------*/
void generateTraffic(Stations *inststations, Users *instusers)
{
	int n = 0;
	bool done = true;
	int rand_user;
	int rand_start;																							//INDEX START'S STATION
	int rand_arrive;																						//INDES END'S STATION

	/*---------------------SIMULATE USERS THAT TAKES BIKE AND DEPOSIT------------------------*/
	while (done)
	{
		
		int numS = inststations->n_stations;
		int numU = instusers->n_users;

		rand_user = rand() % instusers->n_users;
		rand_start = rand() % inststations->n_stations;
		rand_arrive = rand() % inststations->n_stations;

		

		/*------------------------------------STAZIONE DI PARTENZA RIMUOVO BICI-----------------------------*/
		printf("User left from station:     %d\n",rand_start);
		inststations->all_stations[rand_start].remove_bike(numU,numS);
		printf("Remaining bikes:  %d\n", inststations->all_stations[rand_start].n_bikes());
		printf("Free Columns:     %d\n", inststations->all_stations[rand_start].av_columns());
		printf("Gift given by start station  %d: %lf\n", rand_start, inststations->all_stations[rand_start].get_gift_take());
		printf("Gift given by arrive station  %d: %lf\n", rand_start, inststations->all_stations[rand_start].get_gift_release());

		printf("-------------------------------------------------\n");
		
		/*------------------------------------STAZIONE DI ARRIVO AGGIUNGO BICI-------------------------------*/
		printf("User arrived to stations:   %d\n", rand_arrive);
		inststations->all_stations[rand_arrive].add_bike(numU,numS);
		printf("Remaining bikes:  %d\n", inststations->all_stations[rand_arrive].n_bikes());
		printf("Free Columns:     %d\n", inststations->all_stations[rand_arrive].av_columns());
		printf("Gift given by start station  %d: %lf\n", rand_start, inststations->all_stations[rand_arrive].get_gift_take());
		printf("Gift given by arrive station %d: %lf\n\n", rand_arrive, inststations->all_stations[rand_arrive].get_gift_release());

		printf("-------------------------------------------------\n");

		/*-----------------------------------AGGIORNO BUDGET GUADAGNATO/PERSO-------------------------------*/
		instusers->all_users[rand_user].update_budget(inststations->all_stations[rand_start].get_gift_take(), inststations->all_stations[rand_arrive].get_gift_release());
		printf("User %d has %lf money\n", rand_user, instusers->all_users[rand_user].get_budget());
		
		printf("-------------------------------------------------\n");


		printf("------------------------------------------------------------------------------\n\n");


		Sleep(10);
		if (n > 50)
		{
			done = false;
		}
		n++;
	}

	/*--------------------PRINT BIKES AND FREE COLUMNS IN EVERY STATIONS-----------------*/
	if (VERBOSE >= 50){
		for (int k = 0; k < inststations->n_stations; k++){
			printf("Biciclette Presenti Stazione %d: %d \n", k, inststations->all_stations[k].n_bikes());
			printf("Colonnine libere Stazione    %d: %d \n", k, inststations->all_stations[k].av_columns());
		}
		printf("------------------------------------------------------------------------------\n");
	}
}

