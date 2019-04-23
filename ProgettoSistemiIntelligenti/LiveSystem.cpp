/*-----------------------------METHODS TO CREATE A LIVE-SYSTEM OF BIKE USERS--------------------------*/

#include "Station.h"
#include "User.h"
#include <Windows.h>
/*-------------------------------VIRTUAL SIMULATOR USERS AND STATIONS---------------------------------*/
void generateTraffic(Stations *inststations, Users *instusers);
void createEnv(Stations *inststations,Users *instusers);
void selectBestStations(Stations *inststations, Users *instusers);


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
			printf("Available Bike Station %d: %d \n", k, inststations->all_stations[k].n_bikes());
			printf("Free Columns Station   %d: %d \n", k, inststations->all_stations[k].av_columns());
			printf("\n");
		}
		printf("------------------------------------------------------------------------------\n\n");
	}

	instusers->all_users = (User_i*)malloc(instusers->n_users * sizeof(User_i));
	int time_user = rand() % 30;																				//TEMPO RANDOM PERCORSO UTENTI
	for (int j = 0; j < instusers->n_users; j++)
	{
		instusers->all_users[j] = User_i(0, inststations->n_stations, rand() % 15);
	}
}


/*------------------------------------------GENERATE BIKE/USERS TRAFFIC-------------------------------------*/
void generateTraffic(Stations *inststations, Users *instusers)
{
	int n = 0;
	bool done = true;
	int rand_user;
	int rand_start;																								//INDEX START'S STATION
	int rand_arrive;																							//INDES END'S STATION

	/*------------------------------------------STAZIONI INIZIALI---------------------------------------*/
	printf("Money in the system at time 0: %lf \n\n\n", inststations->get_cash_desk());

	int numS = inststations->n_stations;
	int numU = instusers->n_users;

	/*---------------------SIMULATE USERS THAT TAKES BIKE AND DEPOSIT------------------------*/
	while (done)
	{
		

		rand_user = rand() % instusers->n_users;
		rand_start = rand() % inststations->n_stations;
		rand_arrive = rand() % inststations->n_stations;


		/*-----------------------------------AGGIORNO BUDGET GUADAGNATO/PERSO-------------------------------*/
		double take = inststations->all_stations[rand_start].get_gift_take();
		double release = inststations->all_stations[rand_arrive].get_gift_release();
		instusers->all_users[rand_user].update_budget(take, release);											//AGGIORNO IL BUDGET DELL'UTENTE
		inststations->update_cash_desk(instusers, take, release);												//AGGIORNO I SOLDI PRESENTI NEL SISTEMA
		printf("User %d left from station:     %d\n", rand_user, rand_start);
		printf("User %d arrived to stations:   %d\n", rand_user, rand_arrive);

		printf("Gift given by start station   %d: %lf\n", rand_start, take);
		printf("Gift given by arrive station  %d: %lf\n\n", rand_arrive, release);

		printf("User %d has %lf money\n", rand_user, instusers->all_users[rand_user].get_budget());

		printf("-------------------------------------------------\n");

		/*------------------------------------STAZIONE DI PARTENZA RIMUOVO BICI-----------------------------*/
		inststations->all_stations[rand_start].remove_bike(numU,numS);											//RIMUOVO LA BICI
		instusers->all_users[rand_user].visit_counter_start(rand_start);										//AGGIORNO IL CONTATORE DELLE STAZIONI VISITATE DALL'UTENTE
																												
											/*COLONNINE LIBERE E BICI MANCANTI*/
		printf("Remaining bikes station %d:  %d \n",rand_start, inststations->all_stations[rand_start].n_bikes());
		printf("Free Columns station    %d:  %d \n\n",rand_start,inststations->all_stations[rand_start].av_columns());
											/*PREMI STAZIONE DI PARTENZA E ARRIVO*/
		printf("Gift that will be give by start station   %d: %lf\n", rand_start, inststations->all_stations[rand_start].get_gift_take());
		printf("Gift that will be give by arrive station  %d: %lf\n", rand_start, inststations->all_stations[rand_start].get_gift_release());
		
		int startCounter = instusers->all_users[rand_user].get_counter_Start_Visits(rand_start);				//NUMERO DI VOLTE CHE L'UTENTE HA VISITATO QUELLA STAZIONE IN PARTENZA
		printf("Number of Visit of start station %d by the user %d = %d \n",rand_start,rand_user,startCounter);	//NUMERO DI VOLTE CHE L'UTENTE HA VISITATO QUELLA STAZIONE IN PARTENZA
		printf("-------------------------------------------------\n");
		/*---------------------------------------------------------------------------------------------------*/


		/*------------------------------------STAZIONE DI ARRIVO AGGIUNGO BICI-------------------------------*/
		inststations->all_stations[rand_arrive].add_bike(numU,numS);
		instusers->all_users[rand_user].visit_countet_arrive(rand_arrive);										//AGGIORNO IL CONTATORE DELLE STAZIONI VISITATE DALL'UTENTE

											/*COLONNINE LIBERE E BICI MANCANTI*/
		printf("Remaining bikes station %d: %d\n",rand_arrive, inststations->all_stations[rand_arrive].n_bikes());
		printf("Free Columns station    %d: %d \n\n",rand_arrive,inststations->all_stations[rand_arrive].av_columns());
		
											/*PREMI STAZIONE DI PARTENZA E ARRIVO*/
		printf("Gift that will be give by start station   %d: %lf\n", rand_arrive, inststations->all_stations[rand_arrive].get_gift_take());
		printf("Gift that will be give by arrive station  %d: %lf\n\n", rand_arrive, inststations->all_stations[rand_arrive].get_gift_release());
		
		int arriveCounter = instusers->all_users[rand_user].get_counter_Arrive_Visits(rand_arrive);				//NUMERO DI VOLTE CHE L'UTENTE HA VISITATO QUELLA STAZIONE IN ARRIVO
		printf("Number of Visit of arrive station %d by the user %d = %d \n", rand_arrive, rand_user, arriveCounter);		//NUMERO DI VOLTE CHE L'UTENTE HA VISITATO QUELLA STAZIONE IN ARRIVO

		printf("-------------------------------------------------\n");

		printf("Money in the system: %lf \n\n", inststations->get_cash_desk());
		/*---------------------------------------------------------------------------------------------------*/
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

void selectBestStations(Stations *inststations, Users *instusers)
{
	int start = rand() % inststations->n_stations;														//STAZIONE DA CUI VOGLIO PARTIRE
	double x_s = inststations->all_stations[start].get_x_coord();
	double y_s = inststations->all_stations[start].get_y_coord();
	
	int arrive = rand() % inststations->n_stations;
	double x_a = inststations->all_stations[arrive].get_x_coord();
	double y_a = inststations->all_stations[arrive].get_y_coord();

	for (int i = 0; i < inststations->n_stations; i++)
	{
		/*--------------COORDINATE DA CONFRONTARE-------------*/
		double x_i = inststations->all_stations[i].get_x_coord();
		double y_i = inststations->all_stations[i].get_y_coord();

		double dist_s = sqrt(pow(abs(x_s-x_i), 2) + pow(abs(y_s-y_i), 2));
		double dist_a = sqrt(pow(abs(x_a-x_i), 2) + pow(abs(y_a-y_i), 2));
		/*---------------SE LA DISTANZA E' PICCOLA E LA STAZIONE HA BISOGNO DI BICI O DI LIBERARE COLONNINE ALLORA INDIRIZZO L'UTENTE AUMENTANDO IL BUDGET-------------*/
		if (dist_s < 100)
		{

		}
	}
}
