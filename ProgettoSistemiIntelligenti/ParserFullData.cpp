/*-----------------PARSER DEL FILE CONTENENTE DATI ORIGINALI--------------*/


/*-----------------------------------PARSER FUNCTION------------------------------------*/
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <fstream>
#include <string>
#include "Station.h"

/*----------------------------------------METHODS---------------------------------------*/
void save_NAME_stations(Stations *inststations, Users *instusers);

/*----------------------------------COMMAND LINE PARSING--------------------------------*/
void parse_command_line_csv(int argc, char** argv, Stations *inst) {

	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-input") == 0) { strcpy(inst->input_used, argv[++i]); continue; }
	}
	printf("Input used %s\n\n", inst->input_used);
}

/*-----------------------------------READ THE INPUT-------------------------------------*/
void read_input_csv(Stations *inststations, Users *instusers) {

	FILE *input = fopen(inststations->input_used, "r");
	if (input == NULL) { printf(" input file not found!"); exit(1); }

	char line[1024];
	char *par_name;															//LINE TAKEN BY THE PARSER
	char *token1;
	char *token2;
	char *token3;
	char *token4;
	char *token5;
	char *token6;
	char *token7;
	char *token8;
	char *token9;
	char *token10;

	int data_bike = 0;													// =1 NODE_COORD_SECTION
	int n = 0;//INDEX OF DATA
	/*------------------------------------READER----------------------------------------*/
	while (fgets(line, sizeof(line), input) != NULL)
	{
		if (strlen(line) <= 1) continue;									// SKIP BLANK LINES
		par_name = strtok(line, ",");										// "," as delimiter
		//par_name = strtok(NULL, ",\" ");

		if (strncmp(par_name, "\"tripduration\"", 12) == 0)							//SKIP LINE Stations(first line of file)
		{
			instusers->n_trip = 66882;							//NUMBER OF TRIPS (LINE OF THE CVS)
			
			
			/*---------------------INIZIALIZE ALL INPUT DATA--------------------------------------*/
			instusers->tripduration =			(int*)malloc(instusers->n_trip * sizeof(int));
			instusers->start_station_name =		(char**)malloc(instusers->n_trip * sizeof(char*));
			instusers->start_station_id =		(int*)malloc(instusers->n_trip * sizeof(int));
			instusers->star_station_latitude =	(double*)malloc(instusers->n_trip * sizeof(double));
			instusers->star_station_longitude = (double*)malloc(instusers->n_trip * sizeof(double));
			instusers->end_station_id =			(int*)malloc(instusers->n_trip * sizeof(int));
			instusers->end_station_name =		(char**)malloc(instusers->n_trip * sizeof(char*));
			instusers->end_station_latitude =	(double*)malloc(instusers->n_trip * sizeof(double));
			instusers->end_station_longitude =	(double*)malloc(instusers->n_trip * sizeof(double));
			instusers->bikeid =					(int*)malloc(instusers->n_trip * sizeof(int));
			instusers->usertype =				(char**)malloc(instusers->n_trip * sizeof(char*));

			data_bike = 1;
			continue;					
		}
		if (data_bike == 1) {

			instusers->tripduration[n] = atoi(par_name);

			strtok(NULL, ",");//SKIP START DATE
			strtok(NULL, ",");//SKIP END DATE

			token1 = strtok(NULL, ",");//------------------------start_station_id
			instusers->start_station_id[n] = atoi(token1);
			
			token2 = strtok(NULL, ",\"");//----------------------start_station_name
			instusers->start_station_name[n] = (char*)malloc(150 * sizeof(char));		//ALLOCATE SPACE FOR THE STRING
			strcpy(instusers->start_station_name[n],token2);

			token3 = strtok(NULL, ",");//------------------------star_station_latitude
			instusers->star_station_latitude[n] = atof(token3); 

			token4 = strtok(NULL, ",");//------------------------star_station_longitude
			instusers->star_station_longitude[n] = atof(token4);

			token5 = strtok(NULL, ",");//------------------------end_station_id
			instusers->end_station_id[n] = atoi(token5);

			token6 = strtok(NULL, ",\"");//----------------------end_station_name
			instusers->end_station_name[n] = (char*)malloc(150 * sizeof(char));		//ALLOCATE SPACE FOR THE STRING
			strcpy(instusers->end_station_name[n], token6);

			token7 = strtok(NULL, ",");//------------------------end_station_latitude
			instusers->end_station_latitude[n] = atof(token7);

			token8 = strtok(NULL, ",");//------------------------end_station_longitude
			instusers->end_station_longitude[n] = atof(token8);

			token9 = strtok(NULL, ",");//------------------------bikeid
			instusers->bikeid[n] = atoi(token9);

			token10 = strtok(NULL, ",\"");//---------------------usertype
			instusers->usertype[n] = (char*)malloc(150 * sizeof(char));		//ALLOCATE SPACE FOR THE STRING
			strcpy(instusers->usertype[n], token10);

			if (PARSERFULLDATA > 100)
			{
				/*RICORDO CHE L'INDICE n PARTE DA 0 E NEL FILE CSV LE STAZIONI INIZIANO DALL'INDICE 2 DI RIGA*/
				printf("------------------------------------------------------------------\n");
				printf("tripduration %d: %d \n", n + 2, instusers->tripduration[n]);
				printf("start_station_id %d: %d \n", n + 2, instusers->start_station_id[n]);
				printf("start_station_name %d: %s \n", n + 2, instusers->start_station_name[n]);
				printf("star_station_latitude %d: %lf \n", n + 2, instusers->star_station_latitude[n]);
				printf("star_station_longitude %d: %lf \n", n + 2, instusers->star_station_longitude[n]);
				printf("end_station_id %d: %d \n", n + 2, instusers->end_station_id[n]);
				printf("end_station_name %d: %s \n", n + 2, instusers->end_station_name[n]);
				printf("end_station_latitude %d: %lf \n", n + 2, instusers->end_station_latitude[n]);
				printf("end_station_longitude %d: %lf \n", n + 2, instusers->end_station_longitude[n]);
				printf("bikeid %d: %d \n", n + 2, instusers->bikeid[n]);
				printf("usertype %d: %s \n", n + 2, instusers->usertype[n]);
				printf("------------------------------------------------------------------\n");
			}
			
			n++;
		}


	}
	save_NAME_stations(inststations, instusers);

	if (PARSERFULLDATA > 1)
	{
		printf("Number of stations: %d \n", inststations->n_stations);
	}

	fclose(input);
}

