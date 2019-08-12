#include "Station.h"
#include "User.h"
/*-------------------------------METODI-----------------------------------------------------------------*/
void update_initial_start_stations(Stations *inststations, int start_s);//STAZIONE PARTENZA PROVVISORIA
void update_choosen_start_stations(Stations *inststations, int def_start_s);//STAZIONE PARTENZA DEFINITIVA
void update_initial_arrive_stations(Stations *inststations, int arrive_s);//STAZIONE ARRIVO PROVVISORIA
void update_choosen_arrive_stations(Stations *inststations, int def_arrive_s);//STAZIONE ARRIVO DEFINITIVA
void plot_gnuplot(Stations *inststations);
void print_start( FILE *gnuplotPipe2);
void print_def_start(FILE *gnuplotPipe2);
void print_arrive(FILE *gnuplotPipe2);
void print_def_arrive(FILE *gnuplotPipe2);
void print_travel(FILE *gnuplotPipe2);


/*------------------------------------------------------------------------------------------------------*/

int start_STATION;	//MI SERVE PER NON DOVER RITORNARE ALLA STAZIONE CHE HO SCELTO IN PARTENZA 
int arrive_STATION;
/*------------------------METODI CHE INDUCONO L'UTENTE A SCEGLIERE UNA STAZIONE PIUTTOSTO DI UN'ALTRA---------------------------*/

