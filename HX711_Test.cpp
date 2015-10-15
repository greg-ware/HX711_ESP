/*
 * HX711_Test.cpp
 *
 *  Created on: 12 oct. 2015
 *      Author: pgreg
 */
#include "HX711_ESP.h"

#include "user_interface.h"

#define PIN_DOUT 12
#define PIN_SCK 13

// Create instance
HX711 hx711=HX711(PIN_DOUT,PIN_SCK);

// the setup function runs once when you press reset or power the board
void setup()
{
	// init serial
	Serial.begin(115200); // initialize serial communication at 9600 bits per second:
	delay(10);

//	rst_info* restartInfo=system_get_rst_info();
//	Serial.print("Ready Restart reason: ");
//	switch(restartInfo->reason) {
//	case REASON_DEEP_SLEEP_AWAKE: Serial.print("DEEP_SLEEP_AWAKE"); break;
//	case REASON_DEFAULT_RST: 	Serial.print("DEFAULT_RST"); break;
//	case REASON_WDT_RST:		Serial.print("WDT_RST"); break;
//	case REASON_EXCEPTION_RST:	Serial.print("EXCEPTION_RST"); break;
//	case REASON_SOFT_WDT_RST:	Serial.print("SOFT_WDT_RST"); break;
//	case REASON_SOFT_RESTART:	Serial.print("SOFT_RESTART"); break;
//	default: Serial.print("REASON_SOFT_RESTART"); break;
//	}
//	Serial.print(" Exc cause: ");
//	Serial.println(restartInfo->exccause);

	delay(10);

	//intialize HX711
	hx711.setup();
	delay(100);
}

// the loop function runs over and over again forever
void loop()
{
	// power up
	hx711.powerUp();

	// wait for the chip to become ready
	while (!hx711.isReady());

	long rawADC = hx711.readRaw();


	Serial.print("rawADC=0x");
	Serial.print(rawADC,16);
	Serial.print(" ADC=");
	Serial.print(rawADC);
	Serial.println();

	// power down
	hx711.powerDown();

	delay(1000);
}
