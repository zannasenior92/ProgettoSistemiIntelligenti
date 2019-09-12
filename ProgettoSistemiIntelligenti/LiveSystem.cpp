/*-------------------------------VIRTUAL SIMULATOR USERS AND STATIONS---------------------------------*/

#include "Station.h"
#include "User.h"
#include <Windows.h>
#include <time.h>

/*-----------------------------METHODS TO CREATE A LIVE-SYSTEM OF BIKE USERS--------------------------*/
void generateTraffic(Stations *inststations, Users *instusers);
void createEnv(Stations *inststations,Users *instusers);
void budget_time_update(Stations *inststations);
int choose_START_station(Stations *inststations, Users *instusers, int user, FILE *gnuplotPipe2);
int choose_ARRIVE_station(Stations *inststations, Users *instusers, int user, FILE *gnuplotPipe2);
int choose_START_station_from_csv_start(Stations *inststations, Users *instusers, int user, FILE *gnuplotPipe2, int n);
int choose_ARRIVE_station_from_csv_start(Stations *inststations, Users *instusers, int user, FILE *gnuplotPipe2, int n);
int parse_travel_start_station_index(Stations *inststations, Users *instusers, int index_row_csv);
int parse_travel_end_station_index(Stations *inststations, Users *instusers, int index_row_csv);
void initial_critical_stations(Stations *inststations);
void update_travel(Stations *inststations, int def_start_s, int def_arrive_s);
void reset_plot(FILE *gnuplotPipe2);
void print_travel(FILE *gnuplotPipe2);
void reset_print_transfert(Stations *inststations);
void print_money_in_system(Stations *inststations, int number_of_transition);
void print_satisfactions(Users *instusers);


#define USERS_SATISFACTION 50 //SODDISFAZIONE DEGLI UTENTI
#define CRITICAL_STATIONS 50
#define PRINT_TRAVEL_INFO 50 //STAMPO LE INFORMAZIONI DI OGNI VIAGGIO

#define Number_Of_Transition 2000 //NUMERO DI VIAGGI DEGLI UTENTI
#define Pre_to_move 1000 //PREDISPOSIZIONE CHE HA OGNI UTENTE A MUOVERSI (PIU' ALTO PIU' MENO PREDISPOSTI, PIU' BASSO PIU' PREDISPOSTI)
#define V_p_t_m 1000 //VALORE PROPENSION TO MOVE (QUANTO E' DISPOSTO UN UTENDE A SPOSTARSI)
/*viene passato come argomento l'istanza stazione e in questo modo posso accedere al numero di bici per stazione
al numero di colonnine per stazione e al numero di stazioni da creare*/

