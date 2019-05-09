#include "Station.h"
#include <time.h>


/*AD OGNI PARTENZA CONTROLLA LO STATO DELLE COLONNINE E DELLE BICI DI OGNI STAZIONE*/
void budget_time_update(Stations *inststations)
{
	printf("++++++++------------CRITICAL STATIONS------------++++++++\n\n");
	for (int i = 0; i < inststations->n_stations; i++)
	{
		int columns = inststations->all_stations[i].av_columns();
		int bikes = inststations->all_stations[i].av_bikes();

		/*SE CI SONO SOLO BICI O SOLO COLONNINE VUOTE ALLORA SPINGO PER PRELEVARE/DEPOSITARE*/

		if ((columns == 0))//STAZIONE SENZA COLONNINE LIBERE
		{
			//SE NON E' STATA MAI SELEZIONATA COME CRITICA ALLORA LA SELEZIONO E FACCIO PARTIRE IL TEMPO
			if (inststations->critical_station[i] == 0)
			{
				printf("Station %d is critical(full of bikes) \n", i + 1);

				inststations->critical_station[i] = 1;
				inststations->all_stations[i].critical_full_counter++;//AGGIORNO CONTATORE CRITICITA' STAZIONE i-ESIMA PIENA
				inststations->all_stations[i].time0_full_station = (double)clock();
			}
			else//QUALORA FOSSE GIA' CRITICA PRENDO IL TEMPO PER CUI E' CRITICA
			{
				double current_time_full = (double)clock();
				inststations->all_stations[i].station_full_time = (double)(current_time_full - inststations->all_stations[i].time0_full_station) / CLOCKS_PER_SEC;
				printf("Station %d full of bikes for %lf seconds \n", i + 1, inststations->all_stations[i].station_full_time);
			}
		}
		else if ((bikes == 0))//STAZIONE SENZA BICI
		{
			//SE NON E' STATA MAI SELEZIONATA COME CRITICA ALLORA LA SELEZIONO E FACCIO PARTIRE IL TEMPO
			if (inststations->critical_station[i] == 0)
			{
				printf("Station %d is critical(empty of bikes) \n", i + 1);

				inststations->critical_station[i] = 1;
				inststations->all_stations[i].critical_empty_counter++;//AGGIORNO CONTATORE CRITICITA' STAZIONE i-ESIMA VUOTA
				inststations->all_stations[i].time0_empty_station = (double)clock();
			}
			else
			{
				double current_time_empty = (double)clock();
				inststations->all_stations[i].station_empty_time = (double)(current_time_empty - inststations->all_stations[i].time0_empty_station) / CLOCKS_PER_SEC;
				printf("Station %d empty of bikes for %lf seconds \n", i + 1, inststations->all_stations[i].station_empty_time);
			}

		}
		else//DICO CHE LA STAZIONE NON E' PIU' CRITICA E AZZERO I TEMPI PER CUI E' STATA CRITICA IN MODO DA RIPARTIRE DA 0 SUCESSIVAMENTE
		{
			inststations->critical_station[i] = 0;
			printf("STO AZZERANDO I TEMPI DELLE STAZIONI \n");
			inststations->all_stations[i].station_empty_time = 0;
			inststations->all_stations[i].station_full_time = 0;
		}
	}
}