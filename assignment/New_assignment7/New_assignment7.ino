#include <TimerOne.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
Adafruit_SSD1306 OLED(OLED_RESET);

#define select_button 10
#define edithour_button 9
#define editmin_button 8
#define save_button 7

#define buzzer_pin 4

#define Normal 14
#define Edit 15
#define Alarm 16
#define Count 17

bool AlarmOn = false;
int tones[] = {261,277,294,311,330,349,370,392,415,440};

int8_t sec,
    minute,
    hour;
    
int i;
int8_t SEH,SEM;
int8_t SAH,SAM;
int8_t ALH,ALM;
int Mode[3] = {Normal,Edit,Alarm};

unsigned long long past1,past2,past3,past4;

void setup()
{
  Serial.begin(9600);
  Timer1.initialize(1000000); 
  Timer1.attachInterrupt(uptime);
  analogWrite(buzzer_pin,OUTPUT);
  analogWrite(select_button,INPUT_PULLUP);
  analogWrite(edithour_button,INPUT_PULLUP);
  analogWrite(editmin_button,INPUT_PULLUP);
  analogWrite(save_button,INPUT_PULLUP);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  EEPROM.get(0,hour);
  EEPROM.get(1,minute);
  EEPROM.get(2,sec);
  EEPROM.get(3,ALH);
  EEPROM.get(4,ALM);
  millis();
}

void rotatescreen()
{
  Serial.println(analogRead(A1));
  //int bob = map(analogRead(A1),320,400,0,100);
  //Serial.println(bob);
  if(analogRead(A1)<320)
  {
    OLED.setRotation(2);
  }
  else OLED.setRotation(0);
}

void uptime()
{
  sec++;
  if(sec>59)
  {
    minute+=1;
    sec=0;
  }
  if(minute>59)
  {
    hour+=1;
    minute=0;
  }
  if(hour==24)
  {
    hour=0;
  }
}

void displaytime()
{
  OLED.clearDisplay();
  OLED.setCursor(20,1);
  if(hour<10)
  {
    OLED.print("0");
  }
  OLED.print(hour);
  OLED.print(":");
  if(minute<10)
  {
    OLED.print("0");
  }
  OLED.print(minute);
  OLED.print(":");
  if(sec<10)
  {
    OLED.print("0");
  }
  OLED.print(sec);
}

void displayedit()
{
  OLED.clearDisplay();
  OLED.setCursor(32,1);
  if(SEH<10)
  {
    OLED.print("0");
  }
  OLED.print(SEH);
  OLED.print(":");
  if(SEM<10)
  {
    OLED.print("0");
  }
  OLED.print(SEM);
}

void displayalarm()
{
  OLED.clearDisplay();
  OLED.setCursor(32,1);
  if(SAH<10)
  {
    OLED.print("0");
  }
  OLED.print(SAH);
  OLED.print(":");
  if(SAM<10)
  {
    OLED.print("0");
  }
  OLED.print(SAM);
}

void displaysave()
{
    OLED.clearDisplay();
    OLED.setTextSize(2);
    OLED.setCursor(30,2);
    OLED.print("SAVE");
}

void loop()
{
  OLED.setTextColor(WHITE);
  OLED.setTextSize(2);
  rotatescreen();
  if(digitalRead(select_button)==1&&digitalRead(edithour_button)!=1&&digitalRead(editmin_button)!=1) // Select Mode 
  {
    if(millis()-past1>=500)
    {
      //Serial.println(Mode[i]);
      past1=millis();
      i=(i+1)%3;
      
      if(Mode[i]==Edit)
      {
        SEH=hour;
        SEM=minute;
      }
      else if(Mode[i]==Alarm)
      {
        SAH=SEH;
        SAM=SEM;
      }
    }
  }
  if(digitalRead(edithour_button)==1&&digitalRead(select_button)!=1)
  {
    if(Mode[i]==Edit)
    {
      SEH=(SEH+1)%24;
    }
    else if(Mode[i]==Alarm)
    {
      SAH=(SAH+1)%24;
    }
  }
  if(digitalRead(editmin_button)==1&&digitalRead(select_button)!=1)
  {
    if(Mode[i]==Edit)
    {
      SEM=(SEM+1)%60;
    }
    else if(Mode[i]==Alarm)
    {
      SAM=(SAM+1)%60;
    }
  }
  if(digitalRead(save_button)==1)
  {
    if(Mode[i]==Edit)
    {
      hour=SEH;
      minute=SEM;
      EEPROM.update(0,hour);
      EEPROM.update(1,minute);
      EEPROM.update(2,sec);
    }
    if(Mode[i]==Alarm)
    {
     ALH=SAH;
     ALM=SAM;
     EEPROM.update(3,ALH);
     EEPROM.update(4,ALM);
    }
    displaysave();
    i=0;
  }

  // display time and mode 
  if(Mode[i]==Normal) 
  {  
    displaytime();
    OLED.setTextSize(1);
    OLED.setCursor(30,25);
    OLED.println("Mode : Normal");
  }
  if(Mode[i]==Edit)
  {
    displayedit();
    OLED.setTextSize(1);
    OLED.setCursor(30,25);
    OLED.println("Mode : EDIT");
  }
  if(Mode[i]==Alarm)
  {
    displayalarm();
    OLED.setTextSize(1);
    OLED.setCursor(30,25);
    OLED.println("Mode : ALARM");
  }
  
  if(hour==ALH&&minute==ALM&&AlarmOn==false)
  {
    OLED.clearDisplay();
    OLED.setTextSize(2);
    OLED.setCursor(30,2);
    OLED.print("ALARM");
    for(int i=0;i<5;i++)
    {
      tone(buzzer_pin,tones[i],20); 
    }
    if((digitalRead(edithour_button)||digitalRead(editmin_button))==1)
    {
      AlarmOn=true;
      ALH=99;
      ALM=99  ;
      Serial.println("AWAKE");
      noTone(buzzer_pin);
    }
  }
  if(hour!=ALH||minute!=ALM) AlarmOn=false;
  OLED.display();
}
