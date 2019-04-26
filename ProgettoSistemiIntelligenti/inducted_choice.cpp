#include "Station.h"
#include "User.h"


#define RADIUS 3	//RAGGIO ENTRO CUI AUMENTARE IL BUDGET(posso modificarlo per vedere come cambia la situazione)

/*------------------------METODI CHE INDUCONO L'UTENTE A SCEGLIERE UNA STAZIONE PIUTTOSOT DI UN'ALTRA---------------------------*/


/*-----------INDUCE L'UTENTE A PRENDERE LA MIGLIOR STAZIONE DI PARTENZA(POTREBBE NON ESSERE QUELLA INIZIALE)--------------*/
void inductedBestStartStations(Stations *inststations, Users *instusers, int user, int start_station, int arrive_station)
{
	/*RESETTO A ZERO TUTTE I GIFT AGGIUNTIVI DELL'UTENTE BASATI SULLA DISTANZA*/
	instusers->all_users[user].clear_added_gift(inststations->n_stations);

	//----------STAZIONE DA CUI VOGLIO PARTIRE
	double x_s = inststations->xcoords[start_station];
	double y_s = inststations->ycoords[start_station];

	printf("Bikes available at station   %d = %d bikes \n", start_station + 1, inststations->all_stations[start_station].av_bikes());
	/*-------------------------------------------------------------------------------------------------------*/
	double x_i;
	double y_i;

	int start_bikes = inststations->all_stations[start_station].av_bikes();					//MASSIMO NUMERO DI BICI DISPONIBILI NEI DINTORNI

	for (int i = 0; i < inststations->n_stations; i++)
	{
		/*--------------COORDINATE DA CONFRONTARE-------------*/
		x_i = inststations->xcoords[i];
		y_i = inststations->ycoords[i];


		double dist_s = sqrt(pow(abs(x_s - x_i), 2) + pow(abs(y_s - y_i), 2));

		/*---------------INCREMENTO DEL PREMIO SOLO SE CI SONO PIU' BICI LIBERE NELLE VICINANZE-------------*/
		if (dist_s < RADIUS && (i != start_station) && (i != arrive_station) && (inststations->all_stations[i].av_bikes() > start_bikes) )
		{
			printf("Near start station %d has %d bikes \n", i + 1, inststations->all_stations[i].av_bikes());
			/*INSERISCO NEI PREMI DELL'UTENTE QUANTO GLI VIENE DATO SE PARTE DA UNA DELLE STAZIONI VICINE*/
			instusers->all_users[user].add_gift(i, dist_s);

			if (VERBOSE > 200)
			{
				printf("Distance from start station %d to %d = %lf \n", start_station + 1, i + 1, dist_s);
			}
			printf("Money added station %d = %lf \n", i + 1, instusers->all_users[user].get_added_gift(i));
		}

	}
	printf("\n");
}

/*-----------INDUCE L'UTENTE A SCEGLIERE LA MIGLIOR STAZIONE DI ARRIVO(POTREBBE NON ESSERE QUELLA INIZIALE)--------------*/
void inductedBestArriveStations(Stations *inststations, Users *instusers, int user, int start_station, int arrive_station)
{
	/*RESETTO A ZERO TUTTE I GIFT AGGIUNTIVI DELL'UTENTE BASATI SULLA DISTANZA*/
	instusers->all_users[user].clear_added_gift(inststations->n_stations);

	//-----------STAZIONE A CUI VOGLIO ARRIVARE
	double x_a = inststations->xcoords[arrive_station];
	double y_a = inststations->ycoords[arrive_station];

	printf("Columns available at station %d = %d columns \n", arrive_station + 1, inststations->all_stations[arrive_station].av_columns());
	/*-------------------------------------------------------------------------------------------------------*/

	double x_i;
	double y_i;

	int arrive_columns = inststations->all_stations[arrive_station].av_columns();					//MASSIMO NUMERO DI COLONNINE DISPONIBILI NEI DINTORNI

	for (int i = 0; i < inststations->n_stations; i++)
	{
		/*--------------COORDINATE DA CONFRONTARE-------------*/
		x_i = inststations->xcoords[i];
		y_i = inststations->ycoords[i];

		double dist_a = sqrt(pow(abs(x_a - x_i), 2) + pow(abs(y_a - y_i), 2));
		/*---------------INCREMENTO IL PREMIO SOLO SE CI SONO PIU' COLONNINE LIBERE NELLE VICINANZE----------*/
		if (dist_a < RADIUS && (i != arrive_station) && (i != start_station) && (inststations->all_stations[i].av_columns() > arrive_columns))
		{
			printf("Near arrive station %d has %d columns \n", i + 1, inststations->all_stations[i].av_columns());
			/*INSERISCO NEI PREMI DELL'UTENTE QUANTO GLI VIENE DATO SE ARRIVA IN UNA DELLE STAZIONI VICINE*/
			instusers->all_users[user].add_gift(i, dist_a);
			
			if (VERBOSE > 200)
			{
				printf("Distance from arrive station %d to %d = %lf \n", arrive_station + 1, i + 1, dist_a);
			}
			printf("Money added station %d = %lf \n", i + 1, instusers->all_users[user].get_added_gift(i));
		}
	}
	printf("\n");
}
