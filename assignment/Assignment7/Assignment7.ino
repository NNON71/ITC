#include <TimerOne.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
Adafruit_SSD1306 OLED(OLED_RESET);

#define edithour_button 9
#define editmin_button 8
#define editsec_button 7
#define select_button 10

#define buzzer_pin 4

int tones[] = {261,277,294,311,330,349,370,392,415,440};
int8_t sec=0,
    minute=0,
    hour=0;
    
int i;
int8_t SEH,SEM,SES;
int8_t SAH,SAM,SAS;
char Mode[4]={'N','E','A','S'};
bool edit_start=false;
bool stoptime=false;

unsigned long long past1,past2,past3,past4;

void setup()
{
  Serial.begin(9600);
  Timer1.initialize(1000000); 
  Timer1.attachInterrupt(uptime);
  analogWrite(buzzer_pin,OUTPUT);
  analogWrite(edithour_button,INPUT_PULLUP);
  analogWrite(editmin_button,INPUT_PULLUP);
  analogWrite(select_button,INPUT_PULLUP);
  analogWrite(editsec_button,INPUT_PULLUP);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  if(EEPROM.read(0)<24) EEPROM.get(0,hour);
  if(EEPROM.read(1)<60) EEPROM.get(1,minute);
  if(EEPROM.read(2)<60) EEPROM.get(2,sec);
  
  if(EEPROM.read(3)<24) EEPROM.get(3,SAH);
  if(EEPROM.read(4)<60) EEPROM.get(4,SAM);
  if(EEPROM.read(5)<60) EEPROM.get(5,SAS);
  millis();
}

void rotatescreen()
{
  //Serial.println(analogRead(A0));
  if(analogRead(A0)>290)
  {
    OLED.setRotation(2);
  }
  else OLED.setRotation(0);
}

void uptime()
{
  sec++;
//  if(Mode[i]=='E')
//  {
//    if(digitalRead(edithour_button)==1||digitalRead(editmin_button)==1||digitalRead(editsec_button)==1)
//    {
//       stoptime=true;
//       Serial.println("ADW");
//    }
//  }
//  if(Mode[i]!='E')
//  {
//    stoptime=false;
//  }
//  if(stoptime==false)
//  {
//    sec++;
//  }
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

unsigned long long bounce;
int Press(int pin)
{
  if(!digitalRead(pin))
  {
    if(millis()-bounce>=500)
    {
      bounce=millis();
    }
  }
}

void displaytime()
{
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setTextSize(2);
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
  OLED.setTextColor(WHITE);
  OLED.setTextSize(2);
  OLED.setCursor(20,1);
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
  OLED.print(":");
  if(SES<10)
  {
    OLED.print("0");
  }
  OLED.print(SES);
  //Serial.println(SEH+String(" ")+SEM+String(" ")+SES);
}

void displayalarm()
{
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setTextSize(2);
  OLED.setCursor(20,1);
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
  OLED.print(":");
  if(SAS<10)
  {
    OLED.print("0");
  }
  OLED.print(SAS);
  //Serial.println(SEH+String(" ")+SEM+String(" ")+SES);
}

void displaysave()
{
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setTextSize(2);
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

void loop()
{
  rotatescreen();
  //Serial.println(String("b1 :")+digitalRead(edit_button)+String(" b2 :")+digitalRead(next_button)+String(" b3 :")+digitalRead(select_button));
  //Serial.println(String("Sec :")+sec+String(" min :")+minute+String(" Hour :")+hour);
  if(digitalRead(select_button)==1) // Select Mode 
  {
    if(millis()-past1>=500)
    {
      //Serial.println(Mode[i]);
      past1=millis();
      i=(i+1)%4;
      Mode[i];
      if(Mode[i]=='E')
      {
        SEH=hour;
        SEM=minute;
        SES=sec;
      }
      else if(Mode[i]=='A')
      {
        SAH=0;
        SAM=0;
        SAS=0;
      }
      else if(Mode[i]=='S')
      {
        hour=SEH;
        minute=SEM;
        sec=SES;
        EEPROM.update(0,hour);
        EEPROM.update(1,minute);
        EEPROM.update(2,sec);
        EEPROM.update(3,SAH);
        EEPROM.update(4,SAM);
        EEPROM.update(5,SAS);
      }
    }
  }
  
  if(digitalRead(edithour_button)==1) // edit hour
  {
    if(millis()-past2>=200)
    {
      if(Mode[i]=='E') // on edit mode
      {
        past2=millis();
        SEH=(SEH+1)%24;
      }
      else if(Mode[i]=='A') // on alarm mode
      {
        past2=millis();
        SAH=(SAH+1)%24;
      }
    }
  }
  if(digitalRead(editmin_button)==1) // edit min
  {
    if(millis()-past3>=200) // on edit mode
    {
      if(Mode[i]=='E')
      {
        past3=millis();
        SEM=(SEM+1)%60;
      }
      else if(Mode[i]=='A') // on alarm mode 
      {
        past3=millis();
        SAM=(SAM+1)%60;
      }
    }
  }
  if(digitalRead(editsec_button)==1) // edit sec
  {
    if(millis()-past4>=200) // on edit mode
    {
      if(Mode[i]=='E')
      {
        past4=millis();
        SES=(SES+1)%60;
      }
      else if(Mode[i]=='A') // one alarm mode
      {
        past4=millis();
        SAS=(SAS+1)%60;
      }
    }
  }
  
  // display time and mode 
  if(Mode[i]=='N') 
  {  
    displaytime();
    OLED.setTextSize(1);
    OLED.setCursor(30,25);
    OLED.println("Mode : Normal");
  }
  if(Mode[i]=='E')
  {
    displayedit();
    OLED.setTextSize(1);
    OLED.setCursor(30,25);
    OLED.println("Mode : EDIT");
  }
  if(Mode[i]=='A')
  {
    displayalarm();
    OLED.setTextSize(1);
    OLED.setCursor(30,25);
    OLED.println("Mode : ALRAM");
  }
  if(Mode[i]=='S')
  {
    displaysave();
    OLED.setTextSize(1);
    OLED.setCursor(30,25);
    OLED.println("Mode : SAVE");
  }
  
  if(hour==SAH&&minute==SAM&&sec==SAS)
  {
    int al=millis();
    Serial.println("ALARM");
    OLED.clearDisplay();
    OLED.setTextSize(2);
    OLED.setCursor(30,2);
    OLED.println("ALARM");
    if(millis()-al<1000)
    {   
      for(int i=0;i<6;i++)
      {
        tone(buzzer_pin,tones[i],20);
      }
      noTone(buzzer_pin);
    }
  }
  OLED.display();
}
