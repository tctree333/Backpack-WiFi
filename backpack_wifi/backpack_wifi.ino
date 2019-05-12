// include Libraries
#include` <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// include seperate HTML
#include "index.h"

// define credentials
#define APSSID "Backpack_Wifi"
#define APPSK "12345678"

// set buzzer pin to D0 (GPIO 16)
#define buzzerPin 16

// set led pin to builtin led
#define ledPin 2

// set credentials
const char *ssid = APSSID;
const char *password = APPSK;

// define server
ESP8266WebServer server(80);

// assign a unique ID to this sensor at the same time
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(31337);

// what to display
void handleRoot() { // main page
  String content = MAIN_page; // get HTML
  server.send(200, "text/html", content); // send HTML
}

void handleData() { // display data
  server.send(200, "text/plain", String(getDeg()));
}

void handleBuzz() { // trigger the buzzer
  digitalWrite(buzzerPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);
  server.send(200, "text/plain", "ok");
}

void setup(void) {
  // start access point
  WiFi.softAP(ssid, password);

  // start server
  server.on("/", handleRoot);
  server.on("/getData", handleData);
  server.on("/buzz", handleBuzz);
  server.begin();

  // setup buzzer pin
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // start indicator light
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // initialise the sensor
  if (!mag.begin()) {
    // there was a problem detecting the LSM303 ... check your connections
    while (1) {
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
    }
  }

}

// function for getting the sensor value
int getDeg(void) {

  // get a new sensor event
  sensors_event_t event;
  mag.getEvent(&event);

  // define pi
  float Pi = 3.14159;

  // calculate the angle of the vector y,x
  float heading = int((atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi);

  // normalize to 0-360
  if (heading < 0) {
    heading = 360 + heading;
  }

  return heading;
}

void loop(void) { // main loop
  server.handleClient(); // serve pages
}
