#include <iostream>
#include "../include/DatasetLoader.h"
#include "HashMapChaining.h"
#include "HashMapOpen.h"

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
int main() {
    // testing data parsing
    string filename = "../data/michelin_my_maps.csv";
    vector<Restaurant> restaurants = loadDataset(filename);

    SeparateChaining<string,
    SeparateChaining<string,
    SeparateChaining<string, vector<Restaurant>>>> scMap; // using restaurant vector to give more info to user
    updateMaps(restaurants, scMap);

    //testing maps
    string city = "Miami, USA";
    string stars = "1 Star";
    string price = "$$$$";
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

    return 0;
}
