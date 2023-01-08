/************************************************************************/
/* average_temp.c: Innehåller funktionsdefinitioner och variabler för
                   implementering av genomsnittstemperatur.             */
/************************************************************************/

/* Inkluderingsdirektiv */
#include "average_temp.h"

/* Statiska arrayer */
static uint32_t executed_interuppts[5];
static uint32_t executed_temp[5];

/* Variabler */
volatile uint32_t executed_interuppts_num = 0;
volatile uint32_t executed_temp_num = 0;
volatile uint8_t index_executed_temp = 0;
volatile uint8_t index_executed_interuppts = 0;

/************************************************************************/
/* average_temp: Beräknar och returnerar genomsnittstemperatur från de 
                 senaste 5 knapptrycken.                                */
/************************************************************************/
uint32_t average_temp(uint32_t* data, int size)
{
	uint32_t sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += data[i];
	}
	return (uint32_t)(sum / 5.0 + 0.5);
}

/************************************************************************/
/* update_average_temp: Uppdaterar genomsnittstemperaturen.             */
/************************************************************************/
void update_average_temp(const struct tmp36* self)
{
	executed_temp[index_executed_interuppts++] = tmp36_get_temperature(self);
	
	if (index_executed_interuppts >= 5)
	{
		executed_temp_num = average_temp(executed_temp, 5);
		index_executed_interuppts = 0;
	}
	return;
}

/************************************************************************/
/* update_executed_interrupts: Beräknar genomsnittstiden ut ifrån de 5 
                               senaste knapptryckningarna.              */
/************************************************************************/
void update_executed_interrupts(void)
{
	executed_interuppts[index_executed_temp++] = executed_interuppts_num;
	executed_interuppts_num = 0;
	
	if (index_executed_temp >= 5)
	{
		timer_1.counter = average_temp(executed_interuppts, 5);
		index_executed_temp = 0;
	}
	return;
}
