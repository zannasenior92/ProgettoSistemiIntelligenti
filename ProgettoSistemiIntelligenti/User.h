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
	User_i(double M, int n_s , int t, double v_d)													//M = soldi iniziali; t = velocit� utente  v_d = valore di decisione per la scelta di altre stazioni
	{
		this->money_pocket = M;
		this->start_stations_used = new int[n_s] {0};
		this->arrive_stations_used = new int[n_s] {0};
		this->transfert_coef = t;
		this->added_gift = new double[n_s] {0};
		this->value_decision = v_d;
		this->user_satisfaction = 0;
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
	double get_added_gift(int station_i);										//RESTITUISCE I GIFT AGGIUNTIVI DATI
	void clear_added_gift(int n_s);												//AZZERA TUTTE I GIFT AGGIUNTIVI DEL SINGOLO UTENTE
	double get_value_decision();												//MI RESTITUISCE IL VALORE DI DECISIONE DELL'UTENTE
	void update_satisfaction(double s);											//AGGIORNA IL VALORE DI SODDISFAZIONE DELL'UTENTE IN BASE ALLA STAZIONE SCELTA
	double get_satisfaction();

	/*---------------------------------PRIVATE VARIABLES-------------------------*/
private:
	int *start_stations_used;													//PUNTATORE AD ARRAY CONTATORE DEGLI ACCESSI AD OGNI STAZIONE DI PARTENZA
	int *arrive_stations_used;													//PUNTATORE AD ARRAY CONTATORE DEGLI ACCESSI AD OGNI STAZIONE DI ARRIVO
	double money_pocket;														//SOLDI INIZIALI DI BUDGET
	double value_decision;														//VALORE CHE ESPRIME IL RAPPORTO TRA GUADAGNO E DISTANZA - PER LA SCELTA DELLA STAZIONE
	int transfert_coef;															//COEFFICIENTE CHE ESPRIME IL TEMPO DI TRASFERIMENTO IN BASE AI CHILOMETRI
	double *added_gift;															//GIFT AGGIUNTIVI RELATIVI AD OGNI STAZIONE
	double user_satisfaction;													//LIVELLO DI SODDISFAZIONE DELL'UTENTE RIGUARDO AL SERVIZIO OFFERTO
};

/**************************************************************************************************/

/*-------------------------------------CLASSE CHE GESTISCE LE STAZIONI----------------------------*/
class Users
{
public:

	/*----------------------------PUBLIC VARIABLES---------------------------*/
	int n_users;
	User_i* all_users;

	/*----------------------------------ALL DATA------------------------------*/
	int n_trip;
	int *tripduration;
	int *start_station_id;
	char **start_station_name;
	double *star_station_latitude;
	double *star_station_longitude;
	int *end_station_id;
	char **end_station_name;
	double *end_station_latitude;
	double *end_station_longitude;
	int *bikeid;
	char **usertype;
	int travel_deleted;					//FLAG PER INDICARE CHE IL VIAGGIO DELL'UTENTE E' STATO ANNULLATO CAUSA BICI MANCANTE IN STAZIONE DI PARTENZA E VALORE DI DECISIONE PARI A 0(UTENTE CHE VUOLE PARTIRE ASSOLUTAMENTE DA QUELLA STAZIONE)

	/*----------------------------------METHODS-------------------------------*/
	
	
private:
	


};

/*---------------------PARAMETRI CHE POSSONO CAMBIARE----------------------------*/

#endif // !user_h