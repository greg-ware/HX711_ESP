// Do not remove the include below
#include "HX711_ESP.h"


HX711::HX711(byte dout, byte pd_sck, GAIN gain) {
	this->dataOutPin=dout;
	this->clockInPin=pd_sck;
	setGain(gain);
}

HX711::~HX711() {

}

void HX711::setGain(GAIN gain) {
	switch (gain) {
	case CHANNEL_A_64:
		this->gainPulses = 3;
		break;
	case CHANNEL_B_32:
		this->gainPulses = 2;
		break;
	case CHANNEL_A_128:
		this->gainPulses = 1;
		break;
	}
}

void HX711::powerDown() {
	// set HX711 in sleep mode, keep SCK pin high for more than 60 µs
	digitalWrite(clockInPin, HIGH);
	delayMicroseconds(100);
}

void HX711::powerUp() {
	digitalWrite(clockInPin, LOW);
}

void HX711::setup() {
	// initialize HX711, clock as output, dataOut as input
	pinMode(clockInPin, OUTPUT);
	pinMode(dataOutPin, INPUT);

	// set HX711 in sleep mode
	powerDown();

	// and back up
	powerUp();
}


long HX711::readRaw() {
	long rawADC = 0;

	// pulse the clock pin 24 times to read the data
	for (char i = 0; i < 24; i++) {
		digitalWrite(clockInPin, HIGH);
		delayMicroseconds(2);
		rawADC = rawADC << 1;
		if (digitalRead(dataOutPin)) {
			// enter bit at bit pos 8
			rawADC+=0x00000100;
		}
		digitalWrite(clockInPin, LOW);
	}

	// set the channel and the gain factor (A 128) for the next reading using the clock pin (one pulse)
	pulseGain();

	// divide by 256, takes into account sign
	return rawADC/0x100;
}

void HX711::pulseGain() {
	// set the channel and the gain factor (A 128) for the next reading using the clock pin (one pulse)
	for(int g=0;g<gainPulses;g++) {
		digitalWrite(clockInPin, HIGH);
		digitalWrite(clockInPin, LOW);
		delayMicroseconds(60);
	}
}

bool HX711::isReady() {
	return digitalRead(dataOutPin) == LOW;
}
