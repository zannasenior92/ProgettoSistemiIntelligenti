#include "Station.h"								//PER POTER DEFINIRE I METODI DI QUESTA CLASSE
#include <cmath>
#include "User.h"



/*----------------------------METODI CLASSE STATION-----------------------------*/
int Station_i::av_bikes()
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


void Station_i::remove_bike(double u,double s){
	
	if (available_bikes == 0)
	{
		printf("***NO bike avaiable! Choose another station*** \n\n");
	}
	else
	{
		this->available_bikes--;																				//DECREMENTO NUMERO BICI DISPONIBILI
		this->free_columns++;																					//INCREMENTO COLONNINE DISPONIBILI

		/*---------------------------------FEW BIKES AVAIABLE------------------------------*/
		if (this->available_bikes < 5)
		{
			
			this->gift_money_take = -exp((this->free_columns - this->available_bikes)* (log(u) / s));			//DECREMENTO MONETA RILASCIATA DALLA STAZIONE DI PARTENZA (VOGLIO EVITARE CHE SI PRENDANO BICI QUI)
			this->gift_money_release = exp((this->free_columns - this->available_bikes)* (log(u) / s));			//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO CONVOGLIARE QUI LE BICI)
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
			this->gift_money_take = exp((this->available_bikes - this->free_columns)* (log(u) / s));			//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO CONVOGLIARE QUI LE BICI)
			this->gift_money_release = -exp((this->available_bikes - this->free_columns)* (log(u) / s));		//DECREMENTO MONETA RILASCIATA DALLA STAZIONE DI PARTENZA (VOGLIO EVITARE CHE SI PRENDANO BICI QUI)
		}
	}
}

void Station_i::reserve_col(int i){
	this->reserve_up_col[i] = 1;
}

void Station_i::add_bike(double u,double s){
	
	if (free_columns == 0)
	{
	printf("***NO columns avaiable! Please put the bike in another station*** \n\n");
	}
	else
	{
		this->available_bikes++;																				//INCREMENTO NUMERO BICI DISPONIBILI
		this->free_columns--;																					//DECREMENTO COLONNINE LIBERE

		/*---------------------------------FEW BIKES AVAIABLE------------------------------*/
		if (this->available_bikes < 5)
		{
			printf("Cciao dibvbuibbuib %lf \n",u / s);
			this->gift_money_take = -exp((this->free_columns - this->available_bikes)* (log(u) / s));			//DECREMENTO MONETA RILASCIATA DALLA STAZIONE DI PARTENZA (VOGLIO EVITARE CHE SI PRENDANO BICI QUI)
			this->gift_money_release = exp((this->free_columns - this->available_bikes)* (log(u) / s));			//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO CONVOGLIARE QUI LE BICI)
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
			this->gift_money_take = exp((this->available_bikes - this->free_columns)* (log(u) / s));			//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO CONVOGLIARE QUI LE BICI)
			this->gift_money_release = -exp((this->available_bikes - this->free_columns)* (log(u) / s));		//DECREMENTO MONETA RILASCIATA DALLA STAZIONE DI PARTENZA (VOGLIO EVITARE CHE SI PRENDANO BICI QUI)
		}
	}
}

void Station_i::set_money(double val){
	
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

void Stations::set_cash_desk(Users u)
{
	this->cash_desk = SUBSCRIPTION * u.n_users;
}

void Stations::update_cash_desk(Users *u, double t, double r)
{
	this->cash_desk = this->cash_desk - t - r;
}

double Stations::get_cash_desk()
{
	return this->cash_desk;
}
