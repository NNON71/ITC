#include <Wire.h>
#define SLAVE_ADDR_1 1
#define SLAVE_ADDR_2 2
int num;
int slave_state;
char text[] = "Token#0#";
static char message[100];
static unsigned int message_pos = 0;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  slave_state = SLAVE_ADDR_1;
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
  delay(500);
  
  Wire.beginTransmission(slave_state);
  if(message[0] != '\0' && message[6] == '1')
  {
    Wire.write(message);
    Serial.println(message);
   // Serial.println(slave_state);
  }
  else 
  {
    Wire.write(text);
    Serial.println(text);
    //Serial.println(slave_state);
  }
  Wire.endTransmission();
  //Serial.println(String("message = ")+strlen(message));
  
  Wire.requestFrom(slave_state,8);
  if(Wire.available()!=0)
  {
    for(int i=0;i<num;i++)
    {
      text[i] = Wire.read();
    }
    
    Serial.print(String("Slave:")+slave_state+String("    "));
    Serial.println(text);
  }

  slave_state = (slave_state % 2) + 1;
}
