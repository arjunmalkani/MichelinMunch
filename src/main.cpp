#include <iostream>
#include "../include/DatasetLoader.h"

int main() {
    // testing data parsing
    string filename = "../data/michelin_my_maps.csv";
    vector<Restaurant> restaurants = loadDataset(filename);

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
