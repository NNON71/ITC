#include <Wire.h>
#define SLAVE_ADDR 1
char text[100];

void setup()
{
  Wire.begin(SLAVE_ADDR);
  Serial.begin(9600);
     
   Wire.onReceive(receiveEvent);
   Wire.onRequest(requestEvent);
}

void loop()
{
   delay(500);
}

void receiveEvent(int byte)
{
  for(int i=0;i<byte;i++)
  {
    text[i] = Wire.read();
  }
  Serial.println(text);
}

void requestEvent()
{
  for(int i=8;i<100;i++)
  {
    text[i]='\0';
  }
  text[6]='0';
  Wire.write(text);
}
