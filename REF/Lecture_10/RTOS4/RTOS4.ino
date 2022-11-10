#include <Arduino_FreeRTOS.h>

#define RED     7
#define YELLOW  8
#define BLUE    9

const uint16_t *blueLed = (uint16_t *) BLUE;
const uint16_t *redLed  = (uint16_t *) RED;
const uint16_t *yellowLed = (uint16_t) YELLOW;

const uint16_t taskParam[3][2] = { {BLUE, 50}, {RED, 100}, {YELLOW, 200} };

void setup() {
  xTaskCreate(LedControllerTask, "RED LED Task", 128, (void *)&taskParam[0], 1, NULL);
  xTaskCreate(LedControllerTask, "BLUE LED Task", 128, (void *)&taskParam[1], 2, NULL);
  xTaskCreate(LedControllerTask, "YELLOW LED Task", 128, (void *)&taskParam[2], 3, NULL);
}

void LedControllerTask(void *pvParameters)
{
  uint16_t *params = pvParameters;

  int ledPin = params[0];
  int time = params[1];

  pinMode(ledPin, OUTPUT);
  while (1)
  {
    vTaskDelay(time);
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
  }
}


void loop() {}
