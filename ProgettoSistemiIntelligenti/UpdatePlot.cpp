#include "Station.h"
#include <string.h>

/*--METODO CHE COLORA NEL GRAFICO LA STAZIONE DI PARTENZA (SCELTA PROVVISORIAMENTE)--*/
void print_initial_start_stations(Stations *inststations, int start_s)
{
	FILE * temp = fopen("start_s.txt", "w");
	/*--------------------STAMPO IN ROSSO LA STAZIONE CHE HO SCELTO ALL'INIZIO----------*/
	fprintf(temp, "%lf %lf %s \n", inststations->xcoords[start_s], inststations->ycoords[start_s], "start");  //WRITE DATA TO A TEMPORARY FILE
	fclose(temp);
	/*----------------------------------------------------------------------------------*/
}

/*--METODO CHE COLORA NEL GRAFICO LA STAZIONE DI PARTENZA (SCELTA DEFINITIVAMENTE)--*/
void print_choosen_start_stations(Stations *inststations, int def_start_s)
{
	FILE * temp = fopen("def_start_s.txt", "w");
	/*--------------------STAMPO IN ROSSO LA STAZIONE CHE HO SCELTO ALL'INIZIO----------*/
	fprintf(temp, "%lf %lf %s \n", inststations->xcoords[def_start_s], inststations->ycoords[def_start_s], "def-start");  //WRITE DATA TO A TEMPORARY FILE
	fclose(temp);
	/*----------------------------------------------------------------------------------*/
}

/*--METODO CHE COLORA NEL GRAFICO LA STAZIONE DI ARRIVO (SCELTA PROVVISORIAMENTE)--*/
void print_initial_arrive_stations(Stations *inststations, int arrive_s)
{
	/*---------------------------PRINTING POINTS IN FILE--------------------------------*/
	FILE * temp = fopen("arrive_s.txt", "w");
	/*--------------------STAMPO IN ROSSO LA STAZIONE CHE HO SCELTO ALL'INIZIO----------*/
	fprintf(temp, "%lf %lf %s \n", inststations->xcoords[arrive_s], inststations->ycoords[arrive_s], "arrive");  //WRITE DATA TO A TEMPORARY FILE
	fclose(temp);
	/*----------------------------------------------------------------------------------*/
}

/*--METODO CHE COLORA NEL GRAFICO LA STAZIONE DI ARRIVO (SCELTA DEFINITIVAMENTE)--*/
void print_choosen_arrive_stations(Stations *inststations, int def_arrive_s)
{
	/*---------------------------PRINTING POINTS IN FILE--------------------------------*/
	FILE * temp = fopen("def_arrive_s.txt", "w");
	/*--------------------STAMPO IN ROSSO LA STAZIONE CHE HO SCELTO ALL'INIZIO----------*/
	fprintf(temp, "%lf %lf %s \n", inststations->xcoords[def_arrive_s], inststations->ycoords[def_arrive_s], "def-arrive");  //WRITE DATA TO A TEMPORARY FILE
	fclose(temp);
	/*----------------------------------------------------------------------------------*/
}

void choose_transfert(Stations *inststations,int def_start_s,int def_arrive_s)
{
	/*---------------------------PRINTING POINTS IN FILE--------------------------------*/
	FILE * temp = fopen("travel.txt", "w");
	/*--------------------STAMPO IN ROSSO LA STAZIONE CHE HO SCELTO ALL'INIZIO----------*/
	
	fprintf(temp, "%lf %lf %d \n", inststations->xcoords[def_start_s], inststations->ycoords[def_start_s], 6);  //WRITE DATA TO A TEMPORARY FILE
	fprintf(temp, "%lf %lf %d \n", inststations->xcoords[def_arrive_s], inststations->ycoords[def_arrive_s], 6);  //WRITE DATA TO A TEMPORARY FILE
	fprintf(temp, "\n");
	
	fclose(temp);
	/*----------------------------------------------------------------------------------*/
}