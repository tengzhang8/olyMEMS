//Base Station
//File: gui.c
//Implements high level functions in controlling the GUI on the graphics LCD
//Copyright C. Au and T. Zhang, 2010

#include <inttypes.h>
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ks0108.h"
#include "gui.h"
#include "rotatedheadings.h"
#include "bitmap.h"
#include "small.h"
#include "tiny.h"


// Encoder variables
volatile char prev_state[2][2];
volatile char curr_state[2][2];
int ccw = 0;
int cw = 0;


// Other variables
volatile double weight = 40;
volatile double value = 0.0;
volatile double time = 0.0;

volatile int index = 0;
int x =0;
int y = 0;


// Menu Selection States

int prev_menu_option = 1;
int temp = 0;
int temp2 = 0;
char msg[50];



//int encoder_timer_prev = 0;
//int encoder_timer_curr = 0; 
//int fast_rotate = 0;


void welcome_screen(void) {
	ks0108ClearScreen()

	LoadBitmap(IMAGE);

	for(volatile uint16_t k=0; k<10; k++) {
		for(volatile uint16_t k=0; k<50000; k++);
	}
}


// by scienceprog guy
void LoadBitmap(unsigned char *bitmap)
{
uint16_t i, j,by;
for(i=0; i<64; i+=8)

		for(j=0; j<128; j++)
		{
			by=pgm_read_byte(bitmap++);
			ks0108GotoXY(j, i);
			ks0108WriteData(by);
		}

}



void update_encoder(double max, uint8_t pgm_state) {
		// Main Menu ------------------------------------------

		// anti clockwise
		if ((ccw >= 10)&&(pgm_state == MAIN_MENU)) {
			if (prev_menu_option == 2) {
				// un-invert c+j
				ks0108InvertRect(21, 4, 94, 15);
				// invert snatch
				ks0108InvertRect(21, 20, 94, 15);
				prev_menu_option = 1;
			}

			else if (prev_menu_option == 3) {
				// un-invert pc mode
				ks0108InvertRect(21, 38, 94, 15);
				// invert c+j
				ks0108InvertRect(21, 4, 94, 15);
				prev_menu_option = 2;
			}

			else if (prev_menu_option == 1) {
				// un-invert snatch
				ks0108InvertRect(21, 20, 94, 15);
				// invert pc mode
				ks0108InvertRect(21, 38, 94, 15);
				prev_menu_option = 3;
			}
			ccw = 0;
			cw = 0;
		}

		// clockwise
		if ((cw >= 10)&&(pgm_state == MAIN_MENU)) {
			if (prev_menu_option == 2) {
				// un-invert c+j
				ks0108InvertRect(21, 4, 94, 15);
				// invert pc mode
				ks0108InvertRect(21, 38, 94, 15);
				prev_menu_option = 3;
			}

			else if (prev_menu_option == 3) {
				// un-invert pc mode
				ks0108InvertRect(21, 38, 94, 15);
				// invert snatch
				ks0108InvertRect(21, 20, 94, 15);
				prev_menu_option = 1;
			}

			else if (prev_menu_option == 1) {
				// un-invert snatch
				ks0108InvertRect(21, 20, 94, 15);
				// invert c+j
				ks0108InvertRect(21, 4, 94, 15);
				prev_menu_option = 2;
			}
			ccw = 0;
			cw = 0;
		}


		// Weight Selection ------------------------------------
if(prev_menu_option != 3) {
		if ((ccw >= 3)&&(pgm_state == WEIGHT_SEL)) {
//			if (fast_rotate) {
//				weight += 2;
//				fast_rotate = 0;
//			} else {
				weight += 0.5;
//			}
			ks0108FillRect(50, 8, 40, 20, WHITE);

			ks0108GotoXY(50,8);
			sprintf(msg, "%3.1f", weight);
			ks0108Puts(reverse(msg));

			ccw = 0;
			cw = 0;
		}

		if ((cw >= 3)&&(pgm_state == WEIGHT_SEL)) {
//			if (fast_rotate) {
//				weight -= 2;
//				fast_rotate = 0;
//			} else {
				weight -= 0.5;
//			}
			ks0108FillRect(50, 8, 40, 20, WHITE);

			ks0108GotoXY(50,8);
			sprintf(msg, "%3.1f", weight);
			ks0108Puts(reverse(msg));

			ccw = 0;
			cw = 0;
		}
}
		// Wireless stuff --------------------------------------


		// Summary of data -------------------------------------


		// Graph of acceleration -------------------------------

		if ((ccw >= 2)&&(pgm_state == ACC_GRAPH)) {
			graph_scroll(max,0);

			ccw = 0;
			cw = 0;
		}

		if ((cw >= 2)&&(pgm_state == ACC_GRAPH)) {
			graph_scroll(max,1);

			ccw = 0;
			cw = 0;
		}
}

