


#include <Adafru2
it_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif


#define PIN        6


#define NUMPIXELS 16 // Popular NeoPixel ring size


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels


#include <Wire.h>
#include "Adafruit_MCP9808.h"

// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!tempsensor.begin(0x18)) {
    Serial.println("Couldn't find MCP9808! Check your connections and verify the address is correct.");
    while (1);
  }
  tempsensor.setResolution(3);
  pixels.begin();
}

void loop() {

  Serial.println("wake up MCP9808.... ");
  tempsensor.wake();


  Serial.print("Resolution in mode: ");

  float c = tempsensor.readTempC();
  float f = tempsensor.readTempF();
  Serial.print("Temp: ");
  Serial.print(c, 4); Serial.print("*C\t and ");
  Serial.print(f, 4); Serial.println("*F.");

  delay(1000
  );
  Serial.println("Shutdown MCP9808.... ");
  tempsensor.shutdown_wake(1);
  Serial.println("");
  delay(200);




  pixels.clear();
  for (int i = 0; i < NUMPIXELS; i++) {




    if (f >= 75) {
      pixels.setPixelColor(0, pixels.Color(150, 0, 0));
      pixels.setPixelColor(1, pixels.Color(150, 0, 0));
      pixels.setPixelColor(2, pixels.Color(150, 0, 0));
      pixels.setPixelColor(3, pixels.Color(150, 0, 0));
      pixels.setPixelColor(4, pixels.Color(150, 0, 0));
      pixels.setPixelColor(5, pixels.Color(150, 0, 0));
      pixels.setPixelColor(6, pixels.Color(150, 0, 0));
      pixels.setPixelColor(7, pixels.Color(150, 0, 0));
      pixels.show();
      Serial.print("HOT");

    } else {
      pixels.setPixelColor(0, pixels.Color(0, 0, 150));
      pixels.setPixelColor(1, pixels.Color(0, 0, 150));
      pixels.setPixelColor(2, pixels.Color(0, 0, 150));
      pixels.setPixelColor(3, pixels.Color(0, 0, 150));
      pixels.setPixelColor(4, pixels.Color(0, 0, 150));
      pixels.setPixelColor(5, pixels.Color(0, 0, 150));
      pixels.setPixelColor(6, pixels.Color(0, 0, 150));
      pixels.setPixelColor(7, pixels.Color(0, 0, 150));
      pixels.show();
      Serial.print("COLD");
    }
    delay(DELAYVAL);
    pixels.show();
  }
}
