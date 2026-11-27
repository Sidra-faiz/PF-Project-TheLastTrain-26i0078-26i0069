#include "simulator.h"
#include "physics.h"
#include "switches.h"
#include "logger.h"
#include "viewer_iface.h"
#include "util.h"
#include<iostream>
using namespace std;

// Modular simulation loop using primitive variables
bool checkEndConditions(int energy, int time, const bool objectives[NUM_OBJECTIVES]) {

    if (energy <= 0 || time <= 0)
    {
        return true;
    }
    if (objectives[OBJ_MISSION_WON])//Check karta hai ke mission complete hua ya nahi.
    {
        return true;
    }
    return false;
}
bool handleInspectCommand(int currentFloor, int currentRoom,
int& energy, int& time,
const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
int entityCount,
bool objectives[NUM_OBJECTIVES], int& score)
{
applyResourceDelta(energy, time, COST_INSPECT_ENERGY, COST_INSPECT_TIME);

renderRoomDetails(currentFloor, currentRoom, roomEntities, entityCount);

for (int i = 0; i < entityCount; i++)
{
char item = roomEntities[currentFloor - 1][currentRoom - 1][i];

if (item == ENT_CLUE_4 && objectives[OBJ_CLUE_4] == false)
{
objectives[OBJ_CLUE_4] = true;
applyScoreDelta(score, SCORE_CLUE_FOUND);
}

if (item == ENT_CLUE_2 && objectives[OBJ_CLUE_2] == false)
{
objectives[OBJ_CLUE_2] = true;
applyScoreDelta(score, SCORE_CLUE_FOUND);
}

if (item == ENT_CLUE_7 && objectives[OBJ_CLUE_7] == false)
{
objectives[OBJ_CLUE_7] = true;
applyScoreDelta(score, SCORE_CLUE_FOUND);
}
}

return true;
}
bool handleUnlockCabinetCommand(const char* code, int currentFloor, int currentRoom,
bool objectives[NUM_OBJECTIVES], int& score,
char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
int& entityCount)
{
if (currentFloor != 5 || currentRoom != 1)
{
return false;
}

if (!stringEquals(code, "427"))
{
return false;
}

if (objectives[OBJ_CLUE_4] == false ||
objectives[OBJ_CLUE_2] == false ||
objectives[OBJ_CLUE_7] == false)
{
return false;
}

objectives[OBJ_CABINET_UNLOCKED] = true;
applyScoreDelta(score, SCORE_CABINET_UNLOCK);

objectives[OBJ_TRAIN_KEY] = true;
applyScoreDelta(score, SCORE_TRAIN_KEY);

return true;
}

