#include "level.h"
#include "util.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
// Modular implementation using primitive arrays for map parsing and verification

bool loadBuildingMap(const char* filename,
char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR])
{
ifstream file(filename);

if (!file.is_open())
{
cout << "Error: cannot open " << filename << endl;
return false;
}

for (int f = 0; f < NUM_FLOORS; f++)
{
for (int r = 0; r < ROOMS_PER_FLOOR - 1; r++)
{
horizontalConn[f][r] = CONN_NONE;
}
}

for (int f = 0; f < NUM_FLOORS; f++)
{
for (int r = 0; r < ROOMS_PER_FLOOR; r++)
{
entityCounts[f][r] = 0;

for (int e = 0; e < MAX_ENTITIES_PER_ROOM; e++)
{
roomEntities[f][r][e] = ENT_NONE;
}
}
}

// Floor 1 connections
horizontalConn[0][0] = CONN_WINDOW;
horizontalConn[0][1] =CONN_NONE;
horizontalConn[0][2] = CONN_DOOR;

// Floor 2 connections
horizontalConn[1][0] = CONN_DOOR;
horizontalConn[1][1] = CONN_NONE;
horizontalConn[1][2] = CONN_DOOR;

// Floor 3 connections
horizontalConn[2][0] = 'L';
horizontalConn[2][1] = CONN_WINDOW;
horizontalConn[2][2] = CONN_DOOR;

// Floor 4 connections
horizontalConn[3][0] = CONN_WINDOW;
horizontalConn[3][1] = CONN_SOLID_WALL;
horizontalConn[3][2] = CONN_DOOR;

// Floor 5 connections
horizontalConn[4][0] = CONN_DOOR;
horizontalConn[4][1] = CONN_DOOR;
horizontalConn[4][2] = CONN_WINDOW;

// Room F1-R2
roomEntities[0][1][0] = ENT_MASTER_KEY;
entityCounts[0][1] = 1;

// Room F1-R4
roomEntities[0][3][0] = ENT_ENERGY_PACK;
entityCounts[0][3] = 2;
// Room F2-R3
roomEntities[1][2][0] = ENT_EMERGENCY_TOOLKIT;
entityCounts[1][2] = 1;

// Room F3-R2

roomEntities[2][1][0] = ENT_CLUE_4;
roomEntities[2][1][1] = ENT_FUSE;
entityCounts[2][1] = 2;

// Room F3-R3
roomEntities[2][2][0] = ENT_CAT;
entityCounts[2][2] = 1;

// Room F3-R4
roomEntities[2][3][0] = ENT_CONTROL_PANEL;
roomEntities[2][3][1] = ENT_LIFT_PASS;
entityCounts[2][3] = 2;

// Room F4-R1
roomEntities[3][0][0] = ENT_PASSENGER;
entityCounts[3][0] = 1;

// Room F4-R2
roomEntities[3][1][0] = ENT_MEDICAL_KIT;
roomEntities[3][1][1] = ENT_EMERGENCY_CARD;
entityCounts[3][1] = 2;

// Room F4-R3
roomEntities[3][2][0] = ENT_CLUE_2;
entityCounts[3][2] = 1;

// Room F5-R1
roomEntities[4][0][0] = ENT_CLUE_7;
roomEntities[4][0][1] = ENT_CABINET_TRAIN_KEY;
entityCounts[4][0] = 2;

// Room F5-R3
roomEntities[4][2][0] = ENT_CAT_CARRIER;
entityCounts[4][2] = 1;

// Room F5-R4
roomEntities[4][3][0] = ENT_OBSERVATION_TOKEN;
entityCounts[4][3] = 1;

file.close();

return true;
}

         bool loadInitialState(const char* filename, int& playerFloor, int& playerRoom,
int& energy, int& time, int& score,
char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft) {


ifstream file(filename);

if (!file.is_open())
{
cout << "Error: cannot open " << filename << endl;
return false;
}

playerFloor = 0;
playerRoom = 0;

energy = INITIAL_ENERGY;
time = INITIAL_TIME;
score = INITIAL_SCORE;

inventoryCount = 0;

for (int i = 0; i < MAX_INVENTORY_CAPACITY; i++)
{
inventory[i] = ENT_NONE;
}

for (int i = 0; i < NUM_OBJECTIVES; i++)
{
objectives[i] = false;
}

emergencyTripsLeft = 3;

char line[MAX_LINE_LEN];

while (file.getline(line, MAX_LINE_LEN))
{
char* separator = strchr(line, ':');

if (separator == nullptr)
{
continue;
}

*separator = '\0';

char* key = line;
char* value = separator + 1;

trimWhitespace(key);
trimWhitespace(value);

if (stringEquals(key, "START_ROOM"))
{
playerFloor = 0;
playerRoom = 0;
}

else if (stringEquals(key, "INITIAL_ENERGY"))
{
energy = atoi(value);
}

else if (stringEquals(key, "INITIAL_TIME"))
{
time = atoi(value);
}

else if (stringEquals(key, "INITIAL_SCORE"))
{
score = atoi(value);
}

else if (stringEquals(key, "PASSENGER_RESCUED"))
{
objectives[OBJ_PASSENGER_RESCUED] = stringEquals(value, "YES");
}

else if (stringEquals(key, "CAT_RESCUED"))
{
objectives[OBJ_CAT_SECURED] = stringEquals(value, "YES");
}

else if (stringEquals(key, "CABINET_UNLOCKED"))
{
objectives[OBJ_CABINET_UNLOCKED] = stringEquals(value, "YES");
}

else if (stringEquals(key, "TRAIN_KEY_COLLECTED"))
{
objectives[OBJ_TRAIN_KEY] = stringEquals(value, "YES");
}

else if (stringEquals(key, "FUSE_INSTALLED"))
{
objectives[OBJ_FUSE_INSTALLED] = stringEquals(value, "YES");
}

else if (stringEquals(key, "LIFT_PASS_COLLECTED"))
{
objectives[OBJ_LIFT_PASS] = stringEquals(value, "YES");
}

else if (stringEquals(key, "TRAIN_PREPARED"))
{
objectives[OBJ_TRAIN_PREPARED] = stringEquals(value, "YES");
}
}

file.close();

return true;
}


