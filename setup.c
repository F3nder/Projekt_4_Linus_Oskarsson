/************************************************************************/
/* setup.c: Innehåller struktar för implementering av 
            temperaturmätning samt funktionsdefinition.                 */
/************************************************************************/

/* Inkluderingsdirektiv */
#include "setup.h"

/* Definition av struktar */
struct button b1;
struct tmp36 temp_1;
struct timer timer_1;
struct timer timer_0;

/************************************************************************/
/* setup: Initierar tryckknapp, temperatursensor samt timers och ställer
          in deras max_count TIMER_0 = 300ms, TIMER_1 1 minut. Samt 
		  aktiverar avbrott för dessa.                                  */
/************************************************************************/
void setup(void)
{
    button_init(&b1, 13);
	button_enable_interrupt(&b1);
	
	tmp36_init(&temp_1, A2);
	tmp36_print_temperature(&temp_1);
	
	timer_init(&timer_0, TIMER_SEL_0, 300);
	timer_set_new_time(&timer_0, 300);
	timer_enable_interrupt(&timer_0);
	
	timer_init(&timer_1, TIMER_SEL_1, 60000);
	timer_set_new_time(&timer_1, 60000);
	timer_enable_interrupt(&timer_1);
	
	return;
}