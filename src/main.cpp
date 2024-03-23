#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include "sntp.h"
#include <MD_Parola.h>
#include <MD_MAX72xx.h>

#include "secrets.h"

#include <BoardState.hpp>
#include <StateInterval.hpp>
#include <StateTest.hpp>

// NTP settings
const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;
const char *time_zone = "CET-1CEST,M3.5.0,M10.5.0/3"; // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

// Max7219 settings
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 12
#define CLK_PIN 18
#define DATA_PIN 23
#define CS_PIN 5

#define ZONE_LEFT 2
#define ZONE_MIDDLE 1
#define ZONE_RIGHT 0

MD_Parola display(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Callback function (get's called when time adjusts via NTP)
void timeavailable(struct timeval *t)
{
  Serial.println("Got time adjustment from NTP!");
}

void connectToWiFi(const char *ssid, const char *pass)
{
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");
}

BoardState *currState;
// StateInterval stateInterval(display, ZONE_LEFT, ZONE_MIDDLE, ZONE_RIGHT);
StateInterval stateInterval(display, ZONE_RIGHT, ZONE_RIGHT, ZONE_RIGHT);
StateTest stateTest;

void setup()
{
  Serial.begin(115200);

  // set NTP notification call-back function
  sntp_set_time_sync_notification_cb(timeavailable);
  sntp_servermode_dhcp(1);
  configTzTime(time_zone, ntpServer1, ntpServer2);

  // connect to WiFi
  connectToWiFi(wifi_ssid, wifi_password);

  // setop display zones
  display.setZone(ZONE_LEFT, 8, 11);
  display.setZone(ZONE_MIDDLE, 4, 7);
  display.setZone(ZONE_RIGHT, 0, 3);

  currState = &stateInterval;
}

int counter = 0;

void loop()
{
  delay(500);
  currState->update();

  counter++;

  if (counter == 20)
  {
    currState = &stateTest;
  }
  else if (counter == 40)
  {
    currState = &stateInterval;
  }
}
