#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include "sntp.h"

#include "secrets.h"

#include <BoardState.hpp>
#include <StateInterval.hpp>
#include <StateTest.hpp>

const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

const char *time_zone = "CET-1CEST,M3.5.0,M10.5.0/3"; // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

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
StateInterval stateInterval;
StateTest stateTest;

void setup()
{
  Serial.begin(115200);

  // set notification call-back function
  sntp_set_time_sync_notification_cb(timeavailable);
  sntp_servermode_dhcp(1);
  configTzTime(time_zone, ntpServer1, ntpServer2);

  // connect to WiFi
  connectToWiFi(wifi_ssid, wifi_password);

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
