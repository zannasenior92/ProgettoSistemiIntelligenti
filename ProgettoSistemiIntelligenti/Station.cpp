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


void Station::Station_i::remove_bike(int i)
{
	available_bikes--;
}

void Station::Station_i::add_bike(int j)
{
	available_bikes++;
}
