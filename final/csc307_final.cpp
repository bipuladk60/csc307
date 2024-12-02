/* 
Name: Bipul Adhikari, Sushant Aryal, OM Nepal, Akachukwu Nicholas
Description: Enhanced Trie implementation with interactive interface, word popularity tracking, and autocompletion suggestions.
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

// class for single node

class TrieNode {
    public:
        unordered_map<char, TrieNode*> children; // map of children
        bool isEndOfWord; // flag to check if it is end of word

        TrieNode() {
            isEndOfWord = false;
        };
};

// class for Trie
class Trie {
    private:
        TrieNode* root;

        // Helper function to collect all words from a given node
        void collectWords(TrieNode* node, string prefix, vector<string>& words) const {
            if (node->isEndOfWord) {
                words.push_back(prefix);
            }
            for(auto &pair : node->children) {
                collectWords(pair.second, prefix + pair.first, words);
            }
        }

    public:
        Trie() {
            root = new TrieNode();
        }

        ~Trie() {
            delete root;
        }

    // insertion
    void insert(const string& word) {
        TrieNode* curr = root;
        for (char ch : word){
            if(curr->children.find(ch) == curr->children.end()){
                curr->children[ch] = new TrieNode();
            }
            curr = curr->children[ch];
        }
        curr->isEndOfWord = true;
    }

    // search
    bool search(const string& word) {
        TrieNode* curr = root;
        for (char ch : word){
            if(curr->children.find(ch) == curr->children.end()){
                return false;
            }
            curr = curr->children[ch];
        }
        return curr->isEndOfWord;
    }

    // search prefix
    bool startsWith(const string& prefix) {
        TrieNode* curr = root;
        for (char ch : prefix){
            if(curr->children.find(ch) == curr->children.end()){
                return false;
            }
            curr = curr->children[ch];
        }
        return true;
    }

    // remove
    void remove(const string& word) {
        TrieNode* curr = root;
        for (char ch : word){
            if(curr->children.find(ch) == curr->children.end()){
                return;
            }
            curr = curr->children[ch];
        }
        curr->isEndOfWord = false;
    }

    //update
    void update(const string& oldWord, const string& newWord) {
        remove(oldWord);
        insert(newWord);
    }

    // Get all words with the given prefix
    vector<string> getWordsWithPrefix(const string& prefix) const {
        vector<string> words;
        TrieNode* curr = root;
        for(char ch : prefix){
            if(curr->children.find(ch) == curr->children.end()){
                return words; // Empty vector if prefix not found
            }
            curr = curr->children[ch];
        }
        collectWords(curr, prefix, words);
        return words;
    }
};

// Function to display the interactive menu
void displayMenu() {
    cout << "\n==== TypeTrie Interactive Interface ====\n";
    cout << "1. Insert a word\n";
    cout << "2. Search for a word\n";
    cout << "3. Remove a word\n";
    cout << "4. Update a word\n";
    cout << "5. Get Autocomplete Suggestions\n";
    cout << "6. Exit\n";
    cout << "Choose an option (1-6): ";
}

// Function to display suggestions sorted by popularity
void displaySuggestions(const vector<string>& suggestions, const unordered_map<string, int>& wordFrequency) {
    if(suggestions.empty()) {
        cout << "No suggestions found.\n";
        return;
    }

    // Create a vector of pairs (word, frequency)
    vector<pair<string, int>> wordsWithFreq;
    for(const auto& word : suggestions){
        auto it = wordFrequency.find(word);
        if(it != wordFrequency.end()){
            wordsWithFreq.emplace_back(make_pair(word, it->second));
        }
        else{
            wordsWithFreq.emplace_back(make_pair(word, 0)); // Default frequency 0
        }
    }

    // Sort the words based on frequency in descending order
    sort(wordsWithFreq.begin(), wordsWithFreq.end(), 
        [&](const pair<string, int>& a, const pair<string, int>& b) -> bool {
            if(a.second == b.second){
                return a.first < b.first; // If frequencies are equal, sort lexicographically
            }
            return a.second > b.second;
        }
    );

    // Display the sorted suggestions
    cout << "Autocomplete Suggestions:\n";
    for(const auto& pair : wordsWithFreq){
        cout << "- " << pair.first << " (Used " << pair.second << " times)\n";
    }
}

//Tests

int main() {
    Trie trie;
    unordered_map<string, int> wordFrequency; // Hash table to store word frequencies
    
    trie.insert("hello");
    trie.insert("hell");
    trie.insert("heaven");
    trie.insert("heavy");
    trie.insert("world");
    trie.insert("word");
    trie.insert("wonder");
    trie.insert("wood");
    trie.insert("wolf");
    trie.insert("whale");

    // Initialize word frequencies
    wordFrequency["hello"] = 5;
    wordFrequency["hell"] = 2;
    wordFrequency["heaven"] = 3;
    wordFrequency["heavy"] = 4;
    wordFrequency["world"] = 6;
    wordFrequency["word"] = 1;
    wordFrequency["wonder"] = 2;
    wordFrequency["wood"] = 3;
    wordFrequency["wolf"] = 2;
    wordFrequency["whale"] = 1;

    int choice;
    string word, prefix, newWord;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // To ignore the newline character after the integer input

        switch(choice) {
            case 1:
                cout << "Enter the word to insert: ";
                getline(cin, word);
                trie.insert(word);
                wordFrequency[word] += 1; // Initialize frequency or increment if exists
                cout << "Word '" << word << "' inserted successfully.\n";
                break;
            case 2:
                cout << "Enter the word to search: ";
                getline(cin, word);
                if(trie.search(word)){
                    cout << "Word '" << word << "' found in Trie.\n";
                    wordFrequency[word] += 1; // Increment frequency upon search
                }
                else{
                    cout << "Word '" << word << "' not found in Trie.\n";
                }
                break;
            case 3:
                cout << "Enter the word to remove: ";
                getline(cin, word);
                if(trie.search(word)){
                    trie.remove(word);
                    wordFrequency.erase(word);
                    cout << "Word '" << word << "' removed successfully.\n";
                }
                else{
                    cout << "Word '" << word << "' does not exist in Trie.\n";
                }
                break;
            case 4:
                cout << "Enter the old word to update: ";
                getline(cin, word);
                if(trie.search(word)){
                    cout << "Enter the new word: ";
                    getline(cin, newWord);
                    trie.update(word, newWord);
                    wordFrequency[newWord] += wordFrequency[word];
                    wordFrequency.erase(word);
                    cout << "Word updated from '" << word << "' to '" << newWord << "'.\n";
                }
                else{
                    cout << "Word '" << word << "' does not exist in Trie.\n";
                }
                break;
            case 5:
                cout << "Enter the prefix for autocomplete suggestions: ";
                getline(cin, prefix);
                if(trie.startsWith(prefix)){
                    vector<string> suggestions = trie.getWordsWithPrefix(prefix);
                    // Increment frequency for selected suggestion
                    displaySuggestions(suggestions, wordFrequency);
                }
                else{
                    cout << "No words found with the prefix '" << prefix << "'.\n";
                }
                break;
            case 6:
                cout << "Exiting the program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please select a valid option (1-6).\n";
        }
    }

    return 0;
}
