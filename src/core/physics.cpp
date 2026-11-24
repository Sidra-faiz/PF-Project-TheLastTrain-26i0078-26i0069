#include "physics.h"
#include "util.h"

// Movement validation and resource adjustments without structures

void applyScoreDelta(int& score ,int deltascore ) {

    score+=deltascore;

}

void applyResourceDelta(int& energy, int& time, int deltaEnergy, int deltaTime) {
energy += deltaEnergy;
time += deltaTime;
energy = clampInt(energy, 0, MAX_ENERGY); // energy or time 0 se 100 k mid ma rhy ga
time = clampInt(time, 0, MAX_TIME);
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