void main_menu_setup(void) {
	ks0108ClearScreen()
	for(volatile uint16_t i=0; i<5000; i++);
	ks0108ClearScreen()
	
	display_message(0,47,38,">   PC   Mode");

	display_message(0,60,20,">   Snatch");

	display_message(0,26,4,">   Clean   &   Jerk");

	// initially select first option
	//prev_menu_option = 1;
	//ks0108InvertRect(21, 20, 94, 15);
	prev_menu_option = 3;
	ks0108InvertRect(21, 38, 94, 15);
}

int weight_menu_setup() {
		ks0108ClearScreen()

		display_message(1,5,45,"Select   the   weight   of   your");

		if (prev_menu_option == 1) {
			display_message(1,87,30,"Snatch  :");
		} else if (prev_menu_option == 2) {
			display_message(1,57,30,"Clean   &   Jerk  :");					
		} else if (prev_menu_option == 3) {
			ks0108ClearScreen()
			display_message(1,40,30,"PC   Mode   Active");	
			//pgm_state = MAIN_MENU;
			return 3;				
		}

		display_message(0,15,8,"Kg");			

		ks0108GotoXY(50,8);
		sprintf(msg, "%3.1f", weight);
		ks0108Puts(reverse(msg));
		return 0;
}


void connect_setup(uint8_t pgm_state) {
//void connect_setup() {
		ks0108ClearScreen()

//		display_message(0,40,40,"Connecting... ");
				
		display_message(1,40,40,"Waiting   for   data . . .");

		if (pgm_state == DATA_COLLECTED) {
			display_message(1,5,40,"Done");
		}
}

void summary_setup(float max_acc, float max_vel) {

	//weight = 40;

	float force = weight*max_acc;
	float power = force*max_vel;


		ks0108ClearScreen()


		// ACCELERATION
		ks0108DrawRect(58, 45, 69, 14, BLACK);
		ks0108DrawRect(0, 45, 58, 14, BLACK);
		display_message(1,67,47,"2nd  Pull  Acc");
		display_message(1,2,47,"m/s\"");
		ks0108GotoXY(27,47);
		sprintf(msg, "%.1f", max_acc);
		ks0108Puts(reverse(msg));

		// VELOCITY
		ks0108DrawRect(58, 31, 69, 14, BLACK);
		ks0108DrawRect(0, 31, 58, 14, BLACK);
		display_message(1,61,33,"Peak Velocity");
		display_message(1,6,33,"m/s");
		ks0108GotoXY(27,33);
		sprintf(msg, "%.2f", max_vel);
		ks0108Puts(reverse(msg));


		// PEAK FORCE
		ks0108DrawRect(58, 17, 69, 14, BLACK);
		ks0108DrawRect(0, 17, 58, 14, BLACK);
		display_message(1,70,19,"Peak  Force");
		display_message(1,6,19,"N");
		ks0108GotoXY(22,19);
		sprintf(msg, "%.1f", force);
		ks0108Puts(reverse(msg));

		// PEAK POWER
		ks0108DrawRect(58, 3, 69, 14, BLACK);
		ks0108DrawRect(0, 3, 58, 14, BLACK);
		display_message(1,70,5,"Peak  Power");
		display_message(1,6,5,"W");
		ks0108GotoXY(22,5);
		sprintf(msg, "%.0f", power);
		ks0108Puts(reverse(msg));


//ks0108SelectFont(small, ks0108ReadFontData, BLACK);
//		ks0108GotoXY(20,5);
//		sprintf(msg, "%.1f", power);
//		ks0108Puts(reverse(msg));

}

