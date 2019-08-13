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
		"unset xtics",											//remove axis x
		"unset ytics",											//remove axis y
		"unset key",											//remove path legend
		"set pointsize 0.7",									//set size of every point in the plot
		"plot 'stations.txt' with labels offset char 1,-1.0 font 'Times,7' point pointtype 7 lc rgb '#0060ad' ",
		"exit"
		/*------------------------------------------------------------------------------*/
	};
	/*----------------------------------------------------------------------------------*/
	   
	/*--------------------NUMBER OF GNUPLOT COMMANDS------------------------------------*/
	int n_commands = sizeof(commandsForGnuplot) / sizeof(commandsForGnuplot[0]);
	if (VERBOSE > 500)
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
void refresh_plot(Stations *inststations)
{
	const char* commGnuRefresh[] = {

		"set terminal windows 1 size 1300,700",
		"set pointsize 0.7",									//set size of every point in the plot
		"plot 'trasfert.txt' with labels offset char 1,-1.0 font 'Times,7' point pointtype 7 lc rgb '#0060ad' ,\
		'start_s.txt' with labels offset char 0.5,-0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc rgb '#ad0000',\
		'def_start_s.txt' with labels offset char 0.5,0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc rgb '#65ad00',\
		'arrive_s.txt' with labels offset char 0.5,-0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc '#26D4DF',\
		'def_arrive_s.txt' with labels offset char 0.5,0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc '#F38115',\
		'travel.txt' with lp pointtype 7 lc rgb 'red' ",
		"pause 3"
	};

	/*--------------------NUMBER OF GNUPLOT COMMANDS------------------------------------*/
	int n_commands = sizeof(commGnuRefresh) / sizeof(commGnuRefresh[0]);
	if (VERBOSE > 500)
	{
		printf("Number gnuplot commands : %d \n", n_commands);
	}
	/*----------------------------------------------------------------------------------*/

	/*---------------------------PRINTING POINTS IN FILE--------------------------------*/
	FILE * temp = fopen("trasfert.txt", "w");

	for (int i = 0; i < inststations->n_stations; i++)
	{
		fprintf(temp, "%lf %lf %d \n", inststations->xcoords[i], inststations->ycoords[i], i + 1);  //WRITE DATA TO A TEMPORARY FILE
	}
	fclose(temp);
	/*----------------------------------------------------------------------------------*/

	/*----------------USING A PIPE FOR GNUPLOT TO PRINT POINTS--------------------------*/
	FILE * gnuplotPipe2 = _popen("C:/gnuplot/bin/gnuplot.exe", "w");	//"-persistent" KEEPS THE PLOT OPEN EVEN AFTER YOUR C PROGRAM QUIT

	for (int i = 0; i < n_commands; i++)
	{
		fprintf(gnuplotPipe2, "%s \n", commGnuRefresh[i]);					//Send commands to gnuplot one by one.
	}
	_pclose(gnuplotPipe2);
}
