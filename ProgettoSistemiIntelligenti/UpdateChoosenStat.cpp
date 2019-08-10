#include "Station.h"
#include <string.h>

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

void print_transfert(Stations *inststations,int def_start_s,int def_arrive_s)
{
	/*---------------------------PRINTING POINTS IN FILE--------------------------------*/
	FILE * temp = fopen("trasfert2.txt", "w");
	/*--------------------STAMPO IN ROSSO LA STAZIONE CHE HO SCELTO ALL'INIZIO----------*/
	
	fprintf(temp, "%lf %lf %d \n", inststations->xcoords[def_start_s], inststations->ycoords[def_start_s], 6);  //WRITE DATA TO A TEMPORARY FILE
	fprintf(temp, "%lf %lf %d \n", inststations->xcoords[def_arrive_s], inststations->ycoords[def_arrive_s], 6);  //WRITE DATA TO A TEMPORARY FILE
	fprintf(temp, "\n");
	
	fclose(temp);
	/*----------------------------------------------------------------------------------*/
}