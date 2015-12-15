#include <Arduino.h>
#include <SoftwareSerial.h>
#include "lcd_functions.h"
#include "button_reader.h"
SoftwareSerial LCD = SoftwareSerial(0, txPin);
static int noOfAlarms=1;
static int alarmHour[3]={1};
static int alarmMin[3]={30};
static bool alarmAM_PM[3] ={0}; // 0 is AM, 1 is PM
static long alarmDuartion = 30; // in minutes
static int currentTimeHour=1;
static int currentTimeMin=30;
static bool currentTimeAM_PM=0; // 0 is AM, 1 is PM
void initLCD(){
  LCD.begin(9600);
  backLightOff();
  LCD.write(byte(22));
}

void setAlarm(){
  clearLCD();
  LCD.println("Pumps Per Day");
  newLine();
  LCD.println(noOfAlarms);
  delay(10);
  while(1){ //get number of alarms
    delay(50);
    int r = readButtons();
    if(r == UP_PIN){
      if(noOfAlarms < 3){
        LCD.write(byte(148)); //move to (1,0)
        LCD.println(++noOfAlarms);
      }
    }else if(r == DOWN_PIN){
      if(noOfAlarms > 1){
        LCD.write(byte(148)); //move to (1,0)
        LCD.println(--noOfAlarms);
      }
    }else if(r == SET_PIN){
      clearLCD();
      LCD.println("Set Alarm Time");
      newLine();
      LCD.println("01:30 AM");
      break;
    }
  }
  
  
  for(int ith_alarm=0;ith_alarm<noOfAlarms;ith_alarm++){ // get timings for all the alarms
	clearLCD();
	LCD.println("Set Alarm No. ");
	LCD.println(ith_alarm+1);
	newLine();
    LCD.println("01:30 AM");
    while(1){ //get hour
        delay(50);
        int r = readButtons();
        if(r == UP_PIN && (alarmHour[ith_alarm] < 12)){
		  if(alarmHour[ith_alarm] <9){
			LCD.write(byte(148));
			delay(10);
			LCD.println("0");
			delay(10);
			LCD.write(byte(149)); //move to (1,1)
		  }else{
			LCD.write(byte(148)); //move to (1,0)
		  }
          LCD.println(++alarmHour[ith_alarm]);
        }else if(r == DOWN_PIN && (alarmHour[ith_alarm] > 0)){
		  if(alarmHour[ith_alarm] <= 10){
			LCD.write(byte(148));
			delay(10);
			LCD.println("0");
			delay(10);
			LCD.write(byte(149)); //move to (1,1)
		  }else{
			LCD.write(byte(148)); //move to (1,0)
		  }
          LCD.println(--alarmHour[ith_alarm]);
        }else if(r == SET_PIN){
          break;
        }
    }
    
    while(1){ //get minute
      delay(50);
      int r = readButtons();
      if(r == UP_PIN && (alarmMin[ith_alarm] < 60)){
		  if(alarmMin[ith_alarm] <9){
			LCD.write(byte(151));
			delay(10);
			LCD.println("0");
			LCD.write(byte(152)); //move to (1,7)
		  }else{
			LCD.write(byte(151)); //move to (1,6)
		  }
          LCD.println(++alarmMin[ith_alarm]);
      }else if(r == DOWN_PIN && (alarmMin[ith_alarm] > 0)){
          if(alarmMin[ith_alarm] <= 10){
			LCD.write(byte(151));
			delay(10);
			LCD.println("0");
			LCD.write(byte(152)); //move to (1,7)
		  }else{
			LCD.write(byte(151)); //move to (1,6)
		  }
          LCD.println(--alarmMin[ith_alarm]);
      }else if(r == SET_PIN){
        break;
      }
    }
	while(1){ //get AM/PM
      delay(50);
      int r = readButtons();
      if(r == UP_PIN && (alarmAM_PM[ith_alarm] == 0)){
          alarmAM_PM[ith_alarm] =1;
          LCD.write(byte(154)); //move to (1,3)
          LCD.println("P");
      }else if(r == DOWN_PIN && (alarmAM_PM[ith_alarm] == 1)){
          alarmAM_PM[ith_alarm] = 0;
          LCD.write(byte(154)); //move to (1,3)
          LCD.println("A");
      }else if(r == SET_PIN){
        break;
      }
    }
  }
  /*get alarm duration*/
  clearLCD();
  LCD.println("Max Pumping Time");
  newLine();
  LCD.println(alarmDuartion);
  LCD.write(byte(151));
  LCD.println("Minutes");
  while(1){ //get duration
    delay(50);
    int r = readButtons();
    if(r == UP_PIN && (alarmDuartion < 99)){
		if(alarmDuartion <9){
			LCD.write(byte(148));
			delay(10);
			LCD.println("0");
			delay(10);
			LCD.write(byte(149)); //move to (1,1)
		}else{
			LCD.write(byte(148)); //move to (1,0)
		}
        LCD.println(++alarmDuartion);
    }else if(r == DOWN_PIN && (alarmDuartion > 0)){
		if(alarmDuartion <= 10){
			LCD.write(byte(148));
			delay(10);
			LCD.println("0");
			delay(10);
			LCD.write(byte(149)); //move to (1,1)
		}else{
			LCD.write(byte(148)); //move to (1,0)
		}
		LCD.println(--alarmDuartion);
    }else if(r == SET_PIN){
          break;
    }
  }
  
 
}

