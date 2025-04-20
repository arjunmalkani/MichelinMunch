#include <iostream>
#include <chrono>
#include "../include/DatasetLoader.h"
#include "HashMapChaining.h"
#include "HashMapOpen.h"

using namespace std::chrono;

// helper to trim leading/trailing whitespace
string trim(const string& str) {
    const string WHITESPACE = " \t\n"; // handles all forms of white spacing, tabs, newlines. and spaces
    size_t first = str.find_first_not_of(WHITESPACE);
    size_t last = str.find_last_not_of(WHITESPACE);
    if (first == string::npos || last == string::npos)
        return "";
    return str.substr(first, last - first + 1);
}

// makes user input more universal
string normalizeStars(const string& input) {
    string s = trim(input);
    for (auto& c : s) c = tolower(c);
    if (s == "1 star") return "1 Star";
    if (s == "2 stars" || s == "2 star") return "2 Stars";
    if (s == "3 stars" || s == "3 star") return "3 Stars";
    return s;
}

// makes sure user inputs of the city are case-insensitive
string normalizeCity(const string& input) {
    return trim(input);
}



void updateMaps(vector<Restaurant> &restaurants,
    SeparateChaining<string,
    SeparateChaining<string,
    SeparateChaining<string, vector<Restaurant>>>> &scMap) { // last val is vector of restaurant objs to print multiple
    // outputs for the user

    SeparateChaining<string, SeparateChaining<string, string>> cityMapSc;


    for (Restaurant &restaurant : restaurants) {
        string city = restaurant.location;
        string name = restaurant.name;
        string stars = restaurant.starCount;
        string price = restaurant.price;


        if (!scMap.contains(city)) {
            scMap.insert(city, SeparateChaining<string, SeparateChaining<string, vector<Restaurant>>>());
        }
        auto& starMapSc = scMap.search(city);

        if (!starMapSc.contains(stars)) {
            starMapSc.insert(stars, SeparateChaining<string, vector<Restaurant>>());
        }
        auto& priceMapSc = starMapSc.search(stars);

        if (!priceMapSc.contains(price)) {
            priceMapSc.insert(price, vector<Restaurant>());
        }
        priceMapSc.search(price).push_back(restaurant);
    }
}


void sepChainingPrint(SeparateChaining<string,
    SeparateChaining<string,
    SeparateChaining<string, vector<Restaurant>>>> scMap, string city, string stars, string price) {
    if (scMap.contains(city)) {
        auto starMap = scMap.search(city);

        if (starMap.contains(stars)) {
            auto priceMap = starMap.search(stars);

            if (priceMap.contains(price)) {
                vector<Restaurant> matches = priceMap.search(price);
                cout << "Restaurants found in " << city << " with " << stars << " and " << price << " price:" << endl;
                for (const Restaurant& r : matches) {
                    cout << "- " << "Restaurant: " << r.name << " | Address: " << r.address << " | Cuisine: " << r.cuisine << endl;
                }
                cout << endl;
            }
            else {
                cout << "No restaurant found at price: " << price << endl;
            }
        } else {
            cout << "No restaurant found with " << stars << " in " << city << endl;
        }
    } else {
        cout << "No restaurants found in city: " << city << endl;
    }
}

int main() {
    cout << "Welcome to MichelinMunch!" << endl;
    cout << "You can search for restaurants by city, star rating, and price." << endl;
    cout << "Type 'exit' at any point to quit.\n" << endl;

    string filename = "../data/michelin_my_maps.csv";
    vector<Restaurant> restaurants = loadDataset(filename);

    SeparateChaining<string,
            SeparateChaining<string,
                    SeparateChaining<string, vector<Restaurant>>>> scMap;
    auto startScTimer = high_resolution_clock::now();
    updateMaps(restaurants, scMap);
    auto endScTimer = high_resolution_clock::now();
    auto durationSc = duration_cast<milliseconds>(endScTimer - startScTimer).count();

    while (true) {
        string rawCity, rawStars, rawPrice;

        cout << "Enter City **Case Sensitive** (format: City, Country): ";
        getline(cin, rawCity);
        if (rawCity == "exit") break;
        string city = normalizeCity(rawCity);

        cout << "Enter Star Rating (e.g., 1 star, 2 stars, 3 stars): ";
        getline(cin, rawStars);
        if (rawStars == "exit") break;
        string stars = normalizeStars(rawStars);

        cout << "Enter Price Level (e.g., $, $$, $$$, $$$$): ";
        getline(cin, rawPrice);
        if (rawPrice == "exit") break;
        string price = trim(rawPrice);

        cout << "\nSearching...\n" << endl;
        sepChainingPrint(scMap, city, stars, price);
        cout << "Separate Chaining insertion time: " << durationSc << " ms\n";
        cout << "\n--------------------------------------------------\n" << endl;
    }

    cout << "\nThank you for using MichelinMunch. Goodbye!" << endl;
    return 0;
}



//cout << "Total restaurants parsed: " << restaurants.size() << endl;

// prints first 400 restaurants info to verify parsing works
// for (int i = 0; i < 10; i++) {
//     const Restaurant& r = restaurants[i];
//     cout << "Name: " << r.name << endl;
//     cout << "Address: " << r.address << endl;
//     cout << "City: " << r.location  << endl;
//     cout << "Price: " << r.price << endl;
//     cout << "Cuisine: " << r.cuisine << endl;
//     cout << "Stars: " << r.starCount << endl;
//     cout << "------------------------" << endl;
// }