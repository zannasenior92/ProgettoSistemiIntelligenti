/*-----------------------------METHODS TO CREATE A LIVE-SYSTEM OF BIKE USERS--------------------------*/

#include "Station.h"
#include "User.h"
#include <Windows.h>
#include <time.h>
/*-------------------------------VIRTUAL SIMULATOR USERS AND STATIONS---------------------------------*/
void generateTraffic(Stations *inststations, Users *instusers);
void createEnv(Stations *inststations,Users *instusers);
void inductedBestStartStations(Stations *inststations, Users *instusers,int user, int start_station, int arrive_station);
void inductedBestArriveStations(Stations *inststations, Users *instusers,int user, int start_station, int arrive_station);
void budget_time_update(Stations *inststations);



/*viene passato come argomento l'istanza stazione e in questo modo posso accedere al numero di bici per stazione
al numero di colonnine per stazione e al numero di stazioni da creare*/

/*----------------------CREO ARRAY DI STAZIONI E UTENTI E LO INIZIALIZZO--------------------------*/
void createEnv(Stations *inststations, Users *instusers)
{
	inststations->all_stations = (Station_i*)malloc(inststations->n_stations * sizeof(Station_i));
	for (int i = 0; i < inststations->n_stations; i++)
	{
		inststations->all_stations[i] = Station_i(inststations->num_bikes, inststations->num_columns);
	}
	printf("N° of users: %d\n",instusers->n_users);

	/*--------------------PRINT BIKES AND FREE COLUMNS IN EVERY STATIONS-----------------*/
	if (VERBOSE >= 100){
		for (int k = 0; k < inststations->n_stations; k++){
			printf("Available Bike Station %d: %d \n", k, inststations->all_stations[k].av_bikes());
			printf("Free Columns Station   %d: %d \n", k, inststations->all_stations[k].av_columns());
			printf("\n");
		}
		printf("------------------------------------------------------------------------------\n\n");
	}
	
	/*INIZIALIZZO GLI UTENTI*/
	instusers->all_users = (User_i*)malloc(instusers->n_users * sizeof(User_i));
	int time_user = rand() % 30;																				//TEMPO RANDOM PERCORSO UTENTI
	for (int j = 0; j < instusers->n_users; j++)
	{
		instusers->all_users[j] = User_i(0, inststations->n_stations, rand() % 15, rand() % 10);
	}
	

	/*INIZIALIZZO CRITICITA' STAZIONI*/
	inststations->critical_station = (double*)calloc(inststations->n_stations , sizeof(double));
	if (VERBOSE >200)
	{
		for (int i = 0; i < inststations->n_stations; i++)
		{
			printf("Station %d criticity = %lf \n", i, inststations->critical_station[i]);
		}
	}
	
}


