#include <iostream>
#include <vector>

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
    float loadFactor;

    // uses std::hash to hash key values 7
    int hashing(const Key& key) const {
        return hash<Key>{}(key) & capacity;
    }

    // helper function for insert to resize table and rehash key values
    void resize() {
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
    OpenAddressHashMap(int cap = 1000) : capacity(cap), size(0), loadFactor(0.75f) {
        table.resize(capacity);
    }

    void insert(const Key& key, const Value& value) {
        if((size/capacity) >= loadFactor) {
            resize();
        }

        // gets index by getting key's hash value and doing mod capacity
        int index = hashing(key) % capacity;
        int probeCounter = 0;

        // using quadratic probing to avoid clusters
        while (probeCounter < capacity) {
            // probeCounter quadractically increases for fitting probe location
            int probe = (index + probeCounter * probeCounter) % capacity;

            // if probed index is not occupied or the key is the same, place into index
            if(!table[probe].occupied || table[probe].key == key) {
                // bucket's key value pairs get set and it becomes occupied
                table[probe].key = key;
                table[probe].value = value;
                table[probe].occupied = true;
                size++;
                return;
            }
            // if table is occupied, probeCounter increases and loop repeats until found index
            probeCounter++;
        }
    }

    // using bool bc of outdated c++ so no include optional
    bool search(const Key& key, Value& v) {
        // searches if key exists, returns true if so
        // will be used to determine if user inputs exist in maps
        int index = hashing(key) % capacity;
        int probeCounter = 0;
        while (probeCounter < capacity) {
            int probe = (index + probeCounter * probeCounter) % capacity;

            if(!table[probe].occupied) {
                return false;
            }
            if(table[probe].key == key) {
                v = table[probe].value;
                return true;
            }
            probeCounter++;
        }
        return false;
    }
};