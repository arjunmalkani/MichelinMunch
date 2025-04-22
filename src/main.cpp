#include <iostream>
#include <chrono>
#include "../include/DatasetLoader.h"
#include "HashMapChaining.h"
#include "HashMapOpen.h"

using namespace std::chrono;

// helper to trim leading/trailing whitespace in user inputs
string trim(const string& str) {
    const string WHITESPACE = " \t\n"; // handles all forms of white spacing, tabs, newlines, and spaces
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
    if (s == "1 star" || s == "1") return "1 Star";
    if (s == "2 stars" || s == "2 star" || s == "2") return "2 Stars";
    if (s == "3 stars" || s == "3 star" || s == "3") return "3 Stars";
    return s;
}

// makes sure user inputs of city are accepted regardless of spacing format
string normalizeCity(const string& input) {
    return trim(input);
}


void updateMaps(vector<Restaurant> &restaurants,
                SeparateChaining<string,
                    SeparateChaining<string,
                        SeparateChaining<string, vector<Restaurant> > > > &scMap) {
    // last val is vector of restaurant objs to print multiple
    // outputs for the user

    SeparateChaining<string, SeparateChaining<string, string> > cityMapSc;


    for (Restaurant &restaurant: restaurants) {
        string city = restaurant.location;
        string name = restaurant.name;
        string stars = restaurant.starCount;
        string price = restaurant.price;


        if (!scMap.contains(city)) {
            scMap.insert(city, SeparateChaining<string, SeparateChaining<string, vector<Restaurant> > >());
        }
        auto &starMapSc = scMap.search(city);

        if (!starMapSc.contains(stars)) {
            starMapSc.insert(stars, SeparateChaining<string, vector<Restaurant> >());
        }
        auto &priceMapSc = starMapSc.search(stars);

        if (!priceMapSc.contains(price)) {
            priceMapSc.insert(price, vector<Restaurant>());
        }
        priceMapSc.search(price).push_back(restaurant);
    }
}


void sepChainingPrint(SeparateChaining<string,
        SeparateChaining<string,
                SeparateChaining<string, vector<Restaurant>>>>& scMap,
                      const string& city, const string& stars, const string& price) {

    if (!scMap.contains(city)) {
        cout << "No restaurants found in city: " << city << endl;
        return;
    }

    auto& starMap = scMap.search(city);
    if (!starMap.contains(stars)) {
        cout << "No restaurants with " << stars << " in " << city << endl;
        return;
    }

    auto& priceMap = starMap.search(stars);
    if (!priceMap.contains(price)) {
        cout << "No restaurants found at price : " << price << endl;
        return;
    }

    auto& matches = priceMap.search(price);

    cout << "Found " << matches.size()
         << " restaurants in " << city
         << " with " << stars
         << " stars and price " << price << ":\n\n";

    for (const auto& r : matches) {
        cout << "Name:    " << r.name << "\n"
             << "Address: " << r.address << "\n"
             << "Cuisine: " << r.cuisine << "\n";
        if (!r.website.empty()) cout << "Website: " << r.website << "\n";
        if (!r.phone.empty()) cout << "Phone:   " << r.phone << "\n";
        cout << "---------------------------\n";
    }
}


void printRestaurantsOA(
    OpenAddressHashMap<string,
    OpenAddressHashMap<string,
    OpenAddressHashMap<string, vector<Restaurant>>>> &allRestaurants, const string &city,
                                                                      const string &stars, const string &price) {
    if (!allRestaurants.contains(city)) {
        cout << "No restaurants found in city: " << city << endl;
        return;
    }

    auto &starsMap = allRestaurants[city];
    if (!starsMap.contains(stars)) {
        cout << "No restaurants with " << stars << " in " << city << endl;
        return;
    }
    auto &priceMap = starsMap[stars];
    if (!priceMap.contains(price)) {
        cout << "No restaurants found at price : " << price << endl;
        return;
    }
    auto &matches = priceMap[price];

    cout << "Found " << matches.size()
            << " restaurants in " << city
            << " with " << stars
            << " stars and price " << price << ":\n";

    for (auto &r: matches) {
        cout << "Name:    " << r.name << "\n"
                << "Address: " << r.address << "\n"
                << "Cuisine: " << r.cuisine << "\n";
        if (!r.website.empty()) cout << "Website: " << r.website << "\n";
        if (!r.phone.empty()) cout << "Phone:   " << r.phone << "\n";
        cout << "---------------------------\n";
    }
}

