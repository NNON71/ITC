#include <Arduino_FreeRTOS.h>
#include "task.h"

TaskHandle_t TaskHandle_2; // handler for Task2

void setup() 
{
  Serial.begin(9600); // Enable serial communication library.
  pinMode(7, OUTPUT);  // define LED1 pin as a digital output 
  pinMode(8, OUTPUT);  // define LED2 pin as a digital output

  xTaskCreate(Task1, "LED1", 100, NULL, 1, NULL);
}

void loop() {}

void Task1(void* pvParameters)
{
  while(1)
  {
    Serial.println("Task1 Running"); // print "Task1 Running" on Arduino Serial Monitor
    digitalWrite(7, HIGH); // sets the digital pin 7 off
    digitalWrite(8, LOW); // sets the digital pin 8 on
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second    
    xTaskCreate(Task2, "LED2", 100, NULL, 2, &TaskHandle_2); // create task2 with priority 2
  }
}


/* Task2 with priority 2 */
void Task2(void* pvParameters)
{ 
    digitalWrite(7, LOW); // sets the digital pin 5 high
    digitalWrite(8, HIGH); // sets the digital pin 4 low
    Serial.println("Task2 is runnig and about to delete itself");
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second         
    vTaskDelete(TaskHandle_2);     //Delete own task by passing NULL(TaskHandle_2 can also be used)
   
}
