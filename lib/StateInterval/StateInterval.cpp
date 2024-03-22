#include <Arduino.h>
#include "time.h"

#include <StateInterval.hpp>

void StateInterval::update()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("No time available (yet)");
        return;
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}