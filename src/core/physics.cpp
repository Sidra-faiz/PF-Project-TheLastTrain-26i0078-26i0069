#include "physics.h"
#include "util.h"

// Movement validation and resource adjustments without structures

void applyScoreDelta(int& score ,int deltaScore ) {

    score+=deltaScore;

}

void applyResourceDelta(int& energy, int& time, int deltaEnergy, int deltaTime) {
energy += deltaEnergy;
time += deltaTime;
energy = clampInt(energy, 0, MAX_ENERGY); //  energy 0 se 100 k mid ma rhy ga
time = clampInt(time, 0, MAX_TIME);       // // time 0 se 50 ke beech rahega
}

// hasitem wo fix key item dhoondta ha 
//Masalan kisi band darwaze ko kholne ya lift chalane se 
//pehle game check karti hai ke kya player ke paas zaroori item
// hai ya nahi.
bool hasItem(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, char itemSymbol) {
    for (int i = 0; i < inventoryCount; ++i) {
        if (inventory[i] == itemSymbol) {
            return true;
        }
    }
    return false;
}
//addItem ka kaam player ki inventory mein naya item rakhna hai
// lekin pehle yeh check karta hai ke inventory mein khaali
// jagah bachi hai ya nahi.
bool addItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol) {
    if (inventoryCount >= MAX_INVENTORY_CAPACITY) {
        return false;
    }
    inventory[inventoryCount] = itemSymbol;
    inventoryCount++;
    return true;
}
//new item ka matlb wo chizein jo player rasty ma uthay ga

//Jab player koi item istemal kar le (jaise Fuse lagana) 
//ya drop kar de, to usay player ki inventory se hatana zaroori 
//hota hai. Agar darmiyan se koi item nikle, to us ke peeche
// wale items ko ek ek step aage khiskana parta hai taake array
// mein koi khaali gap na bache.
bool removeItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol) {
    for (int i = 0; i < inventoryCount; ++i) {
        if (inventory[i] == itemSymbol) {
            for (int j = i; j < inventoryCount - 1; ++j) {
                inventory[j] = inventory[j + 1];
            }
            inventoryCount--;
            return true;
        }
    }
    return false;
}
// Iska kaam check karna hai ke player ka current room aur target room directly connected hain ya nahi.
bool isDirectlyConnected(int fromF, int fromR, int toF, int toR,
                         const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
                         char& outConnType) {
     outConnType = CONN_NONE;   // pehle "koi connection nahi" maan lo
    // Check floor range (1 to 5)
    if (fromF < 1 || fromF > NUM_FLOORS ||
        toF < 1 || toF > NUM_FLOORS) {
        return false;
    }

    // Check room range (1 to 4)
    if (fromR < 1 || fromR > ROOMS_PER_FLOOR ||
        toR < 1 || toR > ROOMS_PER_FLOOR) {
        return false;
    }

    // Both rooms must be on the same floor
    if (fromF != toF) {
        return false;
    }

    // Rooms zaroor sath sath hona chaiya
    if (fromR == toR + 1) {
        outConnType = horizontalConn[fromF - 1][toR - 1];
    }
    else if (toR == fromR + 1) {
        outConnType = horizontalConn[fromF - 1][fromR - 1];
    }
    else {
        return false;
    }

    // Check whether a connection ha b ya nh
    if (outConnType == CONN_NONE) {
        return false;
    }

    return true;
}
bool canTraverse(int targetFloor, int targetRoom, char connType,
                 const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                 int emergencyTripsLeft, bool lift2Operational) {
            (void)emergencyTripsLeft;
    (void)lift2Operational;

    // Check karo ke floor 1 se 5 ke darmiyan hai
    if (targetFloor < 1 || targetFloor > NUM_FLOORS) {
        return false;
    }

    // Check karo ke room 1 se 4 ke darmiyan hai
    if (targetRoom < 1 || targetRoom > ROOMS_PER_FLOOR) {
        return false;
    }

    // Agar connection mojood nahi hai to move nahi kar sakte
    if (connType == CONN_NONE) {
        return false;
    }

    // Solid wall ko cross nahi kar sakte
    if (connType == CONN_SOLID_WALL) {
        return false;
    }

    // Ordinary door ko asani se cross kar sakte hain
    if (connType == CONN_DOOR) {
        return true;
    }

    // Locked door kholne ke liye Master Key check karo
    if (connType == CONN_LOCKED_DOOR) {
        return hasItem(inventory, inventoryCount, ENT_MASTER_KEY);
    }

    
        // Window ordinary traversal hai, emergency trip ki zaroorat nahi
    if (connType == CONN_WINDOW) {
        return true;
    }

    // Agar connection ka type samajh nahi aaya to move allow nahi hoga
    return false;
}
    