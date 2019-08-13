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

void reset_plot(FILE *gnuplotPipe2)
{
	fprintf(gnuplotPipe2, "%s \n", "plot 'stations.txt' title 'Stations' with labels offset char 1,-1.0 font 'Times,7' point pointtype 7 lc rgb '#0060ad'");
	fprintf(gnuplotPipe2, "%s \n", "pause 1");
}

void print_start(FILE *gnuplotPipe2)
{
	fprintf(gnuplotPipe2, "%s \n", "plot 'stations.txt' title 'Stations' with labels offset char 1,-1.0 font 'Times,7' point pointtype 7 lc rgb '#0060ad',\
		'start_s.txt' title 'ProvvStartStat' with labels offset char 0.5,-0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc rgb '#ad0000'");
	fprintf(gnuplotPipe2, "%s \n", "pause 1");
}

void print_def_start(FILE *gnuplotPipe2)
{
	fprintf(gnuplotPipe2, "%s \n", "plot 'stations.txt' title 'Stations' with labels offset char 1,-1.0 font 'Times,7' point pointtype 7 lc rgb '#0060ad',\
		'start_s.txt' title 'ProvvStartStat' with labels offset char 0.5,-0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc rgb '#ad0000',\
		'def_start_s.txt' title 'DefStartStat' with labels offset char 0.5,0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc rgb '#65ad00'");
	fprintf(gnuplotPipe2, "%s \n", "pause 1");
}

void print_arrive(FILE *gnuplotPipe2)
{
	fprintf(gnuplotPipe2, "%s \n", "plot 'stations.txt' title 'Stations' with labels offset char 1,-1.0 font 'Times,7' point pointtype 7 lc rgb '#0060ad',\
		'start_s.txt' title 'ProvvStartStat' with labels offset char 0.5,-0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc rgb '#ad0000',\
		'def_start_s.txt' title 'DefStartStat' with labels offset char 0.5,0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc rgb '#65ad00',\
		'arrive_s.txt' title 'ProvvArriveStat' with labels offset char 0.5,-0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc '#26D4DF'");
	fprintf(gnuplotPipe2, "%s \n", "pause 1");
}

void print_def_arrive(FILE *gnuplotPipe2)
{
	fprintf(gnuplotPipe2, "%s \n", "plot 'stations.txt' title 'Stations' with labels offset char 1,-1.0 font 'Times,7' point pointtype 7 lc rgb '#0060ad',\
		'start_s.txt' title 'ProvvStartStat' with labels offset char 0.5,-0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc rgb '#ad0000',\
		'def_start_s.txt' title 'DefStartStat' with labels offset char 0.5,0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc rgb '#65ad00',\
		'arrive_s.txt' title 'ProvvArriveStat' with labels offset char 0.5,-0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc '#26D4DF',\
		'def_arrive_s.txt' title 'DefArriveStat' with labels offset char 0.5,0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc '#F38115'");
	fprintf(gnuplotPipe2, "%s \n", "pause 1");
}

void print_travel(FILE *gnuplotPipe2)
{
	fprintf(gnuplotPipe2, "%s \n", "plot 'stations.txt' title 'Stations' with labels offset char 1,-1.0 font 'Times,7' point pointtype 7 lc rgb '#0060ad',\
		'start_s.txt' title 'ProvvStartStat' with labels offset char 0.5,-0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc rgb '#ad0000',\
		'def_start_s.txt' title 'DefStartStat' with labels offset char 0.5,0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc rgb '#65ad00',\
		'arrive_s.txt' title 'ProvvArriveStat' with labels offset char 0.5,-0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc '#26D4DF',\
		'def_arrive_s.txt' title 'DefArriveStat' with labels offset char 0.5,0.5 font 'Times Bold,12' point pointtype 7 pointsize 1 lc '#F38115',\
		'travel.txt' title 'Travel' with lp pointtype 7 lc rgb 'red' ");
	fprintf(gnuplotPipe2, "%s \n", "pause 1");
}

void print_money_in_system(Stations *inststations, int number_of_transition)
{

	char title[150];										//NAME FILE
	strcpy(title, "set title \"Andamento Moneta Disponibile\" ");

	const char * commandsForGnuplot[] = {

		/*-------------------------PLOTTING COMMANDS TO PRINT NODES---------------------*/
		"set terminal windows 3",
		title,													//set title from input file
		"unset key",											//remove path legend
		"set style line 1 lc rgb '#0060ad'",
		"plot 'money.txt' with lines",
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

	/*--FUNZIONE CHE STAMPA SU FILE I SOLDI CHE CI SONO NEL SISTEMA--*/
	FILE * money_in_sy = fopen("money.txt", "w");
	for (int i = 0; i < number_of_transition; i++)
	{
		fprintf(money_in_sy, "%lf \n", inststations->money_in_the_system[i]);
	}
	fclose(money_in_sy);


	/*----------------USING A PIPE FOR GNUPLOT TO PRINT POINTS--------------------------*/
	FILE * gnuplotPipe = _popen("C:/gnuplot/bin/gnuplot.exe -persistent", "w");	//"-persistent" KEEPS THE PLOT OPEN EVEN AFTER YOUR C PROGRAM QUIT

	for (int i = 0; i < n_commands; i++)
	{
		fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);					//Send commands to gnuplot one by one.
	}
	_pclose(gnuplotPipe);
}