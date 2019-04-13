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
	start_stations_used[i]++;
}

void User_i::visit_countet_arrive(int i)
{
	arrive_stations_used[i]++;
}

void User_i::clear_visits(int n_s)
{
	for (int i = 0; i < n_s; i++)
	{
		start_stations_used[i] = 0;
		arrive_stations_used[i] = 0;
	}
}

/************************************************************************************/

/*--------------------------------USERS METHODS----------------------------------*/

