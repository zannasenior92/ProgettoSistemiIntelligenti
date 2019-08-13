#include "Station.h"
#include <string.h>

/*--METODO CHE COLORA NEL GRAFICO LA STAZIONE DI PARTENZA (SCELTA PROVVISORIAMENTE)--*/
void update_initial_start_stations(Stations *inststations, int start_s)
{
	FILE * temp = fopen("start_s.txt", "w");
	fprintf(temp, "%lf %lf %s \n", inststations->xcoords[start_s], inststations->ycoords[start_s], "PSS");  //WRITE DATA TO A TEMPORARY FILE
	fclose(temp);
	
}

/*--METODO CHE COLORA NEL GRAFICO LA STAZIONE DI PARTENZA (SCELTA DEFINITIVAMENTE)--*/
void update_choosen_start_stations(Stations *inststations, int def_start_s)
{
	FILE * temp = fopen("def_start_s.txt", "w");
	fprintf(temp, "%lf %lf %s \n", inststations->xcoords[def_start_s], inststations->ycoords[def_start_s], "DSS");  //WRITE DATA TO A TEMPORARY FILE
	fclose(temp);
	
}

/*--METODO CHE COLORA NEL GRAFICO LA STAZIONE DI ARRIVO (SCELTA PROVVISORIAMENTE)--*/
void update_initial_arrive_stations(Stations *inststations, int arrive_s)
{
	FILE * temp = fopen("arrive_s.txt", "w");
	fprintf(temp, "%lf %lf %s \n", inststations->xcoords[arrive_s], inststations->ycoords[arrive_s], "PAS");  //WRITE DATA TO A TEMPORARY FILE
	fclose(temp);
}

/*--METODO CHE COLORA NEL GRAFICO LA STAZIONE DI ARRIVO (SCELTA DEFINITIVAMENTE)--*/
void update_choosen_arrive_stations(Stations *inststations, int def_arrive_s)
{
	FILE * temp = fopen("def_arrive_s.txt", "w");
	fprintf(temp, "%lf %lf %s \n", inststations->xcoords[def_arrive_s], inststations->ycoords[def_arrive_s], "DAS");  //WRITE DATA TO A TEMPORARY FILE
	fclose(temp);
}

/*------------------METODO CHE STAMPA IL TRAGITTO FATTO DALL'UTENTE---------------------*/
void update_travel(Stations *inststations,int def_start_s,int def_arrive_s)
{
	FILE * temp = fopen("travel.txt", "w");	
	fprintf(temp, "%lf %lf %d \n", inststations->xcoords[def_start_s], inststations->ycoords[def_start_s], 6);  //WRITE DATA TO A TEMPORARY FILE
	fprintf(temp, "%lf %lf %d \n", inststations->xcoords[def_arrive_s], inststations->ycoords[def_arrive_s], 6);  //WRITE DATA TO A TEMPORARY FILE	
	fclose(temp);
	/*----------------------------------------------------------------------------------*/
}

void reset_print_transfert(Stations *inststations)
{
	/*---------------------------PRINTING POINTS IN FILE--------------------------------*/
	FILE * temp = fopen("start_s.txt", "w");
	fclose(temp);
	FILE * temp2 = fopen("def_start_s.txt", "w");
	fclose(temp2);
	FILE * temp3 = fopen("arrive_s.txt", "w");
	fclose(temp3);
	FILE * temp4 = fopen("def_arrive_s.txt", "w");
	fclose(temp4);
	FILE * temp5 = fopen("travel.txt", "w");
	fclose(temp5);
	/*----------------------------------------------------------------------------------*/
}

void update_critical_stations(Stations *inststations)
{
	FILE * crSt = fopen("critical_stations.txt", "w");
	for (int m = 0; m < inststations->n_stations; m++)
	{
		if (inststations->critical_station[m] == 1)
		{
			fprintf(crSt, "%lf %lf \n" ,inststations->xcoords[m],inststations->ycoords[m]);
		}
	}
	fclose(crSt);
}