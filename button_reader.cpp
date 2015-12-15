#include <Arduino.h>
#include "button_reader.h"
int leftVal,rightVal,upVal,downVal,setVal;
/*Reads all the buttons. Returns integer - which button is active accoridng to the #defs.
Returns -1 is no button is pressed.
*/
int readButtons(){
  int ret=-1;
  if((leftVal = analogRead(LEFT_PIN)) > 512){
    ret=LEFT_PIN;
    Serial.println("LEFT");
    delay(100);
  }
  if((rightVal = analogRead(RIGHT_PIN)) > 512){
    ret=RIGHT_PIN;
    Serial.println("RIGHT");
    delay(100);
  }
  if((upVal = analogRead(UP_PIN)) >512){
    ret=UP_PIN;
    Serial.println("UP");
    delay(100);
  }
  if((downVal = analogRead(DOWN_PIN)) >512){
    ret=DOWN_PIN;
    Serial.println("DOWN");
    delay(100);
  }
  if((setVal = analogRead(SET_PIN)) >512){
    ret=SET_PIN;
    Serial.println("SET");
    delay(100);
  }
  return ret;
}