/*----------------------CREO ARRAY DI STAZIONI E UTENTI E LO INIZIALIZZO--------------------------*/
void createEnv(Stations *inststations, Users *instusers)
{
	/*INIZIALIZE STATIONS*/
	inststations->all_stations = (Station_i*)malloc(inststations->n_stations * sizeof(Station_i));
	
	for (int i = 0; i < inststations->n_stations; i++)
	{

		inststations->all_stations[i] = Station_i(inststations->num_bikes, inststations->num_columns);
		
	}
	printf("N° of users: %d\n",instusers->n_users);

	/*--------------------PRINT BIKES AND FREE COLUMNS IN EVERY STATIONS-----------------*/
	if (LIVESYSTEM >= 100){
		for (int k = 0; k < inststations->n_stations; k++){
			printf("Available Bike Station %d: %d \n", k, inststations->all_stations[k].av_bikes());
			printf("Free Columns Station   %d: %d \n", k, inststations->all_stations[k].av_columns());
			printf("\n");
		}
		printf("------------------------------------------------------------------------------\n\n");
	}
	
	/*INIZIALIZE USERS*/
	instusers->all_users = (User_i*)malloc(instusers->n_users * sizeof(User_i));
	int time_user = rand() % 30;														//TEMPO RANDOM PERCORSO UTENTI
	for (int j = 0; j < instusers->n_users; j++)
	{
		instusers->all_users[j] = User_i(0, inststations->n_stations, rand() % 15, (double)(Pre_to_move + rand() % (V_p_t_m +1)));
	}
	

	/*INIZIALIZZO CRITICITA' STAZIONI*/
	inststations->critical_station = (double*)calloc(inststations->n_stations , sizeof(double));
	budget_time_update(inststations);

	if (LIVESYSTEM >200)
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
	int rand_start;																	//INDEX START'S STATION
	int rand_arrive;																//INDES END'S STATION


	/*------------------------------------------SOLDI NEL SISTEMA---------------------------------------*/
	printf("Money in the system at time 0: %lf \n\n\n", inststations->get_cash_desk());
	/*--------------INIZIALIZZO UN ARRAY CON I VALORI DELLA MONETA PRESENTE NEL SISTEMA-----------------*/
	inststations->money_in_the_system = (double*)malloc(Number_Of_Transition * sizeof(double));
	inststations->money_in_the_system[n] = inststations->get_cash_desk();

	int numS = inststations->n_stations;
	int numU = instusers->n_users;

	srand((int)time(NULL));//CAMBIO IL SEME RANDOM
	
	
	FILE *gnuplotPipe2;

	/*---------------------SIMULATE USERS THAT TAKES BIKE AND DEPOSIT------------------------*/
	while (done)
	{	
		/*-------------------APERTURA PIPE GNUPLOT--------------------*/
		gnuplotPipe2 = _popen("C:/gnuplot/bin/gnuplot.exe", "w");	//"-persistent" KEEPS THE PLOT OPEN EVEN AFTER YOUR C PROGRAM QUIT
		
		if (INDUCTEDCHOICE > 100)
		{
		/*------------------------------------------------------------*/
		fprintf(gnuplotPipe2, "%s \n", "set terminal wxt 0 size 1300,700");
		fprintf(gnuplotPipe2, "%s \n", "set title 'SIMULAZIONE UTENTI'");
		fprintf(gnuplotPipe2, "%s \n", "set pointsize 0.7");//set size of every point in the plot
		/*------------------------------------------------------------*/
			reset_plot(gnuplotPipe2);//STAMPO SOLO LE STAZIONI
		}

		/*-------------------------------------UTENTE RANDOM------------------------------------------------*/
		rand_user = rand() % instusers->n_users;
		/*--------------------------------------------------------------------------------------------------*/

		/*--------------------L'UTENTE SCEGLIE STAZIONE DI PARTENZA E STAZIONE DI ARRIVO--------------------*/
		printf("+++++++++++++++CHOICE OF STATIONS+++++++++++++++\n\n");
		rand_start = choose_START_station_from_csv_start(inststations, instusers, rand_user, gnuplotPipe2, n);
		//rand_start = choose_START_station(inststations, instusers, rand_user,gnuplotPipe2);
		printf("::::::::::::::::::::::::::::::::::::::::::::::::\n");
		rand_arrive = choose_ARRIVE_station_from_csv_start(inststations, instusers, rand_user, gnuplotPipe2, n);
		//rand_arrive = choose_ARRIVE_station(inststations, instusers, rand_user,gnuplotPipe2);
		printf("_________________________________________________\n");
		if (INDUCTEDCHOICE > 100)
		{
			update_travel(inststations, rand_start, rand_arrive);
			print_travel(gnuplotPipe2);
		}
		
		if (instusers->travel_deleted !=1)
		{
		/*--------------------------------------------------------------------------------------------------*/

		/*-----------------------------------AGGIORNO BUDGET GUADAGNATO/PERSO-------------------------------*/
			double take;
			double release;

			//GUADAGNO SOLO SE LA STAZIONE DI PARTENZA E' DIVERSA DA QUELLA DI ARRIVO
			if (rand_start != rand_arrive)
			{
				take = inststations->all_stations[rand_start].get_gift_take();
				release = inststations->all_stations[rand_arrive].get_gift_release();
			}
			else
			{
				take = 0;
				release = 0;
			}


			//AGGIORNO IL BUDGET DELL'UTENTE 
			instusers->all_users[rand_user].update_budget(take, release);
			//AGGIORNO I SOLDI PRESENTI NEL SISTEMA
			inststations->update_cash_desk(instusers, take, release);
			if (PRINT_TRAVEL_INFO >=100)
			{
				printf("+++++++++++++++++++++++++GIFT FOR THE USER++++++++++++++++++++\n\n");
				printf("Gift given by start station   %d: %lf\n", inststations->stations_id[rand_start], take);
				printf("Gift given by arrive station  %d: %lf\n", inststations->stations_id[rand_arrive], release);
				printf("______________________________________________________________\n");

				printf("User %d has %lf money\n", rand_user, instusers->all_users[rand_user].get_budget());

				printf("-------------------------------------------------\n");
			}
			

			/*------------------------------------STAZIONE DI PARTENZA RIMUOVO BICI-----------------------------*/
			inststations->all_stations[rand_start].remove_bike(instusers, numU, numS, rand_user);//RIMUOVO LA BICI
			instusers->all_users[rand_user].visit_counter_start(rand_start);//AGGIORNO IL CONTATORE DELLE STAZIONI VISITATE DALL'UTENTE

			if (PRINT_TRAVEL_INFO >= 100)
			{
				/*COLONNINE LIBERE E BICI MANCANTI*/
				printf("Remaining bikes station %d:  %d \n", inststations->stations_id[rand_start], inststations->all_stations[rand_start].av_bikes());
				printf("Free Columns station    %d:  %d \n\n", inststations->stations_id[rand_start], inststations->all_stations[rand_start].av_columns());
				/*PREMI STAZIONE DI PARTENZA E ARRIVO*/
				printf("++++++++++++++++++++++++UPDATE OF GIFT++++++++++++++++++++++++\n\n");
				printf("Gift that will be give by start station   %d: %lf\n", inststations->stations_id[rand_start], inststations->all_stations[rand_start].get_gift_take());
				printf("Gift that will be give by arrive station  %d: %lf\n", inststations->stations_id[rand_start], inststations->all_stations[rand_start].get_gift_release());
				printf("______________________________________________________________\n");
			}
			

			int startCounter = instusers->all_users[rand_user].get_counter_Start_Visits(rand_start);				//NUMERO DI VOLTE CHE L'UTENTE HA VISITATO QUELLA STAZIONE IN PARTENZA
			printf("-------------------------------------------------\n");
			/*---------------------------------------------------------------------------------------------------*/


			/*------------------------------------STAZIONE DI ARRIVO AGGIUNGO BICI-------------------------------*/
			inststations->all_stations[rand_arrive].add_bike(instusers, numU, numS, rand_user);
			instusers->all_users[rand_user].visit_countet_arrive(rand_arrive);										//AGGIORNO IL CONTATORE DELLE STAZIONI VISITATE DALL'UTENTE

			if (PRINT_TRAVEL_INFO >= 100)
			{
				/*COLONNINE LIBERE E BICI MANCANTI*/
				printf("Remaining bikes station %d: %d\n", inststations->stations_id[rand_arrive], inststations->all_stations[rand_arrive].av_bikes());
				printf("Free Columns station    %d: %d \n\n", inststations->stations_id[rand_arrive], inststations->all_stations[rand_arrive].av_columns());

				/*PREMI STAZIONE DI PARTENZA E ARRIVO*/
				printf("++++++++++++++++++++++++UPDATE OF GIFT++++++++++++++++++++++++\n\n");
				printf("Gift that will be give by start station   %d: %lf\n", inststations->stations_id[rand_arrive], inststations->all_stations[rand_arrive].get_gift_take());
				printf("Gift that will be give by arrive station  %d: %lf\n\n", inststations->stations_id[rand_arrive], inststations->all_stations[rand_arrive].get_gift_release());


				int arriveCounter = instusers->all_users[rand_user].get_counter_Arrive_Visits(rand_arrive);	//NUMERO DI VOLTE CHE L'UTENTE HA VISITATO QUELLA STAZIONE IN ARRIVO

				printf("-------------------------------------------------\n");
			}
		}
		
		if (PRINT_TRAVEL_INFO >= 100){printf("Money in the system: %lf \n\n", inststations->get_cash_desk());}

		/*-----------------STAMPO IN UN ARRAY IL VALORE DELLA MONETA PRESENTE NEL SISTEMA-------------------*/
		inststations->money_in_the_system[n] = inststations->get_cash_desk();
		/*---------------------------------------------------------------------------------------------------*/
		
		/*-------------------------------CONTROLLO LA CRITICITA' DELLE STAZIONI------------------------------*/
		budget_time_update(inststations);
		if (PRINT_TRAVEL_INFO >= 100){printf("------------------------------------------------------------------------------\n\n");}


		//Sleep(3000);		//RITARDO DI 30 MILLISECONDI (nella realtà dovranno corrispondere a 10 minuti)
		if (n >= Number_Of_Transition - 1)
		{
			done = false;
		}
		n++;
		
		/*-------------CHIUSURA PIPE GNUPLOT--------------*/
		_pclose(gnuplotPipe2);
		/*------------------------------------------------*/
	}


	/*--------------------PRINT BIKES AND FREE COLUMNS IN EVERY STATIONS-----------------*/
	if (LIVESYSTEM >= 50){
		for (int k = 0; k < inststations->n_stations; k++){
			printf("Bikes present in station %d: %d \n", k + 1, inststations->all_stations[k].av_bikes());
			printf("Free columns station     %d: %d \n", k + 1, inststations->all_stations[k].av_columns());
		}
		printf("------------------------------------------------------------------------------\n\n");
	}
	/*-----------------------------PRINT CRITICAL STATIONS-------------------------------*/
	if (CRITICAL_STATIONS >= 50 )
	{
		printf("++++++++------------CRITICAL STATIONS------------++++++++\n\n");
		for (int m = 0; m < inststations->n_stations; m++)
		{
			if (inststations->critical_station[m]== 1)
			{
				printf("Station %d is critical\n",inststations->stations_id[m]);

			}
		}
	}
	if (LIVESYSTEM >= 50)
	{
		int number_of_times_critical = 0;
		for (int i = 0; i < inststations->n_stations; i++)
		{
			int e_counter = inststations->all_stations[i].critical_empty_counter;
			int f_counter = inststations->all_stations[i].critical_full_counter;
			number_of_times_critical += e_counter + f_counter;
		}
		printf("Stations are been critical for %d times", number_of_times_critical);
	}
	if (USERS_SATISFACTION >= 100)
	{
		for (int user = 0; user < instusers->n_users; user++)
		{
			printf("User %d has satisfaction equal to: %lf \n",user,instusers->all_users[user].get_satisfaction());
		}

	}

	/*--------STAMPO I VALORI DI SODDISFAZIONE-------------*/
	print_satisfactions(instusers);

	/*------STAMPO L'ANDAMENTO DEI SOLDI DEL SISTEMA-------*/
	print_money_in_system(inststations,Number_Of_Transition);
}




