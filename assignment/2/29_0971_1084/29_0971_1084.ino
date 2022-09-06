#define sw1 12
#define sw2 11
#define sw3 10

#define led1 4
#define led2 3
#define led3 2

int Rstate = 0,Gstate = 0,Ystate = 0;
unsigned int pastsw1 = 0,pastsw2 = 0,pastsw3 = 0;
unsigned int pastR = 0,pastG = 0,pastY = 0 ;
int delaytime = 400;

void setup() {
  Serial.begin(9600);
  pinMode(sw1,INPUT);
  pinMode(sw2,INPUT);
  pinMode(sw3,INPUT_PULLUP);
  
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
}

void loop() {
  int count = millis();
  
  //RED
  //Serial.println(String("switch1 = ")+sw1);
  if(digitalRead(sw1) == HIGH && Rstate == 0 ) 
  {
    if(count - pastsw1 >= delaytime)
    {
      digitalWrite(led1,HIGH);
      Rstate = 1;
      pastsw1 = count;
      pastR = pastsw1;
      Serial.println("R1");
    }    
  }
  else if( digitalRead(sw1) != digitalRead(sw1) && Rstate ==1 )
  {
    if(count - pastsw1 >= delaytime)
    {
      digitalWrite(led1,LOW);
      Rstate = 0;
      pastsw1 = count;
      Serial.println("R2");
    }   
  }

  
  else if(count - pastR >= 3000 && Rstate == 1)
  {
    digitalWrite(led1,LOW);
    Rstate = 0;
    //pastR = count;
    Serial.println("R3");
  }
  
  
  //GREEN
  //Serial.println(digitalRead(sw3));
  if(digitalRead(sw3) == LOW && Gstate != 1 && Rstate != 1) 
  {
    if(count - pastsw3 >= delaytime)
    {
      digitalWrite(led3,HIGH);
      Gstate = 1;
      pastsw3 = count;
      pastG = pastsw3;
      Serial.println("gON");
    }    
  }
  
  else if(digitalRead(sw3) != digitalRead(sw3) && Gstate == 1)
  {
    if(count - pastsw3 >= delaytime)
    {
      digitalWrite(led3,LOW);
      Gstate = 0;
      pastsw3 = count;
      Serial.println("Gyam");
    }   
  }
  
  else if(count - pastG >= 3000 && Gstate == 1)
  {
    digitalWrite(led3,LOW);
    Gstate = 0;
    //pastG = count;
    Serial.println("gOFF");
  }
  
  
 
  //YELLOW
  if(digitalRead(sw2) == LOW && Rstate == 0 && Gstate == 0)
  {
    if(count - pastsw2 >= delaytime)
    {
      Ystate = 1;
      pastsw2 = count;
      pastY = count;
      Serial.println("Y0");
    }    
  }
  if(count - pastY <= 2000 && Ystate == 1)
  {
    if(count -pastY < 500)
    {
      digitalWrite(led2,HIGH);
      Serial.println("Y1");
    }
    else if(count -pastY < 1000)
    {
      digitalWrite(led2,LOW);
      Serial.println("Y2");
    }
    else if(count -pastY < 1500)
    {
      digitalWrite(led2,HIGH);
      Serial.println("Y3");
    }
    else if(count -pastY < 2000)
    {
      digitalWrite(led2,LOW);
      Serial.println("Y4");
    }
}
}
