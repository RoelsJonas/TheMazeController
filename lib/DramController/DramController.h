#ifndef DRAMCONTROLLER_H
#define DRAMCONTROLLER_H

#include ".\IOExpander\IOExpander.h"
#include ".\Segmentdriver\Segmentdriver.h"
#include <NintendoExtensionCtrl.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h> 

/*DRAMCONTROLLER PIN AND ADDRESS DEFINITIONS */
#define buzzerPin 2
#define vibratorPin1 12
#define vibratorPin2 5
#define debugLEDPin 13

#define GPIO3Address 0x38
#define segmentDisplay2Address 0x39
#define segmentDisplay1Address 0x3A
#define LEDArrayAddress 0x3B

#define sensor1GPIO1 6
#define sensor1GPIO2 14

#define sensor2GPIO1 39
#define sensor2GPIO2 15

#define sensor3GPIO1 8
#define sensor3GPIO2 16
#define sensor3Analog A2

#define sensor4GPIO1 9
#define sensor4GPIO2 17

#define sensor5GPIO1 10
#define sensor5GPIO2 18

#define sensor6GPIO1 23
#define sensor6GPIO2 19

#define sensor7GPIO1 24
#define sensor7GPIO2 4

#define sensor8GPIO1 22
#define sensor8GPIO2 3

// incoming message syntax {LEDS:00000,BUTTONLEDS:1111,SEG1:c,SEG2:c,VIBRATION:0,BUZZER:0};
#define incomingLength 63

// outgoing message syntax {BUTTONS:xxxx,JOYX:xxx,JOYY:xxx,PITCH:xxxx,ROLL:xxxx,Z:x,C:x,IMUX:xxxx:IMUY:xxxx,IMUZ:xxxx,SOUND:xxxx};


/* WII NUNCHUCK CALIBRATION PARAMETERS */
#define NUNCHUK_JOYSTICK_X_CENTRUM 129
#define NUNCHUK_JOYSTICK_X_MIN 33
#define NUNCHUK_JOYSTICK_X_MAX 236
#define NUNCHUK_JOYSTICK_X_DEADZONE 5

#define NUNCHUK_JOYSTICK_Y_CENTRUM 131
#define NUNCHUK_JOYSTICK_Y_MIN 35
#define NUNCHUK_JOYSTICK_Y_MAX 230
#define NUNCHUK_JOYSTICK_Y_DEADZONE 5

void initializeController();

void sendValues(Nunchuk nchuk);

void readValues(IOExpander* led, Segmentdriver* seg1, Segmentdriver* seg2);

void testButtonLeds();

void updateSoundValues();

int getMaxSound();
int getMinSound();

#endif