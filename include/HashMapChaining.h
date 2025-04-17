#include <iostream>
using namespace std;

struct Node {
    string key;
    string value;
    Node* next;

    Node();
    Node(int k, string v);
};

class SeparateChaining {
    int capacity; // size of table
    int count; // num of items in table
    int hashFunction(int key);
    void reHashing();
    void resize();

    public:
    SeparateChaining();
    ~SeparateChaining();
    void insert(string key);
    void deleteItem(string key);
    string search();
    float loadFactor() const {
        return count/capacity;
    }
    int getSize() const { return capacity;}
    int getCount() const { return count;}





};