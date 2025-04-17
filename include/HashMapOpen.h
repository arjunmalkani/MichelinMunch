#include <iostream>
#include <vector>
#include <optional>

using namespace std;


template<typename Key, typename Value>
class OpenAddressHashMap {
private:
    struct Bucket {
        string key;
        string value;
        bool occupied;
        //bool deleted
    };
    vector<Bucket> table;
    size_t capacity;
    size_t size;


    // core fields: Entry[], size, capacity, etc.
    // insert(key, value)
    // get(key)
    // contains(key)
    // rehash(), etc.
};