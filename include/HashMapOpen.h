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
    float loadFactor;

    // uses std::hash to hash key values 7
    int hashing(const Key &key) const {
        return hash<Key>{}(key) % capacity;
    }

    // helper function for insert to resize table and rehash key values
    void resize() {
        capacity *= 2;
        vector<Bucket> newTable(capacity);

        for (const auto &bucket: table) {
            if (bucket.occupied) {
                int index = hash<Key>{}(bucket.key) % capacity;
                while (newTable[index].occupied) {
                    index = (index + 1) % capacity;
                }
                newTable[index] = bucket;
            }
        }

        table = newTable;
    }

public:
    OpenAddressHashMap(int cap = 1000) : capacity(cap), size(0), loadFactor(0.75f) {
        table.resize(capacity);
    }

    void insert(const Key &key, const Value &value) {
        if(static_cast<float>(size + 1) / capacity >= loadFactor) {
            resize();
        }
        int index = hash<Key>{}(key) % capacity;
        // Open Address Through Linear Probing
        while(table[index].occupied && table[index].key != key) {
            index = (index + 1) % capacity;
        }

        if(!table[index].occupied) {
            table[index].value = value;
            table[index].occupied = true;
            table[index].key = key;
            size++;
        } else {
            // overwrites value if key exists
            table[index].value = value;
        }
    }

    // uses optional to safely return if key isnt found
    optional<Value> search(const Key& key) const {
        int index = hashing(key);
        int probeCount = 0;

        while (probeCount < capacity) {
            int probe = (index + probeCount) % capacity;

            if (!table[probe].occupied) {
                break;
            }
            if (table[probe].key == key) {
                return table[probe].value;
            }
            ++probeCount;
        }

        return nullopt;
    }

    Value& operator[](const Key& key) {
        if(static_cast<float>(size + 1) / capacity >= loadFactor) {
            resize();
        }
        int index = hashing(key);
        while (table[index].occupied && table[index].key != key) {
            index = (index + 1) % capacity;
        }
        if(!table[index].occupied) {
            table[index].occupied = true;
            table[index].key = key;
            size++;
        }
        return table[index].value;
    }


    // checks if key exists
    bool contains(const Key& key) const {
        return search(key).has_value();
    }





    int getSize() { return size; }

};
