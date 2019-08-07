#include "Station.h"
#include <string.h>


/*-------------------------------GNUPLOT PLOT-------------------------------------------*/
void plot_gnuplot(Stations *inststations) {

	char title[150];										//NAME FILE
	strcpy(title, "set title \"Punti Stazioni\" ");

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
		"exit"
		/*------------------------------------------------------------------------------*/
	};
	/*----------------------------------------------------------------------------------*/
	   
	/*--------------------NUMBER OF GNUPLOT COMMANDS------------------------------------*/
	int n_commands = sizeof(commandsForGnuplot) / sizeof(commandsForGnuplot[0]);
	if (VERBOSE > 200)
	{
		printf("Number gnuplot commands : %d \n", n_commands);
	}
	/*----------------------------------------------------------------------------------*/


	/*---------------------------PRINTING POINTS IN FILE--------------------------------*/
	FILE * temp = fopen("stations.txt", "w");

	for (int i = 0; i < inststations->n_stations; i++)
	{
		fprintf(temp, "%lf %lf %d \n", inststations->xcoords[i], inststations->ycoords[i], i + 1);  //WRITE DATA TO A TEMPORARY FILE
	}
	fclose(temp);
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


/*--------------------------------METHOD TO REFRESH GNUPLOT GRAPH-----------------------*/
void refresh_plot(Stations *inst)
{
	const char* commGnuRefresh[] = {

		"plot 'stations.txt' with labels offset char 1,-1.0 point pointtype 7 lc rgb '#0060ad' ",
		"pause 1",
		"reread"
	};
}