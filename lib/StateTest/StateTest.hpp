#ifndef H_STATE_TEST
#define H_STATE_TEST

#include <Arduino.h>

#include <BoardState.hpp>

class StateTest : public BoardState
{
public:
    void update()
    {
        Serial.println("test state");
    }
};

#endif