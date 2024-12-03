#ifndef SLOT_H
#define SLOT_H

#include <string>
#include <functional>

template <typename T>
class Slot {
public:
    std::string key;   // The key for the hash table entry
    T value;           // The value associated with the key

    // Constructor
    
    Slot(const std::string& key = "", const T& value = T()) : key(key), value(value) {}

    // Generate a hash value for the key
    
    int HashKey(int table_size) const {
        std::hash<std::string> hasher;
        return hasher(key) % table_size;
    }
};

#endif // SLOT_H
