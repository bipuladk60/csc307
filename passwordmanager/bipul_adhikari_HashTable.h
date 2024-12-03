#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "bipul_adhikari_Slot.h"
#include <vector>
#include <stdexcept>

template <typename T>
class HashTable {
private:
	std::vector<Slot<T>> table; 
	int size;                    
	int capacity;                

	int ProbeForEmptySlot(int hash) {
		int idx = hash;
		while (!table[idx].key.empty() && table[idx].key != "DELETED") {
			idx = (idx + 1) % capacity;
		}
		return idx;
	}

	int FindKey(const std::string& key) {
		int hash = Slot<T>(key).HashKey(capacity);
		int idx = hash;
		while (!table[idx].key.empty()) {
			if (table[idx].key == key) {
				return idx;
			}
			idx = (idx + 1) % capacity;
		}
		return -1;
	}


	void GrowTable() {
		capacity *= 2;
		std::vector<Slot<T>> old_table = table;
		table = std::vector<Slot<T>>(capacity);
		size = 0;

		for (const auto& slot : old_table) {
			if (!slot.key.empty() && slot.key != "DELETED") {
				InsertItem(slot.key, slot.value);
			}
		}
	}

public:

	HashTable(int initial_capacity = 8) : size(0), capacity(initial_capacity) {
		table.resize(capacity);
	}

	bool InsertItem(const std::string& key, const T& value) {
		if ((float)size / capacity >= 0.5) {
			GrowTable();
		}

		int hash = Slot<T>(key).HashKey(capacity);
		int idx = ProbeForEmptySlot(hash);
		table[idx] = Slot<T>(key, value);
		++size;
		return true;
	}


	bool RemoveItem(const std::string& key) {
		int idx = FindKey(key);
		if (idx == -1) {
			return false;
		}
		table[idx].key = "DELETED";
		--size;
		return true;
	}

	std::pair<T, bool> LookupItem(const std::string& key) {
		int idx = FindKey(key);
		if (idx == -1) {
			return {T(), false};
		}
		return {table[idx].value, true};
	}

	bool UpdateItem(const std::string& key, const T& new_value) {
		int idx = FindKey(key);
		if (idx == -1) {
			return false;
		}
		table[idx].value = new_value;
		return true;
	}
};

#endif