/*------------------------------------------GENERATE BIKE/USERS TRAFFIC-------------------------------------*/
void generateTraffic(Stations *inststations, Users *instusers)
{
	printf("\n");
	int n = 0;
	bool done = true;
	int rand_user;
	int rand_start;																								//INDEX START'S STATION
	int rand_arrive;																							//INDES END'S STATION

	/*------------------------------------------STAZIONI INIZIALI---------------------------------------*/
	printf("Money in the system at time 0: %lf \n\n\n", inststations->get_cash_desk());

	int numS = inststations->n_stations;
	int numU = instusers->n_users;

	srand((int)time(NULL));//CAMBIO IL SEME RANDOM

	/*---------------------SIMULATE USERS THAT TAKES BIKE AND DEPOSIT------------------------*/
	while (done)
	{
		/*PRENDERE IL TEMPO QUI DENTRO PER POTER AGGIORNARE LE STAZIONI CRITICHE*/

		rand_user = rand() % instusers->n_users;
		rand_start = rand() % inststations->n_stations;															//STAZIONE DA CUI VORREBBE PARTIRE L'UTENTE
		rand_arrive = rand() % inststations->n_stations;														//STAZIONE IN CUI VORREBBE ARRIVARE L'UTENTE

		/*-----------------------------------AGGIORNO BUDGET GUADAGNATO/PERSO-------------------------------*/
		double take = inststations->all_stations[rand_start].get_gift_take();
		double release = inststations->all_stations[rand_arrive].get_gift_release();
		instusers->all_users[rand_user].update_budget(take, release);											//AGGIORNO IL BUDGET DELL'UTENTE
		inststations->update_cash_desk(instusers, take, release);												//AGGIORNO I SOLDI PRESENTI NEL SISTEMA
		printf("User %d want left from station:    %d\n", rand_user, rand_start + 1);
		printf("User %d want arrive to stations:   %d\n", rand_user, rand_arrive + 1);
		printf("\n");
		
		printf("\n");
		printf("______________________________________________________________\n");
		printf("Gift given by start station   %d: %lf\n", rand_start + 1, take);
		printf("Gift given by arrive station  %d: %lf\n", rand_arrive + 1, release);
		printf("______________________________________________________________\n");

		printf("User %d has %lf money\n", rand_user, instusers->all_users[rand_user].get_budget());

		printf("-------------------------------------------------\n");

		/*------------------------------------STAZIONE DI PARTENZA RIMUOVO BICI-----------------------------*/
		inststations->all_stations[rand_start].remove_bike(instusers,numU,numS,rand_user);											//RIMUOVO LA BICI
		instusers->all_users[rand_user].visit_counter_start(rand_start);										//AGGIORNO IL CONTATORE DELLE STAZIONI VISITATE DALL'UTENTE
																												
											/*COLONNINE LIBERE E BICI MANCANTI*/
		printf("Remaining bikes station %d:  %d \n",rand_start + 1, inststations->all_stations[rand_start].av_bikes());
		printf("Free Columns station    %d:  %d \n\n",rand_start + 1,inststations->all_stations[rand_start].av_columns());
											/*PREMI STAZIONE DI PARTENZA E ARRIVO*/
		printf("______________________________________________________________\n");
		printf("Gift that will be give by start station   %d: %lf\n", rand_start + 1, inststations->all_stations[rand_start].get_gift_take());
		printf("Gift that will be give by arrive station  %d: %lf\n", rand_start + 1, inststations->all_stations[rand_start].get_gift_release());
		printf("______________________________________________________________\n");

		int startCounter = instusers->all_users[rand_user].get_counter_Start_Visits(rand_start);				//NUMERO DI VOLTE CHE L'UTENTE HA VISITATO QUELLA STAZIONE IN PARTENZA
		printf("Number of Visit of start station %d by the user %d = %d \n",rand_start + 1,rand_user,startCounter);	
		printf("-------------------------------------------------\n");
		/*---------------------------------------------------------------------------------------------------*/


		/*------------------------------------STAZIONE DI ARRIVO AGGIUNGO BICI-------------------------------*/
		inststations->all_stations[rand_arrive].add_bike(instusers,numU,numS,rand_user);
		instusers->all_users[rand_user].visit_countet_arrive(rand_arrive);										//AGGIORNO IL CONTATORE DELLE STAZIONI VISITATE DALL'UTENTE

											/*COLONNINE LIBERE E BICI MANCANTI*/
		printf("Remaining bikes station %d: %d\n",rand_arrive + 1, inststations->all_stations[rand_arrive].av_bikes());
		printf("Free Columns station    %d: %d \n\n",rand_arrive + 1,inststations->all_stations[rand_arrive].av_columns());
		
											/*PREMI STAZIONE DI PARTENZA E ARRIVO*/
		printf("Gift that will be give by start station   %d: %lf\n", rand_arrive + 1, inststations->all_stations[rand_arrive].get_gift_take());
		printf("Gift that will be give by arrive station  %d: %lf\n\n", rand_arrive + 1, inststations->all_stations[rand_arrive].get_gift_release());
		
		int arriveCounter = instusers->all_users[rand_user].get_counter_Arrive_Visits(rand_arrive);							//NUMERO DI VOLTE CHE L'UTENTE HA VISITATO QUELLA STAZIONE IN ARRIVO
		printf("Number of Visit of arrive station %d by the user %d = %d \n", rand_arrive + 1, rand_user, arriveCounter);		//NUMERO DI VOLTE CHE L'UTENTE HA VISITATO QUELLA STAZIONE IN ARRIVO

		printf("-------------------------------------------------\n");

		printf("Money in the system: %lf \n\n", inststations->get_cash_desk());
		/*---------------------------------------------------------------------------------------------------*/
		
		/*-------------------------------CONTROLLO LA CRITICITA' DELLE STAZIONI------------------------------*/
		budget_time_update(inststations);
		printf("------------------------------------------------------------------------------\n\n");


		Sleep(30);		//RITARDO DI 10 MILLISECONDI (nella realtà dovranno corrispondere a 10 minuti)
		if (n > 10)
		{
			done = false;
		}
		n++;
	}

	/*--------------------PRINT BIKES AND FREE COLUMNS IN EVERY STATIONS-----------------*/
	if (VERBOSE >= 50){
		for (int k = 0; k < inststations->n_stations; k++){
			printf("Bikes present in station %d: %d \n", k + 1, inststations->all_stations[k].av_bikes());
			printf("Free columns station     %d: %d \n", k + 1, inststations->all_stations[k].av_columns());
		}
		printf("------------------------------------------------------------------------------\n\n");
	}
	/*-----------------------------PRINT CRITICAL STATIONS-------------------------------*/
	if (VERBOSE >= 50 )
	{
		printf("++++++++------------CRITICAL STATIONS------------++++++++\n\n");
		for (int m = 0; m < inststations->n_stations; m++)
		{
			if (inststations->critical_station[m]== 1)
			{
				printf("Station %d is critical\n",m + 1);

			}
		}

	}
}

/*METODO CHE SCEGLIE LA STAZIONE DI PARTENZA IN BASE A QUELLE VUOTE*/
int choose_START_station(Stations *inststations, Users *instusers, int user)
{
	int rand_s = rand() % inststations->n_stations;
	printf("User %d would start from station %d \n", user, rand_s);

	while (inststations->all_stations[rand_s].av_bikes() == 0)
	{
		double x_i;
		double y_i;

		for (int i = 0; i < inststations->n_stations; i++)
		{
			/*--------------COORDINATE DA CONFRONTARE-------------*/
			x_i = inststations->xcoords[i];
			y_i = inststations->ycoords[i];

			double gift_take = inststations->all_stations[i].get_gift_take();
			double distance = 0;
		}
		rand_s = rand() % inststations->n_stations;
	}
	printf("User %d choose start station %d \n", user, rand_s);
	return rand_s;
}
/*METODO CHE SCEGLIE LA STAZIONE DI ARRIVO IN BASE A QUELLE PIENE*/
int choose_ARRIVE_station(Stations *inststations)
{
	int rand_a = rand() % inststations->n_stations;

	while (inststations->all_stations[rand_a].av_columns() == 0)
	{
		rand_a = rand() % inststations->n_stations;
	}
	return rand_a;
}
