#include <iostream>
#include "../include/DatasetLoader.h"
#include "HashMapChaining.h"
#include "HashMapOpen.h"

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
                              SeparateChaining<string, vector<Restaurant> > > > scMap, string city, string stars,
                      string price) {
    if (scMap.contains(city)) {
        auto starMap = scMap.search(city);

        if (starMap.contains(stars)) {
            auto priceMap = starMap.search(stars);

            if (priceMap.contains(price)) {
                vector<Restaurant> matches = priceMap.search(price);
                cout << "Restaurants found in " << city << " with " << stars << " and " << price << " price:" << endl;
                for (const Restaurant &r: matches) {
                    cout << "- " << r.name << " | " << r.address << " | Cuisine: " << r.cuisine << endl;
                }
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

void printRestaurantsOA(
    OpenAddressHashMap<string,
    OpenAddressHashMap<string,
    OpenAddressHashMap<string, vector<Restaurant>>>> &allRestaurants, const string &city,
                                                                      const string &stars, const string &price) {
    if (!allRestaurants.contains(city)) {
        cout << "No restaurants in that city or city does not exist.\n";
        return;
    }

    auto &starsMap = allRestaurants[city];
    if (!starsMap.contains(stars)) {
        cout << "No restaurants with that star rating.\n";
        return;
    }
    auto &priceMap = starsMap[stars];
    if (!priceMap.contains(price)) {
        cout << "No restaurants with that price range.\n";
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
    string city;
    string stars;
    string price;

    cout << "Welcome To MichelinMunch!\n"
    "We are here to satisfy your cravings of meals from the Michelin Guide's list of restaurants!\n"
    "Just follow the next 3 instructions to find restaurants which suit YOUR delicious dining desires!\n"
    "First, please input a city followed by a comma and its country of origin. Ex: Miami, USA\n";
    // user puts city
    getline(cin, city);

    cout << "Next, please input the amount of stars you intend to dine at (1-3)." << endl;
    // user puts stars
    getline(cin, stars);
    // allows user to enter a number versus "1 Star"
    if(stars == "1") {
        stars += " Star";
    } else if (stars == "2" || stars == "3") {
        stars += " Stars";
    } else {
        cout << "You did not enter a star count from 1-3 so there is no such restaurant.\n"
                "Would you like to see recommended selected restaurants from the Michelin Guide that fit your criteria instead?\n"
                "Please enter Y or N\n";
        string selected;
        getline(cin, selected);

        if (selected == "Y" || selected == "y") {
            stars = "Selected Restaurants";

        } else {
            return 1;
        }
    }


    cout << "Lastly, please input the price range from you intend to dine at. Ex: $-$$$$\n"
            "PLEASE NOTE: The type of currency MUST match the currency of the country you plan to dine in!" << endl;
    // user enters price
    getline(cin, price);


    // testing data parsing
    string filename = "../data/michelin_my_maps.csv";
    vector<Restaurant> restaurants = loadDataset(filename);

    // MY WORK
    cout << "OPEN ADDRESSING RESULT: \n\n";

    OpenAddressHashMap<string,
    OpenAddressHashMap<string,
    OpenAddressHashMap<string, vector<Restaurant>>>> Michelin;
    mapInsertionsOA(restaurants, Michelin);
    printRestaurantsOA(Michelin, city, stars, price);

    cout << "SEPARATE CHAINING RESULT: \n\n";

    // ELYS WORK
    SeparateChaining<string,
    SeparateChaining<string,
    SeparateChaining<string, vector<Restaurant>>>> scMap; // using restaurant vector to give more info to user
    updateMaps(restaurants, scMap);
    sepChainingPrint(scMap, city, stars, price);
    return 0;
}
