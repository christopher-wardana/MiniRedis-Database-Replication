// Seperate Chaining Implementation

#include <iostream>
#include <list> // For linked lists
#include <cstring> // Strings

using namespace std;

class HashTable {
    private:
        static const int hashGroups =10;
        list<pair<int, string>> table[hashGroups]; // Array of lists

    public:
        bool isEmpty() const;
        int hashFunction (int key) const;
        void addItem(int key, string value);
        void removeItem(int key);
        string searchItem(int key) const;
        void printTable() const;

};

bool HashTable::isEmpty() const{ // const here ensures compiler that we won't change member variables of object
    int sum{}; // int sum = 0 same thing

    for(int i{}; i < hashGroups; i++){
        sum += table[i].size();

    }

    if(!sum){ // If sum == 0 same thing
        return true;
    }
    return false;
}

int HashTable::hashFunction (int key) const{
    return key % hashGroups; 

}

void HashTable::addItem(int key, string value){
    int index = hashFunction(key);
    auto& indexGroup = table[index];

    for (auto& entry : indexGroup) {
        if (entry.first == key) {
            entry.second = value;  // key exists, overwrite the value
            return;
        }
    }

    indexGroup.push_back({key, value});
}

void HashTable::removeItem(int key){
    int index = hashFunction(key);
    auto& indexGroup = table[index];
    auto bItr = begin(indexGroup);

    for(; bItr != end(indexGroup); bItr++){
        if(bItr->first == key){
            indexGroup.erase(bItr);
            return;
        }
    }

}

string HashTable::searchItem(int key) const{
    int index = hashFunction(key);
    const auto& indexGroup = table[index];

    for (const auto& entry : indexGroup) {
        if (entry.first == key) {
            return entry.second;
        }
    }

    return "Item not found";
}

void HashTable::printTable() const{

    for(int i{}; i<hashGroups; i++){
        const auto& indexGroup = table[i];

        if(indexGroup.empty()) continue;

        cout << "Bucket number " << i << "\n";
        for (const auto& entry : indexGroup) {
            cout << "(" << entry.first << ", " << entry.second << ")\n";
    
        }
    }
}

int main(){

    HashTable HT;

    if(HT.isEmpty()){
        cout << "Correct\n";
    }else{
        cout << "Wrong\n";
    }

    HT.addItem(342, "Chris");
    HT.addItem(5423, "Jack");
    HT.addItem(738, "Timmy");
    HT.addItem(945, "Bob");
    HT.addItem(123, "Brian");
    HT.addItem(276, "Tom");
    HT.addItem(687, "Billy");

    HT.printTable();

    HT.searchItem(945);
    HT.searchItem(1);

    HT.removeItem(342);
    HT.removeItem(5423);
    HT.removeItem(738);

    cout << "After removal\n";

    HT.printTable();
    
    if(HT.isEmpty()){
        cout << "Wrong\n";
    }else{
        cout << "Correct\n";
    }
}