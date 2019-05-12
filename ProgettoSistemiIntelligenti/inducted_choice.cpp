#include "Station.h"
#include "User.h"


/*------------------------METODI CHE INDUCONO L'UTENTE A SCEGLIERE UNA STAZIONE PIUTTOSTO DI UN'ALTRA---------------------------*/

/*METODO CHE SCEGLIE LA STAZIONE DI PARTENZA IN BASE A QUELLE VUOTE*/
int choose_START_station(Stations *inststations, Users *instusers, int user)
{
	int start_s = rand() % inststations->n_stations;
	printf("User %d would start from station: %d \n", user, start_s + 1);

	//-----------STAZIONE DA CUI VOGLIO PARTIRE
	double x_a = inststations->xcoords[start_s];
	double y_a = inststations->ycoords[start_s];

	double x_i;
	double y_i;

	int best_station = 0;			//INDICE MIGLIOR STAZIONE SCELTA
	int best_dist_station = 0;		//INDICE MIGLIOR STAZIONE VICINA AL DI FUORI DEL MIO COEFFICIENTE DI SCELTA

	double decision = 0;			//VALORE DI DECISIONE CORRENTE
	double distance;				//DISTANZA TRA STAZIONI
	double best_dist = INFINITY;	//MIGLIOR DISTANZA
	double gift_take;				//PREMIO DATO STAZIONE i-ESIMA
	int av_b = inststations->all_stations[start_s].av_bikes();//BICI DISPONIBILI ALLA STAZIONE SCELTA INIZIALMENTE
	
	double user_dec_val = instusers->all_users[user].get_value_decision();//VALORE DECISIONE UTENTE
	printf("User value decision: %lf \n", user_dec_val);

	for (int i = 0; i < inststations->n_stations && (av_b != 0) && (i != start_s); i++)//LA STAZIONE DEVE AVERE BICI DISPONIBILI
	{

		/*--------------DISTANZA DA CONFRONTARE-------------*/
		x_i = inststations->xcoords[i];
		y_i = inststations->ycoords[i];
		distance = sqrt(pow(abs(x_a - x_i), 2) + pow(abs(y_a - y_i), 2));;//DISTANZA TRA STAZIONE DI PARTENZA E STAZIONE i
		gift_take = inststations->all_stations[i].get_gift_take();//PREMIO FORNITO STAZIONE DI PARTENZA
		double i_dec_val = gift_take / distance;

		printf("Decision value from my station %d and station %d is: %lf \n", start_s + 1, i + 1, i_dec_val);
			
		/*---------TROVO LA STAZIONE PIU' VICINA AL DI FUORI DEL MIO COEFFICIENTE DI SCELTA--------------------------*/
		if (((i_dec_val > user_dec_val) || (i_dec_val < decision)) && (distance < best_dist))
		{
			best_dist = distance;
			best_dist_station = i;
		}

		/*--SE L'UTENTE E' PREDISPOSTO A SPOSTARSI VERSO LA STAZIONE E SE LA STAZIONE ESAMINATA E' PIU' CONVENIENTE--*/
		if ((i_dec_val <= user_dec_val) && (i_dec_val >= decision))
		{
			best_station = i;
			decision = i_dec_val;
		}
		else
		{
			best_station = best_dist_station;
		}
	}
	start_s = best_station;
   
	printf("User %d choose start station:     %d \n", user, start_s + 1);
	return start_s;
}


/*METODO CHE SCEGLIE LA STAZIONE DI ARRIVO IN BASE A QUELLE PIENE*/
int choose_ARRIVE_station(Stations *inststations, Users *instusers, int user)
{
	int arrive_s = rand() % inststations->n_stations;
	printf("User %d would arrive to stations: %d \n", user, arrive_s + 1);

	//-----------STAZIONE A CUI VOGLIO ARRIVARE
	double x_a = inststations->xcoords[arrive_s];
	double y_a = inststations->ycoords[arrive_s];

	double x_i;
	double y_i;
	int best_station = 0;			//INDICE MIGLIOR STAZIONE SCELTA
	int best_dist_station = 0;		//INDICE MIGLIOR STAZIONE VICINA AL DI FUORI DEL MIO COEFFICIENTE DI SCELTA
	double decision = 0;			//VALORE DI DECISIONE CORRENTE
	double distance;				//DISTANZA TRA STAZIONI
	double best_dist = INFINITY;	//MIGLIOR DISTANZA
	double gift_take;				//PREMIO DATO STAZIONE i-ESIMA
	double user_dec_val = instusers->all_users[user].get_value_decision();//VALORE DECISIONE UTENTE
	int av_b = inststations->all_stations[arrive_s].av_bikes();//BICI DISPONIBILI ALLA STAZIONE SCELTA INIZIALMENTE

	for (int i = 0; i < inststations->n_stations && (av_b == 0) && (i != arrive_s); i++)//LA STAZIONE DEVE AVERE BICI DISPONIBILI
	{
		printf("User value decision: %lf \n", user_dec_val);

		/*--------------DISTANZA DA CONFRONTARE-------------*/
		x_i = inststations->xcoords[i];
		y_i = inststations->ycoords[i];
		distance = sqrt(pow(abs(x_a - x_i), 2) + pow(abs(y_a - y_i), 2));;//DISTANZA TRA STAZIONE DI PARTENZA E STAZIONE i
		gift_take = inststations->all_stations[i].get_gift_take();//PREMIO FORNITO STAZIONE DI PARTENZA
		double i_dec_val = gift_take / distance;

		printf("Decision value from my station %d and station %d is: %lf \n", arrive_s + 1, i + 1, i_dec_val);

		/*---------TROVO LA STAZIONE PIU' VICINA AL DI FUORI DEL MIO COEFFICIENTE DI SCELTA--------------------------*/
		if (((i_dec_val > user_dec_val) || (i_dec_val < decision)) && (distance < best_dist))
		{
			best_dist = distance;
			best_dist_station = i;
		}

		/*--SE L'UTENTE E' PREDISPOSTO A SPOSTARSI VERSO LA STAZIONE E SE LA STAZIONE ESAMINATA E' PIU' CONVENIENTE--*/
		if ((i_dec_val <= user_dec_val) && (i_dec_val >= decision))
		{
			best_station = i;
			decision = i_dec_val;
		}
		else
		{
			best_station = best_dist_station;
		}
	}
	arrive_s = best_station;

	printf("User %d choose start station:     %d \n", user, arrive_s + 1);
	return arrive_s;
}