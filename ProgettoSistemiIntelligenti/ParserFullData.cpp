/*-----------------PARSER DEL FILE CONTENENTE DATI ORIGINALI--------------*/


/*-----------------------------------PARSER FUNCTION------------------------------------*/
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <fstream>
#include "Station.h"

/*----------------------------------COMMAND LINE PARSING--------------------------------*/
void parse_command_line_csv(int argc, char** argv, Stations *inst) {

	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-input") == 0) { strcpy(inst->input_used, argv[++i]); continue; }
	}
	printf("Input used %s\n\n", inst->input_used);
}

/*-----------------------------------READ THE INPUT-------------------------------------*/
void read_input_csv(Stations *inst, Users *instusers) {

	FILE *input = fopen(inst->input_used, "r");
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
			inst->n_stations = 200;								//NUMBER OF STATIONS (atoi = string argument to integer)
			inst->xcoords = (double *)calloc(inst->n_stations, sizeof(double));
			inst->ycoords = (double *)calloc(inst->n_stations, sizeof(double));
			
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
			printf("Number of stations: %d \n", inst->n_stations);
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
			
			token2 = strtok(NULL, ",");						//start_station_name
			instusers->start_station_name[n] = token2;
			printf("start_station_name %d: %s \n", n, instusers->start_station_name[n]);
			/*token3 = strtok(NULL, "");
			token4 = strtok(NULL, "");
			token5 = strtok(NULL, "");
			token6 = strtok(NULL, "");
			token7 = strtok(NULL, "");
			token8 = strtok(NULL, "");
			token9 = strtok(NULL, "");
			token10 = strtok(NULL, "");
			
			instusers->start_station_id;
			instusers->star_station_latitude;
			instusers->star_station_longitude;
			instusers->end_station_id;
			instusers->end_station_name;
			instusers->end_station_latitude;
			instusers->end_station_longitude;
			instusers->bikeid;
			instusers->usertype;
			*/
		
			//int i = atoi(par_name) - 1;										//FIRST COORD INDEX (-1 because indexes start from 0)
			//token1 = strtok(NULL, " ");										// x COORDINATE
			//token2 = strtok(NULL, " ");										// y COORDINATE
			//inst->xcoords[i] = atof(token1);								// COORDINATA x STAZIONE i (ISTANZA STAZIONI)
			//inst->ycoords[i] = atof(token2);								// COORDINATA y STAZIONE i (ISTANZA STAZIONI)
			
			n++;
			continue;
		}
	}

	fclose(input);
}