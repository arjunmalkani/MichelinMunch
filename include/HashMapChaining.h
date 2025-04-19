#include <iostream>
using namespace std;

struct Node {
    string key;
    string value;
    Node* next;

    Node() : key(""), value(""), next(nullptr) {}
    Node(string k, string v) : key(k), value(v) {}
};

class SeparateChaining {
    int capacity; // size of table
    int count; // num of items in table
    Node** table;
    int hashFunction(string key);
    void reHash() {
        int oldCapacity = capacity;
        capacity *=2;
        Node** oldTable = table;
        table = new Node*[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
        count = 0;
        for (int i = 0; i < oldCapacity; i++) {
            Node* node = oldTable[i];
            while (node != nullptr) {
                insert(node->key, node->value);
                node = node->next;
            }
        }
        for (int i = 0; i < capacity; i++) {
            Node* curr = table[i];
            while(curr != nullptr) {
                Node* node = curr;
                curr = curr->next;
                delete node;
            }
        }
        delete[] table;
    }

    public:
    SeparateChaining() {
        table = new Node*[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }
    ~SeparateChaining() {
        for (int i = 0; i < capacity; i++) {
            Node* curr = table[i];
            while(curr != nullptr) {
                Node* node = curr;
                curr = curr->next;
                delete node;
            }
        }
        delete[] table;
    }
    void insert(string key, string value) {
        int index = hashFunction(key);
        Node *node = new Node(key, value);
        node->next = table[index];
        table[index] = node;
        count++;
        if (loadFactor() >= 0.75) {
            reHash();
        }
    }
    // void deleteItem(string key, string value);
    string search(string key) {
        int index = hashFunction(key);
        Node* curr = table[index];
        while(curr != nullptr) {
            if (curr->key == key) {
                return curr->value;
            }
            curr = curr->next;
        }
        return "Key not found";
    }
    float loadFactor() const {
        return count/capacity;
    }
    int getSize() const { return capacity;}
    int getCount() const { return count;}


};