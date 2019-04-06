#include "Station.h"								//PER POTER DEFINIRE I METODI DI QUESTA CLASSE
#include <cmath>



/*----------------------------METODI CLASSE STATION-----------------------------*/
int Station_i::n_bikes()
{
	return available_bikes;
}

int Station_i::av_columns()
{
	return free_columns;
}

double Station_i::g_m_t()
{
	return gift_money_take;
}

double Station_i::get_x_coord()
{
	return xcoord;
}

double Station_i::get_y_coord()
{
	return ycoord;
}

double Station_i::g_m_r()
{
	return gift_money_release;
}


void Station_i::remove_bike()
{
	available_bikes--;
}

void Station_i::reserve_col(int i)
{
	reserve_up_col[i] = 1;
}

void Station_i::add_bike()
{
	available_bikes++;
}

void Station_i::set_money(double val)
{
	gift_money_take = val;
}

/*---------------------------------------------------------------------------------*/


/*--------------------------------METODI STATIONS----------------------------------*/

int Stations::n_stat()
{
	return n_stations;
}

void Stations::set_n_stations(int num)
{
	this->n_stations = num;
}

void Stations::set_n_columns_for_station(int n_c)
{
	this->num_columns = n_c;
}

void Stations::set_n_bikes_for_stations(int n_b)
{
	this->num_bikes = n_b;
}