/*FUNCTION FOR FIND THE NUMBER OF STATIONS AND SAVE STATIONS*/
void save_NAME_stations(Stations *inststations, Users *instusers)
{
	/*----------------------ID SECTION---------------------*/
	int *temporary_id = (int*)malloc(instusers->n_trip * sizeof(int));
	/*---------------------NAME SECTION--------------------*/
	char** temporary_stations_names = (char**)malloc(instusers->n_trip * sizeof(char*));
	int *indexes_stations = (int*)malloc(instusers->n_trip * sizeof(int));
	int s = 0;												//COUNTER OF NUMBER OF STATIONS
	int finded = 0;											//FLAG FOR STATION ALREADY PRESENT

	/*--------------------START STATIONS NAME*/
	for (int i = 0; i < instusers->n_trip; i++)				//SCAN ALL TRIP
	{
		char *station_name = instusers->start_station_name[i];
		int current_id = instusers->start_station_id[i];

		for (int f = 0; f < s; f++)//FIND IF THE STATION NAME IS ALREADY PRESENT
		{
			if (strcmp(temporary_stations_names[f], station_name) == 0)
			{
				finded = 1;
			}
		}
		if (finded == 0)//SAVE THE NEW STATION
		{

			indexes_stations[s] = i;
			temporary_stations_names[s] = station_name;
			temporary_id[s] = current_id;
			s++;
		}
		finded = 0;
	}
	/*****************************************/
	/*----------------------END STATIONS NAME*/
	for (int i = 0; i < instusers->n_trip; i++)				//SCAN ALL TRIP
	{
		char *station_name = instusers->end_station_name[i];
		int current_id = instusers->end_station_id[i];

		for (int f = 0; f < s; f++)//FIND IF THE STATION NAME IS ALREADY PRESENT
		{
			if (strcmp(temporary_stations_names[f], station_name) == 0)
			{
				finded = 1;
			}
		}
		if (finded == 0)//SAVE THE NEW STATION
		{

			indexes_stations[s] = i;
			temporary_stations_names[s] = station_name;
			temporary_id[s] = current_id;
			s++;
		}
		finded = 0;
	}
	inststations->n_stations = s;							//INIZIALIZE THE NUMBER OF STATIONS

	/*----------------------------CREATE THE STATIONS COORDS-------------------------*/
	inststations->xcoords = (double *)calloc(inststations->n_stations, sizeof(double));
	inststations->ycoords = (double *)calloc(inststations->n_stations, sizeof(double));
	for (int k = 0; k < inststations->n_stations; k++)
	{
		inststations->xcoords[k] = instusers->star_station_longitude[indexes_stations[k]];
		inststations->ycoords[k] = instusers->star_station_latitude[indexes_stations[k]];
	}

	/*SAVE THE STATION NAME IN AN ARRAY WITH CORRECT DIMENSION*/
	inststations->stations_names = (char**)malloc(s * sizeof(char*));
	for (int i = 0; i < inststations->n_stations; i++) { inststations->stations_names[i] = temporary_stations_names[i]; }
	

	/*SAVE THE STATION id IN AN ARRAY WITH CORRECT DIMENSION*/
	inststations->stations_id = (int*)malloc(s * sizeof(int*));
	for (int j = 0; j < inststations->n_stations; j++){inststations->stations_id[j] = temporary_id[j];}
	

	if (PARSERFULLDATA > 50)
	{
		for (int i = 0; i < inststations->n_stations; i++)
		{
			printf("Station_%d is: %s - id: %d \n", i, inststations->stations_names[i], inststations->stations_id[i]);
		}

	}
	free(indexes_stations);
	free(temporary_stations_names);
	free(temporary_id);
}


double dist_stations(int station_i, int station_j, Stations *inststations) {

	/*-------------------------GEO DISTANCE-----------------------------*/
		double PI = 3.141592;
		double deg = (int)(inststations->xcoords[station_i]);
		double min = inststations->xcoords[station_i] - deg;
		double lati = PI * (deg + 5.0*min / 3.0) / 180.0;
		deg = (int)(inststations->ycoords[station_i]);
		min = inststations->ycoords[station_i] - deg;
		double longi = PI * (deg + 5.0*min / 3.0) / 180.0;

		deg = (int)(inststations->xcoords[station_j]);
		min = inststations->xcoords[station_j] - deg;
		double latj = PI * (deg + 5.0*min / 3.0) / 180.0;
		deg = (int)(inststations->ycoords[station_j]);
		min = inststations->ycoords[station_j] - deg;
		double longj = PI * (deg + 5.0*min / 3.0) / 180.0;

		double RRR = 6378.388;
		double q1 = cos(longi - longj);
		double q2 = cos(lati - latj);
		double q3 = cos(lati + latj);
		int dij = (int)(RRR*acos(0.5*((1.0 + q1)*q2 - (1.0 - q1)*q3)) + 1.0);
		return dij;
}