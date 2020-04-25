/* Project 3
   3 LEDs are toggled using BUTTONs & IR Remote with FreeRTOS.
   
    modified 16/6/17
  by Pooja Kose 
  
 */

#include <Arduino_FreeRTOS.h>
#include <IRremote.h>

void TaskBlink( void *pvParameters );
void TaskBlink1( void *pvParameters );
bool outputState = false;
 bool outputState1 = false;
  bool outputState2 = false;

void setup() {

  xTaskCreate(
    TaskBlink
    ,  (const portCHAR *)"Blink"  
    ,  250
    ,  NULL
    , 2
    ,  NULL );
  
    
    xTaskCreate(
    TaskBlink1
    ,  (const portCHAR *)"Blink3"   
    ,  128 
    ,  NULL
    ,  2
    ,  NULL );
   
}
void loop()
{
}

void TaskBlink(void *pvParameters)  
{
  (void) pvParameters;
 int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
irrecv.enableIRIn();

#define BUTTON_1 0xFF6897
#define BUTTON_2 0xFF9867
#define BUTTON_3 0xFFB04F
int r_LED = 9;
int y_LED = 10;
int b_LED = 13;

  pinMode(r_LED, OUTPUT);
  pinMode(b_LED, OUTPUT);
  pinMode(y_LED, OUTPUT);
  for (;;)
  { 
if (irrecv.decode(&results)) {
    irrecv.resume();
    
    if(results.value == BUTTON_1)
    {
      outputState = !outputState;
       digitalWrite(r_LED, outputState);
    }
    
     if(results.value == BUTTON_2)
    {
     outputState1 = !outputState1;
       digitalWrite(y_LED, outputState1);
    }
        if(results.value == BUTTON_3)
    {
     outputState2 = !outputState2;
       digitalWrite(b_LED, outputState2);
    }
  }
  }
}

  void TaskBlink1(void *pvParameters)
  {
    (void) pvParameters;

int r_LED = 9;
int y_LED = 10;
int b_LED = 13;
int r0_LED = 3;
int b0_LED = 4;
int y0_LED = 5;

  long time = 0;         
long debounce = 500; 
  
 pinMode(r_LED,OUTPUT);
    pinMode(r0_LED, INPUT);
    pinMode(y_LED,OUTPUT);
    pinMode(y0_LED, INPUT);
     pinMode(b_LED,OUTPUT);
    pinMode(b0_LED, INPUT);
    
   for (;;)
   {
   int buttonState = digitalRead(r0_LED);
    int buttonState1 = digitalRead(y0_LED);
      int buttonState2 = digitalRead(b0_LED);

    if(buttonState == 1 && millis() - time > debounce)
    {
      outputState = !outputState;
       digitalWrite(r_LED, outputState);
         time = millis();  
    }
    
     if(buttonState1 == 1 && millis() - time > debounce)
    {
      outputState1 = !outputState1;
       digitalWrite(y_LED, outputState1);
       time = millis();
    }
        if(buttonState2 == 1 && millis() - time > debounce)
    {
      outputState2 = !outputState2;
       digitalWrite(b_LED, outputState2);
       time = millis();
    }
  
}
  }    


