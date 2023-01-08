/************************************************************************/
/* average_temp.h: Inneh�ller funktionsdeklarationer och variabler f�r 
                   implementering av genomsnittstemperatur.             */
/************************************************************************/
#ifndef AVERAGE_TEMP_H_
#define AVERAGE_TEMP_H_

/* Inkluderingsdirektiv */
#include "setup.h"

/* Statiska arrayer */
static uint32_t executed_interuppts[];
static uint32_t executed_temp[];

/* Variabler */
extern volatile uint32_t executed_interuppts_num;
extern volatile uint32_t executed_temp_num;
extern volatile uint8_t index_executed_temp;
extern volatile uint8_t index_executed_interuppts;

/* Funktionsdeklarationer */
/************************************************************************/
/* average_temp: Ber�knar och returnerar genomsnittstemperatur fr�n de 
                 senaste 5 knapptrycken.                                */
/************************************************************************/
uint32_t average_temp(uint32_t* data, int size);

/************************************************************************/
/* update_average_temp: Uppdaterar genomsnittstemperaturen.             */
/************************************************************************/
void update_average_temp(const struct tmp36* self);

/************************************************************************/
/* update_executed_interrupts: Ber�knar genomsnittstiden ut ifr�n de 5 
                               senaste knapptryckningarna.              */
/************************************************************************/
void update_executed_interrupts(void);


#endif /* AVERAGE_TEMP_H_ */