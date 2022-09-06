int r[] = {12, 13, 11};

void setup() {

}

void loop() {
  
  pinMode(r[0], OUTPUT);//1
  digitalWrite(r[0], LOW);
  pinMode(r[1], OUTPUT);
  digitalWrite(r[1], HIGH);
  pinMode(r[2], INPUT);
  delay(1000);
  pinMode(r[0], OUTPUT);//2
  digitalWrite(r[0], HIGH);
  pinMode(r[1], OUTPUT);
  digitalWrite(r[1], LOW);
  pinMode(r[2], INPUT);
  delay(1000);
  pinMode(r[1], OUTPUT);//3
  digitalWrite(r[1], LOW);
  pinMode(r[2], OUTPUT);
  digitalWrite(r[2], HIGH);
  pinMode(r[0], INPUT);
  delay(1000);
  pinMode(r[1], OUTPUT);//4
  digitalWrite(r[1], HIGH);
  pinMode(r[2], OUTPUT);
  digitalWrite(r[2], LOW);
  pinMode(r[0], INPUT);
  delay(1000);
  pinMode(r[0], OUTPUT);//5
  digitalWrite(r[0], LOW);
  pinMode(r[2], OUTPUT);
  digitalWrite(r[2], HIGH);
  pinMode(r[1], INPUT);
  delay(1000);
  pinMode(r[0], OUTPUT);//6
  digitalWrite(r[0], HIGH);
  pinMode(r[2], OUTPUT);
  digitalWrite(r[2], LOW);
  pinMode(r[1], INPUT);
  delay(1000);
  //L2
  pinMode(r[0], OUTPUT);//5
  digitalWrite(r[0], LOW);
  pinMode(r[2], OUTPUT);
  digitalWrite(r[2], HIGH);
  pinMode(r[1], INPUT);
  delay(1000);
  pinMode(r[1], OUTPUT);//4
  digitalWrite(r[1], HIGH);
  pinMode(r[2], OUTPUT);
  digitalWrite(r[2], LOW);
  pinMode(r[0], INPUT);
  delay(1000);
  pinMode(r[1], OUTPUT);//3
  digitalWrite(r[1], LOW);
  pinMode(r[2], OUTPUT);
  digitalWrite(r[2], HIGH);
  pinMode(r[0], INPUT);
  delay(1000);
  pinMode(r[0], OUTPUT);//2
  digitalWrite(r[0], HIGH);
  pinMode(r[1], OUTPUT);
  digitalWrite(r[1], LOW);
  pinMode(r[2], INPUT);
  delay(1000);

}
