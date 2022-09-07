int number; // number to display
int bitPattern[9] = {B11101101, B01000011, B01001001, B00101101, B00011001, B00010001, B11001101, B00000001, B00001001};
int bitans[3] = {B10000001, B10010001, B10110011};
#define buttonA 13
#define buttonB 12
const byte numPins = 8;
const int segmentPins[8] = {11, 10 , 9, 8, 7, 6, 5, 4};
int i = 0;
unsigned int pastA = 0;
unsigned int pastB = 0;
int randomNo ;
boolean isBitSet;
void setup () {
  Serial.begin(9600);
  for (int i = 0; i < numPins; i++)
    pinMode(segmentPins[i], OUTPUT);
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  for (int segment = 0; segment < 8; segment++)
  {
    isBitSet = bitRead(bitPattern[0], segment);
    digitalWrite(segmentPins[segment], isBitSet);
  }
  randomSeed(analogRead(A0));
  randomNo  = random(1, 10);
  Serial.println(String("random = ") + randomNo );

}

void switchA() {
  //Serial.println(digitalRead(buttonA));
  if (digitalRead(buttonA) == 1)
  {
    Serial.println(i);
    if (millis() - pastA >= 600)
    {
      pastA = millis();
      i++;
      if (i > 8) i = 0;
      /*
        for (int segment = 0; segment < 8; segment++)
        {
        isBitSet = bitRead(bitPattern[i], segment);
        digitalWrite(segmentPins[segment], isBitSet);
        }
      */
    }
  }
}

void switchB() {
  if (digitalRead(buttonB) == 1)
  {
    if (millis() - pastB >= 400)
    {
      pastB = millis();
      if (i + 1 == randomNo )
      {

        for (int segment = 0; segment < 8; segment++)
        {
          isBitSet = bitRead(bitans[0], segment);
          digitalWrite(segmentPins[segment], isBitSet);
        }
        delay(1000);
        randomNo  = random(1, 10);
        i = 0;
        Serial.println(String("random = ") + randomNo );
      }

      else if (i + 1 > randomNo )
      {

        for (int segment = 0; segment < 8; segment++)
        {
          isBitSet = bitRead(bitans[1], segment);
          digitalWrite(segmentPins[segment], isBitSet);
        }
        delay(1000);
      }
      else if (i + 1 < randomNo )
      {

        for (int segment = 0; segment < 8; segment++)
        {
          isBitSet = bitRead(bitans[2], segment);
          digitalWrite(segmentPins[segment], isBitSet);
        }
        delay(1000);
      }
    }
  }
}

void loop() {
  switchA();
  //Serial.println(i);
  switchB();
  delay(100);
  for (int segment = 0; segment < 8; segment++)
  {
    isBitSet = bitRead(bitPattern[i], segment);
    digitalWrite(segmentPins[segment], isBitSet);
  }
}
