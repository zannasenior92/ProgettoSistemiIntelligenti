/*----------------------------STAZIONE BICI------------------------------*/


#ifndef station_h
#define station_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>  

#define VERBOSE 50

namespace Station {
	class Station_i;
}
class Station::Station_i
{
public:
	/*-------------------DEFINISCO N° BICI E N° COLONNINE------------------------*/
	Station_i(int b, int c)
	{
		this->available_bikes = b;
		this->columns = c;
		this->free_columns = this->columns - this->available_bikes;
	}
	/*-------------------------------------METHODS-------------------------------*/
	void remove_bike();															//RIMUOVE UNA BICI DALLA STAZIONE
	void add_bike();															//AGGIUNGE UNA BICI ALLA STAZIONE
	void set_money(double val);													//SETTA LA MONETA OFFERTA DALLA STAZIONE
	int n_bikes();																//MI RESTITUISCE IL NUMERO DI BICI
	int av_columns();															//RESTITUISCE N° COLONNINE LIBERE
	int g_o_m();																//RESTITUISCE I SOLDI CHE OFFRE QUELLA STAZIONE	
	
/*---------------------------------PRIVATE VARIABLES-------------------------*/
private:
	int gift_of_money;															//REGALO DI DENARO CHE OFFRE LA STAZIONE
	int columns;																//COLONNINE TOTALI
	int available_bikes;														//BICI DISPONIBILI
	int free_columns;															//NUMERO COLONNINE LIBERE
};

/*---------------------PARAMETRI CHE POSSONO CAMBIARE----------------------------*/
																
#endif // !station_h