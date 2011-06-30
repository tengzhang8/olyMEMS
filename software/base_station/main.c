//Base Station
//File: main.c
//Main source file for the Base Station
//Copyright C. Au and T. Zhang, 2010

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <avr/boot.h> 

#include "uart.h"
#include "ks0108.h"
#include "gui.h"
#include "small.h"

#include "nordic_spi.h"
#include "nrf24l01.h"
#include "delay.h"


#ifndef F_CPU
#define F_CPU 7372800UL
#endif

#define XTAL		7372800L    // Crystal frequency in Hz
#define UART_BAUD_RATE      115200

#define PACKET_SIZE 16

//Global Variables
volatile uint32_t tenms = 0;
volatile uint32_t main_timer = 0;

volatile int currenttimer = 0;
volatile int button_timer = 0;
volatile int button_prev = 0;
volatile int button_current = 0;
volatile int cond = 0;
volatile int h = 0;
volatile int i = 0;
volatile int first_dip = 0;
volatile int lastval = 0;
volatile int pc_mode = 0;


volatile uint8_t pgm_state = 0;
volatile double avg = 0;
volatile double max = 0;
volatile double max_second_pull = 0;

float	 yaxis_n[3], yaxis_max[3];

void update_gui(void);
void update_button(int back);


void boot_program_page (uint32_t page, uint8_t *buf) BOOTLOADER_SECTION; 
void disassemble_bytepacket(uint8_t *byte_data, uint8_t *datatype, uint8_t *datanumber,
							uint8_t *data1, int len1, 
							uint8_t *data2, int len2,
							uint8_t *data3, int len3);

volatile uint8_t c[256] __attribute__ ((aligned (256))) = "223456789"; 

static FILE mystdout = FDEV_SETUP_STREAM(uart_putc, NULL, _FDEV_SETUP_WRITE);

//char FlashString[] PROGMEM = "This is a string held completely in flash memory."; 

// handler for Output Compare 1 overflow interrupt
ISR(SIG_OUTPUT_COMPARE1A)  
{
	tenms++;
}

// encoder A change
ISR(INT4_vect) {
	encoder_logic();
}
// encoder B change
ISR(INT7_vect) {
	encoder_logic();
}
// encoder SW change
ISR(INT5_vect) {
	button_current = (PINE >> PE5) & 1;

	button_timer = 0;
	while (button_current == 0) {
		button_current = (PINE >> PE5) & 1;
		h++;
		if (h >= 1280) {
			button_timer++;
			h = 0;
		}
		if (button_timer >= 150) {
			update_button(1);
			cond = 1;
			button_current = 1;
		}
	}

	if (cond == 0) {
		update_button(0);
	}
	h = 0;
	cond = 0;
}



void boot_program_page (uint32_t page, uint8_t *buf)
{
    uint16_t i;
    uint8_t sreg;

    // Disable interrupts.

    sreg = SREG;
    cli();
   
    eeprom_busy_wait ();

    boot_page_erase (page);
    boot_spm_busy_wait ();      // Wait until the memory is erased.

    for (i=0; i<SPM_PAGESIZE; i+=2)
    {
       // Set up little-endian word.

        uint16_t w = *buf++;
        w += (*buf++) << 8;
       
        boot_page_fill (page + i, w);
    }

    boot_page_write (page);     // Store buffer in flash page.
    boot_spm_busy_wait();       // Wait until the memory is written.

    // Reenable RWW-section again. We need this if we want to jump back
    // to the application after bootloading.

    boot_rww_enable ();
 
    // Re-enable interrupts (if they were ever enabled).
   sei();

    SREG = sreg;
} 

