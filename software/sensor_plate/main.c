/**************************************************************************/
/*! 
    @file     main.c
    @author   K. Townsend (microBuilder.eu)

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2010, microBuilder SARL
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/
#include "projectconfig.h"
#include "sysinit.h"

#include <math.h>

#include "drivers/itg3200/itg3200.h"
#include "drivers/bma180/bma180_lpc.h"
#include "drivers/nordic/nordic_spi.h"
#include "drivers/nordic/nrf24l01.h"
#include "drivers/kalman/kalman.h"
#include "core/pmu/pmu.h"
#include "core/timer16/timer16.h"
#include "core/timer32/timer32.h"


#ifdef CFG_INTERFACE
  #include "core/cmd/cmd.h"
#endif

void assemble_bytepacket(uint8_t *byte_data, uint8_t datatype, uint8_t *datanumber, 
							uint8_t *data1, int len1, 
							uint8_t *data2, int len2,
							uint8_t *data3, int len3);


/**************************************************************************/
/*! 
    Approximates a 1 millisecond delay using "nop".  This is less
    accurate than a dedicated timer, but is useful in certain situations.

    The number of ticks to delay depends on the optimisation level set
    when compiling (-O).  Depending on the compiler settings, one of the
    two defined values for 'delay' should be used.
*/
/**************************************************************************/
void delayms(uint32_t ms)
{
  uint32_t delay = ms * ((CFG_CPU_CCLK / 100) / 80);      // Release Mode (-Os)
  // uint32_t delay = ms * ((CFG_CPU_CCLK / 100) / 140);  // Debug Mode (No optimisations)

  while (delay > 0)
  {
    __asm volatile ("nop");
    delay--;
  }
}

  // Gyro variables
//extern volatile  int32_t gyrot; // Gyro Temp Out
//extern volatile  int32_t gyrox; // Gyro X Out
//extern volatile  int32_t gyroy; // Gyro Y Out
//extern volatile  int32_t gyroz; // Gyro Z Out
//extern volatile int testdata[4];

kalman angle_kalman_state;