void graph_setup(double max) {

	uint16_t val = 0;

	max += 9.8;

	ks0108ClearScreen()
	ks0108DrawLine(127, 0, 0, 0, BLACK);
	ks0108DrawLine(127, 63, 127, 0, BLACK);

	index = 0;
	for (x=126;x>=0;x--) {
		val = (uint16_t)((((datatest[index]+9.8)*1000) * 63) / ((max)*1000));
				if ((val < 0)||(val > 63)) {
					val = 0;
				}
		ks0108SetDot(x,val, BLACK);
		if(index == 0) {
			temp = val;
		} else {
			ks0108DrawLine(x+1, temp, x, val, BLACK);
			temp = val;
		}
		index++;
//		for(volatile uint16_t k=0; k<20000; k++);
	}
	index = 127;

	ks0108FillRect(10, 23, 110, 14, WHITE);
	ks0108DrawRect(10, 23, 110, 14, BLACK);

	display_message(1,13,25,"Acceleration   vs.   Time");

	ccw = -5;
	cw = -5;
	
}


void graph_scroll(double max, char direction) {

			uint16_t val = 0;

			max += 9.8;

			ks0108FillRect(0, 1, 126, 62, WHITE);
//			ks0108FillRect(33, 1, 93, 62, WHITE);
//			ks0108FillRect(0, 1, 33, 10, WHITE);
//			ks0108FillRect(0, 56, 33, 7, WHITE);
//			ks0108FillRect(0, 1, 3, 62, WHITE);

			index -= 127;
			
	
			if (direction == 0) {
				index += 5;
			} else if (direction == 1) {
				index -= 5;
				if (index<0) {
					index = 0;
				}
			}						

			for (x=126;x>=0;x--) {
				val = (uint16_t)((((datatest[index]+9.8)*1000) * 63) / ((max)*1000));
				if ((val < 0)||(val > 63)) {
					val = 0;
				}
				if (index >= (500-127)) {
					val = (uint16_t) ((((datatest[499]+9.8)*1000) * 63) / ((max)*1000));	
				}

				ks0108SetDot(x,val, BLACK);
				if(index == 0) {
					temp = val;
				} else {
					ks0108DrawLine(x+1, temp, x, val, BLACK);
					temp = val;
				}

//				if (x == 70) {
//					value = val;
//					time = index*3;
/*
					ks0108DrawLine(x-3, val, x+3, val, BLACK);
					if (((val+3)<=63)&&((val-3)>=0)) {
						ks0108DrawLine(x, val-3, x, val+3, BLACK);
					} else if ((val+3)>63) {
						ks0108DrawLine(x, val-3, x, val+(63-val), BLACK);
					} else if ((val-3)<0) {
						ks0108DrawLine(x, val-val, x, val+3, BLACK);
					} 
*/
//				}

				index++;
			}

//			ks0108FillRect(4, 12, 28, 43, WHITE);
/*			ks0108DrawRect(4, 12, 28, 43, BLACK);

			display_message(2,12,45,"Acc:");
			display_message(2,7,23,"Time:");

			ks0108GotoXY(7,35);
			sprintf(msg, "%.1f", (value));
			ks0108Puts(reverse(msg));

			ks0108GotoXY(7,13);
			sprintf(msg, "%.1f", time);
			ks0108Puts(reverse(msg));
*/
}




//void check_time(int timer) {
//	encoder_timer_curr++;
//	fast_rotate = 0;
//}


