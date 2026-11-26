#include "level.h"
#include "util.h"
#include <fstream>
#include <iostream>
using namespace std;
// Modular implementation using primitive arrays for map parsing and verification
bool loadBuildingMap(const char* filename,
                     char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
                     char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                     int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]) {
    ifstream file(filename);
if (!file.is_open()) {
    cout << "Error: cannot open " << filename << endl;
    return false;
}
 char line[200];
while (file.getline(line, 200)) { //200 characters ka khali dibba banaya
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == 'F' && line[i+1] >= '1' && line[i+1] <= '5'
            && line[i+2] == '-' && line[i+3] == 'R') {
            cout << "Floor " << (line[i+1] - '0')
                 << " Room " << (line[i+4] - '0') << endl;
        }
    }
}
file.close();
return true;
                     }
         bool loadInitialState(const char* filename, int& playerFloor, int& playerRoom,
int& energy, int& time, int& score,
char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft) {
return false;
}

bool validateStartingRoom(int startFloor, int startRoom,
const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1]) {
return false;
}

const char* getEntityName(char entitySymbol) {
return "";
}        
