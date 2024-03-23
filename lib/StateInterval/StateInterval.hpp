#ifndef H_STATE_INTERVAL
#define H_STATE_INTERVAL

#include <MD_Parola.h>

#include <BoardState.hpp>

class StateInterval : public BoardState
{
public:
    StateInterval(MD_Parola display, uint8_t zoneLeftID, uint8_t zoneMiddleID, uint8_t zoneRightID) : display(display), zoneLeftID(zoneLeftID), zoneMiddleID(zoneMiddleID), zoneRightID(zoneRightID){};
    void update();

private:
    MD_Parola display;
    uint8_t zoneLeftID;
    uint8_t zoneMiddleID;
    uint8_t zoneRightID;
};

#endif