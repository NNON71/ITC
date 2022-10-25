#include <Wire.h>
#define SLAVE_ADDR 1
char text[] = "Token#0#";
static char message[100];
static unsigned int message_pos = 0;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  while (Serial.available() > 0)
  {
    char inByte = Serial.read();
    
    if ( inByte != '\n')
    {
      message[message_pos] = inByte;
      message_pos++;
    }
    else
    {
      message[message_pos] = '\0';
      message_pos = 0;
    }
  }
  if(message[0] != '\0')
  {
    
    text[6] = '1'; 
  }
  delay(500);
  
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(text);
  Wire.write(message);
  Wire.endTransmission();

  
  Serial.print(text);
  Serial.println(message);

  
  Wire.requestFrom(SLAVE_ADDR,8);
  if(Wire.available()!=0)
  {
    for(int i=0;i<8;i++)
    {
      text[i] = Wire.read();
      message[0] = '\0';
      //Serial.println(i);
    }
    Serial.println(text);
 
  }
}
