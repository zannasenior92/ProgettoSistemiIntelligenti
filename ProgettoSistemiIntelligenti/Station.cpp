#include "Station.h"								//PER POTER DEFINIRE I METODI DI QUESTA CLASSE
#include <cmath>
#include "User.h"



/*----------------------------METODI CLASSE STATION-----------------------------*/
int Station_i::av_bikes()
{
	return this->available_bikes;
}

int Station_i::av_columns()
{
	return this->free_columns;
}

double Station_i::g_m_t()
{
	return this->gift_money_take;
}

double Station_i::get_x_coord()
{
	return this->xcoord;
}

double Station_i::get_y_coord()
{
	return this->ycoord;
}

double Station_i::get_gift_release()
{
	return this->gift_money_release;
}

double Station_i::get_gift_take()
{
	return this->gift_money_take;
}

double Station_i::g_m_r()
{
	return this->gift_money_release;
}

/*INSERIRE CHE SE IN UNA STAZIONE NON CI SONO PIU' BICI CON L'AUMENTARE DEL TEMPO AUMENTA ANCHE L'OFFERTA DATA DALLA PARTENZA DA QUELLA POSTAZIONE*/
void Station_i::remove_bike(Users *instusers ,double n_u,double n_s,int user){
	
	if (available_bikes == 0)
	{
		printf("***NO bike avaiable! Choose another station*** \n\n");

		/*BICI E COLONNE DISPONIBILI DOPO LA RIMOZIONE*/
		int fc = this->free_columns;
		int av_b = this->available_bikes;

		/*CONTATORI CRITICITA' PER STAZIONE VUOTA (EMPTY)*/
		int cr_e_c = this->critical_empty_counter;						//n° DI VOLTE STAZIONE VUOTA
		double s_e_t = this->station_empty_time;
		if (VERBOSE > 300)
		{
			printf("Time empty station: %lf \n", s_e_t);
		}
		/*USO IL TEMPO PER CUI LA STAZIONE E' RIMASTA VUOTA PER AGGIORNARE I SOLDI DATI SE RILASCIO LA BICI*/
		this->gift_money_release = exp((fc - av_b)* (log(n_u) / n_s) *sqrt(cr_e_c + 1) *cbrt(s_e_t + 1));	//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO CONVOGLIARE QUI LE BICI)
	}
	else
	{
		this->available_bikes--;																				//DECREMENTO NUMERO BICI DISPONIBILI
		this->free_columns++;																					//INCREMENTO COLONNINE DISPONIBILI
		printf("--------BIKE REMOVED-------\n");


		/*BICI E COLONNE DISPONIBILI DOPO LA RIMOZIONE*/
		int fc = this->free_columns;
		int av_b = this->available_bikes;

		/*CONTATORI CRITICITA' PER STAZIONE PIENA O VUOTA (FULL/EMPTY)*/
		int cr_f_c = this->critical_full_counter;						//n° DI VOLTE STAZIONE PIENA
		int cr_e_c = this->critical_empty_counter;						//n° DI VOLTE STAZIONE VUOTA


		/*---------------------------------FEW BIKES AVAIABLE------------------------------*/
		if (this->available_bikes < 5)
		{
			/*USO IL CRITICAL EMPTY COUNTER PERCHE' NON VOGLIO CHE LA STAZIONE RIMANGA DI NUOVO VUOTA.
			INCENTIVO QUINDI A DEPOSITARE LA BICI QUI E A NON PRELEVARLA USANDO IN ENTRAMBI I CASI IL 
			CONTATORE DI CRITICITA' DELLA STAZIONE*/
			this->gift_money_take = -exp((fc - av_b)* (log(n_u) / n_s) *sqrt(cr_e_c + 1));		//DECREMENTO MONETA RILASCIATA DALLA STAZIONE DI PARTENZA (VOGLIO EVITARE CHE SI PRENDANO BICI QUI)
			this->gift_money_release = exp((fc - av_b)* (log(n_u) / n_s) *sqrt(cr_e_c + 1));	//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO CONVOGLIARE QUI LE BICI)
		}
		/*---------------------------STATE 0 - EQUAL BIKES AND COLUMNS---------------------*/
		else if ((this->available_bikes - this->free_columns) == 0)
		{
			this->gift_money_take = 0;
			this->gift_money_release = 0;
		}
		/*---------------------------------FEW FREE COLUMNS--------------------------------*/
		else
		{
			/*USO IL CRITICAL FULL COUNTER PERCHE' NON VOGLIO CHE LA STAZIONE RIMANGA DI NUOVO PIENA.
			INCENTIVO QUINDI A PRELEVARE LA BICI QUI E A NON DEPOSITARLA USANDO IN ENTRAMBI I CASI IL
			CONTATORE DI CRITICITA' DELLA STAZIONE*/
			this->gift_money_take = exp((av_b - fc)* (log(n_u) / n_s) *sqrt(cr_f_c + 1));			//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO CONVOGLIARE QUI LE BICI)
			this->gift_money_release = -exp((av_b - fc)* (log(n_u) / n_s) *sqrt(cr_f_c + 1));		//DECREMENTO MONETA RILASCIATA DALLA STAZIONE DI PARTENZA (VOGLIO EVITARE CHE SI PRENDANO BICI QUI)
		}
	}
}


