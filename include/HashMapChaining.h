#include <iostream>
using namespace std;

template<typename Key, typename Value>
struct Node {
    Key key;
    Value value;
    Node* next;

    Node() : key(""), value(""), next(nullptr) {}
    Node(Key k, Value v) : key(k), value(v) {}
};

template<typename Key, typename Value>
class SeparateChaining {
    int capacity; // size of table
    int count; // num of items in table
    Node<Key, Value>** table;
    int hashFunction(const Key& key) {
        return hash<Key>{}(key) % capacity;
    }
    void reHash() {
        int oldCapacity = capacity;
        capacity *=2;
        Node<Key, Value>** oldTable = table;
        table = new Node<Key, Value>*[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
        count = 0;
        for (int i = 0; i < oldCapacity; i++) {
            Node<Key, Value>* node = oldTable[i];
            while (node != nullptr) {
                insert(node->key, node->value);
                node = node->next;
            }
        }
        for (int i = 0; i < oldCapacity; i++) {
            Node<Key, Value>* curr = oldTable[i];
            while(curr != nullptr) {
                Node<Key, Value>* node = curr;
                curr = curr->next;
                delete node;
            }
        }
        delete[] oldTable;
    }

    public:
    SeparateChaining(const SeparateChaining& other) {
        capacity = other.capacity;
        count = other.count;
        table = new Node<Key, Value>*[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
            Node<Key, Value>* curr = other.table[i];
            Node<Key, Value>* prev = nullptr;
            while (curr != nullptr) {
                Node<Key, Value>* newNode = new Node<Key, Value>(curr->key, curr->value);
                if (prev == nullptr) {
                    table[i] = newNode;
                } else {
                    prev->next = newNode;
                }
                prev = newNode;
                curr = curr->next;
            }
        }
    }
    SeparateChaining& operator=(const SeparateChaining& other) {
        if (this == &other) { return *this;}
        this->~SeparateChaining();
        capacity = other.capacity;
        count = other.count;
        table = new Node<Key, Value>*[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
            Node<Key, Value>* curr = other.table[i];
            Node<Key, Value>* prev = nullptr;
            while (curr != nullptr) {
                Node<Key, Value>* newNode = new Node<Key, Value>(curr->key, curr->value);
                if (prev == nullptr) {
                    table[i] = newNode;
                } else {
                    prev->next = newNode;
                }
                prev = newNode;
                curr = curr->next;
            }
        }
        return *this;
    }
    SeparateChaining() {
        capacity = 10000;
        count = 0;
        table = new Node<Key, Value>*[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }
    ~SeparateChaining() {
        for (int i = 0; i < capacity; i++) {
            Node<Key, Value>* curr = table[i];
            while(curr != nullptr) {
                Node<Key, Value>* node = curr;
                curr = curr->next;
                delete node;
            }
        }
        delete[] table;
    }
    void insert(const Key& key, const Value &value) {
        int index = hashFunction(key);
        auto *node = new Node<Key, Value>(key, value);
        node->next = table[index];
        table[index] = node;
        count++;
        if (loadFactor() >= 0.75) {
            reHash();
        }
    }
    // void deleteItem(string key, string value);
    Value& search(Key key) {
        int index = hashFunction(key);
        Node<Key, Value>* curr = table[index];
        while(curr != nullptr) {
            if (curr->key == key) {
                return curr->value;
            }
            curr = curr->next;
        }
        throw runtime_error("Key not found");
    }
    bool contains(Key key) {
        int index = hashFunction(key);
        Node<Key, Value>* curr = table[index];
        while(curr != nullptr) {
            if (curr->key == key) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }
    float loadFactor() const {
        return static_cast<float>(count)/capacity;
    }
    int getSize() const { return capacity;}
    int getCount() const { return count;}


};