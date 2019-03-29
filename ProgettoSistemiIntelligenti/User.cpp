#include "User.h"

void User_i::decrement_money(int p)
{
	money_pocket--;
}

void User_i::increment_money(int m)
{
	money_pocket++;
}
void User_i::visit_counter(int i)
{
	stations_used[i]++;
}

void User_i::clear_visits(int n_s)
{
	for (int i = 0; i < n_s; i++)
	{
		stations_used[i] = 0;
	}
}
