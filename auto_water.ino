#include <SoftwareSerial.h>
#include "state_machine.h"
#include "lcd_functions.h"
#include "button_reader.h"

static int noOfAlarms=0;
//int leftVal,rightVal,upVal,downVal,setVal;
int settingsItems=2; //number of settings
void setup(){
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello Serial");
  initLCD();
  clearLCD();
  runningState();
}

state_machine fsm = {STATE_RUNNING,NOTHING_PRESSED};

void loop() {
  // put your main code here, to run repeatedly:
  int rc = readButtons();
  if(rc != -1){
    //some button(s) active
    //ToDo -- Switch Case of actions to take...
    switch(rc){
      case 0:
        fsm.event=LEFT_PRESSED;
        break;
      case 1:
        fsm.event=RIGHT_PRESSED;
        break;
      case 2:
        fsm.event=UP_PRESSED;
        break;
      case 3:
        fsm.event=DOWN_PRESSED;
        break;
      case 4:
        fsm.event=SET_PRESSED;
        break;
    }
    Serial.println("Sending to state_next");
    Serial.print(rc);
    nextState(&fsm);
  }
}






