
#pragma warning(suppress : 4996)

#ifndef station_h
#define station_h
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>  

#define VERBOSE 50

/*------------------------------------------------STAZIONE BICI-----------------------------------*/
class Station_i
{
public:
	/*-------------------DEFINISCO N° BICI E N° COLONNINE------------------------*/
	Station_i(int b, int c)
	{
		this->available_bikes = b;
		this->columns = c;
		this->free_columns = this->columns - this->available_bikes;
		this->reserve_up_col = new int[free_columns];
		for (int i = 0; i < free_columns; i++)									//AZZERA LE COLONNINE LIBERE PRENOTATE
		{
			reserve_up_col[i] = 0;
		}
	}
	/*-------------------------------------METHODS---------------------------*/
	void remove_bike();															//RIMUOVE UNA BICI DALLA STAZIONE
	void reserve_col(int i);
	void add_bike();															//AGGIUNGE UNA BICI ALLA STAZIONE
	void set_money(double val);													//SETTA LA MONETA OFFERTA DALLA STAZIONE
	int n_bikes();																//MI RESTITUISCE IL NUMERO DI BICI
	int av_columns();															//RESTITUISCE N° COLONNINE LIBERE
	double g_m_r();																//RESTITUISCE PREMIO PER LA STAZIONE DI PARTENZA
	double g_m_t();																//RESTITUISCE PREMIO PER LA STAZIONE DI RILASCIO
	double get_x_coord();														//RESTITUISCE LA COORDINATA x
	double get_y_coord();														//RESTITUISCE LA COORDINATA y
	

/*---------------------------------PRIVATE VARIABLES-------------------------*/
private:
	double gift_money_release;													//PREMIO SCELTA STAZIONE PARTENZA
	double gift_money_take;														//PREMIO SCELTA STAZIONE RILASCIO
	int columns;																//COLONNINE TOTALI
	int available_bikes;														//BICI DISPONIBILI
	int free_columns;															//NUMERO COLONNINE LIBERE
	int *reserve_up_col;														//ARRAY COLONNINA LIBERA PRENOTATO
	double xcoord;																//COORDINATA x
	double ycoord;																//COORDINATA y
};
/**************************************************************************************************/

																
/*-------------------------------------CLASSE CHE GESTISCE LE STAZIONI----------------------------*/
class Stations
{
public:
	
	/*----------------------------PUBLIC VARIABLES---------------------------*/
	char input_used[200];
	char name[20];																//NAME OF FILE USED
	int n_stations;																//NUMERO STAZIONI
	double *xcoords;															//COORDINATE x STAZIONI
	double *ycoords;															//COORDINATE y STAZIONI
	int num_bikes;																//NUMERO TOTALE BICI PRESENTI
	int num_columns;															//NUMERO TOTALE COLONNINE
	Station_i* all_stations;


	/*-------------------------------------METHODS---------------------------*/
	int n_stat();																//RESTITUISCO IL NUMERO DI STAZIONI PRESENTI
	void set_n_stations(int num);												//SETTO IL NUMERO DI STAZIONI PRESENTI 
	void set_n_columns_for_station(int n_c);									//SETTO IL NUMERO DI COLONNE PER OGNI STAZIONE
	void set_n_bikes_for_stations(int n_b);										//SETTO IL NUMERO DI BICI PER OGNI STAZIONE

private:
	
};

/*---------------------PARAMETRI CHE POSSONO CAMBIARE----------------------------*/
#endif // !station_h
