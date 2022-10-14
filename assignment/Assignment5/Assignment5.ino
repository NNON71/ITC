#define LED_W_R 5
#define LED_W_Y 6
#define LED_W_G 7
#define WEST_BUTTON_PIN 2
#define LED_S_R 8
#define LED_S_Y 9
#define LED_S_G 10
#define SOUTH_BUTTON_PIN 3
#define LED_P_R 11
#define LED_P_G 12
#define P_BUTTON_PIN 4

#define goW 0
#define waitW 1
#define goS 2
#define waitS 3
#define GoPW 4
#define waitPWtid1 5
#define waitPWdab1 6
#define waitPWtid2 7
#define waitPWdab2 8
#define waitPWtid3 9
#define waitPWdab3 10
#define GoPS 11
#define waitPStid1 12
#define waitPSdab1 13
#define waitPStid2 14
#define waitPSdab2 15
#define waitPStid3 16
#define waitPSdab3 17
#define swapS 18
#define swapW 19

int input, input1, input2,input3;

struct State {
  unsigned long ST_Out; // 6-bit pattern to street output
  unsigned long Time; // delay in ms units
  unsigned long Next[8];
}; // next state for inputs 0,1,2,3
typedef const struct State SType;
SType FSM[20] = {
  {B01001100,2000,{goW, goW, waitW, waitW, waitPWtid1, waitPWtid1, waitPStid1, waitPStid1}},
  {B01010100,500, {goS, goS, goS, goS, goS, goS, goS, goS}},
  {B01100001,2000,{goS, waitS, goS, waitS, waitPWtid1, waitPWtid1, waitPStid1, waitPWtid1}},
  {B01100010,500, {goW, goW, goW, goW, goW, goW, goW, goW}},
  {B10001001,2000,{GoPW, swapW, swapS, swapW, GoPW, swapW, swapS, swapW}},
  {B00001001,500, {waitPWdab1, waitPWdab1, waitPWdab1, waitPWdab1, waitPWdab1, waitPWdab1, waitPWdab1, waitPWdab1}},
  {B01001001,500, {waitPWtid2, waitPWtid2, waitPWtid2, waitPWtid2, waitPWtid2, waitPWtid2, waitPWtid2, waitPWtid2}},
  {B00001001,500, {waitPWdab2, waitPWdab2, waitPWdab2, waitPWdab2, waitPWdab2, waitPWdab2, waitPWdab2, waitPWdab2}},
  {B01001001,500, {waitPWtid3, waitPWtid3, waitPWtid3, waitPWtid3, waitPWtid3, waitPWtid3, waitPWtid3, waitPWtid3}},
  {B00001001,500, {waitPWdab3, waitPWdab3, waitPWdab3, waitPWdab3, waitPWdab3, waitPWdab3, waitPWdab3, waitPWdab3}},
  {B01001001,500, {GoPW, GoPW, GoPW, GoPW, GoPW, GoPW, GoPW, GoPW}},
  {B10001001,2000,{GoPS, swapW, swapS, swapS, waitPWtid1, waitPWtid1, swapS, swapS}},
  {B00001001,500, {waitPSdab1, waitPSdab1, waitPSdab1, waitPSdab1, waitPSdab1, waitPSdab1, waitPSdab1, waitPSdab1}},
  {B01001001,500, {waitPStid2, waitPStid2, waitPStid2, waitPStid2, waitPStid2, waitPStid2, waitPStid2, waitPStid2}},
  {B00001001,500, {waitPSdab2, waitPSdab2, waitPSdab2, waitPSdab2, waitPSdab2, waitPSdab2, waitPSdab2, waitPSdab2}},
  {B01001001,500, {waitPStid3, waitPStid3, waitPStid3, waitPStid3, waitPStid3, waitPStid3, waitPStid3, waitPStid3}},
  {B00001001,500, {waitPSdab3, waitPSdab3, waitPSdab3, waitPSdab3, waitPSdab3, waitPSdab3, waitPSdab3, waitPSdab3}},
  {B01001001,500, {GoPS, GoPS, GoPS, GoPS, GoPS, GoPS, GoPS, GoPS}},
  {B01010001,500, {goS, goS, goS, goS, goS, goS, goS, goS}},
  {B01001010,500, {goW, goW, goW, goW, goW, goW, goW, goW}}
};
unsigned long S = 0; // index to the current state

void setup() {
  pinMode(LED_W_R, OUTPUT);
  pinMode(LED_W_Y, OUTPUT);
  pinMode(LED_W_G, OUTPUT);
  pinMode(WEST_BUTTON_PIN, INPUT);
  pinMode(LED_S_R, OUTPUT);
  pinMode(LED_S_Y, OUTPUT);
  pinMode(LED_S_G, OUTPUT);
  pinMode(SOUTH_BUTTON_PIN, INPUT);
  pinMode(LED_P_R, OUTPUT);
  pinMode(LED_P_G, OUTPUT);
  pinMode(P_BUTTON_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  //Serial.println(String("BW = ")+input1+String("BS = ")+input2+String("BP = ")+input3);
  Serial.println(input);
  Serial.println(S);
  
  digitalWrite(LED_W_R, bitRead(FSM[S].ST_Out,0));
  digitalWrite(LED_W_Y, bitRead(FSM[S].ST_Out,1));
  digitalWrite(LED_W_G, bitRead(FSM[S].ST_Out,2));
  digitalWrite(LED_S_R, bitRead(FSM[S].ST_Out,3));
  digitalWrite(LED_S_Y, bitRead(FSM[S].ST_Out,4));
  digitalWrite(LED_S_G, bitRead(FSM[S].ST_Out,5));
  digitalWrite(LED_P_R, bitRead(FSM[S].ST_Out,6));
  digitalWrite(LED_P_G, bitRead(FSM[S].ST_Out,7));
  
  delay(FSM[S].Time);
  
  input1 = digitalRead(WEST_BUTTON_PIN);
  input2 = digitalRead(SOUTH_BUTTON_PIN);
  input3 = digitalRead(P_BUTTON_PIN); 
  input = input2*2 + input1 + input3*4;
  S = FSM[S].Next[input];
}
