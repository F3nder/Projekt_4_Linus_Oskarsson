/************************************************************************/
/* Interrupts.c: Inneh�ller avbrottsrutiner f�r timerkretasr samt 
                 tryckknapp.                                            */
/************************************************************************/
#include "setup.h"
#include "average_temp.h"

/************************************************************************/
/* ISR (TIMER1_COMPA_vect): Avbrottsrutin f�r TIMER_1 som sker vid 
                            uppr�king till 256 av TIMER_1 i CTC mode, 
							vilket sker var 0.128 ms.
							
							N�r TIMER_1 n�r dess max_count skrivs 
							temperaturen ut till en seriell monitor och
							timern nollst�lls.                          */
/************************************************************************/
ISR (TIMER1_COMPA_vect)
{
	timer_count(&timer_1);
	
	if (timer_1.counter >= timer_1.max_count)
	{
        tmp36_print_temperature(&temp_1);
		timer_reset_counter(&timer_1);
	}
	return;
}

/************************************************************************/
/* ISR (PCINT0_vect): Avbrottsrutin f�r tryckknapp. 
                      Avbrott inaktiveras f�r att undvika kontaktstudsar.
					  Temperaturen skrivs ut samt den genomsnittliga 
					  temperaturen mellan de 5 senaste knapptrycken.    */
/************************************************************************/
ISR (PCINT0_vect)
{
	PCICR &= ~(1 << PCIE0);
	TIMSK0 = (1 << TOIE0);
	
	if (button_is_pressed(&b1))
	{
		tmp36_print_temperature(&temp_1);
		timer_reset_counter(&timer_1);
		update_executed_interrupts();
		update_average_temp(&temp_1);
		tmp36_print_average_temperature(executed_temp_num);
	}
	return;
}

/************************************************************************/
/* ISR (TOMER0_OVF_vect):  Avbrottsrutin f�r TIMER_0 som sker vid overflow
                           av TIMER_0. Vilket inneb�r uppr�kning till 256
						   som sker var 0.128 ms.
						   
						   Avbrottsrutinen �r till f�r att aktivera 
						   avbrott p� tryckknappen igen efter undvikning
						   av kontaktstudsar.                           */
/************************************************************************/
ISR (TIMER0_OVF_vect)
{	
	timer_count(&timer_0);
	
	if (timer_0.counter >= timer_0.max_count)
	{
		PCICR = (1 << PCIE0);
		TIMSK0 = 0x00;
        timer_reset_counter(&timer_0);
	}
	return;
}
