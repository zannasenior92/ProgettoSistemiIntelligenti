#include "Station.h"
#include <string.h>


/*--METODO CHE COLORA NEL GRAFICO LA STAZIONE DI PARTENZA (SCELTA PROVVISORIAMENTE)--*/
void print_initial_start_stations(Stations *inststations, int start_s)
{
	/*---------------------------PRINTING POINTS IN FILE--------------------------------*/
	FILE * temp = fopen("trasfert.txt", "w");
	/*--------------------STAMPO IN ROSSO LA STAZIONE CHE HO SCELTO ALL'INIZIO----------*/
	for (int i = 0; i < inststations->n_stations; i++)
	{
		if (i == start_s)
		{
			fprintf(temp, "%lf %lf %d \n", inststations->xcoords[i], inststations->ycoords[i], 2);  //WRITE DATA TO A TEMPORARY FILE
		}
		else
		{
			fprintf(temp, "%lf %lf %d \n", inststations->xcoords[i], inststations->ycoords[i], 1);  //WRITE DATA TO A TEMPORARY FILE
		}
	}
	fclose(temp);
	/*----------------------------------------------------------------------------------*/
}

/*--METODO CHE COLORA NEL GRAFICO LA STAZIONE DI PARTENZA (SCELTA DEFINITIVAMENTE)--*/
void print_choosen_start_stations(Stations *inststations, int def_start_s)
{
	/*---------------------------PRINTING POINTS IN FILE--------------------------------*/
	FILE * temp = fopen("trasfert.txt", "w");
	/*--------------------STAMPO IN ROSSO LA STAZIONE CHE HO SCELTO ALL'INIZIO----------*/
	for (int i = 0; i < inststations->n_stations; i++)
	{
		if (i == def_start_s)
		{
			fprintf(temp, "%lf %lf %d \n", inststations->xcoords[i], inststations->ycoords[i], 4);  //WRITE DATA TO A TEMPORARY FILE
		}
		else
		{
			fprintf(temp, "%lf %lf %d \n", inststations->xcoords[i], inststations->ycoords[i], 1);  //WRITE DATA TO A TEMPORARY FILE
		}
	}
	fclose(temp);
	/*----------------------------------------------------------------------------------*/
}

/*--METODO CHE COLORA NEL GRAFICO LA STAZIONE DI ARRIVO (SCELTA PROVVISORIAMENTE)--*/
void print_initial_arrive_stations(Stations *inststations, int arrive_s)
{
	/*---------------------------PRINTING POINTS IN FILE--------------------------------*/
	FILE * temp = fopen("trasfert.txt", "w");
	/*--------------------STAMPO IN ROSSO LA STAZIONE CHE HO SCELTO ALL'INIZIO----------*/
	for (int i = 0; i < inststations->n_stations; i++)
	{
		if (i == arrive_s)
		{
			fprintf(temp, "%lf %lf %d \n", inststations->xcoords[i], inststations->ycoords[i], 5);  //WRITE DATA TO A TEMPORARY FILE
		}
		else
		{
			fprintf(temp, "%lf %lf %d \n", inststations->xcoords[i], inststations->ycoords[i], 1);  //WRITE DATA TO A TEMPORARY FILE
		}
	}
	fclose(temp);
	/*----------------------------------------------------------------------------------*/
}

/*--METODO CHE COLORA NEL GRAFICO LA STAZIONE DI ARRIVO (SCELTA DEFINITIVAMENTE)--*/
void print_choosen_arrive_stations(Stations *inststations, int def_arrive_s)
{
	/*---------------------------PRINTING POINTS IN FILE--------------------------------*/
	FILE * temp = fopen("trasfert.txt", "w");
	/*--------------------STAMPO IN ROSSO LA STAZIONE CHE HO SCELTO ALL'INIZIO----------*/
	for (int i = 0; i < inststations->n_stations; i++)
	{
		if (i == def_arrive_s)
		{
			fprintf(temp, "%lf %lf %d \n", inststations->xcoords[i], inststations->ycoords[i], 6);  //WRITE DATA TO A TEMPORARY FILE
		}
		else
		{
			fprintf(temp, "%lf %lf %d \n", inststations->xcoords[i], inststations->ycoords[i], 1);  //WRITE DATA TO A TEMPORARY FILE
		}
	}
	fclose(temp);
	/*----------------------------------------------------------------------------------*/
}
