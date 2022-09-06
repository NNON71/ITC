int number; // number to display
int bitPattern[10] = {B01000001, B01111011, B11000010, B01010010, B01111000, B01010100, B01000100, B01110011, B01000000, B01010000};
int bitans[3] = {B01000001,B01000101,B11001101};
#define buttonA 13
#define buttonB 2
const byte numPins = 8;
const int segmentPins[8] = {11, 10 , 9, 8, 7, 6, 5, 4};
int i = 0;
unsigned int pastA=0;
int bob;
void setup () {
  Serial.begin(9600);
  for (int i = 0; i < numPins; i++)
    pinMode(segmentPins[i], OUTPUT);
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  bob = random(1,9);
}
void loop() {
  //Serial.println(digitalRead(buttonB));
  Serial.println(String("random = ")+bob);
  if (digitalRead(buttonA)==0) {
    //Serial.println(i);
    if (millis() - pastA >= 400) {
      pastA = millis();
      i = i + 1;
      boolean isBitSet;
      for (int segment = 0; segment < 8; segment++) 
      {
        isBitSet = bitRead(bitPattern[i], segment);
        digitalWrite(segmentPins[segment], isBitSet);
      }
      if(i>=9) {i=0;}
    }
  }
  
//  if (digitalRead(buttonB)==1){
//    if(i==bob)
//    {
//      
//      boolean isBitSet;
//      for (int segment = 0; segment < 8; segment++) 
//      {
//        isBitSet = bitRead(bitans[0], segment);
//        digitalWrite(segmentPins[segment], isBitSet);
//      }
//    }
//    
//    if(i > bob)
//    {
//      boolean isBitSet;
//      for (int segment = 0; segment < 8; segment++) 
//      {
//        isBitSet = bitRead(bitans[1], segment);
//        digitalWrite(segmentPins[segment], isBitSet);
//      }
//    }
//    if(i < bob)
//    {
//      boolean isBitSet;
//      for (int segment = 0; segment < 8; segment++) 
//      {
//        isBitSet = bitRead(bitans[2], segment);
//        digitalWrite(segmentPins[segment], isBitSet);
//      }
//    }
//  }
}
 