int main(void) {
//	char c1 = 0;
	int k = 0;

//	char buffer[10];
	uint8_t nordic_data[32];
	int	nordic_sample_number = 0;
	double nordic_double_data[4];
	int		nordic_raw_data[4];

	uint16_t bmadata[4];
	uint16_t gyrodata[4];
	float	 vertical_data[3];
	uint16_t datanumber;
	uint8_t  datatype;



//	char *point = NULL;

	//Test CS
	//DDRD |= (1<<PD4);
	//PORTD |= (1<<PD4);

	// Timer setup
    // use CLK/64 prescale value, clear timer/counter on compareA match                               
   	TCCR1B = _BV(CS11) | _BV(WGM12);
    // preset timer1 high/low byte
    OCR1A = 9216; // 10 milliseconds  
    // enable Output Compare 1 overflow interrupt
    TIMSK  = _BV(OCIE1A); 
	main_timer = tenms;
	
	init_nordic_spi();
	nrf24l01_initialize_debug(true, 32, false); //Initailize as RX, 1 data byte and auto-acknowledge on

	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
	stdout = &mystdout;

	// Wait a little while the display starts up
	for(volatile uint16_t i=0; i<10000; i++);
	// Initialize the LCD
	ks0108Init(0);
	// Wait a little while the display starts up
	for(volatile uint16_t i=0; i<10000; i++);


	init_encoders();
	init_switches();

	sei();

	// Display welcome screen
	pgm_state = WELCOME_SCR;
	update_gui();


	// Set up main menu
	pgm_state = MAIN_MENU;
	update_gui();


	printf("SYSTEM INITIALIZED\n\r");
 

	while(1) {

		if ((pgm_state == CONNECT_SCR) || (pc_mode == 1)) {
//		if (pc_mode == 1) {
		//for(volatile uint16_t i=0; i<5000; i++);
		//printf("TENG IS AWESOME\n\r");
			while ((!(nrf24l01_irq_pin_active() && nrf24l01_irq_rx_dr_active()))) {
				update_encoder(max,pgm_state);
			}
		    nrf24l01_read_rx_payload(nordic_data, 32); //read the packet into data 
		    nrf24l01_irq_clear_all(); //clear all interrupts in the 24L01 
			//nordic_data[1] = '\0';

		//printf("%s\n\r", nordic_data);
			disassemble_bytepacket(nordic_data, &datatype, (void*)&datanumber,
								(void*)vertical_data, 3*sizeof(float),
								(void*)bmadata, 4*sizeof(uint16_t),
								(void*)gyrodata, 4*sizeof(uint16_t));

			//if (datanumber == 0) {
			//	pgm_state = CONNECT_SCR;
			//	update_gui();
			//}			


			if(datatype == 0) {

				disassemble_bytepacket(nordic_data, &datatype, (void*)&datanumber,
								(void*)vertical_data, 3*sizeof(float),
								(void*)bmadata, 4*sizeof(uint16_t),
								(void*)gyrodata, 4*sizeof(uint16_t));
//				printf("%d#F:%.4f:%.4f:%.4f#A#X:%dY:%dZ:%dT:%d#G#X:%dY:%dZ:%dT%d\n\r",(unsigned int)datanumber, vertical_data[0],vertical_data[1],vertical_data[2],bmadata[0],bmadata[1],bmadata[2],bmadata[3],gyrodata[0],gyrodata[1],gyrodata[2],gyrodata[3]);
//				printf("%d#F:%.4f:%.4f:%.4f\n\r",(unsigned int)datanumber, vertical_data[0],vertical_data[1],vertical_data[2]);
				//if (pc_mode) {
					// acc angle, gyro angle, kalman angle
					printf("%d:A%.4f,B%.4f,C%.4f,S123\r\n",(unsigned int)datanumber, vertical_data[0],vertical_data[1],vertical_data[2]);
					// acc x,y,z
					printf("%d:D%d,E%d,F%d\r\n",(unsigned int)datanumber, bmadata[0],bmadata[1],bmadata[2]);
					// gyro x, y, z
					printf("%d:G%d,H%d,I%d\r\n",(unsigned int)datanumber, gyrodata[0],gyrodata[1],gyrodata[2]);
				//}

			}
			else if (datatype == 1) {

				disassemble_bytepacket(nordic_data, &datatype, (void*)&datanumber,
									(void*)yaxis_n, 3*sizeof(float),
									(void*)bmadata, 0,
									(void*)gyrodata, 0);

				//if (pc_mode) {
					printf("%d:J%.4f,K%.4f,L%.4f,Z123\r\n",(unsigned int)datanumber, yaxis_n[0], yaxis_n[1], yaxis_n[2]);
				//}

			}
			else if (datatype == 2) {
				disassemble_bytepacket(nordic_data, &datatype, (void*)&datanumber,
									(void*)yaxis_max, 3*sizeof(float),
									(void*)bmadata, 0,
									(void*)gyrodata, 0);

				//if (pc_mode) {
					printf("%d:M%.4f,N%.4f,P%.4f,Z123\r\n",(unsigned int)datanumber, yaxis_max[0], yaxis_max[1], yaxis_max[2]);
					printf("&&&&&&&&&&&&&&&&&&&&&\r\n");
					printf("&&&&&&&&&&&&&&&&&&&&&\r\n");
					printf("&&&&&&&&&&&&&&&&&&&&&\r\n");
					printf("&&&&&&&&&&&&&&&&&&&&&\r\n");
					printf("&&&&&&&&&&&&&&&&&&&&&\r\n");
					printf("&&&&&&&&&&&&&&&&&&&&&\r\n");
					printf("&&&&&&&&&&&&&&&&&&&&&\r\n");
					printf("&&&&&&&&&&&&&&&&&&&&&\r\n");
					printf("&&&&&&&&&&&&&&&&&&&&&\r\n");
					printf("&&&&&&&&&&&&&&&&&&&&&\r\n");
					printf("&&&&&&&&&&&&&&&&&&&&&\r\n");
					printf("&&&&&&&&&&&&&&&&&&&&&\r\n");
					printf("&&&&&&&&&&&&&&&&&&&&&\r\n");
				//}

				pgm_state = SUMMARY_SCR;
				ks0108ClearScreen()
				update_gui();
			}
		}
			

		// respond to encoder movements
		update_encoder(max,pgm_state);
		
	}
}