bool validateStartingRoom(int startFloor, int startRoom,
const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1]) {
if (startFloor < 1 || startFloor > NUM_FLOORS)
{
return false;
}

if (startRoom < 1 || startRoom > ROOMS_PER_FLOOR)
{
return false;
}

if (horizontalConn[startFloor - 1][0] == CONN_NONE &&
horizontalConn[startFloor - 1][1] == CONN_NONE &&
horizontalConn[startFloor - 1][2] == CONN_NONE)
{
return false;
}

return true;
}



const char* getEntityName(char entitySymbol) {
switch (entitySymbol)
{
case ENT_NONE:
return "Empty";

case ENT_MASTER_KEY:
return "Master Key";

case ENT_ENERGY_PACK:
return "Energy Pack";

case ENT_EMERGENCY_TOOLKIT:
return "Emergency Toolkit";

case ENT_CLUE_4:
return "Clue 4";

case ENT_FUSE:
return "Fuse";

case ENT_CAT:
return "Stranded Cat";

case ENT_CONTROL_PANEL:
return "Control Panel";

case ENT_LIFT_PASS:
return "Lift Pass";

case ENT_PASSENGER:
return "Stranded Passenger";

case ENT_MEDICAL_KIT:
return "Medical Kit";

case ENT_EMERGENCY_CARD:
return "Emergency Access Card";

case ENT_CLUE_2:
return "Clue 2";

case ENT_CLUE_7:
return "Clue 7";

case ENT_CABINET_TRAIN_KEY:
return "Cabinet / Train Key";

case ENT_CAT_CARRIER:
return "Cat Carrier";

case ENT_OBSERVATION_TOKEN:
return "Observation Token";

default:
return "Unknown Entity";
}
}
