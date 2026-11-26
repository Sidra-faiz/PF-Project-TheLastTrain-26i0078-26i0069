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
// door will only open jb player k pas master key hgi "<" ya phr ENT_MASTER_KEY
bool unlockFloor3Door(const char inventory[], int inventoryCount)
{
    for (int i = 0; i < inventoryCount; i++)
    {
        if (inventory[i] == ENT_MASTER_KEY)
        {
            return true;
        }
    }

    return false;
}


// control panel mein fuse ko install krna hy inventory sy remove kr k

bool installFuseControlPanel(char inventory[],
                             int& inventoryCount,
                             bool objectives[NUM_OBJECTIVES],
                             int& score)
{
   // checks if fuse is already installed
    if (objectives[OBJ_FUSE_INSTALLED])
    {
        return false;
    }

   // checking for fuse in inventory
    int fuseIndex = -1;

    for (int i = 0; i < inventoryCount; i++)
    {
        if (inventory[i] == ENT_FUSE)
        {
            fuseIndex = i;
            break;
        }
    }

   // -1 is representing false
    if (fuseIndex == -1)
    {
        return false;
    }

    // Removing Fuse from inventory
    for (int i = fuseIndex; i < inventoryCount - 1; i++)
    {
        inventory[i] = inventory[i + 1];
    }

    inventoryCount--;

    // installed fuse 
    objectives[OBJ_FUSE_INSTALLED] = true;

    // Activate Lift 2 agr Lift Pass is also available
    if (objectives[OBJ_LIFT_PASS])
    {
        objectives[OBJ_LIFT2_ACTIVE] = true;
    }

    // Award points
    score += SCORE_INSTALL_FUSE;

    return true;
}


//  Verifying Security Cabinet Code

bool verifyCabinetCode(const char* enteredCode,
                       const bool objectives[NUM_OBJECTIVES])
{
    // validation
    if (enteredCode == nullptr)
    {
        return false;
    }

    // agr yay numbers nai hein to return false
    if (!objectives[OBJ_CLUE_4] ||
        !objectives[OBJ_CLUE_2] ||
        !objectives[OBJ_CLUE_7])
    {
        return false;
    }

    // Checking the correct cabinet code: 427
    if (enteredCode[0] == '4' &&
        enteredCode[1] == '2' &&
        enteredCode[2] == '7' &&
        enteredCode[3] == '\0')
    {
        return true;
    }

    return false;
}