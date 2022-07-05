#include <SPI.h>
#include <DHT.h>
#include <Wire.h>
#include "images.h"
#include "SH1106Wire.h"               // Only needed for Arduino 1.6.5 and earlier
#define DHTPIN 2         // Digital pin 4
#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);
SH1106Wire display(0x3c, D2, D1);

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}

void setup()
{
  Serial.begin(115200); // See the connection status in Serial Monitor
  dht.begin();
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  pinMode(A0, INPUT);
  pinMode(D5, OUTPUT);
}
void drawProgressBarDemo() {
  // display.setColor(INVERSE);
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "Humidity : " + String(h) + "%");
  display.drawProgressBar(0, 12, 103, 10, h);
  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 35,"Temprature : " +  String(t) + char(223) + "C");
  display.drawProgressBar(0, 48, 103, 10, t);
  
}

void drawImageDemo() {
  // see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
  // on how to create xbm files
  display.drawXbm(104, 0, h_width, h_height, h_bits);
  display.drawXbm(104, 40, t_width, t_height, t_bits);
}

void printDisplay(){
  display.clear();
  drawProgressBarDemo();
  drawImageDemo();
  display.display();
  delay(2000);
}

void loop()
{
printDisplay();
}