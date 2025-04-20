#pragma once
#include <vector>
#include <optional>
#include <functional>
template<typename Key, typename Value>
class OpenAddressHashMap {
private:
    struct Bucket {
        Key key;
        optional<Value> value; // only constructs vals when needed
        bool occupied = false;
    };

    vector<Bucket> table;
    int capacity;
    int size;
    float loadFactor;

    // Primary hash function (mod capacity)
    int hashing(const Key& key) const {
        return hash<Key>{}(key) % capacity;
    }

    // helper function for insert to resize table and rehash key values
    void resize() {
        capacity *= 2;
        vector<Bucket> newTable(capacity);

        for (auto& bucket : table) {
            if (bucket.occupied) {
                int idx = hash<Key>{}(bucket.key) % capacity;
                while (newTable[idx].occupied) {
                    idx = (idx + 1) % capacity;
                }
                newTable[idx].occupied = true;
                newTable[idx].key = move(bucket.key);
                newTable[idx].value = move(bucket.value);
            }
        }
        table = move(newTable);
    }

public:
    // constructor
    OpenAddressHashMap(int cap = 1000)
      : table(cap), capacity(cap), size(0), loadFactor(0.75f)
    {}

    // inserts key-value pairs for map
    void insert(const Key& key, const Value& val) {
        if (static_cast<float>(size + 1) / capacity >= loadFactor) {
            resize();
        }
        int idx = hashing(key);
        // linear probing approach
        while (table[idx].occupied && table[idx].key != key) {
            idx = (idx + 1) % capacity;
        }
        if (!table[idx].occupied) {
            table[idx].occupied = true;
            table[idx].key      = key;
            table[idx].value.emplace(val);
            ++size;
        } else {
            // overwrites value if key exists
            table[idx].value = val;
        }
    }

    // replicates maps' [] operation with avg case O(1) runtime
    // access keys and returns reference to value
    Value& operator[](const Key& key) {
        if (static_cast<float>(size + 1) / capacity >= loadFactor) {
            resize();
        }
        int idx = hashing(key);
        while (table[idx].occupied && table[idx].key != key) {
            idx = (idx + 1) % capacity;
        }
        if (!table[idx].occupied) {
            table[idx].occupied = true;
            table[idx].key = key;
            table[idx].value.emplace();
            ++size;
        }
        return *table[idx].value;
    }

    // uses optional to safely return if key isnt found
    optional<Value> search(const Key& key) const {
        int start = hashing(key);
        for (int probe = 0; probe < capacity; ++probe) {
            int idx = (start + probe) % capacity;
            if (!table[idx].occupied) {
                // table breaks if empty bucket
                break;
            }
            if (table[idx].key == key) {
                // returns table's index if keys match
                return table[idx].value;
            }
        }
        // returns "no value"
        return nullopt;
    }

    // checks if key exists
    bool contains(const Key& key) const {
        return search(key).has_value();
    }

    // Current number of stored key-value pairs
    int getSize() const {
        return size;
    }
};