void mapInsertionsOA(vector<Restaurant> &restaurants, OpenAddressHashMap<string,
                         OpenAddressHashMap<string,
                             OpenAddressHashMap<string,
                                 vector<Restaurant>>>> &allRestaurants) {

    // iterates across all parsed restaurants
    for (auto &r: restaurants) {
        // uses [] to access map and assignkey value pairs
        auto &starsMap = allRestaurants[r.location];
        auto &priceMap = starsMap[r.starCount];
        auto &matches = priceMap[r.price];
        matches.push_back(r);
    }
}


int main() {
    cout << "Welcome to MichelinMunch!\n"
         << "You can search for restaurants by city, star rating, and price.\n"
         << "Type 'exit' at any point to quit.\n\n";

    // Load dataset and create maps only once
    string filename = "../data/michelin_my_maps.csv";
    vector<Restaurant> restaurants = loadDataset(filename);

    // Open Addressing setup
    auto startOAInsert = high_resolution_clock::now();
    OpenAddressHashMap<string,
            OpenAddressHashMap<string,
                    OpenAddressHashMap<string, vector<Restaurant>>>> Michelin;
    mapInsertionsOA(restaurants, Michelin);
    auto endOAInsert = high_resolution_clock::now();

    // Separate Chaining setup
    auto startSCInsert = high_resolution_clock::now();
    SeparateChaining<string,
            SeparateChaining<string,
                    SeparateChaining<string, vector<Restaurant>>>> scMap;
    updateMaps(restaurants, scMap);
    auto endSCInsert = high_resolution_clock::now();

    long long durationOAInsert = duration_cast<milliseconds>(endOAInsert - startOAInsert).count();
    long long durationSCInsert = duration_cast<milliseconds>(endSCInsert - startSCInsert).count();

    while (true) {
        string rawCity, rawStars, rawPrice;

        cout << "Enter City, Country (e.g., Miami, USA): " << endl;
        getline(cin, rawCity);
        if (rawCity == "exit") break;
        string city = normalizeCity(rawCity);

        cout << "Enter Star Rating (e.g., 1 star, 2 stars, 3 stars), 'Selected Restaurants', or 'Bib Gourmand': " << endl;
        getline(cin, rawStars);
        if (rawStars == "exit") break;
        string stars = normalizeStars(rawStars);

        // ugly implementation but was meant to not mess with normalizeStars()
        if(stars == "bib gourmand"){
            stars = "Bib Gourmand";
        }
        else if (stars == "selected restaurants") {
            stars = "Selected Restaurants";
        }
        else if (stars != "1 Star" && stars != "2 Stars" && stars != "3 Stars" && stars != "1" && stars != "2" && stars != "3") {
            cout << "Invalid star rating." << endl << endl;
            continue;
        }


        cout << "Enter Price Level (e.g., $, $$, $$$, $$$$): \n";
        getline(cin, rawPrice);
        if (rawPrice == "exit") break;
        string price = trim(rawPrice);

        cout << "\nSearching...\n\n";

        // Open Addressing
        auto startOAQuery = high_resolution_clock::now();
        cout << "OPEN ADDRESSING RESULT:\n\n";
        printRestaurantsOA(Michelin, city, stars, price);
        auto endOAQuery = high_resolution_clock::now();
        auto durationOAQuery = duration_cast<milliseconds>(endOAQuery - startOAQuery).count();

        cout << "Open Addressing - Insertion Time: " << durationOAInsert << " ms\n";
        cout << "Open Addressing - Access Time:     " << durationOAQuery << " ms\n";

        // Separate Chaining
        auto startSCQuery = high_resolution_clock::now();
        cout << "\nSEPARATE CHAINING RESULT:\n\n";
        sepChainingPrint(scMap, city, stars, price);
        auto endSCQuery = high_resolution_clock::now();
        auto durationSCQuery = duration_cast<milliseconds>(endSCQuery - startSCQuery).count();

        cout << "Separate Chaining - Insertion Time: " << durationSCInsert << " ms\n";
        cout << "Separate Chaining - Access Time:     " << durationSCQuery << " ms\n";
        cout << "--------------------------------------------------\n";
    }

    cout << "\nThank you for using MichelinMunch. Goodbye!" << endl;
    return 0;
}

