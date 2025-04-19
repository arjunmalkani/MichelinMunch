#include <iostream>
#include <vector>
#include <optional>

using namespace std;


template<typename Key, typename Value>
class OpenAddressHashMap {
private:
    struct Bucket {
        Key key;
        Value value;
        bool occupied;
        //bool deleted
    };
    vector<Bucket> table;
    int capacity;
    int size;
    float loadFactor = 0.0f;

    int hashing(const Key& key) const {
        return hash<Key>{}(key) & capacity;
    }

    void rehash() {
        capacity *= 2;
        vector<Bucket> newTable;
        table.clear();
        table.resize(capacity);
        size = 0;

        for (const auto& bucket : table) {
            if(bucket.occupied) {
                insert(bucket.key, bucket.value);
            }
        }
    }

public:





    // core fields: Entry[], size, capacity, etc.
    // insert(key, value)
    // get(key)
    // contains(key)
    // rehash(), etc.
};