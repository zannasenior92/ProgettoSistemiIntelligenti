/*---------------------------------------USER-----------------------------------*/


#ifndef user_h
#define user_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>  


class User_i
{
public:
	/*-------------------DEFINISCO MONETA INIZIALE UTENTE------------------------*/
	User_i(double M, int n_s)													//M = soldi iniziali; t = velocit� utente  
	{
		this->money_pocket = M;
		this->stations_used = new int[n_s];
	}
	/*-------------------------------------METHODS-------------------------------*/
	void decrement_money();
	void increment_money();
	void visit_counter(int i);													//QUANDO VISITA UNA STAZIONE NE INCREMENTA IL CONTATORE
	void clear_visits(int n_s);													//AZZERA LE VISITE IN TUTTE LE STAZIONI



/*---------------------------------PRIVATE VARIABLES-------------------------*/
private:
	int *stations_used;															//PUNTATORE AD ARRAY CONTATORE DEGLI ACCESSI AD OGNI STAZIONE
	double money_pocket;															//SOLDI INIZIALI DI BUDGET
	int travel_time;															//VELOCITA' MEDIA UTENTE
};

/**************************************************************************************************/

/*-------------------------------------CLASSE CHE GESTISCE LE STAZIONI----------------------------*/
class Users
{
public:

	/*----------------------------PUBLIC VARIABLES---------------------------*/
	int n_users;
	User_i* all_users;


	
private:

};

/*---------------------PARAMETRI CHE POSSONO CAMBIARE----------------------------*/

#endif // !user_h