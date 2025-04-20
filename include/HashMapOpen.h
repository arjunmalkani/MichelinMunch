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
        return hash<Key>{}(key) & capacity;
    }

    // helper function for insert to resize table and rehash key values
    void resize() {
        capacity *= 2;
        vector<Bucket> newTable(capacity);

        for (const auto &bucket: table) {
            if (bucket.isOccupied) {
                int index = hash<Key>{}(bucket.key) % capacity;
                while (newTable[index].isOccupied) {
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
        if((size / capacity) >= loadFactor) {
            resize();
        }
        int index = hash<Key>{}(key) % capacity;
        // Open Address Through Linear Probing
        while(table[index].isOccupied) {
            index = (index + 1) % capacity;
        }

        if(!table[index].isOccupied || table[index].key == key) {
            table[index].value = value;
            table[index].occupied = true;
            table[index].key = key;
            size++;
        }
    }

    std::optional<Value> search(const Key& key) const {
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

        return std::nullopt;
    }



    int getSize() { return size; }

};
