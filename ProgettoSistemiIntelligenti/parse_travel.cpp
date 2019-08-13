#include "Station.h"
#include "User.h"

/*--FUNZIONE PER TROVARE L'INDICE DELLA STAZIONE DI PARTENZA ALL'INTERNO DELL'ARRAY DELLE STAZIONI SALVATE--*/
int parse_travel_start_station_index(Stations *inststations, Users *instusers, int index_row_csv)
{
	int start_station_index;

	/*--------------------START STATIONS NAME*/
	char *station_name = instusers->start_station_name[index_row_csv];

	for (int f = 0; f < inststations->n_stations; f++)//FIND IF THE STATION NAME IS ALREADY PRESENT
	{
		if (strcmp(inststations->stations_names[f], station_name) == 0)
		{
			start_station_index = f; //SALVO L'INDICE CHE HA LA STAZIONE ALL'INTERNO DELL'ARRAY DELLE STAZIONI 
			return start_station_index;
		}
	}
	return NULL;
}

int parse_travel_end_station_index(Stations *inststations, Users *instusers, int index_row_csv)
{
	int end_station_index;

	/*--------------------ARRIVE STATIONS NAME*/
	char *station_name = instusers->end_station_name[index_row_csv];

	for (int f = 0; f < inststations->n_stations; f++)
	{
		if (strcmp(inststations->stations_names[f], station_name) == 0)
		{
			end_station_index = f; //SALVO L'INDICE CHE HA LA STAZIONE ALL'INTERNO DELL'ARRAY DELLE STAZIONI 
			return end_station_index;
		}
	}
	return NULL;
}