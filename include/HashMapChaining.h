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
    void reHashing();
    void resize();

    public:
    SeparateChaining() {
        table = new Node*[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }
    ~SeparateChaining();
    void insert(string key, string value) {
        int index = hashFunction(key);
        Node *node = new Node(key, value);
        node->next = table[index];
        table[index] = node;
        count++;
        if (loadFactor() >= 0.75) {
            reHashing();
        }
    }
    // void deleteItem(string key, string value);
    string search();
    float loadFactor() const {
        return count/capacity;
    }
    int getSize() const { return capacity;}
    int getCount() const { return count;}


};