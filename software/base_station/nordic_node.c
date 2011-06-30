#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "nordic_spi.h"
#include "nrf24l01.h"
#include "delay.h"
#include "uart.h"


#define F_CPU			8000000L
#define UART_BAUD_RATE	38400

int main() {

	char data = 'k';

	char buffer[36];

	DDRD |= (1<<PD1)|(1<<PD0);

	//PRR &= ~(1<<PRUSART0);

	init_nordic_spi();
	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));
	sei();

	nrf24l01_initialize_debug(true, 1, false); //Initailize as RX, 1 data byte and auto-acknowledge off

	//nrf24l01_irq_clear_all();

	while(1) {

      //wait until a packet has been received 
	  //while(nrf24l01_irq_pin_active());
      //while(!(1 && nrf24l01_irq_rx_dr_active())); 

	  while(data = nrf24l01_irq_pin_active()) {
	  
	  		//if(nrf24l01_irq_rx_dr_active()) {
	 

      		nrf24l01_read_rx_payload(&data, 1); //read the packet into data 
      		nrf24l01_irq_clear_all(); //clear all interrupts in the 24L01 
	  		nrf24l01_set_as_rx(true);

		//nrf24l01_get_all_registers(buffer);

			itoa(data,buffer,10);

	  		uart_puts(buffer);

	  //PORTD ^= (1<<PD0);

	  //nrf24l01_clear_csn();
	  //nrf24l01_set_csn();      

      //delay_10us_multiple(130); //wait for the other 24L01 to come from standby to RX 
      
	  //nrf24l01_set_csn();

	   		delay_10us_multiple(13);
			//}
		}

	  /*
      nrf24l01_set_as_tx(); //change the device to a TX to send back from the other 24L01 
      nrf24l01_write_tx_payload(&data, 1, true); //transmit received char over RF 
       
      //wait until the packet has been sent 
      while(!(nrf24l01_irq_pin_active() && nrf24l01_irq_tx_ds_active())); 

      nrf24l01_irq_clear_all(); //clear interrupts again 
      nrf24l01_set_as_rx(true); //resume normal operation as an RX 

      //ToggleLED(); //toggle the on-board LED as visual indication that the loop has completed 

	  */

	}

}
