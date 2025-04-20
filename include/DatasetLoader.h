#include <fstream>
#include <sstream>
#include <vector>
#include "../include/Restaurant.h"

using namespace std;

// helper to normalize price to dollar format
string normalizePrice(const string& rawPrice) {
    int count = 0;
    for (size_t i = 0; i < rawPrice.size(); ++i) {
        // check for dollar sign
        if (rawPrice[i] == '$') {
            count++;
        }
            // check for the other currency symbols using substrings
        else if (rawPrice.substr(i, 2) == "€" || rawPrice.substr(i, 2) == "£" ||
        rawPrice.substr(i, 2) == "¥") {
            count++;
            i++; // skip next byte since
        }
    }
    return string(count, '$');  // normalize to $$$
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
        vector<string> fields;
        string field;
        bool insideQuotes = false;
        stringstream value;

        for (char c : line) {
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
        fields.push_back(value.str());

        if (fields.size() < 14) continue;

        Restaurant r;
        r.name = fields[0];
        r.address = fields[1];
        r.location = fields[2];
        r.price = normalizePrice(fields[3]);
        r.cuisine = fields[4];
        r.starCount = fields[10];

        restaurants.push_back(r);
    }
    return restaurants;
}
