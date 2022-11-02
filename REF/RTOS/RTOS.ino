#include <Arduino_FreeRTOS.h>
#define RED 8
#define YELLOW 6
#define BLUE 7
const uint16_t *blueLed = (uint16_t *) BLUE;
const uint16_t *redLed = (uint16_t *) RED;
const uint16_t *yellowLed = (uint16_t *) YELLOW;
void setup() {
  xTaskCreate(LedControllerTask, "RED LED Task", 128, (void *)redLed, 2, NULL);
  xTaskCreate(LedControllerTask, "BLUE LED Task", 128, (void *)blueLed, 1, NULL);
  xTaskCreate(LedControllerTask, "YELLOW LED Task", 128, (void *)yellowLed, 1, NULL);
}
void LedControllerTask(void *pvParameters) {
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  while (1) {
    delay(1000);
    digitalWrite(pvParameters, digitalRead(pvParameters) ^ 1);
  }
}
void loop() {}
