#include <string.h>
#include <Arduino.h>
#include <SPI.h>

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

#include <Adafruit_CircuitPlayground.h>

// Configuration (you don't need to change these, but can!):
#define FACTORYRESET_ENABLE     1   // Set to 1 to factory reset the Bluefruit LE
                                    // module.  In general this is a smart idea to
                                    // put the module into a known good state.
                                    // A value of 1 means perform a factory reset
                                    // on start, and 0 means no factory reset.

#define NUMPIXELS               10  // Number of NeoPixels on the board.

//#define BRIGHTNESS              255 // NeoPixel brightness (0...255, low to max brightness)
#define CLICKTHRESHHOLD 120

float X, Y, Z;
float activity;
#define MOVE_THRESHOLD 3

/*=========================================================================*/

// Create the bluefruit object, for Circuit Playground this needs to be
// hardware serial.
Adafruit_BluefruitLE_UART ble(BLUEFRUIT_HWSERIAL_NAME, BLUEFRUIT_UART_MODE_PIN);

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}
///////////////////////////////////////////////////////////////////////////////
// Circuit Playground Bike Light - Rainbow Chaser
//
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)

 
#define ROTATION_RATE   100    // lower is faster
 
// Define 10 colors here.
// Must be 10 entries.
// Use 0x000000 if you want a blank space.
uint32_t colors[] = {
  0xFF0000,   
  0xFF5500,
  0xFFFF00,
  0x00FF00,
  0x0000FF,
  0xFF00FF,
  0xFF0000,
  0xFF5500,
  0xFFFF00,
  0x00FF00
};
 
int colorIndex;
int startIndex;
int currentAllowed; 
///////////////////////////////////////////////////////////////////////////////
void setup() {

    // Initialize Circuit Playground library and turn off the Pixels.
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
  activity = 10;
  currentAllowed=1;
  //while (!Serial);
  delay(500);
  // Initialize serial output.
  Serial.begin(115200);
  Serial.println(F("Adafruit Circuit Playground Bluefruit"));
  Serial.println(F("-------------------------------------------------------------------"));

  // Initialise the module
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in DATA mode & check wiring...."));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    // Perform a factory reset to make sure everything is in a known state
    Serial.println(F("Performing a factory reset: "));
    if (!ble.factoryReset()) {
      Serial.println(F("Couldn't factory reset, making another attempt..."));
      delay(1000);
      if (!ble.factoryReset()) {
        error(F("Couldn't factory reset!"));
      }
    }
  }

  // Disable command echo from Bluefruit
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  // Print Bluefruit information
  ble.info();

  // Change advertised name to Circuit_Playground_BLE
  ble.println("AT+GAPDEVNAME=CPlay_BLE");
  delay(100);
  ble.println("ATZ");
  delay(100);

  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in Controller mode"));
  Serial.println(F("Then activate/use the sensors, color picker, game controller, etc!"));
  Serial.println();

  ble.verbose(false);  // debug info is a little annoying after this point!

  // Wait for connection
  while (! ble.isConnected()) {
      delay(500);
  }

  Serial.println(F("***********************"));

  // Set Bluefruit to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("***********************"));

  
  // Make it bright!
  //CircuitPlayground.setBrightness(255);
 
  // Start at the beginning
  startIndex = 0;
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
  
  // 0 = turn off click detection & interrupt
  // 1 = single click only interrupt output
  // 2 = double click only interrupt output, detect single click
  // Adjust threshhold, higher numbers are less sensitive
  CircuitPlayground.setAccelTap(1, CLICKTHRESHHOLD);
  
  // have a procedure called when a tap is detected
  attachInterrupt(digitalPinToInterrupt(CPLAY_LIS3DH_INTERRUPT), tapTime, FALLING);
}
 
void tapTime(void) {
  // do something :)
   Serial.print("Tap! ");
   currentAllowed++;
} 
///////////////////////////////////////////////////////////////////////////////
void loop() {
  //This prints the value for activity
  //------------------------------------------------
  ble.println(activity);

  //---------------------------------------------------
  //Here is were Motion is detected
  //CircuitPlayground.clearPixels();
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();
 
   // Get the magnitude (length) of the 3 axis vector
  // http://en.wikipedia.org/wiki/Euclidean_vector#Length
  double storedVector = X*X;
  storedVector += Y*Y;
  storedVector += Z*Z;
  storedVector = sqrt(storedVector);
  //Serial.print("Len: "); Serial.println(storedVector);
  
  // wait a bit
  delay(100);
  
  // get new data!
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();
  double newVector = X*X;
  newVector += Y*Y;
  newVector += Z*Z;
  newVector = sqrt(newVector);
  //Serial.print("New Len: "); Serial.println(newVector);
  
  // are we moving 
  if (abs(10*newVector - 10*storedVector) > MOVE_THRESHOLD) {
    Serial.println("Twinkle!");
    if (activity < 100){
      activity += 1;
    }
    //CircuitPlayground.setPixelColor(0, 255,   0,   0);
    //delay(1000);
  }


  //From here is where the Visual Effect is handled
  //------------------------------------
  // Turn off all the NeoPixels
  CircuitPlayground.clearPixels();
 
  // Loop through and set pixels
  colorIndex = startIndex;
  for (int pixel=0; pixel<10; pixel++) {
    if (colorIndex>currentAllowed){
      CircuitPlayground.setPixelColor(pixel, 0x111111);
    } else {
      CircuitPlayground.setPixelColor(pixel, colors[colorIndex]);
    }
    colorIndex++;
    if (colorIndex > 9) colorIndex = 0;
  }
  CircuitPlayground.setBrightness(activity);
 
  // Increment start index into color array
  startIndex++;
 
  // Check value and reset if necessary
  if (startIndex > 9) startIndex = 0;
 
  // Wait a little bit so we don't spin too fast
  delay(ROTATION_RATE-map(activity,0,100,0,ROTATION_RATE));
}
