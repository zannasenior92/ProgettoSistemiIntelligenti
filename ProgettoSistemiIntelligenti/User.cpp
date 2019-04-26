#include "User.h"
#include "Station.h"

/*--------------------------------USER METHODS----------------------------------*/
void User_i::update_budget(double start,double arrive,int start_s,int arrive_s)
{
	/*IL PREMIO E' CALCOLATO PER LA STAZIONE DI PARTENZA IN BASE AL NUMERO DI BICI/COLONNINE E INOLTRE A QUESTO E' AGGIUNTO IL FATTO CHE L'UTENTE
	E' PARTITO DA QUESTA STAZIONE PUR DOVENDO PARTIRE DA UN'ALTRA. STESSA COSA PER LA STAZIONE DI ARRIVO*/
	money_pocket = money_pocket + start + arrive + this->added_gift[start_s] + this->added_gift[arrive_s];
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

/************************************************************************************/

/*--------------------------------USERS METHODS----------------------------------*/

