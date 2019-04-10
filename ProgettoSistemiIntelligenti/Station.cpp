#include "Station.h"								//PER POTER DEFINIRE I METODI DI QUESTA CLASSE
#include <cmath>



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


void Station_i::remove_bike(){
	this->available_bikes--;									//DECREMENTO NUMERO BICI DISPONIBILI
	this->free_columns++;										//INCREMENTO COLONNINE DISPONIBILI
	this->gift_money_take--;									//DECREMENTO MONETA RILASCIATA DALLA STAZIONE DI PARTENZA (VOGLIO EVITARE CHE SI PRENDANO BICI QUI)
	this->gift_money_release++;									//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO CONVOGLIARE QUI LE BICI)
}

void Station_i::reserve_col(int i){
	this->reserve_up_col[i] = 1;
}

void Station_i::add_bike(){
	this->available_bikes++;									//INCREMENTO NUMERO BICI DISPONIBILI
	this->free_columns--;										//DECREMENTO COLONNINE LIBERE
	this->gift_money_take++;									//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI PARTENZA (VOGLIO INCENTIVARE LA PARTENZA DA QUESTA STAZIONE)
	this->gift_money_release--;									//DECREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO EVITARE CHE LE BICI SIANO CONVOGLIATE QUI)
}

void Station_i::set_money(double val){
	this->gift_money_take = val;
}

/*---------------------------------------------------------------------------------*/


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
