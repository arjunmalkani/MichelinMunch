#include <iostream>
#include "../include/DatasetLoader.h"
#include "HashMapChaining.h";
#include "HashMapOpen.h"

void updateMaps(vector<Restaurant> &restaurants,
    SeparateChaining &cityMapSc, SeparateChaining &starMapSc, SeparateChaining &moneyMapSc) {
    for (Restaurant &restaurant : restaurants) {
        string name = restaurant.name;
        cityMapSc.insert(name, restaurant.location);
        starMapSc.insert(name, restaurant.starCount);
        moneyMapSc.insert(name, restaurant.price);
    }
}
int main() {
    // testing data parsing
    string filename = "../data/michelin_my_maps.csv";
    vector<Restaurant> restaurants = loadDataset(filename);
    SeparateChaining cityMapSc, starMapSc, moneyMapSc;
    updateMaps(restaurants, cityMapSc, starMapSc, moneyMapSc);

    //testing maps
    string restaurantName = "Le Bernardin";
    cout << "City: " << cityMapSc.search(restaurantName) << endl;
    cout << "Stars: " << starMapSc.search(restaurantName) << endl;
    cout << "Price: " << moneyMapSc.search(restaurantName) << endl;

    cout << "Total restaurants parsed: " << restaurants.size() << endl;

    // prints first 400 restaurants info to verify parsing works
    for (int i = 0; i < 400; i++) {
        const Restaurant& r = restaurants[i];
        cout << "Name: " << r.name << endl;
        cout << "Address: " << r.address << endl;
        cout << "City: " << r.location  << endl;
        cout << "Price: " << r.price << endl;
        cout << "Cuisine: " << r.cuisine << endl;
        cout << "Stars: " << r.starCount << endl;
        cout << "------------------------" << endl;
    }

    return 0;
}
