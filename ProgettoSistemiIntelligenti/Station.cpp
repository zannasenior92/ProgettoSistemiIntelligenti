#include "Station.h"								//PER POTER DEFINIRE I METODI DI QUESTA CLASSE
#include <cmath>


int Station::Station_i::n_bikes()
{
	return available_bikes;
}

int Station::Station_i::av_columns()
{
	return free_columns;
}

int Station::Station_i::g_o_m()
{
	return gift_of_money;
}


void Station::Station_i::remove_bike()
{
	available_bikes--;
}

void Station::Station_i::add_bike()
{
	available_bikes++;
}

void Station::Station_i::set_money(double val)
{
	gift_of_money = val;
}
