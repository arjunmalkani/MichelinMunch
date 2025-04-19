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

    // users would want this info too so i added it and was part of initial project scope
    // - ant :3
    string website;
    string phone;
};