/************************************************************************/
/* Interrupts.c: Innehåller avbrottsrutiner för timerkretasr samt 
                 tryckknapp.                                            */
/************************************************************************/
#include "setup.h"
#include "average_temp.h"

/************************************************************************/
/* ISR (TIMER1_COMPA_vect): Avbrottsrutin för TIMER_1 som sker vid 
                            uppräking till 256 av TIMER_1 i CTC mode, 
							vilket sker var 0.128 ms.
							
							När TIMER_1 når dess max_count skrivs 
							temperaturen ut till en seriell monitor och
							timern nollställs.                          */
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
/* ISR (PCINT0_vect): Avbrottsrutin för tryckknapp. 
                      Avbrott inaktiveras för att undvika kontaktstudsar.
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
/* ISR (TOMER0_OVF_vect):  Avbrottsrutin för TIMER_0 som sker vid overflow
                           av TIMER_0. Vilket innebär uppräkning till 256
						   som sker var 0.128 ms.
						   
						   Avbrottsrutinen är till för att aktivera 
						   avbrott på tryckknappen igen efter undvikning
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
