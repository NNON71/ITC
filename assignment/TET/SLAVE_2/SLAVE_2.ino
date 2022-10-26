#include <Wire.h>

#define SLAVE_ADDR_2 2

char text[100];
void setup()
{
  char text[100];
  Wire.begin(SLAVE_ADDR_2);
  Serial.begin(9600);
     
   Wire.onReceive(receiveEvent);
   Wire.onRequest(requestEvent);
}

void loop()
{
  delay(500);
}


void receiveEvent(int bytes)
{
  Serial.print("Recieve messag! :  ");
  
  for(int i=0;i<bytes;i++)
  {
    text[i] = Wire.read();
  }
  
  if(text[8] =='2' )     
  {
    Serial.println(text);
    text[6] = '0';
    text[8] = '\0';
  }
}


void requestEvent()
{
  Serial.print("send : ");
  Serial.println(text);
  Wire.write(text);
}
