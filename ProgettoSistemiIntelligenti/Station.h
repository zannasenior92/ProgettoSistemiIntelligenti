
#pragma warning(suppress : 4996)

#ifndef station_h
#define station_h
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <stdio.h> 
#include "User.h"

#define VERBOSE 300
#define	GNUPLOT 50
#define USERH 50
#define USERCPP 50
#define STATIONH 50
#define STATIONCPP 50
#define PARSER 50
#define	PARSERFULLDATA 50
#define CRITICALSTATIONS 50
#define UPDATEPRICES 50
#define INDUCTEDCHOICE 50
#define LIVESYSTEM 50
#define MAINPROGRAM 50
#define SUBSCRIPTION 25															//SOLDI ABBONAMENTO

/*------------------------------------------------STAZIONE BICI-----------------------------------*/
class Station_i
{
public:
	/*-------------------DEFINISCO N° BICI E N° COLONNINE------------------------*/
	Station_i(int b, int c)
	{
		this->available_bikes = b;
		this->columns = c;
		this->free_columns = abs(this->columns - this->available_bikes);

		this->gift_money_take = 0;												//ALL'INIZIO NON VIENE DATA MONETA-STAZIONE PARTENZA(5 BICI E 5 COLONNINE LIBERE)
		this->gift_money_release = 0;											//ALL'INIZIO NON VIENE DATA MONETA-STAZIONE ARRIVO(5 BICI E 5 COLONNINE LIBERE)
		
																				
		/*IMPORTANTE: POTREI DECIDERE DI DARE GIA' ALL'INIZIO PIU' MONETA A UNA STAZIONE PERCHE' MAGARI E' PIU' SOGGETTA AL PRELIEVO DI BICI
		E QUINDI QUANDO INIZIALIZZO UNA STAZIONE DOVREI PASSARGLI IL PARAMETRO RELATIVO(PENSARCI)*/
	
	
	}
	/*-------------------------------------METHODS---------------------------*/
	void remove_bike(Users *instusers, double n_u, double n_s, int user);													//RIMUOVE UNA BICI DALLA STAZIONE
	void add_bike(Users *instusers, double n_u, double n_s, int user);														//AGGIUNGE UNA BICI ALLA STAZIONE
	int av_bikes();																//MI RESTITUISCE IL NUMERO DI BICI
	int av_columns();															//RESTITUISCE N° COLONNINE LIBERE
	double g_m_r();																//RESTITUISCE PREMIO PER LA STAZIONE DI PARTENZA
	double g_m_t();																//RESTITUISCE PREMIO PER LA STAZIONE DI RILASCIO
	double get_x_coord();														//RESTITUISCE LA COORDINATA x
	double get_y_coord();														//RESTITUISCE LA COORDINATA y
	double get_gift_release();													//RESTITUISCE IL PREMIO DELLA STAZIONE DI PARTENZA
	double get_gift_take();														//RESTITUISCE IL PREMIO DELLA STAZIONE DI ARRIVO
	double xcoord;																//COORDINATA x
	double ycoord;																//COORDINATA y
	int critical_empty_counter = 0;												//CONTATORE CRITICITA' STAZIONE VUOTA
	int critical_full_counter = 0;												//CONTATORE CRITICITA' STAZIONE PIENA
	double station_empty_time = 0;													//ARRAY RIFERITO AI TEMPI IN CUI LA STAZIONE RESTA VUOTA
	double station_full_time = 0;													//ARRAY RIFERITO AI TEMPI IN CUI LA STAZIONE RIMANE PIENA
	double time0_empty_station = 0;													//TEMPO 0 STAZIONI SENZA BICI
	double time0_full_station = 0;													//TEMPO 0 STAZIONI SENZA COLONNINE LIBERE

/*---------------------------------PRIVATE VARIABLES-------------------------*/
private:
	double gift_money_release;													//PREMIO SCELTA STAZIONE PARTENZA
	double gift_money_take;														//PREMIO SCELTA STAZIONE RILASCIO
	int columns;																//COLONNINE TOTALI
	int available_bikes;														//BICI DISPONIBILI
	int free_columns;															//NUMERO COLONNINE LIBERE
	int *reserve_up_col;														//ARRAY COLONNINA LIBERA PRENOTATO
	
};

/**************************************************************************************************/
															
/*-------------------------------------CLASSE CHE GESTISCE LE STAZIONI----------------------------*/
class Stations 
{
public:
	
	/*----------------------------PUBLIC VARIABLES---------------------------*/
	Station_i* all_stations;													//ARRAY DELLE STAZIONI
	
	char **stations_names;														//NAMES OF ALL STATIONS
	char input_used[200];
	char name[20];																//NAME OF FILE USED
	int n_stations;																//NUMERO STAZIONI
	double *xcoords;															//COORDINATE x STAZIONI
	double *ycoords;															//COORDINATE y STAZIONI
	int num_bikes;																//NUMERO TOTALE BICI PRESENTI
	int num_columns;															//NUMERO TOTALE COLONNINE
	double *critical_station;													//ARRAY CHE IDENTIFICA COME CRITICA UNA STAZIONE
	

	/*-------------------------------------METHODS---------------------------*/
	void set_n_stations(int num);												//SETTO IL NUMERO DI STAZIONI PRESENTI 
	void set_n_columns_for_station(int n_c);									//SETTO IL NUMERO DI COLONNE PER OGNI STAZIONE
	void set_n_bikes_for_stations(int n_b);										//SETTO IL NUMERO DI BICI PER OGNI STAZIONE
	void set_cash_desk(Users u);												//SETTO IL DENARO TOTALE PRESENTE NEL SISTEMA
	void update_cash_desk(Users *u,double t,double r);							//AGGIORNO DELLA QUANTITA' r IL DENARO TOTALE PRESENTE NEL SISTEMA
	double get_cash_desk();														//RITORNA LA QUANTITA' DI DENARO PRESENTE NEL SISTEMA

private:
	/*----------------------------PRIVATE VARIABLES--------------------------*/

	double cash_desk;															//SOLDI PRESENTI NEL SISTEMA

};

/*---------------------PARAMETRI CHE POSSONO CAMBIARE----------------------------*/
#endif // !station_h
