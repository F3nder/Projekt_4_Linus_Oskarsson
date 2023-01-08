/************************************************************************/
/* setup.h: Innehåller externa struktar för implementering av 
            temperaturmätning samt funktionsdeklaration.                */
/************************************************************************/
#ifndef SETUP_H_
#define SETUP_H_

/* Inkluderingsdirektiv */
#include "button.h"
#include "timer.h"
#include "tmp36.h"

/* Struktar */
extern struct button b1;
extern struct tmp36 temp_1;
extern struct timer timer_0;
extern struct timer timer_1;

/* Funktionsdeklaration */
/************************************************************************/
/* setup: Initierar tryckknapp, temperatursensor samt timers och ställer
          in deras max_count TIMER_0 = 300ms, TIMER_1 1 minut. Samt 
		  aktiverar avbrott för dessa.                                  */
/************************************************************************/
void setup(void);

#endif /* SETUP_H_ */