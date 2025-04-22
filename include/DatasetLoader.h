#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <string>
#include "../include/Restaurant.h"

using namespace std;

// helper to normalize price to dollar format
string normalizePrice(const string& rawPrice) {
    // add all the currencies present in dataset
    vector<string> currencySymbols = {"$", "€", "£", "¥", "₩", "฿", "₺", "₫", "﷼"};
    int count = 0;

    for (size_t i = 0; i < rawPrice.size(); ) {
        // check up to 4-bytes
        bool matched = false;
        for (int len = 1; len <= 4 && i + len <= rawPrice.size(); ++len) {
            string symbol = rawPrice.substr(i, len);
            if (find(currencySymbols.begin(), currencySymbols.end(), symbol) != currencySymbols.end()) {
                count++;
                i += len;
                matched = true;
                break;
            }
        }
        if (!matched) i++;  // skip non-currency characters
    }

    return string(count, '$'); // append into dollar
}


vector<Restaurant> loadDataset(const string& filename) {
    vector<Restaurant> restaurants;
    ifstream file(filename);

    if(!file.is_open()){
        cout << "File not opened." << endl;
        return {};
    }
    string line;

    getline(file, line); // skip header

    while (getline(file, line)) {
        // reads in each line
        vector<string> fields;
        string field;
        bool insideQuotes = false;
        stringstream value;

        for (char c : line) {
            // flags handle cases where commas are nested in quotes: "arjun, anthony, ely" for ex
            if (c == '"') {
                insideQuotes = !insideQuotes;
            } else if (c == ',' && !insideQuotes) {
                fields.push_back(value.str());
                value.str("");
                value.clear();
            } else {
                value << c;
            }
        }
        fields.push_back(value.str()); // add last field

        if (fields.size() < 14) continue; // skip unused features of lines which starts at 14th field

        // create restaurant obj and initilize each attribute to corresponding feature of data in a line
        Restaurant r;
        r.name = fields[0];
        r.address = fields[1];
        r.location = fields[2];
        r.price = normalizePrice(fields[3]);
        r.phone = fields[7];
        r.michelinWebsite = fields[8];
        r.officialWebsite = fields[9];
        r.cuisine = fields[4];
        r.starCount = fields[10];
        r.description = fields[13];

        restaurants.push_back(r);

    }

    return restaurants;
}
