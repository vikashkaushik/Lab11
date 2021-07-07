/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Vikash/Downloads/Lab11/src/Lab11.ino"
/*
 * Project Lab11
 * Description:
 * Author:
 * Date:
 */
#include <blynk.h>
#include "LIS3DH.h"
void setup();
void loop();
#line 9 "c:/Users/Vikash/Downloads/Lab11/src/Lab11.ino"
LIS3DHSPI accel(SPI, D3, WKP); // there are two SPI busses, SPI and SP1. We should use SPI based on our schematic.
SYSTEM_THREAD(ENABLED);
// setup() runs once, when the device is first turned on.
unsigned long lastPrintSample = 0;
const unsigned long PRINT_SAMPLE_PERIOD = 100;
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(D3,INPUT);
  Serial.begin(9600);
  Blynk.begin("xEHyJ1ZygwI7OXGc9-eLg3KWMaR4x7l5", IPAddress(167, 172, 234, 162), 9090); 

  // Initialize sensors
	LIS3DHConfig config;
	config.setAccelMode(LIS3DH::RATE_100_HZ);

	bool setupSuccess = accel.setup(config);
	Serial.printlnf("setupSuccess=%d", setupSuccess);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  Blynk.run();
  LIS3DHSample sample;
  if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD) {
		lastPrintSample = millis();

		
		if (accel.getSample(sample)) {
			Serial.printlnf("%d,%d,%d", sample.x, sample.y, sample.z);
		}
		else {
			Serial.println("no sample");
		}
	}
  
    Blynk.virtualWrite(V1,sample.x);
    Blynk.virtualWrite(V2,sample.y);
    Blynk.virtualWrite(V3,sample.z);
    

}
