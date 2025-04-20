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

void printRestaurantsOA(CityMap& allRestaurants, const string& city, const string& stars, const string& price) {
    if (allRestaurants.contains(city)) {
        StarsMap starsMap = allRestaurants.search(city);
        if (starsMap.contains(stars)) {
            PriceMap priceMap = starsMap.search(stars);
            if (priceMap.contains(price)) {
                vector<Restaurant> matches;

                try {
                    matches = priceMap.search(price);
                } catch (const runtime_error& e) {
                    cout << "Price not found: " << e.what() << endl;
                    return;
                }

                cout << "Found " << matches.size() << " restaurants in " << city
                     << " with " << stars << " stars and price " << price << ":\n\n";

                for (const auto& r : matches) {
                    cout << "Name: " << r.name << "\n";
                    cout << "Address: " << r.address << "\n";
                    cout << "Cuisine: " << r.cuisine << "\n";
                    cout << "Website: " << r.website << "\n";
                    cout << "Phone: " << r.phone << "\n";
                    cout << "---------------------------\n";
                }
            } else {
                cout << "No restaurants at that price.\n";
            }
        } else {
            cout << "No restaurants with that star rating.\n";
        }
    } else {
        cout << "No restaurants in that city.\n";
    }
}


void mapInsertionsOA(vector<Restaurant>& restaurants, CityMap& allRestaurants) {
    for (auto& r : restaurants) {
        const string& city = r.location;
        const string& stars = r.starCount;
        const string& price = r.price;

        StarsMap starsMap;
        if (!allRestaurants.contains(city)) {
            starsMap = StarsMap();
        } else {
            starsMap = allRestaurants.search(city);
        }

        PriceMap priceMap;
        if (!starsMap.contains(stars)) {
            priceMap = PriceMap();
        } else {
            priceMap = starsMap.search(stars);
        }

        vector<Restaurant> matches;
        if (!priceMap.contains(price)) {
            matches = vector<Restaurant>();
        } else {
            matches = priceMap.search(price);
        }

        matches.push_back(r);
        priceMap.insert(price, matches);
        starsMap.insert(stars, priceMap);
        allRestaurants.insert(city, starsMap);
    }
}

int main() {
    // testing data parsing
    string filename = "../data/michelin_my_maps.csv";
    vector<Restaurant> restaurants = loadDataset(filename);

    //testing maps
    string city = "Miami, USA";
    string stars = "1 Star";
    string price = "$$$$";


    CityMap Michelin;
    mapInsertionsOA(restaurants, Michelin);
    printRestaurantsOA(Michelin, city, stars, price);


    // SeparateChaining<string,
    // SeparateChaining<string,
    // SeparateChaining<string, vector<Restaurant>>>> scMap; // using restaurant vector to give more info to user
    // updateMaps(restaurants, scMap);
    // sepChainingPrint(scMap, city, stars, price);
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