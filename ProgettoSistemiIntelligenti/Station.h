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
	void define_n_bikes(int k);													//MI DEFINISCE IL NUMERO DI BICI
	void define_n_columns(int c);												//MI DEFINISCE IL NUMERO DI COLONNINE
	void remove_bike(int i);													//RIMUOVE UNA BICI DALLA STAZIONE
	void add_bike(int j);														//AGGIUNGE UNA BICI ALLA STAZIONE
	int n_bikes();																//MI RESTITUISCE IL NUMERO DI BICI
	int av_columns;																//RESTITUISCE N° COLONNINE LIBERE

private:
	int b;																		//BICI TOTALI POSIZIONABILI
	int available_bikes;														//BICI DISPONIBILI
	int columns;																//NUMERO COLONNINE LIBERE
};

/*---------------------PARAMETRI CHE POSSONO CAMBIARE--------------------*/
																
#endif // !station_h