void update_gui(void) {
		if (pgm_state == WELCOME_SCR) {
			welcome_screen();
		} else if (pgm_state == MAIN_MENU) {
			main_menu_setup();
		} else if (pgm_state == WEIGHT_SEL) {

		} else if (pgm_state == CONNECT_SCR) {
			connect_setup(CONNECT_SCR);
			printf("WAITING FOR DATA\n\r");
			pc_mode = 1;
		} else if (pgm_state == SUMMARY_SCR) {
			summary_setup(yaxis_max[0], yaxis_max[1]);
//		} else if (pgm_state == ACC_GRAPH) {
//			graph_setup(max);
		}

}

void update_button(int back) {

			if (pgm_state == MAIN_MENU) {
				pgm_state = WEIGHT_SEL;
				if (weight_menu_setup() == 3) {
					pc_mode = 1;
				} else {
					pc_mode = 0;
				}
			} else if (pgm_state == WEIGHT_SEL) {
				pgm_state = CONNECT_SCR;
				
//				if (back == 1) {
//					pgm_state = MAIN_MENU;
//				}
		//		if (pc_mode == 1) {
		//			pgm_state = MAIN_MENU;
		//			pc_mode = 0;
		//		}
			} else if (pgm_state == CONNECT_SCR) {
//				pgm_state = WEIGHT_SEL;
				pgm_state = SUMMARY_SCR;	

//				if (back == 1) {
//					pgm_state = WEIGHT_SEL;
//				}	
//			} else if (pgm_state == DATA_COLLECTED) {
//				pgm_state = SUMMARY_SCR;	
//				if (back == 1) {
//					pgm_state = WEIGHT_SEL;
//				}									
			} else if (pgm_state == SUMMARY_SCR) {
//				pgm_state = ACC_GRAPH;
//				if (back == 1) {
					pgm_state = MAIN_MENU;
//				} 								
//			} else if (pgm_state == ACC_GRAPH) {
//				pgm_state = MAIN_MENU;
//				if (back == 1) {
//					pgm_state = SUMMARY_SCR;
//				}
				pc_mode = 0;
			}

			update_gui();
}


void disassemble_bytepacket(uint8_t *byte_data, uint8_t *datatype, uint8_t *datanumber,
							uint8_t *data1, int len1, 
							uint8_t *data2, int len2,
							uint8_t *data3, int len3) {

	int i;

	*datatype = byte_data[0];
	datanumber[0] = byte_data[1];
	datanumber[1] = byte_data[2];

	for(i=0;i<len1;i++) {
		data1[i] = byte_data[i+3];
	}

	for(i=i;i<(len1+len2);i++) {
		data2[i-len1] = byte_data[i+3];
	}

	for(i=i;i<(len1+len2+len3);i++) {
		data3[i-(len1+len2)] = byte_data[i+3];
	}
}
