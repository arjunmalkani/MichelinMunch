#include <iostream>
#include "../include/DatasetLoader.h"
#include "HashMapChaining.h"
#include "HashMapOpen.h"

using PriceMap = OpenAddressHashMap<string, vector<Restaurant>>;
using StarsMap = OpenAddressHashMap<string, PriceMap>;
using CityMap = OpenAddressHashMap<string, StarsMap>;

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
                    cout << "- " << r.name << " | " << r.address << " | Cuisine: " << r.cuisine << endl;
                }
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

void printRestaurantsOA(CityMap& allRestaurants, const string& city, const string& stars, const string& price)
{
    if (!allRestaurants.contains(city)) {
        cout << "No restaurants in that city.\n";
        return;
    }
    StarsMap& starsMap = allRestaurants[city];

    if (!starsMap.contains(stars)) {
        cout << "No restaurants with that star rating.\n";
        return;
    }
    PriceMap& priceMap = starsMap[stars];

    if (!priceMap.contains(price)) {
        cout << "No restaurants at that price.\n";
        return;
    }
    vector<Restaurant>& matches = priceMap[price];

    // 4) Print results
    cout << "Found " << matches.size()
         << " restaurants in " << city
         << " with " << stars
         << " stars and price " << price << ":\n\n";

    for (const auto& r : matches) {
        cout << "Name:    " << r.name    << "\n"
             << "Address: " << r.address << "\n"
             << "Cuisine: " << r.cuisine << "\n";
        if (!r.website.empty()) cout << "Website: " << r.website << "\n";
        if (!r.phone.empty())   cout << "Phone:   " << r.phone   << "\n";
        cout << "---------------------------\n";
    }
}


void mapInsertionsOA(vector<Restaurant>& restaurants,
                     CityMap& allRestaurants) {
    for (auto& r : restaurants) {
        StarsMap& starsMap = allRestaurants[r.location];
        PriceMap& priceMap = starsMap[r.starCount];
        auto& matches = priceMap[r.price];

        matches.push_back(r);
    }
}

int main() {
    //testing maps
    string city = "Miami, USA";
    string stars = "1 Star";
    string price = "$$$$";

    // testing data parsing
    string filename = "../data/michelin_my_maps.csv";
    vector<Restaurant> restaurants = loadDataset(filename);
    cout << "Loaded " << restaurants.size() << " restaurants\n";

    CityMap Michelin;
    cout << "Starting insertion…\n";

    // 2) Track progress in the big loop
    for (size_t i = 0; i < restaurants.size(); ++i) {
        // your existing per‑restaurant logic:
        StarsMap&   starsMap = Michelin[restaurants[i].location];
        PriceMap&   priceMap = starsMap[restaurants[i].starCount];
        auto&       vec      = priceMap[restaurants[i].price];
        vec.push_back(restaurants[i]);

        // every 1 000 entries, spit out a line
        if (i % 1000 == 0) {
            cout << "  inserted " << i << "/" << restaurants.size() << "\n";
        }
    }

    cout << "Done inserting. Now printing…\n";
    printRestaurantsOA(Michelin, city, stars, price);
    return 0;
}
