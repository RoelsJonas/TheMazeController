#include "DramController.h"
 

void initializeController(){
    // set buttons as input
    pinMode(sensor5GPIO2, INPUT);
    pinMode(sensor6GPIO2, INPUT);
    pinMode(sensor7GPIO2, INPUT);
    pinMode(sensor8GPIO2, INPUT);

    // set the microphone as input
    pinMode(sensor3Analog, INPUT);

    // set leds on button as output
    pinMode(sensor5GPIO1, OUTPUT);  
    pinMode(sensor6GPIO1, OUTPUT);
    pinMode(sensor7GPIO1, OUTPUT);
    pinMode(sensor8GPIO1, OUTPUT);

    pinMode(buzzerPin, OUTPUT);
    pinMode(vibratorPin1, OUTPUT);
    pinMode(vibratorPin2, OUTPUT);



    SerialUSB.begin(115200);

}

void sendValues(Nunchuk nchuk){

  boolean updated = nchuk.update();   
    SerialUSB.print("{BUTTONS:");
  if(not(digitalRead(sensor5GPIO2))){
    SerialUSB.print("1");
  }
  else{
    SerialUSB.print("0");
  }
  if(not(digitalRead(sensor6GPIO2))){
    SerialUSB.print("1");
  }
  else{
    SerialUSB.print("0");
  }
  if(not(digitalRead(sensor7GPIO2))){
    SerialUSB.print("1");
  }
  else{
    SerialUSB.print("0");
  }
  if(not(digitalRead(sensor8GPIO2))){
    SerialUSB.print("1");
  }
  else{
    SerialUSB.print("0");
  }
  

  if(updated){
    SerialUSB.print(",JOYX:");
    SerialUSB.print(nchuk.joyX());

    SerialUSB.print(",JOYY:");
    SerialUSB.print(nchuk.joyY());

    SerialUSB.print(",PITCH:");
    SerialUSB.print(nchuk.pitchAngle());
    SerialUSB.print(",ROLL:");
    SerialUSB.print(nchuk.rollAngle());
    SerialUSB.print(",Z:");
    SerialUSB.print(nchuk.buttonZ());
    SerialUSB.print(",C:");
    SerialUSB.print(nchuk.buttonC());
  }
/*
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  SerialUSB.print(",IMUX:");
  SerialUSB.print(a.acceleration.x);

  SerialUSB.print(",IMUY:");
  SerialUSB.print(a.acceleration.y);

  SerialUSB.print(",IMUZ:");
  SerialUSB.print(a.acceleration.z);
*/
  updateSoundValues();
  
  int max = getMaxSound();
  int min = getMinSound();

  SerialUSB.print(",SOUND:");
  SerialUSB.print(max - min);
}

void readValues(IOExpander* led, Segmentdriver* seg1, Segmentdriver* seg2){
    if(SerialUSB.available()){
    String s = SerialUSB.readStringUntil(';');
    if(s.length() == incomingLength){
      int leds = 0b00000000;
      int buttonLeds[4];

      char kar1 = s[33];
      char kar2 = s[40];

      seg1->write_char(kar1);
      seg2->write_char(kar2);

      int vibrator = String(s[52]).toInt();

      digitalWrite(vibratorPin1, vibrator);
      digitalWrite(vibratorPin2, vibrator);
      SerialUSB.println(s[61]);
      int buzzer = String(s[61]).toInt();

      if(buzzer == 1){
        digitalWrite(buzzerPin, HIGH);
      }
      else{
        digitalWrite(buzzerPin, LOW);
      }
      SerialUSB.println(digitalRead(buzzerPin));

      int BUTTONLEDGPIOS[4] = {sensor5GPIO1, sensor6GPIO1, sensor7GPIO1, sensor8GPIO1};

      for(int i = 0; i<5; i++){
          leds |= String(s[i+6]).toInt() << (7-i);
      }
      led->setOut(leds);
      

      for(int i = 0; i<4; i++){
        buttonLeds[i] = String(s[i+23]).toInt();
        if(buttonLeds[i] == 1){
          digitalWrite(BUTTONLEDGPIOS[i], HIGH);
        }
        else{
          digitalWrite(BUTTONLEDGPIOS[i], LOW);
        }
      }
    }
  }
}


void testButtonLeds(){
    digitalWrite(sensor5GPIO1, HIGH);
    delay(1000);
    digitalWrite(sensor5GPIO1, LOW);
    digitalWrite(sensor6GPIO1, HIGH);
    delay(1000);
    digitalWrite(sensor6GPIO1, LOW);
    digitalWrite(sensor7GPIO1, HIGH);
    delay(1000);
    digitalWrite(sensor7GPIO1, LOW);
    digitalWrite(sensor8GPIO1, HIGH);
    delay(1000);
    digitalWrite(sensor8GPIO1, LOW);
}

int counter = 0;
int sound_values[100];


void updateSoundValues(){
  if(counter < 100){
    sound_values[counter] = analogRead(sensor3Analog);
    counter ++;
  }
  else{
    for(int i = 0; i < 99; i++){
      sound_values[i] = sound_values[i+1];
    }
    sound_values[99] = analogRead(sensor3Analog);
  }
}


int getMaxSound(){
  int max = 0;
  for(int i = 0; i < counter; i++){
    if(sound_values[i] > max){
      max = sound_values[i];
    }
  }
  return max;
}

int getMinSound(){
  int min = 1024;
  for(int i = 0; i < counter; i++){
    if(sound_values[i] < min){
      min = sound_values[i];
    }
  }
  return min;
}