/*--METODO CHE SCEGLIE LA STAZIONE DI PARTENZA IN BASE A QUELLE VUOTE--*/
int choose_START_station(Stations *inststations, Users *instusers, int user, FILE *gnuplotPipe2)
{
	start_STATION = 1000;//AZZERO LA STAZIONE SCELTA

	int start_s = rand() % inststations->n_stations;
	/*STAMPO IL PUNTO DI PARTENZA PROVVISORIO NEL GRAFICO*/
	update_initial_start_stations(inststations,start_s);
	print_start(gnuplotPipe2);
	/*****************************************************/
	printf("User %d would start from station: %d \n", user, start_s + 1);
	
	int av_b = inststations->all_stations[start_s].av_bikes();//BICI DISPONIBILI ALLA STAZIONE SCELTA INIZIALMENTE
	
	/*---SE LA STAZIONE E' VUOTA ALLORA PROVVEDO A SCEGLIERE UN'ALTRA STAZIONE---*/
	if (av_b == 0)
	{
		printf("EMPTY STATION-I CAN'T START FROM THIS STATION\n\n");
		//-----------STAZIONE DA CUI VOGLIO PARTIRE
		double x_a = inststations->xcoords[start_s];
		double y_a = inststations->ycoords[start_s];

		double x_i;
		double y_i;
		int find_altern_station = 0;	//TROVATA STAZIONE ALTERNATIVA
		int best_start_station = 0;		//INDICE MIGLIOR STAZIONE SCELTA
		double decision = 0;			//MIGLIOR VALORE DI DECISIONE DELLA STAZIONE VERSO CUI MI POSSO SPOSTARE
		double distance;				//DISTANZA TRA STAZIONI
		double best_dist = INFINITY;	//MIGLIOR DISTANZA
		double gift_take;				//PREMIO DATO STAZIONE i-ESIMA
		double user_dec_val = instusers->all_users[user].get_value_decision();//VALORE DECISIONE UTENTE
		if (INDUCTEDCHOICE > 10)
		{
			printf("User value decision: %lf \n", user_dec_val);
		}

		for (int i = 0; i < inststations->n_stations; i++)
		{
			av_b = inststations->all_stations[i].av_bikes();//BICI DISPONIBILI ALLA STAZIONE i CORRENTE

			if ((i != start_s) && ( av_b != 0 ))//LA STAZIONE DEVE AVERE BICI DISPONIBILI
			{
				/*--------------DISTANZA DA CONFRONTARE-------------*/
				x_i = inststations->xcoords[i];
				y_i = inststations->ycoords[i];
				distance = sqrt(pow(abs(x_a - x_i), 2) + pow(abs(y_a - y_i), 2));;//DISTANZA TRA STAZIONE DI PARTENZA E STAZIONE i
				gift_take = inststations->all_stations[i].get_gift_take();//PREMIO FORNITO STAZIONE i-ESIMA
				double i_dec_val = gift_take / distance;
				if (INDUCTEDCHOICE > 10)
				{
					printf("Decision value from my station %d and station %d is: %lf \n", start_s + 1, i + 1, i_dec_val);
				}

				/*--TROVO LA MIGLIORE STAZIONE IN CUI SPOSTARMI TRA QUELLE PER CUI SONO DISPOSTO A SPOSTARMI--*/
				if ((i_dec_val >= 0) && (i_dec_val >= user_dec_val) && (i_dec_val > decision))
				{
					if (find_altern_station == 0)	//METTO IL FLAG A 1 CIOE' HO TROVATO UNA STAZIONE POSSIBILE DA CUI PARTIRE
					{
						find_altern_station = 1;
					}
					best_start_station = i;			//INDICE MIGLIOR STAZIONE VERSO CUI POSSO SPOSTARMI
					decision = i_dec_val;			//MIGLIOR VALORE DI DECISIONE DELLA STAZIONE VERSO CUI MI POSSO SPOSTARE
				}

				/*--TROVO LA STAZIONE PIU' VICINA AL DI FUORI DEL MIO COEFFICIENTE DI SCELTA--*/
				else if(find_altern_station == 0)
				{
					if (distance < best_dist)
					{
						best_dist = distance;
						best_start_station = i;
					}
				}
			}
		}
		if (find_altern_station == 0){printf("Choosen nearest station\n");}
		start_s = best_start_station;
		start_STATION = start_s;//VARIABILE ESTERNA AI METODI RELATIVA ALLA STAZIONE DI PARTENZA SCELTA
	}
	/************************************************************************************/

	/*---SE LA STAZIONE HA BICI DISPONIBILI TROVO LA STAZIONE MIGLIORE DA CUI PARTIRE---
	INFATTI POTREBBERO ESSERCI STAZIONI MOLTO PIU' VANTAGGIOSE DI QUELLA DOVE SONO ATTUALMENTE E
	PER TROVARLE CALCOLO COME VALORE DI CONFRONTO IL VALORE DI DECISIONE USANDO I GIFT DELLA STAZIONE
	DA CUI PARTO E COME DISTANZA LA DISTANZA MINIMA TRA LA STAZIONE DA CUI VOGLIO PARTIRE
	E LE ALTRE STAZIONI--*/
	/************************************************************************************/
	else
	{
		//-----------STAZIONE DA CUI VOGLIO PARTIRE
		double x_a = inststations->xcoords[start_s];
		double y_a = inststations->ycoords[start_s];

		double x_i;
		double y_i;
		int find_altern_station = 0;	//TROVATA STAZIONE ALTERNATIVA
		int best_start_station = 0;		//INDICE MIGLIOR STAZIONE SCELTA
		double decision = 0;			//MIGLIOR VALORE DI DECISIONE DELLA STAZIONE VERSO CUI MI POSSO SPOSTARE
		double distance_i;				//DISTANZA TRA STAZIONI
		double s_virtual_dist =INFINITY;//DISTANZA FITTIZZIA PER COMPARARE LA SCELTA ANCHE CON LA STAZIONE INIZIALE
		double best_dist = INFINITY;	//MIGLIOR DISTANZA
		double gift_take;				//PREMIO DATO STAZIONE i-ESIMA

		double start_gift_take = inststations->all_stations[start_s].get_gift_take();//PREMIO DATO DALLA STAZIONE DI PARTENZA
		double user_dec_val = instusers->all_users[user].get_value_decision();//VALORE DECISIONE UTENTE
		if (INDUCTEDCHOICE > 10)
		{
			printf("User value decision: %lf \n", user_dec_val);
		}
		
		/*MI CALCOLO LA DISTANZA MINIMA TRA LA STAZIONE DI PARTENZA E LE ALTRE STAZIONI*/
		for (int k = 0; k < inststations->n_stations; k++)
		{
			if (k != start_s)
			{
				/*--------------DISTANZA DA CONFRONTARE-------------*/
				x_i = inststations->xcoords[k];
				y_i = inststations->ycoords[k];
				distance_i = sqrt(pow(abs(x_a - x_i), 2) + pow(abs(y_a - y_i), 2));;//DISTANZA TRA STAZIONE DI PARTENZA E STAZIONE i
				if (distance_i < s_virtual_dist)
				{
					s_virtual_dist = distance_i;
				}
			}
			
		}
		
		/*--SE C'E' UN'ALTRA STAZIONE CHE MI GARANTISCE UN MIGLIOR GUADAGNO RISPETTO A QUESTO VALORE INIZIALE
		DI DEFAULT ALLORA SCELGO QUELLA STAZIONE--*/

		/*--VALORE DI DECISIONE PER LA STAZIONE DI PARTENZA (PRENDO LA META' DELLA DISTANZA MINIMA TROVATA 
		PERCHE' POTREBBE ESSERCI IL CASO IN CUI IL VALORE DI DECISIONE E' UGUALE A QUELLO DELLA STAZIONE DI PARTENZA
		E QUINDI TRA LE DUE OVVIO CHE DOVRO' SCEGLIERE LA STAZIONE IN CUI SONO PERCHE' ALTRIMENTI DOVREI MUOVERMI
		PER GUADAGNARE LA STESSA CIFRA)--*/

		double s_dec_val = start_gift_take / (s_virtual_dist / 2);
		printf("Value DEFAULT decision at initial station %d: %lf \n", start_s + 1, s_dec_val);

		/*-----------------------------TROVO LA STAZIONE MIGLIORE DA CUI PARTIRE---------------------*/
		for (int i = 0; i < inststations->n_stations; i++)
		{
			av_b = inststations->all_stations[i].av_bikes();//BICI DISPONIBILI ALLA STAZIONE i CORRENTE

			if ((i != start_s) && (av_b != 0))//LA STAZIONE DEVE AVERE BICI DISPONIBILI
			{
				/*--------------DISTANZA DA CONFRONTARE-------------*/
				x_i = inststations->xcoords[i];
				y_i = inststations->ycoords[i];
				distance_i = sqrt(pow(abs(x_a - x_i), 2) + pow(abs(y_a - y_i), 2));;//DISTANZA TRA STAZIONE DI PARTENZA E STAZIONE i
				gift_take = inststations->all_stations[i].get_gift_take();			//PREMIO FORNITO STAZIONE i-ESIMA
				double i_dec_val = gift_take / distance_i;
				if (INDUCTEDCHOICE > 50)
				{
					printf("Decision value from my station %d and station %d is: %lf \n", start_s + 1, i + 1, i_dec_val);
				}

				/*--SE L'UTENTE E' PREDISPOSTO A SPOSTARSI VERSO LA STAZIONE E SE LA STAZIONE ESAMINATA E' PIU' CONVENIENTE--*/
				if ((i_dec_val >= 0) && (i_dec_val >= user_dec_val) && (i_dec_val > decision))
				{
					if (find_altern_station == 0)//METTO IL FLAG A 1 CIOE' HO TROVATO UNA STAZIONE POSSIBILE DA CUI PARTIRE
					{
						find_altern_station = 1;
					}
					best_start_station = i;
					decision = i_dec_val;
				}
				/*--SE L'UTENTE NON HA TROVATO UNA STAZIONE CONVENIENTE ALLORA SCEGLIE LA STAZIONE PIU' VICINA--*/
				else if (find_altern_station == 0)
				{
					/*---------TROVO LA STAZIONE PIU' VICINA AL DI FUORI DEL MIO COEFFICIENTE DI SCELTA--------------------------*/
					if (distance_i < best_dist)
					{
						best_dist = distance_i;
						best_start_station = i;
					}
				}
			}
		}
		if (find_altern_station == 0) { printf("Choosen nearest station\n"); }

		//SE LA STAZIONE DI PARTENZA CONVIENE RISPETTO ALLE ALTRE ALLORA LA SCELGO
		if (s_dec_val >= decision)
		{
			printf("\n");
			printf("User %d choose start station:     %d \n", user, start_s + 1);
			start_STATION = start_s;

			/*STAMPO LA STAZIONE DEFINITIVA DI PARTENZA NEL GRAFICO*/
			update_choosen_start_stations(inststations, start_s);
			print_def_start(gnuplotPipe2);
			/*******************************************************/

			return start_s;
		}
		else
		{
			start_s = best_start_station;
			start_STATION = start_s;
		}
	}
	printf("\n");
	printf("User %d change station and choose %d as start station \n", user, start_s + 1);

	/*STAMPO LA STAZIONE DEFINITIVA DI PARTENZA NEL GRAFICO*/
	update_choosen_start_stations(inststations, start_s);
	print_def_start(gnuplotPipe2);
	/*******************************************************/

	return start_s;
}


