

/***************************************************
 *                    Preprocessor
 ***************************************************/
/*  using uCOS-II to manage tasks */
#include "ucos_ii.h"
#include <stdio.h>

#define TASK_STACKSIZE   2048
#define TASK1_PRIORITY   1      // kevin 設多少都沒差後面會改
#define TASK2_PRIORITY   2      // kevin 設多少都沒差後面會改
#define TASK3_PRIORITY   3      // kevin 設多少都沒差後面會改
#define TASK4_PRIORITY   4      // kevin 設多少都沒差後面會改
#define TASK1_ID         1
#define TASK2_ID         2
#define TASK3_ID         3
#define TASK4_ID         4

#define F_CPU 1

/***************************************************
 *                    Globals
 ***************************************************/

OS_STK    task1_stk[TASK_STACKSIZE];
OS_STK    task2_stk[TASK_STACKSIZE];
OS_STK    task3_stk[TASK_STACKSIZE];
OS_STK    task4_stk[TASK_STACKSIZE];

const byte T1_LEDPin = 49;
const byte T2_LEDPin = 51;
const byte T3_LEDPin = 53;


/***************************************************
 *                    Prototypes
 ***************************************************/

void task1(void* pdata);
void task2(void* pdata);
void task3(void* pdata);

void  StartupTask (void  *pdata);

void task1(void* pdata);
void task2(void* pdata);
void task3(void* pdata); // kevin
void task4(void* pdata); // kevin

/***************************************************
 *                    Main
 ***************************************************/

void setup() {
    Serial.begin(115200);                                                /* Use serial port for control (board rate : 9600) */
    
    pinMode(T1_LEDPin, OUTPUT);
    pinMode(T2_LEDPin, OUTPUT);
    pinMode(T3_LEDPin, OUTPUT);

    OSInit();                                                          /* initialize uCOS */
    OSTaskCreateExt(task1,
      NULL,
      (unsigned int *) &task1_stk[TASK_STACKSIZE - 1],
      TASK1_PRIORITY,
      1,
      task1_stk,
      TASK_STACKSIZE,
      NULL,
      0);
    OSTaskCreateExt(task2,
      NULL,
      (unsigned int *) &task2_stk[TASK_STACKSIZE - 1],
      TASK2_PRIORITY,
      2,
      task2_stk,
      TASK_STACKSIZE,
      NULL,
      0);
    // if(kevin_task_num >= 3) // kevin
    OSTaskCreateExt(task3,
      NULL,
      (unsigned int *) &task3_stk[TASK_STACKSIZE - 1],
      TASK3_PRIORITY,
      3,
      task3_stk,
      TASK_STACKSIZE,
      NULL,
      0);
    // if(kevin_task_num >= 4) // kevin
    OSTaskCreateExt(task4,
      NULL,
      (unsigned int *) &task4_stk[TASK_STACKSIZE - 1],
      TASK4_PRIORITY,
      4,
      task4_stk,
      TASK_STACKSIZE,
      NULL,
      0);

    OSStart();
}

/***************************************************
 *                    Functions
 ***************************************************/
void task1(void* pdata) {
  boolean state = HIGH;
  while (1)
  { 
    Serial.println("Hello from task1");
    // digitalWrite(T1_LEDPin, state);
    // state = !state;
    OSTimeDly(1000);
    // while (1); // kevin 讓他一直卡在裡面 靠OSintexit來切
  }
}

void task2(void* pdata) {
  boolean state = HIGH;
  while (1)
  {
    Serial.println("Hello from task2");
    // digitalWrite(T2_LEDPin, state);
    // state = !state;
    OSTimeDly(5000);
    // while (1); // kevin 讓他一直卡在裡面 靠OSintexit來切
  }
}

void task3(void* pdata) {
  boolean state = HIGH;
  while (1)
  {
    Serial.println("Hello from task3");
    // digitalWrite(T3_LEDPin, state);
    // state = !state;
    OSTimeDly(7000);
    // while (1); // kevin 讓他一直卡在裡面 靠OSintexit來切
  }
}

void task4(void* pdata) {
  boolean state = HIGH;
  while (1)
  {
    Serial.println("Hello from task4");
    // digitalWrite(T4_LEDPin, state);
    // state = !state;
    OSTimeDly(7000);
    // while (1); // kevin 讓他一直卡在裡面 靠OSintexit來切
  }
}

/***************************************************
 *                    Fin
***************************************************/
void loop() {
}
