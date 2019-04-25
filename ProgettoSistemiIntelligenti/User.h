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
	User_i(double M, int n_s , int t)													//M = soldi iniziali; t = velocità utente  
	{
		this->money_pocket = M;
		this->start_stations_used = new int[n_s] {0};
		this->arrive_stations_used = new int[n_s] {0};
		this->travel_time = t;
		this->added_gift = new double[n_s] {0};
	}
	/*-------------------------------------METHODS-------------------------------*/
	void update_budget(double start, double arrive);							//AGGIORNA IL BUDGET DELL'UTENTE(PREMIO STAZIONE PARTENZA+PREMIO STAZIONE ARRIVO)
	double get_budget();														//MI RESTITUISCE IL BUDGET DELL'UTENTE
	void visit_counter_start(int i);											//QUANDO VISITA UNA STAZIONE(DI PARTENZA) NE INCREMENTA IL CONTATORE
	void visit_countet_arrive(int i);											//QUANDO VISITA UNA STAZIONE(DI ARRIVO) NE INCREMENTA IL CONTATORE
	void clear_visits(int n_s);													//AZZERA LE VISITE IN TUTTE LE STAZIONI
	int get_counter_Start_Visits(int i);										//MI DICE QUANTE VOLTE HO VISITATO QUELLA STAZIONE IN PARTENZA
	int get_counter_Arrive_Visits(int i);										//MI DICE QUANTE VOLTE HO VISITATO QUELLA STAZIONE IN ARRIVO
	void add_gift(int station_i,double quantity);								//AGGIUNGE CREDITO DA GUADAGNARE ALLA STAZIONE i
	double get_added_gift(int station_i);

/*---------------------------------PRIVATE VARIABLES-------------------------*/
private:
	int *start_stations_used;													//PUNTATORE AD ARRAY CONTATORE DEGLI ACCESSI AD OGNI STAZIONE DI PARTENZA
	int *arrive_stations_used;													//PUNTATORE AD ARRAY CONTATORE DEGLI ACCESSI AD OGNI STAZIONE DI ARRIVO
	double money_pocket;														//SOLDI INIZIALI DI BUDGET
	int travel_time;															//VELOCITA' MEDIA UTENTE
	int value_decision;															//VALORE CHE ESPRIME IL RAPPORTO TRA GUADAGNO E DISTANZA PER LA SCELTA DELLA STAZIONE
	double *added_gift;															//GIFT AGGIUNTIVI RELATIVI AD OGNI STAZIONE
};

/**************************************************************************************************/

/*-------------------------------------CLASSE CHE GESTISCE LE STAZIONI----------------------------*/
class Users
{
public:

	/*----------------------------PUBLIC VARIABLES---------------------------*/
	int n_users;
	User_i* all_users;

	/*-------------------------------------METHODS-------------------------------*/
	
	
private:

};

/*---------------------PARAMETRI CHE POSSONO CAMBIARE----------------------------*/

#endif // !user_h