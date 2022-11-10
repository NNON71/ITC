#include <Arduino_FreeRTOS.h>
#include "queue.h"

#define SWYellow 11
#define SWRed 12
#define SWGreen 13
#define Yellow 5
#define Red 6
#define Green 7

//debounce
unsigned long Yellowbounce;
unsigned long Redbounce;
unsigned long Greenbounce;

QueueHandle_t YellowQueue;
QueueHandle_t RedQueue;
QueueHandle_t GreenQueue;

bool Yready;
bool Rready;
bool Gready;

void setup()
{
  Serial.begin(9600); 
  YellowQueue = xQueueCreate(5,sizeof(int32_t));// (queuelength,sizequeue)
  RedQueue = xQueueCreate(5,sizeof(int32_t));
  GreenQueue = xQueueCreate(5,sizeof(int32_t));
  //sender
  xTaskCreate(vSWtask,"SW Yellow",100,SWYellow,1,NULL); //(function ที่เรียกทำงาน,ชื่อเรียกtask,ขนาดstackที่จองให้task,paramiter,priority,)
  xTaskCreate(vSWtask,"SW Red",100,SWRed,1,NULL);
  xTaskCreate(vSWtask,"SW Green",100,SWGreen,1,NULL);
  //reciever
  xTaskCreate(vYellow,"Recieve Task",100,NULL,1,NULL);
  xTaskCreate(vRed,"Recieve Task",100,NULL,1,NULL);
  xTaskCreate(vGreen,"Recieve Task",100,NULL,1,NULL);
}

void vSWtask(void *pvParameters)
{
  BaseType_t qStatus; 
  int32_t valuetosent=0;
  int SW = (int32_t)pvParameters;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  pinMode(SW, INPUT);
  while(1)
  {
    if(digitalRead(SW)==LOW )
    {
      if(SW==11)
      {
        Yready = true;
      }
      if(SW==12)
      {
        Rready = true;
      }
      if(SW==13)
      {
        Gready = true;
      }
    }
    if(digitalRead(SW)==HIGH )
    {
      if(SW==11 && Yready == true)
      {
        valuetosent = SW;
        qStatus = xQueueSend(YellowQueue,&valuetosent,xTicksToWait); //(ต่อคิวในYellowQueue,pointerชี้ส่งเข้าqueue,ระยะเวลาที่ต้องรอก่อนส่งเข้าqueue)
        //Yready = false;
      }
      if(SW==12 && Rready == true)
      {
        Serial.println("SW2");
        valuetosent = SW;
        qStatus = xQueueSend(RedQueue,&valuetosent,xTicksToWait);
        Rready = false;
      }
      if(SW==13 && Gready == true)
      {
        valuetosent = SW;
        qStatus = xQueueSend(GreenQueue,&valuetosent,xTicksToWait);
        Gready = false;
      }
    }
  }
}

void vYellow(void *pvParameters)
{
  int32_t valueReceived;
  int Ycount = 0;
  bool check = false;
  BaseType_t qStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100); 
  pinMode(Yellow, OUTPUT); 
  digitalWrite(Yellow, LOW);
  while (1)
  {
    qStatus = xQueueReceive(YellowQueue, &valueReceived, xTicksToWait); //(ชื่อคิวที่รับ,pointerที่รับ,ระยะเวลาที่รอก่อนรับคิว)
    
    if (qStatus  == pdPASS) // ส่งข้อมูลสำเร็จ
    {
      Serial.print("Received value  : ");
      Serial.println(valueReceived);
      Ycount += 1;
      Serial.println(Ycount);
    }
    if(Ycount >= 1 && check == false)
    {
        digitalWrite(Yellow,HIGH);
        check = true;
        Yellowbounce = millis();
        Serial.println(Ycount);
    }
    if(millis() - Yellowbounce >= 3000 && digitalRead(Yellow) == 1)
    {
      Ycount -=1;
      check = false;
      if(Ycount <= 0)
      {
         digitalWrite(Yellow,LOW);
      }
    }
  }
}

void vRed(void *pvParameters)
{
  int32_t valueReceived;
  int Rstats;
  BaseType_t qStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  pinMode(Red, OUTPUT); 
  digitalWrite(Red, LOW);
  while (1)
  {
    qStatus = xQueueReceive(RedQueue, &valueReceived, xTicksToWait);
    if (qStatus  == pdPASS) 
    {
      Serial.print("Received value  : ");
      Serial.println(valueReceived);
       if (valueReceived == 12)
       {
        if (Rstats == 0)
        {
         Rstats = 1;
         digitalWrite(Red,!digitalRead(Red));
         Redbounce = millis();
        }
        else
        {
         Rstats = 0;
         digitalWrite(Red,LOW);
        }
       }
    }
    if(Rstats == 1 && millis() - Redbounce >= 50)
    {
      digitalWrite(Red,!digitalRead(Red));
      Redbounce = millis();
    }
  }
}

void vGreen(void *pvParameters)
{
  int32_t valueReceived;
  BaseType_t qStatus;
  int Gcount = 0;
  int Gstats = 0;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  pinMode(Green, OUTPUT); 
  digitalWrite(Green, LOW);
  while (1)
  {
    qStatus = xQueueReceive(GreenQueue, &valueReceived, xTicksToWait);
    if (qStatus  == pdPASS)
    {
      Serial.print("Received value  : ");
      Serial.println(valueReceived);
      if (valueReceived == 13 && Gstats == 0) 
      {
        Gstats =1;
      }
    }
    if(millis()-Greenbounce>=500 && Gstats ==1)
    {
     Serial.println(Gcount);
     digitalWrite(Green,digitalRead(Green)^1);
     Gcount++;
     Greenbounce = millis();
    }
    if(Gcount==6)
    {
      Gcount=0;
      Gstats=0;
    }
  }
}

void loop(){}
