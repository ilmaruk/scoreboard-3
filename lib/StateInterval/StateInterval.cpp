#include <Arduino.h>
#include "time.h"

#include <MD_Parola.h>

#include <StateInterval.hpp>

void StateInterval::update()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("No time available (yet)");
        return;
    }
    char buffer[9];
    sprintf(buffer, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    // Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    Serial.println(buffer);

    if (display.displayAnimate())
    {
        display.displayZoneText(zoneMiddleID, buffer, PA_CENTER, 25, 500, PA_SCAN_HORIZX, PA_NO_EFFECT);
        // display.displayZoneText(zoneMiddleID, buffer, PA_CENTER, 25, 500, PA_NO_EFFECT);
    }
}