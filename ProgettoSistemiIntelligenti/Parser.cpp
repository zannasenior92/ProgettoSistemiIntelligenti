/*--------------------PARSER PER INCLUDERE I DATI DELLE STAZIONI------------------*/

/*-----------------------------------PARSER FUNCTION------------------------------------*/
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "Station.h"


char input_file[1000];
/*----------------------------------COMMAND LINE PARSING--------------------------------*/
void parse_command_line(int argc, char** argv) {

	for (int i = 0; i < argc; i++) 
	{
		if (strcmp(argv[i], "-input") == 0) { strcpy(input_file, argv[++i]); continue; }
	}
}

/*-----------------------------------READ THE INPUT-------------------------------------*/
void read_input(char file) {

	FILE *input = fopen(file, "r");
	if (input == NULL) { printf(" input file not found!"); exit(1); }

	char line[180];
	char *par_name;															//LINE TAKEN BY THE PARSER
	char *token1;
	char *token2;
	int coord_section = 0;													// =1 NODE_COORD_SECTION

	/*------------------------------------READER----------------------------------------*/
	while(fgets(line, sizeof(line), input) != NULL)
	{

		if (strlen(line) <= 1) continue;									// SKIP BLANK LINES
		par_name = strtok(line, " :");										// " :" as delimiter

		if (VERBOSE >= 300)
		{
			printf("par_name= %s \n", par_name);
		}

		if (strncmp(par_name, "STAT_COORD", 10) == 0)
		{
			continue;
		}

		/*---------------SELECT THE RIGHT TYPE DISTANCE--------------------*/
	
		if (strncmp(par_name, "EOF", 3) == 0)								//END OF FILE
		{
			coord_section = 0;
			break;
		}
		if (coord_section == 1) {
			int i = atoi(par_name) - 1;										//FIRST COORD INDEX (-1 because indexes start from 0)
			token1 = strtok(NULL, " ");										// x COORDINATE
			token2 = strtok(NULL, " ");										// y COORDINATE
			inst->xcoord[i] = atof(token1);
			inst->ycoord[i] = atof(token2);
			continue;
		}
	}
}