void encoder_logic(void) {
	// check time since last interrupt
	// if < 0.1 increment by more than 1
//	if (((encoder_timer_curr - encoder_timer_prev) <= 2) && ((encoder_timer_curr - encoder_timer_prev) != 0)) {
//		fast_rotate = 1;
//	}
//	if ((encoder_timer_curr - encoder_timer_prev) <= 5) {
//		fast_rotate++;
//	}		
	// else set timer to current time

	//Obtain current states
	curr_state[0][0] = (PINE >> PE4) & 1; // A
	curr_state[0][1] = (PINE >> PE7) & 1; // B

	for(volatile uint16_t i=0; i<50; i++);

	//Process the hue encoder
	if(((prev_state[0][0] == 0) && (prev_state[0][1] == 0) && (curr_state[0][0] == 0) && (curr_state[0][1] == 1))
	|| ((prev_state[0][0] == 0) && (prev_state[0][1] == 1) && (curr_state[0][0] == 1) && (curr_state[0][1] == 1))
	|| ((prev_state[0][0] == 1) && (prev_state[0][1] == 1) && (curr_state[0][0] == 1) && (curr_state[0][1] == 0))
	|| ((prev_state[0][0] == 1) && (prev_state[0][1] == 0) && (curr_state[0][0] == 0) && (curr_state[0][1] == 1))) {
		
//		if (fast_rotate) {
//			ccw += 25;
//		} else {
			cw++;
//		}
	} 
	else if(((prev_state[0][0] == 0) && (prev_state[0][1] == 0) && (curr_state[0][0] == 1) && (curr_state[0][1] == 1))
	|| ((prev_state[0][0] == 1) && (prev_state[0][1] == 0) && (curr_state[0][0] == 1) && (curr_state[0][1] == 1))
	|| ((prev_state[0][0] == 1) && (prev_state[0][1] == 1) && (curr_state[0][0] == 0) && (curr_state[0][1] == 1))
	|| ((prev_state[0][0] == 0) && (prev_state[0][1] == 1) && (curr_state[0][0] == 0) && (curr_state[0][1] == 0))) {

//		if (fast_rotate) {
//			cw += 25;
//		} else {
			ccw++;
//		}
	}

	//Put current states into past states
	prev_state[0][0] = curr_state[0][0];
	prev_state[0][1] = curr_state[0][1];

//	encoder_timer_prev = encoder_timer_curr;
}

void init_encoders(void) {

	DDRE &= ~((1<<PORTE4)|(1<<PORTE7));
	PORTE |= (1<<PORTE4)|(1<<PORTE7);

	EICRB = 0x00;
	EICRB |= (1<<ISC40)|(1<<ISC70);
	EIMSK |= (1<<INT4)|(1<<INT7);
	SREG |= (1<<7);

	prev_state[0][0] = PINE & (1<<PORTE4);
	prev_state[0][1] = PINE & (1<<PORTE7);
}

void init_switches(void) {

	DDRE &= ~((1<<PORTE5));
	PORTE &= ~((1<<PORTE5));

	EICRB |= (1<<ISC51);
	EIMSK |= (1<<INT5);
	SREG |= (1<<7);

}

void display_message(char fontnum,char co_ord_x, char co_ord_y,char *input) {

	if (fontnum == 0) {
		ks0108SelectFont(rotatedheadings, ks0108ReadFontData, BLACK);
	} else if (fontnum == 1) {
		ks0108SelectFont(small, ks0108ReadFontData, BLACK);
	} else if (fontnum == 2) {
		ks0108SelectFont(tiny, ks0108ReadFontData, BLACK);
	}

	ks0108GotoXY(co_ord_x,co_ord_y);
	sprintf(msg, input);
	ks0108Puts(reverse(msg));

}

char *reverse (char *input) {
	char temp;
	int i = 0;
	int j = 0;

	while (input[i] != '\0') {
		i++;
	}

	for (j=0;j<(i/2);j++) {
		temp = input[j];
		input[j] = input[i-1-j];
		input[i-1-j] = temp;
	}

	return input;
}
