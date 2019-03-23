#include "Station.h"								//PER POTER DEFINIRE I METODI DI QUESTA CLASSE
#include <cmath>

void Station::Station_i::define_station(int c, int b, int av_b, int fr_c)
{
	bikes = b;
	columns = c;

}

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
