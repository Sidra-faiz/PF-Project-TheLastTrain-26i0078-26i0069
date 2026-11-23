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
bool canUseLift2(int fromFloor, int toFloor, bool lift2Operational, int emergencyTripsLeft) {
    // Lift 2 only connects Floors 2, 4, and 5 (aur same floor pr travel nai kr skti)
    bool validFrom = (fromFloor == 2 || fromFloor == 4 || fromFloor == 5);
    bool validTo = (toFloor == 2 || toFloor == 4 || toFloor == 5);

    if (!validFrom || !validTo || fromFloor == toFloor) {
        return false;
    }

    // Allowed if Lift 2 is operational (Fuse aur Lift Pass dono ka hona ) or remaining emergency trips
    if (lift2Operational || emergencyTripsLeft > 0) {
        return true;
    }

    return false;
}
