#include "Station.h"
#include <string.h>


/*-------------------------------GNUPLOT PLOT-------------------------------------------*/
void plot_trasfert(Stations *inststations) {

	char title[150];										//NAME FILE
	strcpy(title, "set title \"Trasferimento bici\" ");

	const char * commandsForGnuplot[] = {

		/*-------------------------PLOTTING COMMANDS TO PRINT NODES---------------------*/
		"set terminal windows",
		title,													//set title from input file
		"set output 'nodes.eps'",
		"set style line 1 \
	linecolor rgb '#0060ad' ",									//set the color line
		"unset border",											//remove the bordes
		"unset xtics",											//remove axis x
		"unset ytics",											//remove axis y
		"unset key",											//remove path legend
		"plot 'stations.txt' with labels offset char 1,-1.0 point pointtype 7 lc rgb '#0060ad' ",
		"pause 1",
		"reread"
		/*------------------------------------------------------------------------------*/
	};
	/*----------------------------------------------------------------------------------*/

	/*---------------------------PRINTING POINTS IN FILE--------------------------------*/
	FILE * temp = fopen("trasfert.txt", "w");

	for (int i = 0; i < inststations->n_stations; i++)
	{
		fprintf(temp, "%lf %lf %d \n", inststations->xcoords[i], inststations->ycoords[i], i + 1);  //WRITE DATA TO A TEMPORARY FILE
	}
	fclose(temp);
	/*----------------------------------------------------------------------------------*/

	/*--------------------NUMBER OF GNUPLOT COMMANDS------------------------------------*/
	int n_commands = sizeof(commandsForGnuplot) / sizeof(commandsForGnuplot[0]);
	if (VERBOSE > 200)
	{
		printf("Number gnuplot commands : %d \n", n_commands);
	}
	/*----------------------------------------------------------------------------------*/

	/*----------------USING A PIPE FOR GNUPLOT TO PRINT POINTS--------------------------*/
	FILE * gnuplotPipe = _popen("C:/gnuplot/bin/gnuplot.exe -persistent", "w");	//"-persistent" KEEPS THE PLOT OPEN EVEN AFTER YOUR C PROGRAM QUIT

	for (int i = 0; i < n_commands; i++)
	{
		fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);					//Send commands to gnuplot one by one.
	}
	_pclose(gnuplotPipe);
}
/*--------------------------------------------------------------------------------------*/


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
			fprintf(temp, "%lf %lf %d %s \n", inststations->xcoords[i], inststations->ycoords[i], i + 1, "red");  //WRITE DATA TO A TEMPORARY FILE
		}
		else
		{
			fprintf(temp, "%lf %lf %d %s \n", inststations->xcoords[i], inststations->ycoords[i], i + 1, "blue");  //WRITE DATA TO A TEMPORARY FILE
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
			fprintf(temp, "%lf %lf %d %s \n", inststations->xcoords[i], inststations->ycoords[i], i + 1, "green");  //WRITE DATA TO A TEMPORARY FILE
		}
		else
		{
			fprintf(temp, "%lf %lf %d %s \n", inststations->xcoords[i], inststations->ycoords[i], i + 1, "blue");  //WRITE DATA TO A TEMPORARY FILE
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
			fprintf(temp, "%lf %lf %d %s \n", inststations->xcoords[i], inststations->ycoords[i], i + 1, "red");  //WRITE DATA TO A TEMPORARY FILE
		}
		else
		{
			fprintf(temp, "%lf %lf %d %s \n", inststations->xcoords[i], inststations->ycoords[i], i + 1, "blue");  //WRITE DATA TO A TEMPORARY FILE
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
			fprintf(temp, "%lf %lf %d %s \n", inststations->xcoords[i], inststations->ycoords[i], i + 1, "green");  //WRITE DATA TO A TEMPORARY FILE
		}
		else
		{
			fprintf(temp, "%lf %lf %d %s \n", inststations->xcoords[i], inststations->ycoords[i], i + 1, "blue");  //WRITE DATA TO A TEMPORARY FILE
		}
	}
	fclose(temp);
	/*----------------------------------------------------------------------------------*/
}