/*METODO CHE SCEGLIE LA STAZIONE DI ARRIVO IN BASE A QUELLE PIENE*/
int choose_ARRIVE_station(Stations *inststations, Users *instusers, int user, FILE *gnuplotPipe2)
{
	arrive_STATION = 1000;
	int arrive_s = rand() % inststations->n_stations;
	while (arrive_s==start_STATION)//NON VOGLIO ARRIVARE NELLA STAZIONE DI PARTENZA
	{
		arrive_s = rand() % inststations->n_stations;
	}
	/*-----STAMPO LA STAZIONE DI ARRIVO PROVVISORIA NEL GRAFICO-----*/
	update_initial_arrive_stations(inststations, arrive_s);
	print_arrive(gnuplotPipe2);
	/****************************************************************/
	printf("User %d would arrive to stations: %d \n", user, arrive_s + 1);

	int av_c = inststations->all_stations[arrive_s].av_columns();//COLONNE DISPONIBILI ALLA STAZIONE SCELTA INIZIALMENTE
	
	/*---SE LA STAZIONE E' VUOTA ALLORA PROVVEDO A SCEGLIERE UN'ALTRA STAZIONE---*/
	if (av_c == 0)
	{
		printf("FULL STATION - I CAN'T ARRIVE IN THIS STATION\n\n");
		//-----------STAZIONE A CUI VOGLIO ARRIVARE
		double x_a = inststations->xcoords[arrive_s];
		double y_a = inststations->ycoords[arrive_s];

		double x_i;
		double y_i;
		int find_altern_station = 0;	//TROVATA STAZIONE ALTERNATIVA
		int best_arrive_station = 0;	//INDICE MIGLIOR STAZIONE SCELTA
		double decision = 0;			//MIGLIOR VALORE DI DECISIONE DELLA STAZIONE VERSO CUI MI POSSO SPOSTARE
		double distance_i;				//DISTANZA TRA STAZIONI
		double best_dist = INFINITY;	//MIGLIOR DISTANZA
		double gift_release;			//PREMIO DATO STAZIONE i-ESIMA
		double user_dec_val = instusers->all_users[user].get_value_decision();//VALORE DECISIONE UTENTE
		if (INDUCTEDCHOICE > 10)
		{
			printf("User value decision: %lf \n", user_dec_val);
		}

		for (int i = 0; i < inststations->n_stations; i++)//COLONNE DISPONIBILI ALLA STAZIONE i-ESIMA
		{
			av_c = inststations->all_stations[i].av_columns();

			//LA STAZIONE DEVE AVERE COLONNE DISPONIBILI E NON DEVE ESSERE QUELLA DI PARTENZA
			if (( i != arrive_s ) && ( av_c != 0 ) && (i!= start_STATION))
			{
				/*--------------DISTANZA DA CONFRONTARE-------------*/
				x_i = inststations->xcoords[i];
				y_i = inststations->ycoords[i];
				distance_i = sqrt(pow(abs(x_a - x_i), 2) + pow(abs(y_a - y_i), 2));;//DISTANZA TRA STAZIONE DI ARRIVO E STAZIONE i
				gift_release = inststations->all_stations[i].get_gift_release();//PREMIO FORNITO STAZIONE DI ARRIVO
				double i_dec_val = gift_release / distance_i;

				if (INDUCTEDCHOICE > 50)
				{
					printf("Decision value from my station %d and station %d is: %lf \n", arrive_s + 1, i + 1, i_dec_val);
				}
				
				/*--SE L'UTENTE E' PREDISPOSTO A SPOSTARSI VERSO LA STAZIONE E SE LA STAZIONE ESAMINATA E' PIU' CONVENIENTE--*/
				if ((i_dec_val >= 0) && (i_dec_val >= user_dec_val) && (i_dec_val > decision))
				{
					if (find_altern_station == 0)//METTO IL FLAG A 1 CIOE' HO TROVATO UNA STAZIONE POSSIBILE SU CUI ANDARE
					{
						find_altern_station = 1;
					}
					best_arrive_station = i;
					decision = i_dec_val;
				}
				else if(find_altern_station == 0)
				{
					/*---------TROVO LA STAZIONE PIU' VICINA AL DI FUORI DEL MIO COEFFICIENTE DI SCELTA----------------------*/
					if (distance_i < best_dist)
					{
						best_dist = distance_i;
						best_arrive_station = i;
					}
				}
			}
		}
		if (find_altern_station == 0) { printf("Choosen nearest station\n"); }
		arrive_s = best_arrive_station;
	}
	/************************************************************************************/
	/*---SE LA STAZIONE HA BICI DISPONIBILI TROVO LA STAZIONE MIGLIORE A CUI ARRIVARE---
	INFATTI POTREBBERO ESSERCI STAZIONI MOLTO PIU' VANTAGGIOSE DI QUELLA DOVE VOGLIO ARRIVARE E
	PER TROVARLE CALCOLO COME VALORE DI CONFRONTO IL VALORE DI DECISIONE USANDO I GIFT DELLA STAZIONE
	IN CUI VOGLIO ARRIVARE E COME DISTANZA LA DISTANZA MINIMA TRA LA STAZIONE IN CUI VOGLIO ARRIVARE
	E LE ALTRE STAZIONI--*/
	else
	{
		//-----------STAZIONE A CUI VOGLIO ARRIVARE
		double x_a = inststations->xcoords[arrive_s];
		double y_a = inststations->ycoords[arrive_s];

		double x_i;
		double y_i;
		int find_altern_station = 0;	//TROVATA STAZIONE ALTERNATIVA
		int best_arrive_station = 0;	//INDICE MIGLIOR STAZIONE SCELTA
		double decision = 0;			//MIGLIOR VALORE DI DECISIONE DELLA STAZIONE VERSO CUI MI POSSO SPOSTARE
		double distance_i;				//DISTANZA TRA STAZIONI
		double s_virtual_dist = INFINITY;//DISTANZA FITTIZZIA PER COMPARARE LA SCELTA ANCHE CON LA STAZIONE INIZIALE
		double best_dist = INFINITY;	//MIGLIOR DISTANZA
		double gift_release;			//PREMIO DATO STAZIONE i-ESIMA

		double arrive_gift_take = inststations->all_stations[arrive_s].get_gift_release();//PREMIO DATO DALLA STAZIONE DI ARRIVO
		double user_dec_val = instusers->all_users[user].get_value_decision();//VALORE DECISIONE UTENTE
		if (INDUCTEDCHOICE > 10)
		{
			printf("User value decision: %lf \n", user_dec_val);
		}

		/*MI CALCOLO LA DISTANZA MINIMA TRA LA STAZIONE DI ARRIVO E LE ALTRE STAZIONI*/
		for (int k = 0; k < inststations->n_stations; k++)
		{
			if (k != arrive_s)
			{
				/*--------------DISTANZA DA CONFRONTARE-------------*/
				x_i = inststations->xcoords[k];
				y_i = inststations->ycoords[k];
				distance_i = sqrt(pow(abs(x_a - x_i), 2) + pow(abs(y_a - y_i), 2));;//DISTANZA TRA STAZIONE DI ARRIVO E STAZIONE i
				if (distance_i < s_virtual_dist)
				{
					s_virtual_dist = distance_i;
				}
			}
		}

		/*VALORE DI DECISIONE PER LA STAZIONE DI ARRIVO (PRENDO LA META' DELLA DISTANZA MINIMA TROVATA
		PERCHE' POTREBBE ESSERCI IL CASO IN CUI IL VALORE DI DECISIONE E' UGUALE A QUELLO DELLA STAZIONE DI ARRIVO
		E QUINDI TRA LE DUE OVVIO CHE DOVRO' SCEGLIERE LA STAZIONE IN CUI SONO PERCHE' ALTRIMENTI DOVREI MUOVERMI
		PER GUADAGNARE LA STESSA CIFRA)--*/
		double s_dec_val = arrive_gift_take / (s_virtual_dist / 2);
		printf("Value DEFAULT decision at initial station %d: %lf \n", arrive_s + 1, s_dec_val);

		/*-----------------------------TROVO LA STAZIONE MIGLIORE DA CUI PARTIRE---------------------*/
		for (int i = 0; i < inststations->n_stations; i++)
		{
			av_c = inststations->all_stations[i].av_columns();

			if ((i != arrive_s) && (av_c != 0) && (i != start_STATION))//LA STAZIONE DEVE AVERE BICI DISPONIBILI
			{
				/*--------------DISTANZA DA CONFRONTARE-------------*/
				x_i = inststations->xcoords[i];
				y_i = inststations->ycoords[i];
				distance_i = sqrt(pow(abs(x_a - x_i), 2) + pow(abs(y_a - y_i), 2));;//DISTANZA TRA STAZIONE DI ARRIVO E STAZIONE i
				gift_release = inststations->all_stations[i].get_gift_release();//PREMIO FORNITO STAZIONE i-ESIMA
				double i_dec_val = gift_release / distance_i;
				if (INDUCTEDCHOICE > 50)
				{
					printf("Decision value from my station %d and station %d is: %lf \n", arrive_s + 1, i + 1, i_dec_val);
				}

				if (distance_i < best_dist)
				{
					best_dist = distance_i;
				}
				/*--SE L'UTENTE E' PREDISPOSTO A SPOSTARSI VERSO LA STAZIONE E SE LA STAZIONE ESAMINATA E' PIU' CONVENIENTE--*/
				if ((i_dec_val >= 0) && (i_dec_val >= user_dec_val) && (i_dec_val > decision))
				{
					if (find_altern_station == 0)//METTO IL FLAG A 1 CIOE' HO TROVATO UNA STAZIONE POSSIBILE DA CUI PARTIRE
					{
						find_altern_station = 1;
					}
					best_arrive_station = i;
					decision = i_dec_val;
				}
				else if (find_altern_station == 0)
				{
					/*---------TROVO LA STAZIONE PIU' VICINA AL DI FUORI DEL MIO COEFFICIENTE DI SCELTA--------------------------*/
					if (distance_i < best_dist)
					{
						best_dist = distance_i;
						best_arrive_station = i;
					}
				}
			}
		}
		if (find_altern_station == 0) { printf("Choosen nearest station\n"); }

		if (s_dec_val >= decision)//SE LA STAZIONE DI ARRIVO CONVIENE RISPETTO ALLE ALTRE ALLORA LA SCELGO
		{
			printf("\n");
			printf("User %d choose arrive station:    %d \n", user, arrive_s + 1);

			/*STAMPO LA STAZIONE DI ARRIVO DEFINITIVA NEL GRAFICO*/
			update_choosen_arrive_stations(inststations, arrive_s);
			print_def_arrive(gnuplotPipe2);
			/*****************************************************/
			
			return arrive_s;
		}
		else
		{
			arrive_s = best_arrive_station;
		}
	}
	printf("\n");
	printf("User %d change station and choose %d as arrive station \n", user, arrive_s + 1);

	/*STAMPO LA STAZIONE DI ARRIVO DEFINITIVA NEL GRAFICO*/
	update_choosen_arrive_stations(inststations, arrive_s);
	print_def_arrive(gnuplotPipe2);
	/*****************************************************/
	return arrive_s;
}