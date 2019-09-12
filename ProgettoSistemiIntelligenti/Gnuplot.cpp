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
		"plot 'stations.txt' with labels offset char 1,-1.0 font 'Times,9' point pointtype 7 lc rgb '#0060ad' ",
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
		fprintf(temp, "%lf %lf %d \n", inststations->xcoords[i], inststations->ycoords[i], inststations->stations_id[i]);  //WRITE DATA TO A TEMPORARY FILE
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
		"set terminal wxt 3",
		title,													//set title from input file
		"unset key",											//remove path legend
		"set ylabel 'Amount of Budget'",
		"set xlabel 'Trips'",
		"set yrange [22000:25000]"
		"set xrange [0:2000]",
		"plot 'money.txt' with lines lc rgb '#000dff'",
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

void print_satisfactions(Users *instusers)
{
	char title[150];										//NAME FILE
	strcpy(title, "set title \"Soddisfazione Utenti\" ");

	const char * commandsForGnuplot[] = {

		/*-------------------------PLOTTING COMMANDS TO PRINT NODES---------------------*/
		"set terminal wxt 4",
		title,													//set title from input file
		"unset key",											//remove path legend
		"set xlabel 'Users'",
		"set ylabel 'Satisfaction Value'",
		"plot 'satisfactions.txt' with boxes lc rgb '#00aaff',\
		'mean_sat.txt' with lines lw 2 lc rgb '#ff0000'",
		"pause 4",
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
	FILE * satisfactions = fopen("satisfactions.txt", "w");
	for (int user = 0; user < instusers->n_users; user++)
	{
		fprintf(satisfactions, "%lf \n", instusers->all_users[user].get_satisfaction());
	}
	fclose(satisfactions);

	FILE * mean_satisfaction = fopen("mean_sat.txt", "w");
	double mean_sat = 0;//MEDIA SODDISFAZIONE
	double sum_sat = 0;//SOMMA SODDISFAZIONI UTENTI
	for (int user = 0; user < instusers->n_users; user++)
	{
		sum_sat = sum_sat + instusers->all_users[user].get_satisfaction();
	}

	mean_sat = sum_sat / instusers->n_users;

	for (int user = 0; user < instusers->n_users; user++)
	{
		fprintf(mean_satisfaction, "%lf \n", mean_sat);
	}
	fclose(mean_satisfaction);

	FILE *gnuplotPipe3 = _popen("C:/gnuplot/bin/gnuplot.exe -persistent", "w");	//"-persistent" KEEPS THE PLOT OPEN EVEN AFTER YOUR C PROGRAM QUIT
	for (int i = 0; i < n_commands; i++)
	{
		fprintf(gnuplotPipe3, "%s \n", commandsForGnuplot[i]);					//Send commands to gnuplot one by one.
	}
	_pclose(gnuplotPipe3);

}