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
        vector<Bucket> oldTable = table;
        capacity *= 2;
        table.clear();
        table.resize(capacity);
        size = 0;

        for (const auto& bucket : oldTable) {
            if (bucket.occupied) {
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

    // returns value of input key to user
    const Value& search(const Key& key) const {
        int index = hashing(key) % capacity;
        int probeCounter = 0;
        while (probeCounter < capacity) {
            int probe = (index + probeCounter * probeCounter) % capacity;

            if (!table[probe].occupied) break;
            if (table[probe].key == key) return table[probe].value;
            probeCounter++;
        }
        throw runtime_error("Key not found");
    }

    // checks if key exists
    bool contains(const Key& key) const {
        try {
            const_cast<OpenAddressHashMap*>(this)->search(key);
            return true;
        } catch (const std::runtime_error&) {
            return false;
        }
    }

    int getSize() { return size; }

};