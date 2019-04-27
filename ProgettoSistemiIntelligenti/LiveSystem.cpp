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
	printf("N� of users: %d\n",instusers->n_users);

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
			printf("%lf \n", inststations->critical_station[i]);
		}
	}

	/*INIZIALIZZO TEMPO STAZIONI VUOTE E PIENE*/
	inststations->station_empty_time = (double*)calloc(inststations->n_stations, sizeof(double));
	inststations->station_full_time = (double*)calloc(inststations->n_stations, sizeof(double));
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

	double time0 = 0; //PRENDO IL TEMPO INIZIALE PER POTER AGGIORNARE I PREMI DELLE STATIONI CRITICHE

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
		printf("User %d want left from station:     %d\n", rand_user, rand_start + 1);
		printf("User %d want arrive to stations:   %d\n", rand_user, rand_arrive + 1);
		printf("\n");
		
		printf("\n");
		printf("Gift given by start station   %d: %lf\n", rand_start + 1, take);
		printf("Gift given by arrive station  %d: %lf\n\n", rand_arrive + 1, release);

		printf("-------BIKE REMOVED-------\n");
		printf("User %d has %lf money\n", rand_user, instusers->all_users[rand_user].get_budget());

		printf("-------------------------------------------------\n");

		/*------------------------------------STAZIONE DI PARTENZA RIMUOVO BICI-----------------------------*/
		inststations->all_stations[rand_start].remove_bike(instusers,numU,numS,rand_user);											//RIMUOVO LA BICI
		instusers->all_users[rand_user].visit_counter_start(rand_start);										//AGGIORNO IL CONTATORE DELLE STAZIONI VISITATE DALL'UTENTE
																												
											/*COLONNINE LIBERE E BICI MANCANTI*/
		printf("Remaining bikes station %d:  %d \n",rand_start + 1, inststations->all_stations[rand_start].av_bikes());
		printf("Free Columns station    %d:  %d \n\n",rand_start + 1,inststations->all_stations[rand_start].av_columns());
											/*PREMI STAZIONE DI PARTENZA E ARRIVO*/
		printf("Gift that will be give by start station   %d: %lf\n", rand_start + 1, inststations->all_stations[rand_start].get_gift_take());
		printf("Gift that will be give by arrive station  %d: %lf\n", rand_start + 1, inststations->all_stations[rand_start].get_gift_release());
		
		int startCounter = instusers->all_users[rand_user].get_counter_Start_Visits(rand_start);				//NUMERO DI VOLTE CHE L'UTENTE HA VISITATO QUELLA STAZIONE IN PARTENZA
		printf("Number of Visit of start station %d by the user %d = %d \n",rand_start + 1,rand_user,startCounter);	
		printf("-------------------------------------------------\n");
		/*---------------------------------------------------------------------------------------------------*/


		/*------------------------------------STAZIONE DI ARRIVO AGGIUNGO BICI-------------------------------*/
		inststations->all_stations[rand_arrive].add_bike(instusers,numU,numS,rand_user);
		instusers->all_users[rand_user].visit_countet_arrive(rand_arrive);										//AGGIORNO IL CONTATORE DELLE STAZIONI VISITATE DALL'UTENTE
		printf("-------BIKE RELEASED------\n");

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
		printf("------------------------------------------------------------------------------\n\n");


		Sleep(10);		//RITARDO DI 10 MILLISECONDI
		if (n > 50)
		{
			done = false;
		}
		n++;
	}

	/*--------------------PRINT BIKES AND FREE COLUMNS IN EVERY STATIONS-----------------*/
	if (VERBOSE >= 50){
		for (int k = 0; k < inststations->n_stations; k++){
			printf("Biciclette Presenti Stazione %d: %d \n", k + 1, inststations->all_stations[k].av_bikes());
			printf("Colonnine libere Stazione    %d: %d \n", k + 1, inststations->all_stations[k].av_columns());
		}
		printf("------------------------------------------------------------------------------\n");
	}
}


/*AD OGNI PARTENZA CONTROLLA LO STATO DELLE COLONNINE E DELLE BICI DI OGNI STAZIONE*/
void budget_time_update(Stations *inststations)
{
	//PRENDO IL TEMPO CORRENTE
	clock_t current_time = clock();

	for (int i = 0; i < inststations->n_stations; i++)
	{
		int columns = inststations->all_stations[i].av_columns();
		int bikes = inststations->all_stations[i].av_bikes();
		
		/*SE CI SONO SOLO BICI O SOLO COLONNINE VUOTE ALLORA SPINGO PER PRELEVARE/DEPOSITARE*/

		if ((columns == 0))//STAZIONE SENZA COLONNINE LIBERE
		{
			if (inststations->critical_station[i] == 0)//SE NON E' STATA MAI SELEZIONATA COME CRITICA ALLORA LA SELEZIONO
			{
				inststations->critical_station[i] = 1;
			}
			else//QUALORA FOSSE GIA' CRITICA PRENDO IL TEMPO PER CUI E' CRITICA
			{
				inststations->station_full_time[i] = current_time;
			}
		}
		else if((bikes == 0))//STAZIONE SENZA BICI
		{
			if (inststations->critical_station[i] == 0)//SE NON E' STATA MAI SELEZIONATA COME CRITICA ALLORA LA SELEZIONO
			{
				inststations->critical_station[i] = 1;
			}
			else
			{
				inststations->station_empty_time[i] = current_time;
			}

		}
		else//DICO CHE LA STAZIONE NON E' PIU' CRITICA E AZZERO I TEMPI PER CUI E' STATA CRITICA IN MODO DA RIPARTIRE DA 0 SUCESSIVAMENTE
		{
			inststations->critical_station[i] = 0;

			inststations->station_empty_time[i] = 0;
			inststations->station_full_time[i] = 0;
		}
	}
}
