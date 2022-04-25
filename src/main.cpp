#include <Arduino.h>
#include "DramController.h"
#include <NintendoExtensionCtrl.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>


Nunchuk nchuk;
//int BUTTONLEDGPIOS[4] = [sensor5GPIO1, sensor6GPIO1, sensor7GPIO1, sensor8GPIO1];

IOExpander* led;
Segmentdriver* seg1;
Segmentdriver* seg2;
Adafruit_MPU6050 mpu;



void setup() {
  // put your setup code here, to run once:

  led = new IOExpander(ledAddress);
  seg1 = new Segmentdriver(segmentDisplay1Address);
  seg2 = new Segmentdriver(segmentDisplay2Address);
  mpu.begin();
  initializeController();
  nchuk.begin();

  while (!nchuk.connect()) {
		delay(1000);
	}

  delay(100);



  testButtonLeds();
  led->setOut(0b11111000);
  seg1->write_char('7');
  seg2->write_char('8');
  delay(1000);
  led->setOut(0);
  seg1->write_char('1');
  seg2->write_char('2');
  delay(1000);
  led->setOut(0b11111000);
  seg1->write_char('3');
  seg2->write_char('4');
  delay(1000);
  led->setOut(0);
  seg1->write_char('5');
  seg2->write_char('6');

  
 
}

void loop() {
  readValues(led, seg1, seg2);

  
  sendValues(nchuk);

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  SerialUSB.print(",IMUX:");
  SerialUSB.print(a.acceleration.x);

  SerialUSB.print(",IMUY:");
  SerialUSB.print(a.acceleration.y);

  SerialUSB.print(",IMUZ:");
  SerialUSB.print(a.acceleration.z);

  SerialUSB.println("};");
  
  
  delay(10);
}