/*INSERIRE CHE SE IN UNA STAZIONE NON CI SONO PIU' COLONNINE CON L'AUMENTARE DEL TEMPO AUMENTA ANCHE L'OFFERTA DATA DAL RAGGIUNGIMENTO DI QUELLA POSTAZIONE*/
void Station_i::add_bike(Users *instusers, double n_u, double n_s, int user){
		
	if (free_columns == 0)
	{
		/*BICI E COLONNE DISPONIBILI DOPO LA RIMOZIONE*/
		int fc = this->free_columns;
		int av_b = this->available_bikes;
		
		/*CONTATORI CRITICITA' PER STAZIONE PIENA O VUOTA (FULL/EMPTY)*/
		int cr_f_c = this->critical_full_counter;						//n° DI VOLTE STAZIONE PIENA
		double s_f_t = this->station_full_time;							//TEMPO STAZIONE RIMASTA PIENA

		printf("***NO columns avaiable! Please put the bike in another station*** \n\n");
		printf("Time full station: %lf \n", s_f_t);
		
		/*USO IL TEMPO PER CUI LA STAZIONE E' RIMASTA VUOTA PER AGGIORNARE I SOLDI DATI SE PRELEVO LA BICI*/
		this->gift_money_take = exp((av_b - fc)* (log(n_u) / n_s) *sqrt(cr_f_c + 1) *cbrt(s_f_t + 1));//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO CONVOGLIARE QUI LE BICI)
	}
	else
	{
		this->available_bikes++;															//INCREMENTO NUMERO BICI DISPONIBILI
		this->free_columns--;																//DECREMENTO COLONNINE LIBERE
		printf("-------BIKE RELEASED------\n");


		/*BICI E COLONNE DISPONIBILI DOPO LA RIMOZIONE*/
		int fc = this->free_columns;
		int av_b = this->available_bikes;

		/*CONTATORI CRITICITA' PER STAZIONE PIENA O VUOTA (FULL/EMPTY)*/
		int cr_f_c = this->critical_full_counter;						//n° DI VOLTE STAZIONE PIENA
		int cr_e_c = this->critical_empty_counter;						//n° DI VOLTE STAZIONE VUOTA

		/*---------------------------------FEW BIKES AVAIABLE------------------------------*/
		if (this->available_bikes < 5)
		{
			/*USO IL CRITICAL EMPTY COUNTER PERCHE' NON VOGLIO CHE LA STAZIONE RIMANGA DI NUOVO VUOTA.
			INCENTIVO QUINDI A DEPOSITARE LA BICI QUI E A NON PRELEVARLA USANDO IN ENTRAMBI I CASI IL
			CONTATORE DI CRITICITA' DELLA STAZIONE*/
			this->gift_money_take = -exp((fc - av_b)* (log(n_u) / n_s)  *sqrt(cr_e_c + 1));	//DECREMENTO MONETA RILASCIATA DALLA STAZIONE DI PARTENZA (VOGLIO EVITARE CHE SI PRENDANO BICI QUI)
			this->gift_money_release = exp((fc - av_b)* (log(n_u) / n_s) *sqrt(cr_e_c + 1));//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO CONVOGLIARE QUI LE BICI)
		}
		/*---------------------------STATE 0 - EQUAL BIKES AND COLUMNS---------------------*/
		else if ((this->available_bikes - this->free_columns) == 0)
		{
			this->gift_money_take = 0;
			this->gift_money_release = 0;
		}
		/*---------------------------------FEW FREE COLUMNS--------------------------------*/
		else
		{
			/*USO IL CRITICAL FULL COUNTER PERCHE' NON VOGLIO CHE LA STAZIONE RIMANGA DI NUOVO PIENA.
			INCENTIVO QUINDI A PRELEVARE LA BICI QUI E A NON DEPOSITARLA USANDO IN ENTRAMBI I CASI IL
			CONTATORE DI CRITICITA' DELLA STAZIONE*/
			this->gift_money_take = exp((av_b - fc)* (log(n_u) / n_s) *sqrt(cr_f_c + 1));//INCREMENTO MONETA RILASCIATA DALLA STAZIONE DI ARRIVO (VOGLIO CONVOGLIARE QUI LE BICI)
			this->gift_money_release = -exp((av_b - fc)* (log(n_u) / n_s)  *sqrt(cr_f_c + 1));//DECREMENTO MONETA RILASCIATA DALLA STAZIONE DI PARTENZA (VOGLIO EVITARE CHE SI PRENDANO BICI QUI)
		}
	}
}



/*****************************************************************************************************************************************/


/*--------------------------------STATIONS METHODS----------------------------------*/

void Stations::set_n_stations(int num){
	this->n_stations = num;
}

void Stations::set_n_columns_for_station(int n_c){
	this->num_columns = n_c;
}

void Stations::set_n_bikes_for_stations(int n_b){
	this->num_bikes = n_b;
}

void Stations::set_cash_desk(Users u)
{
	this->cash_desk = SUBSCRIPTION * u.n_users;
}

void Stations::update_cash_desk(Users *u, double t, double r)
{
	this->cash_desk = this->cash_desk - t - r;
}

double Stations::get_cash_desk()
{
	return this->cash_desk;
}
