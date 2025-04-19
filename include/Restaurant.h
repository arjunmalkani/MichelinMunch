#pragma once
#include <string>

using namespace std;

// Restaurant objects that will be stored in our hashmaps
struct Restaurant {
    string name;
    string address;
    string location;
    string price;
    string cuisine;
    string starCount;
};