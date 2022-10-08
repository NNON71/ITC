#include "LedControl.h"
LedControl lc = LedControl(11, 13, 10, 4); // CLK,DIN,CS,Number of LED Module
int x;
int y=17;
boolean chonright = 0;
boolean chonup = 0;
unsigned long bob,bob1,pastB=0;
boolean start=1;
int buzzs = 3;
#define player1 4
#define player2 2
#define senp1 A0
#define senp2 A4
int button=7;
int p1;
int p2;
int tones[] = {261,277,294,311,330,349,370,392,415,440};
int lemap[8][2] =
{ 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

int leball[8][32] =
{ 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

int P[8][8] =
{ 0, 0, 1, 1, 1, 1, 0, 0,
  0, 1, 0, 0, 0, 1, 0, 0,
  0, 1, 0, 0, 0, 1, 0, 0,
  0, 1, 0, 0, 0, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

int P1[8][8] 
{ 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 0 ,0,
  0, 0, 0, 0, 0, 0, 0, 0
};

int P2[8][8] =
{ 0, 0, 1, 1, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

int letclear[8][8] =
{ 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

void setup()
{
  randomSeed(analogRead(A2));
  for (int address = 0; address < 4; address++) {
    lc.shutdown(address, false);
    lc.setIntensity(address, 1);
    lc.clearDisplay(address);
  }
  pinMode(player1, OUTPUT);
  pinMode(player2, OUTPUT);
  pinMode(buzzs,OUTPUT);
  pinMode(button,INPUT);
  digitalWrite(player1, HIGH);
  digitalWrite(player2, HIGH);
  x = random(0,8);
  millis();
  Serial.begin(9600);
  
}

void buzz(int x)
{
    tone(buzzs,x);
    delay(500);
    noTone(buzzs);
}

void gameover()
{
  start=0;
  if(start==0)
  {
    if(y==0)
    {
      for (int i = 0; i < 8; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          if(P[i][j] == 0) lc.setLed(2,j,i,LOW);   
          else if(P[i][j] == 1) lc.setLed(2,j,i,HIGH);
          if(P1[i][j]==0)lc.setLed(1,j,i,LOW);
          else if(P1[i][j]==1)lc.setLed(1,j,i,HIGH);
        }
       }
    }
    else if(y==31)
    {
      for (int i = 0; i < 8; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          if(P[i][j] == 0) lc.setLed(2,j,i,LOW);   
          else if(P[i][j] == 1) lc.setLed(2,j,i,HIGH);
          if(P2[i][j]==0)lc.setLed(1,j,i,LOW);
          else if(P2[i][j]==1)lc.setLed(1,j,i,HIGH);
        }
       }
    }
  for(int i=0;i<3;i++)
  {
    buzz(tones[i]);
  }
  noTone(buzzs);
  }
}

void clearmap()
{
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<2;j++)
    {
      lemap[i][j]=0;
    }
  }
}

void clearball()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 32; j++)
    {
      leball[i][j]=0;
    }
  }
}

void leclear()
{
    for (int j = 0; j < 8; j++)
    {
      for(int i=0;i<8;i++)
      {
        if(letclear[i][j]==0) 
        {
          lc.setLed(0,i,j,LOW);
          lc.setLed(1,i,j,LOW); 
          lc.setLed(2,i,j,LOW);
          lc.setLed(3,i,j,LOW); 
          delay(10);
        }
      }
    }
}

void updateplayer()
{
  p1=(analogRead(senp1)/145);
  p2=(analogRead(senp2)/145);
  //Serial.println(p1);
  switch(p1)
  {
  case 0 :
    lemap[0][1]=1;
    lemap[1][1]=1;
    lemap[2][1]=1;
    break;
  case 1 :
    lemap[0][1]=1;
    lemap[1][1]=1;
    lemap[2][1]=1;
    break;
  
  case 2 :
    lemap[1][1]=1;
    lemap[2][1]=1;
    lemap[3][1]=1;
    break;

  case 3 :
    lemap[2][1]=1;
    lemap[3][1]=1;
    lemap[4][1]=1;
    break;
 
  case 4 :
    lemap[3][1]=1;
    lemap[4][1]=1;
    lemap[5][1]=1;
    break;
    
  case 5 :
    lemap[4][1]=1;
    lemap[5][1]=1;
    lemap[6][1]=1;
    break;

  case 6 :
    lemap[5][1]=1;
    lemap[6][1]=1;
    lemap[7][1]=1;
    break;
    
  case 7 :
    lemap[5][1]=1;
    lemap[6][1]=1;
    lemap[7][1]=1;
    break;
  }

  switch(p2)
  {
  case 0 :
    lemap[0][0]=1;
    lemap[1][0]=1;
    lemap[2][0]=1;
    break;
  case 1 :
    lemap[0][0]=1;
    lemap[1][0]=1;
    lemap[2][0]=1;
    break;
  
  case 2 :
    lemap[1][0]=1;
    lemap[2][0]=1;
    lemap[3][0]=1;
    break;

  case 3 :
    lemap[2][0]=1;
    lemap[3][0]=1;
    lemap[4][0]=1;
    break;
 
  case 4 :
    lemap[3][0]=1;
    lemap[4][0]=1;
    lemap[5][0]=1;
    break;
    
  case 5 :
    lemap[4][0]=1;
    lemap[5][0]=1;
    lemap[6][0]=1;
    break;

  case 6 :
    lemap[5][0]=1;
    lemap[6][0]=1;
    lemap[7][0]=1;
    break;
    
  case 7 :
    lemap[5][0]=1;
    lemap[6][0]=1;
    lemap[7][0]=1;
    break;
  }
  bob1=millis();
}