/**************************************************************************/
/*! 
    Main program entry point.  After reset, normal code execution will
    begin here.
*/
/**************************************************************************/
int main (void)
{
	uint8_t byte_packet[32];
	
	uint16_t sample_number = 0;


  uint32_t currentSecond, lastSecond;
  currentSecond = lastSecond = 0;
  
//int32_t gyrot; // Gyro Temp Out
//int32_t gyrox; // Gyro X Out
//int32_t gyroy; // Gyro Y Out
//int32_t gyroz; // Gyro Z Out

int16_t gyrodata[4];
float	vertical_data[3];
float	cumulative_gyroz;

float	gyroz_n,accelx_n,accely_n,angle_acc,angle_est;

float	yaxis_n[3] = {0.0,0.0,0.0};
float	yaxis_max[3] = {0.0,0.0,0.0};
float	yaxis_env = 0;

int8_t	prgm_state;

  // BMA180 variables
  int16_t testdata[4];
  
  //testdata[0] = atan2(2,5);
  
  //vertical_data[0] = atan2(2,5);
  //vertical_data[1] = 2.791;
  //vertical_data[2] = 3.141;

  // Initialise power management
  
   systemInit(); 
  
  gpioSetDir(1,8,gpioDirection_Output);   //Init PS FET
  gpioSetValue(1,8,1);
  pmuInit();
  pmuPowerDown();
   
  // Configure cpu and mandatory peripherals
  //systemInit();  
  


    // Initialise 32-bit timer 0 with 100uS ticks
    timer32Init(1, TIMER32_DEFAULTINTERVAL);

    // Enable timer 0
    timer32Enable(1);

    // Cause a blocking delay for 1 second (1000mS)
    //timer32Delay(1, TIMER32_DELAY_1MS * 100);
  
  gpioSetDir(1,8,gpioDirection_Output);   //Init PS FET
  gpioSetValue(1,8,0);
  
    // Cause a blocking delay for 1 second (1000mS)
    timer32Delay(1, TIMER32_DELAY_1MS * 100);

	//systemInit();

  init_nordic_spi();
  nrf24l01_initialize_debug(false, 32, false);
  
  gpioSetValue (CFG_LED_PORT, CFG_LED_PIN, CFG_LED_ON);
  //switch_BMA180();
  init_BMA180(0x04,0x00);

  gyroinit();
  
  
  prgm_state = 0;

  
  // Timer Test
  // 10Hz
//  timer32Init(0, 4800000);
  // Enable the timer
//  timer32Enable(0);
  
	//unsigned char testchar[32] = "carson is the awesomest person!";
  
  
//Test Sleep On - first read button as input
/*
  gpioSetDir(1,4,gpioDirection_Input);
  while (1) {
	  if(gpioGetValue(1,4) == 0) {
		  gpioSetValue (CFG_LED_PORT, CFG_LED_PIN, CFG_LED_ON);
	  }
	  else {
		  gpioSetValue (CFG_LED_PORT, CFG_LED_PIN, CFG_LED_OFF);
	  }
  }
*/
  
  while (1)
  {
    currentSecond = systickGetTicks();
    if (currentSecond >= lastSecond + 10)
    {
	
		switch_BMA180();
		sample_BMA180(testdata);	
		readgyro(8, &gyrodata[0], &gyrodata[1], &gyrodata[2], &gyrodata[3]);
		 
		
		//Preprocess Raw Data
		gyroz_n = (float)gyrodata[2];
		//ITG-3200 outputs 14.375 LSB per degree/sec --> degree/sec
		gyroz_n = gyroz_n*0.069565;
		
		//Integrate gyro. Basic.
		cumulative_gyroz += gyroz_n/100;
		
		accelx_n = (float)testdata[0];
		accely_n = (float)testdata[1];
		
		//Correct common mode offset
		accelx_n = accelx_n + 33.7915;
		accely_n = accely_n + 151.148;
		
		//Correct inter-axis dependency
		accely_n = accely_n - 37*(accelx_n/2048);
		accelx_n = accelx_n + 42*(accely_n/2048);
		
		accelx_n = accelx_n / 2048;
		accely_n = accely_n / 2048;
		
		angle_acc = atan2(-accely_n,accelx_n)*57.29578;
		
		vertical_data[0] = angle_acc;
		
		if(sample_number <= 0) {
			kalman_init(&angle_kalman_state, 0.01, 17000, 0.0001, 0.3, angle_acc, 0.0);
			cumulative_gyroz = angle_acc;
		}
		
		//Kalman Update
		angle_est = kalman_update(&angle_kalman_state, gyroz_n, angle_acc);
		//angle_est = 124.23;
		//printf("Teng: %d \r\n", (int)angle_est);

		//Make sure angle est is within bounds
		if(cumulative_gyroz > 180) {
			cumulative_gyroz -= 360.0;
		} else if (cumulative_gyroz < -180) {
			cumulative_gyroz += 360.0;
		}

		vertical_data[1] = cumulative_gyroz;

		//Make sure angle est is within bounds
		if(angle_est > 180) {
			angle_est -= 360.0;
		} else if (angle_est < -180) {
			angle_est += 360.0;
		}

		//Calculate vertical acceleration component
		yaxis_n[0] = -sin(angle_est/57.29578)*accely_n + cos(angle_est/57.29578)*accelx_n;
		yaxis_n[0] = 9.8*(yaxis_n[0] - 1);
		
		if(yaxis_n[0] > yaxis_max[0]) {
			yaxis_max[0] = yaxis_n[0];
		}
		
		if(yaxis_n[0] > yaxis_env) {
			yaxis_env = yaxis_n[0];
		}
		else if(yaxis_n[0] < -yaxis_env) {
			yaxis_env = -yaxis_n[0];
		}
		else if(yaxis_n[0] < 0) {
			yaxis_env = yaxis_env - ((yaxis_env + yaxis_n[0])/25);
		}
		else {
			yaxis_env = yaxis_env - ((yaxis_env - yaxis_n[0])/25);
		}
		
		if((prgm_state == 0) && (yaxis_env > 1)) {
			sample_number = 0;
			prgm_state = 1;
			
			//Reset Max Variables
			yaxis_max[0] = 0.0;
			yaxis_max[1] = 0.0;
			yaxis_max[2] = 0.0;
			
			//Reset Velocity/Displacement
			yaxis_n[1] = 0.0;
			yaxis_n[2] = 0.0;
		}
		else if((prgm_state == 1) && (yaxis_env < 0.75)) {
			
			assemble_bytepacket(byte_packet, 2, (void*)&sample_number,
							(void*)yaxis_max, 3*sizeof(float),
							(void*)yaxis_max, 0,
							(void*)yaxis_max, 0);

			timer32Delay(1, TIMER32_DELAY_1MS * 5);
 		
			switch_nordic();
			nrf24l01_write_tx_payload(byte_packet, 32, true); 
			while(!(nrf24l01_irq_pin_active() && nrf24l01_irq_tx_ds_active())); 
				  //|| nrf24l01_irq_max_rt_active())));
				  
			nrf24l01_irq_clear_all();
			prgm_state = 0;
		}


		if((prgm_state == 1) && sample_number >= 0) {
			
			gpioSetValue (CFG_LED_PORT, CFG_LED_PIN, CFG_LED_OFF); 
			
			vertical_data[2] = (float)angle_est;
			
			//Integrate acceleration to get velocity
			yaxis_n[1] += yaxis_n[0]/100;
			
			if(yaxis_n[1] > yaxis_max[1]) {
				yaxis_max[1] = yaxis_n[1];
			}
			
			//Integrate velocity to get displacement
			yaxis_n[2] += yaxis_n[1]/100;
			
			if(yaxis_n[2] > yaxis_max[2]) {
				yaxis_max[2] = yaxis_n[2];
			}
			
			assemble_bytepacket(byte_packet, 0, (void*)&sample_number,
							(void*)vertical_data, 3*sizeof(float),
							(void*)testdata, 4*sizeof(int16_t),
							(void*)gyrodata, 4*sizeof(int16_t));

 		
			switch_nordic();
			nrf24l01_write_tx_payload(byte_packet, 32, true); 
			while(!(nrf24l01_irq_pin_active() && nrf24l01_irq_tx_ds_active())); 
				  //|| nrf24l01_irq_max_rt_active())));
				  
			nrf24l01_irq_clear_all();
		

		
			assemble_bytepacket(byte_packet, 1, (void*)&sample_number,
								(void*)yaxis_n, 3*sizeof(float),
								(void*)yaxis_n, 0,
								(void*)yaxis_n, 0);

			timer32Delay(1, TIMER32_DELAY_1MS * 3);

			nrf24l01_write_tx_payload(byte_packet, 32, true); 
			while(!(nrf24l01_irq_pin_active() && nrf24l01_irq_tx_ds_active())); 
				  //|| nrf24l01_irq_max_rt_active())));
				  
			nrf24l01_irq_clear_all();

			
		}
		
		
	  gpioSetValue (CFG_LED_PORT, CFG_LED_PIN, CFG_LED_ON);
		

	  lastSecond = currentSecond;
	  
	  sample_number++;
		
    }

    // Poll for CLI input if CFG_INTERFACE is enabled in projectconfig.h
    #ifdef CFG_INTERFACE 
      cmdPoll(); 
    #endif
  }
}

void assemble_bytepacket(uint8_t *byte_data, uint8_t datatype, uint8_t *datanumber, 
							uint8_t *data1, int len1, 
							uint8_t *data2, int len2,
							uint8_t *data3, int len3) {
	
	int i;
	
	byte_data[0] = datatype;
	byte_data[1] = datanumber[0];
	byte_data[2] = datanumber[1];
	
	for(i=0;i<len1;i++) {
		byte_data[i+3] = data1[i];
	}
	
	for(i=i;i<(len1+len2);i++) {
		byte_data[i+3] = data2[i-len1];
	}

	for(i=i;i<(len1+len2+len3);i++) {
		byte_data[i+3] = data3[i-(len1+len2)];
	}
	
}