/************************************************************************/
/* average_temp.h: Innehåller funktionsdeklarationer och variabler för 
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
/* average_temp: Beräknar och returnerar genomsnittstemperatur från de 
                 senaste 5 knapptrycken.                                */
/************************************************************************/
uint32_t average_temp(uint32_t* data, int size);

/************************************************************************/
/* update_average_temp: Uppdaterar genomsnittstemperaturen.             */
/************************************************************************/
void update_average_temp(const struct tmp36* self);

/************************************************************************/
/* update_executed_interrupts: Beräknar genomsnittstiden ut ifrån de 5 
                               senaste knapptryckningarna.              */
/************************************************************************/
void update_executed_interrupts(void);


#endif /* AVERAGE_TEMP_H_ */