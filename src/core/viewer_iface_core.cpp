#include "viewer_iface.h"
#include "util.h"
#include <iostream>
using namespace std;
// Terminal UI and dashboard rendering using primitive parameters
void renderDashboard(int playerFloor, int playerRoom, int energy, int time, int score,
                     const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                     int emergencyTripsLeft) {

    cout << "Location: Floor " << playerFloor << ", Room " << playerRoom << endl;
    cout << "Emergency trips left: " << emergencyTripsLeft << endl;
    cout << "Time     : " << time << " / " << MAX_TIME << endl;
    cout << "Energy   : " << energy << " / " << MAX_ENERGY << endl;
    cout << "Score    : " << score << endl;
    cout << "Inventory: ";
if (inventoryCount == 0) {
    cout << "(empty)";
}
for (int i = 0; i < inventoryCount; i++) {
    cout << inventory[i] << " ";
}
cout << endl;

}
//Game mein kai kaam (objectives) hain,
// jaise Master Key uthana, Passenger bachana, Cat secure karna.
void renderObjectivesChecklist(const bool objectives[NUM_OBJECTIVES]) {
for (int i = 0; i < NUM_OBJECTIVES; i++) {
 if (objectives[i]) {
 cout << "[X] ";
 } else {
cout << "[ ] ";
 }
 cout << "Objective " << (i + 1) << endl;
 }
}
//Player jis room mein khada hai, us room ke items screen par dikhana.
// Jaise player Floor 1, Room 2 mein hai aur wahan Master Key < rakhi hai
void renderRoomDetails(int floor, int room,
                const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                 int entityCount) {
 cout << "Room F" << floor << "-R" << room << " contains: ";
 if (entityCount == 0) {
    cout << "(nothing)";
}
for (int i = 0; i < entityCount; i++) {
    cout << roomEntities[floor - 1][room - 1][i] << " ";
}
cout << endl;
if (floor < 1 || floor > NUM_FLOORS || room < 1 || room > ROOMS_PER_FLOOR) {
    cout << "Invalid room" << endl;
    return;
}

}
void renderAsciiBuilding(int playerFloor, int playerRoom) {
 for (int f = NUM_FLOORS; f >= 1; f--) {
 cout << "Floor " << f << ": ";
for (int r = 1; r <= ROOMS_PER_FLOOR; r++) {
 if (f == playerFloor && r == playerRoom) {
  cout << "[P] ";
 } else {
  cout << "[ ] ";
 }
 }
 cout << endl;
}
}
