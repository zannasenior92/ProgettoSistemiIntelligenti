/*----------------------------STAZIONE BICI------------------------------*/


#ifndef station_h
#define station_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>  

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

	void remove_bike(int i);													//RIMUOVE UNA BICI DALLA STAZIONE
	void add_bike(int j);														//AGGIUNGE UNA BICI ALLA STAZIONE
	int n_bikes();																//MI RESTITUISCE IL NUMERO DI BICI
	int av_columns();																//RESTITUISCE N° COLONNINE LIBERE

private:
	int columns;																//COLONNINE TOTALI
	int available_bikes;														//BICI DISPONIBILI
	int free_columns;															//NUMERO COLONNINE LIBERE
};

/*---------------------PARAMETRI CHE POSSONO CAMBIARE--------------------*/
																
#endif // !station_h