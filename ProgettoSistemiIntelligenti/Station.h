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
	void define_station(int c, int b, int av_b, int fr_c);

	void remove_bike(int i);													//RIMUOVE UNA BICI DALLA STAZIONE
	void add_bike(int j);														//AGGIUNGE UNA BICI ALLA STAZIONE
	int n_bikes();																//MI RESTITUISCE IL NUMERO DI BICI
	int av_columns();																//RESTITUISCE N° COLONNINE LIBERE

private:
	int columns;
	int bikes;																		//BICI TOTALI POSIZIONABILI
	int available_bikes;														//BICI DISPONIBILI
	int free_columns;																//NUMERO COLONNINE LIBERE
};

/*---------------------PARAMETRI CHE POSSONO CAMBIARE--------------------*/
																
#endif // !station_h