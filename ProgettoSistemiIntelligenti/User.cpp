#include "User.h"
#include "Station.h"

/*--------------------------------USER METHODS----------------------------------*/
void User_i::update_budget(double start,double arrive)
{
	money_pocket = money_pocket + start + arrive;
}

double User_i::get_budget()
{
	return this->money_pocket;
}

void User_i::visit_counter_start(int i)
{
	this->start_stations_used[i]++;
}

void User_i::visit_countet_arrive(int i)
{
	this->arrive_stations_used[i]++;
}

void User_i::clear_visits(int n_s)
{
	for (int i = 0; i < n_s; i++)
	{
		start_stations_used[i] = 0;
		arrive_stations_used[i] = 0;
	}
}

int User_i::get_counter_Arrive_Visits(int i)
{
	return this->arrive_stations_used[i];
}

int User_i::get_counter_Start_Visits(int i)
{
	return this->start_stations_used[i];
}

void User_i::add_gift(int station_i,double quantity)
{
	this->added_gift[station_i] = cbrt(quantity);
}

double User_i::get_added_gift(int station_i)
{
	return this->added_gift[station_i];
}

void User_i::clear_added_gift(int n_s)
{
	for (int i = 0; i < n_s; i++)
	{
		this->added_gift[i] = 0;
	}
}

double User_i::get_value_decision()
{
	return this->value_decision;
}

/************************************************************************************/

/*--------------------------------USERS METHODS----------------------------------*/

