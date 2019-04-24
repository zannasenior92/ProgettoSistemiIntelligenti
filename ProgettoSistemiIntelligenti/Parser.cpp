/*--------------------PARSER PER INCLUDERE I DATI DELLE STAZIONI------------------*/

/*-----------------------------------PARSER FUNCTION------------------------------------*/
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <fstream>
#include "Station.h"

/*----------------------------------COMMAND LINE PARSING--------------------------------*/
void parse_command_line(int argc, char** argv, Stations *inst) {
	
	for (int i = 0; i < argc; i++) 
	{
		if (strcmp(argv[i], "-input") == 0) { strcpy(inst->input_used, argv[++i]); continue; }
	}
	printf("Input used %s\n\n", inst->input_used);
}

/*-----------------------------------READ THE INPUT-------------------------------------*/
void read_input(Stations *inst) {
	
	FILE *input = fopen(inst->input_used, "r");
	if (input == NULL) { printf(" input file not found!"); exit(1); }

	char line[180];
	char *par_name;															//LINE TAKEN BY THE PARSER
	char *token1;
	char *token2;
	int coord_section = 0;													// =1 NODE_COORD_SECTION
	
	/*------------------------------------READER----------------------------------------*/
	while (fgets(line, sizeof(line), input) != NULL)
	{
		

		if (strlen(line) <= 1) continue;									// SKIP BLANK LINES
		par_name = strtok(line, " :");										// " :" as delimiter
		if (strncmp(line, "Stations", 8) == 0) continue;					//SKIP LINE Stations(first line of file)
		if (strncmp(par_name, "NAME", 4) == 0)
		{
			token1 = strtok(NULL, " :");
			strcpy(inst->name, token1);
			continue;
		}
		if (strncmp(par_name, "DIMENSION", 9) == 0)
		{
			token1 = strtok(NULL, " :");									//NULL gives the following word
			inst->n_stations = atoi(token1);								//NUMBER OF STATIONS (atoi = string argument to integer)
			inst->xcoords = (double *)calloc(inst->n_stations, sizeof(double));
			inst->ycoords = (double *)calloc(inst->n_stations, sizeof(double));

			printf("Number of stations: %d \n", inst->n_stations);
			continue;
		}


		if (strncmp(par_name, "NODE_COORD_SECTION", 18) == 0)				//COORD SECTION
		{
			if (inst->n_stations <= 0) { printf(" DIMENSION section should appear before NODE_COORD_SECTION section"); exit(1); }
			coord_section = 1;
			continue;
		}
		if (strncmp(par_name, "EOF", 3) == 0)								//END OF FILE
		{
			coord_section = 0;
			break;
		}
		if (coord_section == 1) {
			int i = atoi(par_name) - 1;										//FIRST COORD INDEX (-1 because indexes start from 0)
			token1 = strtok(NULL, " ");										// x COORDINATE
			token2 = strtok(NULL, " ");										// y COORDINATE
			inst->xcoords[i] = atof(token1);								// COORDINATA x STAZIONE i (ISTANZA STAZIONI)
			inst->ycoords[i] = atof(token2);								// COORDINATA y STAZIONE i (ISTANZA STAZIONI)
			continue;
		}
	}
	
	fclose(input);
}