#include "Station.h"
#include "User.h"

/*----------METODI CHE INDUCONO L'UTENTE A SCEGLIERE UNA STAZIONE PIUTTOSOT DI UN'ALTRA----*/


/*-----------INDUCE L'UTENTE A PRENDERE LA MIGLIOR STAZIONE DI PARTENZA(POTREBBE NON ESSERE QUELLA INIZIALE)--------------*/
void inductedBestStartStations(Stations *inststations, Users *instusers, int user, int start_station, int arrive_station)
{
	//----------STAZIONE DA CUI VOGLIO PARTIRE
	double x_s = inststations->xcoords[start_station];
	double y_s = inststations->ycoords[start_station];

	/*-------------------------------------------------------------------------------------------------------*/
	double x_i;
	double y_i;

	int max_bikes = inststations->all_stations[start_station].av_bikes();					//MASSIMO NUMERO DI BICI DISPONIBILI NEI DINTORNI

	for (int i = 0; i < inststations->n_stations; i++)
	{
		/*--------------COORDINATE DA CONFRONTARE-------------*/
		x_i = inststations->xcoords[i];
		y_i = inststations->ycoords[i];


		double dist_s = sqrt(pow(abs(x_s - x_i), 2) + pow(abs(y_s - y_i), 2));

		/*---------------INCREMENTO DEL PREMIO SOLO SE CI SONO PIU' BICI LIBERE NELLE VICINANZE-------------*/
		if (dist_s < 2 && (i != start_station) && (i != arrive_station) && (inststations->all_stations[i].av_bikes() > max_bikes) )
		{
			printf("Stazione di partenza %d vicina a %d con distanza %lf \n", start_station + 1, i + 1, dist_s);
			/*INSERISCO NEI PREMI DELL'UTENTE QUANTO GLI VIENE DATO SE PARTE DA UNA DELLE STAZIONI VICINE*/
			instusers->all_users[i].add_gift(i, dist_s);
		}

	}
	printf("\n");
}

/*-----------INDUCE L'UTENTE A SCEGLIERE LA MIGLIOR STAZIONE DI ARRIVO(POTREBBE NON ESSERE QUELLA INIZIALE)--------------*/
void inductedBestArriveStations(Stations *inststations, Users *instusers, int user, int start_station, int arrive_station)
{
	//-----------STAZIONE A CUI VOGLIO ARRIVARE
	double x_a = inststations->xcoords[arrive_station];
	double y_a = inststations->ycoords[arrive_station];
	/*-------------------------------------------------------------------------------------------------------*/
	//-----------COORDINATE DA CONFRONTARE
	double x_i;
	double y_i;

	int max_columns = inststations->all_stations[start_station].av_columns();					//MASSIMO NUMERO DI COLONNINE DISPONIBILI NEI DINTORNI

	for (int i = 0; i < inststations->n_stations; i++)
	{
		/*--------------COORDINATE DA CONFRONTARE-------------*/
		x_i = inststations->xcoords[i];
		y_i = inststations->ycoords[i];

		double dist_a = sqrt(pow(abs(x_a - x_i), 2) + pow(abs(y_a - y_i), 2));
		/*---------------INCREMENTO IL PREMIO SOLO SE CI SONO PIU' COLONNINE LIBERE NELLE VICINANZE----------*/
		if (dist_a < 3 && (i != arrive_station) && (i != start_station) && (inststations->all_stations[i].av_columns() > max_columns))
		{
			printf("Stazione di arrivo %d vicina a %d con distanza %lf \n", arrive_station + 1, i + 1, dist_a);
			/*INSERISCO NEI PREMI DELL'UTENTE QUANTO GLI VIENE DATO SE ARRIVA IN UNA DELLE STAZIONI VICINE*/
			instusers->all_users[user].add_gift(i, dist_a);
		}
	}
	printf("\n");

}