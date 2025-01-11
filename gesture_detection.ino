#include "DFRobot_Gesture_Touch.h"
#include <FastLED.h>

#define LED_PIN     3    // DPin Number
#define NUM_LEDS    20   // Number of lights
CRGB leds[NUM_LEDS];

#ifdef __AVR__
  SoftwareSerial    mySerial(/*RX*/10, /*TX*/11); 
#elif defined ESP_PLATFORM
// ESP32:IO16 <--> TX:sensor
// ESP32:IO17 <--> RX:sensor
HardwareSerial mySerial(1);
#endif

// init sensor object, request write and read function
DFRobot_Gesture_Touch   DFGT(&mySerial);

const int ledPin = 3; // Pin connected to the LED

void setup()
{
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

  Serial.begin(115200);

  // suggest default value
  DFGT.setGestureDistance(20);

  // enable all functions
  DFGT.enableFunction(DFGT_FUN_ALL);

  // disable function test
  DFGT.disableFunction(DFGT_FUN_RIGHT | DFGT_FUN_LEFT);

  // enable function test
  // DFGT.enableFunction(DFGT_FUN_RIGHT | DFGT_FUN_LEFT);

  // set auto sleep time out, in sleep mode, something approach will wake it up
  // DFGT.setSleep(4);

  Serial.println("simple Gesture!");
}

void loop()
{
  // get an event that data saved in serial buffer
  int8_t rslt = DFGT.getAnEvent();  

  if(rslt != DF_ERR) 
  {
    // disable auto sleep
    // DFGT.setSleep(DFGT_SLEEP_DISABLE);
    switch(rslt) 
    {
      case DFGT_EVT_BACK: 
        Serial.println("get event back");
        break;
      case DFGT_EVT_FORWARD: 
        Serial.println("get event forward");

        for (int i = 0; i < NUM_LEDS; i++) {
          // Assign random colors to each LED
          leds[i] = CRGB(random(0, 256), random(0, 256), random(0, 256));
        }

        FastLED.show();
        delay(5000);

        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CRGB::Black; // Turn off the light
        }
        FastLED.show();
        delay(1000);
        break;
      case DFGT_EVT_RIGHT: 
        Serial.println("get event right");
        break;
      case DFGT_EVT_LEFT: 
        Serial.println("get event left");
        break;
      case DFGT_EVT_PULLUP: 
        Serial.println("get event pull up");
        break;
      case DFGT_EVT_PULLDOWN: 
        Serial.println("get event pull down");
        break;
      case DFGT_EVT_PULLREMOVE: 
        Serial.println("get event pull and remove");
        break;
      case DFGT_EVT_TOUCH1: 
        Serial.println("get event touch1");
        break;
      case DFGT_EVT_TOUCH2: 
        Serial.println("get event touch2");
        break;
      case DFGT_EVT_TOUCH3:  
        Serial.println("get event touch3");
        break;
      case DFGT_EVT_TOUCH4: 
        Serial.println("get event touch4");
        break;
      case DFGT_EVT_TOUCH5: 
        Serial.println("get event touch5");
        break;
    }
  }
}
