#include "switches.h"
#include "util.h"

// Door lock mechanics, lifts, and cabinet verification without structures
bool canUseLift1(int fromFloor, int toFloor) {
    // Lift 1 only goes between Floor 1 and Floor 2(koi pass ya key nai chaey)
    if ((fromFloor == 1 && toFloor == 2) || (fromFloor == 2 && toFloor == 1)) {
        return true;
    }
    return false;
}
