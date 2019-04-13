#include "Station.h"								//PER POTER DEFINIRE I METODI DI QUESTA CLASSE
#include <cmath>
#include "User.h"



/*----------------------------METODI CLASSE STATION-----------------------------*/
int Station_i::n_bikes()
{
	return this->available_bikes;
}

int Station_i::av_columns()
{
	return this->free_columns;
}

double Station_i::g_m_t()
{
	return this->gift_money_take;
}

double Station_i::get_x_coord()
{
	return this->xcoord;
}

double Station_i::get_y_coord()
{
	return this->ycoord;
}

double Station_i::get_gift_release()
{
	return this->gift_money_release;
}

double Station_i::get_gift_take()
{
	return this->gift_money_take;
}

double Station_i::g_m_r()
{
	return this->gift_money_release;
}


void Station_i::remove_bike(int u,int s){
	this->available_bikes--;																				//DECREMENTO NUMERO BICI DISPONIBILI
	this->free_columns++;																					//INCREMENTO COLONNINE DISPONIBILI
	
	/*---------------------------------FEW BIKES AVAIABLE------------------------------*/
	if (this->available_bikes < 5)
	{															
		this->gift_money_take = -exp(this->free_columns - this->available_bikes) / s +1;		//DECREMENTO MONETA RILASCIATA DALLA STAZIONE DI PARTENZA (VOGLIO EVITARE CHE SI PRENDANO BICI QUI)
		this->gift_money_release = exp(this->free_columns - this->available_bikes) / s -1;		//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO CONVOGLIARE QUI LE BICI)
	}
	/*---------------------------STATE 0 - EQUAL BIKES AND COLUMNS---------------------*/
	else if ((this->available_bikes-this->free_columns) == 0)
	{
		this->gift_money_take = 0;
		this->gift_money_release = 0;
	}
	/*---------------------------------FEW FREE COLUMNS--------------------------------*/
	else
	{		
		this->gift_money_take = exp(this->available_bikes - this->free_columns) / s -1;		//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO CONVOGLIARE QUI LE BICI)
		this->gift_money_release = -exp(this->free_columns - this->available_bikes) / s +1;	//DECREMENTO MONETA RILASCIATA DALLA STAZIONE DI PARTENZA (VOGLIO EVITARE CHE SI PRENDANO BICI QUI)
	}
}

void Station_i::reserve_col(int i){
	this->reserve_up_col[i] = 1;
}

void Station_i::add_bike(int u,int s){
	this->available_bikes++;																				//INCREMENTO NUMERO BICI DISPONIBILI
	this->free_columns--;																					//DECREMENTO COLONNINE LIBERE
	
	/*---------------------------------FEW BIKES AVAIABLE------------------------------*/
	if (this->available_bikes < 5)
	{
		this->gift_money_take = -exp(this->free_columns - this->available_bikes)  / s +1;		//DECREMENTO MONETA RILASCIATA DALLA STAZIONE DI PARTENZA (VOGLIO EVITARE CHE SI PRENDANO BICI QUI)
		this->gift_money_release = exp(this->free_columns - this->available_bikes) / s -1;		//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO CONVOGLIARE QUI LE BICI)
	}
	/*---------------------------STATE 0 - EQUAL BIKES AND COLUMNS---------------------*/
	else if ((this->available_bikes - this->free_columns) == 0)
	{
		this->gift_money_take = 0;
		this->gift_money_release = 0;
	}
	/*---------------------------------FEW FREE COLUMNS--------------------------------*/
	else
	{
		this->gift_money_take = exp(this->available_bikes - this->free_columns) / s -1;		//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO CONVOGLIARE QUI LE BICI)
		this->gift_money_release = -exp(this->free_columns - this->available_bikes) / s +1;	//DECREMENTO MONETA RILASCIATA DALLA STAZIONE DI PARTENZA (VOGLIO EVITARE CHE SI PRENDANO BICI QUI)
	}
}

void Station_i::set_money(double val){
	this->gift_money_take = val;
}


/*****************************************************************************************************************************************/


/*--------------------------------STATIONS METHODS----------------------------------*/

int Stations::n_stat(){
	return n_stations;
}

void Stations::set_n_stations(int num){
	this->n_stations = num;
}

void Stations::set_n_columns_for_station(int n_c){
	this->num_columns = n_c;
}

void Stations::set_n_bikes_for_stations(int n_b){
	this->num_bikes = n_b;
}
