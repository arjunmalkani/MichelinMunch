#include <iostream>
#include "../include/DatasetLoader.h"
#include "HashMapChaining.h"
#include "HashMapOpen.h"

void updateMaps(vector<Restaurant> &restaurants,
    SeparateChaining<string,
    SeparateChaining<string,
    SeparateChaining<string, string>>> &scMap) {

    SeparateChaining<string, SeparateChaining<string, string>> cityMapSc;


    for (Restaurant &restaurant : restaurants) {
        string city = restaurant.location;
        string name = restaurant.name;
        string stars = restaurant.starCount;
        string price = restaurant.price;


        if (!scMap.contains(city)) {
            scMap.insert(city, SeparateChaining<string, SeparateChaining<string, string>>());
        }
        auto& starMapSc = scMap.search(city);

        if (!starMapSc.contains(stars)) {
            starMapSc.insert(stars, SeparateChaining<string, string>());
        }
        auto& priceMapSc = starMapSc.search(stars);
        priceMapSc.insert(price, name);
    }
}

void sepChainingPrint(SeparateChaining<string,
    SeparateChaining<string,
    SeparateChaining<string, string>>>& scMap, string& city, string& stars, string& price) {
    if (scMap.contains(city)) {
        auto starMap = scMap.search(city);

        if (starMap.contains(stars)) {
            auto priceMap = starMap.search(stars);

            if (priceMap.contains(price)) {
                string name = priceMap.search(price);
                cout << "Restaurant found in " << city << " with " << stars << " and " << price << " price: " << name << endl;
            } else {
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
    // testing data parsing
    string filename = "../data/michelin_my_maps.csv";
    vector<Restaurant> restaurants = loadDataset(filename);

    SeparateChaining<string,
    SeparateChaining<string,
    SeparateChaining<string, string>>> scMap;
    updateMaps(restaurants, scMap);

    //testing maps
    string city = "Miami, USA";
    string stars = "2 Stars";
    string price = "$$$";

    sepChainingPrint(scMap, city, stars, price);


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

