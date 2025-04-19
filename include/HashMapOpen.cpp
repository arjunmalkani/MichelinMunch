#include <iostream>
#include "HashMapOpen.h"
#include "Restaurant.h"

using PriceMap = OpenAddressHashMap<string, vector<Restaurant>>;
using StarsMap = OpenAddressHashMap<string, PriceMap>;
using CityMap = OpenAddressHashMap<string, StarsMap>;

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