void player()
{
  if(millis()-bob1>=100)
  {
   clearmap();
   updateplayer();
  }
  for (int i = 0; i < 8; i++)
  {
      if(lemap[i][1] == 0) 
      {
        lc.setLed(0,i,7,LOW);
  
      }
      else if(lemap[i][1] == 1)
      {
        lc.setLed(0,i,7,HIGH);
      }
  } 
  for (int i = 0; i < 8; i++)
  {
      if(lemap[i][0] == 0) 
      {
        lc.setLed(3,i,0,LOW);
  
      }
      else if(lemap[i][0] == 1)
      {
        lc.setLed(3,i,0,HIGH);
      }
  } 
}

void testBall()
{
  if(millis()-bob>=200)
  {
    clearball();
    testupdateball();
  }
}

void drawball()
{
  if(y<8)
  {
    for (int j = 1; j < 8; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        lc.setLed(2,i,0,LOW);
        if(leball[i][j]==0)
        {
          lc.setLed(3,i,j,LOW);
        }
        else if(leball[i][j]==1)
        {
          lc.setLed(3,i,j,HIGH);
        }          
      }
    }
    //Serial.println("S4");  
  }
  else if(y>=8&&y<16)
  { 
    for (int j = 8; j < 16; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        lc.setLed(1,i,0,LOW);
        lc.setLed(3,i,7,LOW);
        if(leball[i][j]==0)
        {
          lc.setLed(2,i,j%8,LOW);
        }
        else if(leball[i][j]==1)
        {
          lc.setLed(2,i,j%8,HIGH);
        }          
      }
    }
    //Serial.println("S3");  
  }
  else if(y>=16&&y<24)
  {
    for (int j = 16; j < 24; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        lc.setLed(0,i,0,LOW);
        lc.setLed(2,i,7,LOW);
        if(leball[i][j]==0)
        {
          lc.setLed(1,i,j%8,LOW);
        }
        else if(leball[i][j]==1)
        {
          lc.setLed(1,i,j%8,HIGH);
        }          
      }
    }
    //Serial.println("S2");  
  }
  
  if(y>=24&&y<32)
  {
    for (int j = 24; j < 31; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        lc.setLed(1,i,7,LOW);
        if(leball[i][j]==0)
        {
          lc.setLed(0,i,j%8,LOW);
        }
        else if(leball[i][j]==1)
        {
          lc.setLed(0,i,j%8,HIGH);
        }          
      }
    }
    //Serial.println("S1");  
  }
}

void testupdateball()
{
  //bouncing pong
  if(chonup==1) y++; 
  else y--;
  
  if(chonright==1) x--; 
  else x++;

  //update ball in array leball and print led at x y of ball
  leball[x][y]=1;
  drawball();

  //check khob
  if(x==7)chonright=1; //ขอบซ้าย
  else if(x==0) chonright=0;//ขอบขวา
  
  //p1 win
  if(y==0)
  {
    gameover(); 
    //start=0;
    Serial.println("P2 WIN");
    
  }
  else if(y==31)
  {
    gameover(); 
    //start=0;
    Serial.println("P1 WIN");
  }
  
  //p2 bar controll
  if(y==1) 
  {
   if(lemap[x][0]==1){
      {
        chonup=1;
        Serial.println("BONG");
        buzz(600);
      }
    }
    if((lemap[x+1][0]==1&&chonup==0&&chonright==0&&x!=0) || (x==7&&lemap[x-1][0]==1)){
      {
        //Serial.println(String("chonup = ")+chonup+String("chonright = ")+chonright); 
        chonup=1;
        chonright=1;
        buzz(700);
        Serial.println("BONG1");
      }
    }
    if((lemap[x-1][0]==1&&chonup==0&&chonright==1&&x!=7) || (x==0&&lemap[x+1][0]==1)){
      {
        //Serial.println(String("chonup = ")+chonup+String("chonright = ")+chonright); 
        chonup=1;
        chonright=0;
        buzz(700);
        Serial.println("BONG2");
      }
    }
  }

  //p1 bar controll
  if(y==30) 
  {
    if(lemap[x][1]==1){
      {
        chonup=0;
        Serial.println("BONG");
        buzz(600);
      }
    }
    if((lemap[x+1][1]==1&&chonup==1&&chonright==0&&x!=0) || (x==7&&lemap[x-1][1]==1)){
      {
        //Serial.println(String("chonup = ")+chonup+String("chonright = ")+chonright); 
        chonup=0;
        chonright=1;
        Serial.println("BONG1");
        buzz(700);
      }
    }
    if((lemap[x-1][1]==1&&chonup==1&&chonright==1&&x!=7) || (x==0&&lemap[x+1][1]==1)){
      {
        //Serial.println(String("chonup = ")+chonup+String("chonright = ")+chonright); 
        chonup=0;
        chonright=0;
        Serial.println("BONG2");
        buzz(700);
      }
    }
  }
   
  bob=millis();  
}

void loop()
{
  //Serial.println(analogRead(senp2));
  //Serial.println(String("x = ")+x+String("y = ")+y); 
  //Serial.println(start);
  //Serial.println(digitalRead(button));
  if(start==1)
  {
    testBall();
    player();
  }
  else
  {  
    if(millis()-pastB>=500)
    {
      if(digitalRead(button)==1)
      {
        leclear();
        x=random(0,8);
        y=17;
        start=1;
        pastB=millis();    
      }
    }
  }
}
