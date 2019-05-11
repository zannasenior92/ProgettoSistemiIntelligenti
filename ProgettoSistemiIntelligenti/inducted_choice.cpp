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

	while (inststations->all_stations[start_s].av_bikes() == 0)//LA STAZIONE DEVE AVERE BICI DISPONIBILI
	{
		double x_i;
		double y_i;
		int best_station = 0;	//INDICE MIGLIOR STAZIONE SCELTA
		double decision = 0;	//VALORE DI DECISIONE CORRENTE
		double distance;		//DISTANZA TRA STAZIONI
		double gift_take;		//PREMIO DATO STAZIONE i-ESIMA
		double user_dec_val = instusers->all_users[user].get_value_decision();//VALORE DECISIONE UTENTE
		printf("User value decision: %lf \n", user_dec_val);

		for (int i = 0; i < inststations->n_stations && i != start_s; i++)
		{
			/*--------------DISTANZA DA CONFRONTARE-------------*/
			x_i = inststations->xcoords[i];
			y_i = inststations->ycoords[i];
			distance = sqrt(pow(abs(x_a - x_i), 2) + pow(abs(y_a - y_i), 2));;//DISTANZA TRA STAZIONE DI PARTENZA E STAZIONE i
			gift_take = inststations->all_stations[i].get_gift_take();//PREMIO FORNITO STAZIONE DI PARTENZA
			double i_dec_val = gift_take / distance;

			printf("Decision value from my station %d and station %d is: %lf \n", start_s, i, i_dec_val);

			/*--SE L'UTENTE E' PREDISPOSTO A SPOSTARSI VERSO LA STAZIONE E SE LA STAZIONE ESAMINATA E' PIU' CONVENIENTE--*/
			if ((i_dec_val > user_dec_val) && (i_dec_val > decision))
			{
				best_station = i;
				decision = i_dec_val;
			}
		}
		start_s = best_station;
	}   
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

	while (inststations->all_stations[arrive_s].av_columns() == 0)
	{
		double x_i;
		double y_i;
		int best_station = 0;	//INDICE MIGLIOR STAZIONE SCELTA
		double decision = 0;	//VALORE DI DECISIONE CORRENTE
		double distance;		//DISTANZA TRA STAZIONI
		double gift_take;		//PREMIO DATO STAZIONE i-ESIMA
		double user_dec_val = instusers->all_users[user].get_value_decision();//VALORE DECISIONE UTENTE
		printf("User value decision: %lf \n", user_dec_val);

		for (int i = 0; i < inststations->n_stations && i != arrive_s; i++)
		{
			/*--------------DISTANZA DA CONFRONTARE-------------*/
			x_i = inststations->xcoords[i];
			y_i = inststations->ycoords[i];
			distance = sqrt(pow(abs(x_a - x_i), 2) + pow(abs(y_a - y_i), 2));;//DISTANZA TRA STAZIONE DI PARTENZA E STAZIONE i
			gift_take = inststations->all_stations[i].get_gift_take();//PREMIO FORNITO STAZIONE DI PARTENZA
			double i_dec_val = gift_take / distance;

			printf("Decision value from my station %d and station %d is: %lf \n", arrive_s, i, i_dec_val);

			/*--SE L'UTENTE E' PREDISPOSTO A SPOSTARSI VERSO LA STAZIONE E SE LA STAZIONE ESAMINATA E' PIU' CONVENIENTE--*/
			if ((i_dec_val > user_dec_val) && (i_dec_val > decision))
			{
				best_station = i;
				decision = i_dec_val;
			}
		}
		arrive_s = best_station;
	}
	printf("User %d choose arrive station:    %d \n", user, arrive_s + 1);
	return arrive_s;
}