/*-----------------PARSER DEL FILE CONTENENTE DATI ORIGINALI--------------*/


/*-----------------------------------PARSER FUNCTION------------------------------------*/
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <fstream>
#include <string>
#include "Station.h"

/*----------------------------------------METHODS---------------------------------------*/
void save_stations(Stations *inststations, Users *instusers);


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
			instusers->n_trip = 18303;							//NUMBER OF TRIPS (LINE OF THE CVS)
			
			
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
			printf("tripduration %d: %d \n", n, instusers->tripduration[n]);

			strtok(NULL, ",");//SKIP START DATE
			strtok(NULL, ",");//SKIP END DATE

			token1 = strtok(NULL, ",");						//start_station_id
			instusers->start_station_id[n] = atoi(token1);
			printf("start_station_id %d: %d \n", n, instusers->start_station_id[n]);
			
			token2 = strtok(NULL, ",\"");						//start_station_name
			instusers->start_station_name[n] = token2;
			printf("start_station_name %d: %s \n", n, instusers->start_station_name[n]);
			
			token3 = strtok(NULL, ",");
			instusers->star_station_latitude[n] = atof(token3); 
			printf("star_station_latitude %d: %lf \n", n, instusers->star_station_latitude[n]);

			token4 = strtok(NULL, ",");
			instusers->star_station_longitude[n] = atof(token4);
			printf("star_station_longitude %d: %lf \n", n, instusers->star_station_longitude[n]);

			token5 = strtok(NULL, ",");
			instusers->end_station_id[n] = atoi(token5);
			printf("end_station_id %d: %d \n", n, instusers->end_station_id[n]);

			token6 = strtok(NULL, ",\"");
			instusers->end_station_name[n] = token6;
			printf("end_station_name %d: %s \n", n, instusers->end_station_name[n]);

			token7 = strtok(NULL, ",");
			instusers->end_station_latitude[n] = atof(token7);
			printf("end_station_latitude %d: %lf \n", n, instusers->end_station_latitude[n]);

			token8 = strtok(NULL, ",");
			instusers->end_station_longitude[n] = atof(token8);
			printf("end_station_longitude %d: %lf \n", n, instusers->end_station_longitude[n]);

			token9 = strtok(NULL, ",");
			instusers->bikeid[n] = atoi(token9);
			printf("bikeid %d: %d \n", n, instusers->bikeid[n]);

			token10 = strtok(NULL, ",\"");
			instusers->usertype[n] = token10;
			printf("usertype %d: %s \n", n, instusers->usertype[n]);

			printf("------------------------------------------------------------------\n");
			
			n++;
			continue;
		}


	}
	save_stations(inststations, instusers);
	printf("Number of stations: %d \n", inststations->n_stations);

	fclose(input);
}

/*FUNCTION FOR FIND THE NUMBER OF STATIONS AND SAVE STATIONS*/
void save_stations(Stations *inststations, Users *instusers)
{
	char** temporary_stations_names = (char**)malloc(instusers->n_trip * sizeof(char*));
	int *indexes_stations = (int*)malloc(instusers->n_trip * sizeof(int));
	int s = 0;												//COUNTER OF NUMBER OF STATIONS
	int finded = 0;											//FLAG FOR STATION ALREADY PRESENT
	for (int i = 0; i < instusers->n_trip; i++)				//SCAN ALL TRIP
	{
		char *station_name = instusers->start_station_name[i];

		for (int f = 0; f < s; f++)//FIND IF THE STATION NAME IS ALREADY PRESENT
		{
			if (strcmp(temporary_stations_names[f],station_name) == 0)
			{
				printf("%d\n",i);

				finded = 1;
			}
		}
		if (finded == 0)//SAVE THE NEW STATION
		{

			indexes_stations[s] = i;
			temporary_stations_names[s] = station_name;
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
		inststations->xcoords[k] = instusers->star_station_latitude[indexes_stations[k]];
		inststations->ycoords[k] = instusers->star_station_longitude[indexes_stations[k]];
	}

	/*SAVE THE STATION IN AN ARRAY WITH CORRECT DIMENSION*/
	inststations->stations_names = (char**)malloc(s * sizeof(char*));
	inststations->stations_names = temporary_stations_names;

	free(indexes_stations);
	free(temporary_stations_names);
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