#include "util.h"

// Primitive helper utilities, clamping, and screen control
#include <iostream>
#include <cstring>
using namespace std;

int clampInt(int val, int minVal, int maxVal) {
    if (val < minVal) {
        return minVal;
    }
    if (val > maxVal) {
        return maxVal;
    }
    return val;
}

// spaces jo extra hon un ko remove krna k lie 
void trimWhitespace(char* str) {
    if (str == nullptr || str[0] == '\0') {
        return;
    }

    int start = 0;
    while (str[start] == ' ' || str[start] == '\t' || str[start] == '\r' || str[start] == '\n') {
        start++;
    }

    if (str[start] == '\0') {
        str[0] = '\0';
        return;
    }

    int end = static_cast<int>(strlen(str)) - 1;
    while (end > start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\r' || str[end] == '\n')) {
        end--;
    }

    int len = end - start + 1;
    if (start > 0) {
        for (int i = 0; i < len; ++i) {
            str[i] = str[start + i];
        }
    }
    str[len] = '\0';
}

// 2 string values ko chk krty k equal hain ya nh agra hain toh true ni toh false
// agr user move kra toh match hoga move command se then true
bool stringEquals(const char* a, const char* b) {
    if (a == nullptr || b == nullptr) {
        return a == b;
    }

    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return false;
        }
        i++;
    }

    return a[i] == b[i];
}
//koi b heading print k lie wo 2 lines k drmyan hogi print
void printHeader(const char* title) {
    const char* safeTitle = (title != nullptr) ? title : "";
    cout << "========================================\n";
    cout << safeTitle << "\n";
    cout << "========================================\n";
}
//40 khaali lines print ho chuki hoti hain, jis se purana text upar scroll ho kar screen saaf nazar aati hai.
void clearScreen() {
    for (int i = 0; i < 40; ++i) {
    cout << '\n';
    }
}