void setTime(){
  clearLCD();
  LCD.println("Set Clock Time");
  delay(10);
  newLine();
  LCD.println("01:30 AM");
   while(1){ //get hour
        delay(50);
        int r = readButtons();
        if(r == UP_PIN && (currentTimeHour < 12)){
		  if(currentTimeHour <9){
			LCD.write(byte(148)); //move to (1,0)
			LCD.println("0");
			LCD.write(byte(149)); //move to (1,1)
		  }else{
			LCD.write(byte(148)); //move to (1,0)
		  }
          LCD.println(++currentTimeHour);
        }else if(r == DOWN_PIN && (currentTimeHour > 0)){
		  if(currentTimeHour <= 10){
			LCD.write(byte(148)); //move to (1,0)
			LCD.println("0");
			LCD.write(byte(149)); //move to (1,1)
		  }else{
			LCD.write(byte(148)); //move to (1,0)
		  }
          LCD.println(--currentTimeHour);
        }else if(r == SET_PIN){
          break;
        }
   }
   
    while(1){ //get minute
      delay(50);
      int r = readButtons();
      if(r == UP_PIN && (currentTimeMin < 60)){
		  if(currentTimeMin <9){
			LCD.write(byte(151)); //move to (1,6)
			LCD.println("0");
			LCD.write(byte(152)); //move to (1,7)
		  }else{
			LCD.write(byte(151)); //move to (1,6)
		  }
          LCD.println(++currentTimeMin);
      }else if(r == DOWN_PIN && (currentTimeMin > 0)){
          if(currentTimeMin <=10){
			LCD.write(byte(151)); //move to (1,6)
			LCD.println("0");
			LCD.write(byte(152)); //move to (1,7)
		  }else{
			LCD.write(byte(151)); //move to (1,6)
		  }
          LCD.println(--currentTimeMin);
      }else if(r == SET_PIN){
        break;
      }
    }
	
	while(1){ //get AM/PM
      delay(50);
      int r = readButtons();
      if(r == UP_PIN && (currentTimeAM_PM == 0)){
          currentTimeAM_PM =1;
          LCD.write(byte(154)); //move to (1,3)
          LCD.println("P");
      }else if(r == DOWN_PIN && (currentTimeAM_PM == 1)){
          currentTimeAM_PM = 0;
          LCD.write(byte(154)); //move to (1,3)
          LCD.println("A");
      }else if(r == SET_PIN){
        break;
      }
    }
	
  
}


void runningState(){
  clearLCD();
  backLightOff();
  LCD.println("Chill state!");
  delay(10);
}

void clearLCD(){
  LCD.write(byte(12));
  delay(10);
}
void newLine(){
  LCD.write(byte(13));
  delay(10);
}

void settingsLoop(int item){
  clearLCD();
  LCD.println("Settings");
  delay(10);
  newLine();
  if(item == 1){
    LCD.println("1.Set Pump  Time");
  }else if(item == 2){
    LCD.println("2.Set Clock Time");
  }
}

void backLightOn(){
	LCD.write(byte(17)); //backlight on
}
void backLightOff(){
	LCD.write(byte(18)); //backlight off
}
