#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>


#include <stack>
using namespace std;

// Each node in the Trie
class TrieNode
{
public:
    // Each node has up to 26 children (for each letter)
    TrieNode *children[26];


    // Marks if this node completes a word
    bool isEndOfWord;

    // Constructor
    TrieNode *children[26];                      // for lowercase insert/search
    unordered_map<char, TrieNode *> childrenMap; // for extended insert/search
    bool isEndOfWord;

    TrieNode()
    {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

// The Trie class
class Trie
{
private:
    TrieNode *root;


    // Helper function to find all words from a node
    // Input: current node, current word formed so far, results vector to store words
    // Output: none (modifies results vector by reference)
    // Purpose: Recursively find all complete words starting from the given node
    void findAllWords(TrieNode *node, string currentWord, vector<string> &results)
    {
        if (node == nullptr)
            return;

        if (node->isEndOfWord)
        {
            results.push_back(currentWord);
        }

        for (int i = 0; i < 26; i++)
        {
            if (node->children[i] != nullptr)
            {
                char c = 'a' + i;
                findAllWords(node->children[i], currentWord + c, results);
            }
        }
    }

public:
    // Constructor
    // Input: none
    // Output: none
    // Purpose: Initialize the Trie with a root node
    Trie()
    {
        root = new TrieNode();
    }

    // Insert a word into the Trie
    // Input: word to insert (string)
    // Output: none
    // Purpose: Add a word to the Trie by creating nodes for each character
    void insert(string word)
    {
        // TODO: Implement this function
    }

    // Search for a word in the Trie
    // Input: word to search for (string)
    // Output: boolean indicating if the word exists
    // Purpose: Check if the complete word exists in the Trie

    bool search(string word) {
        TrieNode* node = root;
        for(char c : word){
            int index = c - 'a';
            if(!node->children[index])
                return false;
            node = node->children[index];
        }
        if(node->isEndOfWord)
            return true;
        return false;
    }

    // Check if any word starts with the given prefix
    // Input: prefix to check (string)
    // Output: boolean indicating if any word has this prefix
    // Purpose: Verify if the prefix exists in the Trie (doesn't need to be a complete word)
    bool startsWith(string prefix)
    {
     TrieNode *node = root;

        for (char c : prefix)
        {
            int index = c - 'a';

            if (node->children[index] == nullptr)
            {
                return false;
            }

            node = node->children[index];
        }

        return true;       
    }

    // Get all words that start with the given prefix
    // Input: prefix to complete (string)
    // Output: vector of strings that start with the prefix
    // Purpose: Find all complete words that begin with the given prefix
    vector<string> autocomplete(string prefix)
    {
        vector<string> suggestions;
        TrieNode* node = root;
        for (char ch : prefix){
        int childIndex = ch - 'a';
        if (!node->children[childIndex]){
            return suggestions;
        }
        node = node->children[childIndex];
        }
        findAllWords(node, prefix, suggestions);
        return suggestions;
        return suggestions;
    }
    string longestWord()
    {
        vector<string> words;
        string answer = "";

        findAllWords(root, "", words);

        for (const string &word : words)
        {
            if (word.size() > answer.size())
            {
                answer = word;
            }
        }
        return answer;
    }
    void insertExtended(const string &word)
    {
        TrieNode *node = root;
        for (char ch : word)
        {
            auto it = node->childrenMap.find(ch);
            if (it == node->childrenMap.end())
            {
                node->childrenMap[ch] = new TrieNode();
            }
            node = node->childrenMap[ch];
        }
        node->isEndOfWord = true;
    }
    bool searchExtended(const string &word)
    {
        TrieNode *node = root;
        for (char ch : word)
        {
            auto it = node->childrenMap.find(ch);
            if (it == node->childrenMap.end())
                return false;
            node = it->second;
        }
        return node->isEndOfWord;

    bool spellCheck(string word){
        return search(word);

    bool hasChild(TrieNode* node){
        if(!node)
            return false;
        for(int i = 0; i < 26; i++){
            if(node->children[i])
                return true;
        }
        return false;
    }
    bool remove(string word){
        TrieNode* node = root;
        stack<TrieNode*> nodes;
        stack<int> indexs;
        for(char c : word){
            int index = c - 'a';
            if(!node->children[index])
                return false;
            nodes.push(node);
            indexs.push(index);
            node = node->children[index];
        }
        nodes.push(node);   //last node

        // If the word does not exist as a full word
        if(!node->isEndOfWord) 
            return false;
        
        if(node->isEndOfWord){      //end of the word
            node->isEndOfWord = false;
            while(node != root){
                if(hasChild(node) || node->isEndOfWord)
                    break;
                else{        //has no child and not end of the word
                    //remove from the stack and delete it
                    TrieNode* child = nodes.top(); 
                    nodes.pop();
                    if(!nodes.empty()){     //if not empty get parent and set the child = null
                        TrieNode* parent = nodes.top();
                        parent->children[indexs.top()] = nullptr;
                        indexs.pop();
                        node = parent;
                    }
                    delete child;
                }
            }
        }
        return true;
    }
        
    int countWordsFromNode(TrieNode* node) {
        if (node == nullptr) return 0;

        int count = 0;

        if (node->isEndOfWord) {
            count++;
        }

        for (int i = 0; i < 26; i++) {
            count += countWordsFromNode(node->children[i]);
        }

        return count;
    }

    int countWords() {
        return countWordsFromNode(root);
    }
};

// Main function
// Input: none
// Output: integer return code
// Purpose: Program entry point, run tests and interactive demo
int main()
{
    cout << "=== TRIE DATA STRUCTURE IMPLEMENTATION ===" << endl;
    cout << "Testing all Trie functionalities..." << endl;

    Trie trie;

    // Test 1: Basic insertion and search
    cout << "\n1. Testing basic insertion and search:" << endl;
    cout << "======================================" << endl;

    vector<string> words = {"apple", "banana", "orange", "grape", "kiwi"};
    for (const string &word : words)
    {
        trie.insert(word);
        cout << "Inserted: " << word << endl;
    }

    // Test search for existing words
    for (const string &word : words)
    {
        bool found = trie.search(word);
        cout << "Search '" << word << "': " << (found ? "FOUND" : "NOT FOUND") << endl;
    }

    // Test search for non-existing words
    vector<string> nonExisting = {"app", "ban", "ora", "graph", "kiwis"};
    for (const string &word : nonExisting)
    {
        bool found = trie.search(word);
        cout << "Search '" << word << "': " << (found ? "FOUND" : "NOT FOUND") << " (expected: NOT FOUND)" << endl;
    }

    // Test 2: Prefix checking
    cout << "\n2. Testing prefix checking:" << endl;
    cout << "==========================" << endl;

    vector<string> prefixes = {"app", "ban", "ora", "grap", "k"};
    for (const string &prefix : prefixes)
    {
        bool hasPrefix = trie.startsWith(prefix);
        cout << "Prefix '" << prefix << "': " << (hasPrefix ? "EXISTS" : "DOESN'T EXIST") << endl;
    }

    vector<string> nonPrefixes = {"x", "yield", "zed", "micro", "nano"};
    for (const string &prefix : nonPrefixes)
    {
        bool hasPrefix = trie.startsWith(prefix);
        cout << "Prefix '" << prefix << "': " << (hasPrefix ? "EXISTS" : "DOESN'T EXIST") << " (expected: DOESN'T EXIST)" << endl;
    }

    // Test 3: Autocomplete functionality
    cout << "\n3. Testing autocomplete functionality:" << endl;
    cout << "======================================" << endl;

    vector<string> testPrefixes = {"a", "b", "o", "g", "k", "ap", "ban", "ora", "gr", "ki"};
    for (const string &prefix : testPrefixes)
    {
        vector<string> suggestions = trie.autocomplete(prefix);
        cout << "Autocomplete for '" << prefix << "': ";
        if (suggestions.empty())
        {
            cout << "No suggestions found";
        }
        else
        {
            for (size_t i = 0; i < suggestions.size(); i++)
            {
                if (i > 0)
                    cout << ", ";
                cout << suggestions[i];
            }
        }
        cout << endl;
    }

    // Test 4: Edge cases
    cout << "\n4. Testing edge cases:" << endl;
    cout << "======================" << endl;

    // Empty string tests
    bool emptySearch = trie.search("");
    cout << "Search empty string: " << (emptySearch ? "FOUND" : "NOT FOUND") << " (expected: NOT FOUND)" << endl;

    bool emptyPrefix = trie.startsWith("");
    cout << "Starts with empty prefix: " << (emptyPrefix ? "EXISTS" : "DOESN'T EXIST") << " (expected: EXISTS)" << endl;

    vector<string> emptySuggestions = trie.autocomplete("");
    cout << "Autocomplete for empty string: ";
    if (emptySuggestions.empty())
    {
        cout << "No suggestions found";
    }
    else
    {
        for (size_t i = 0; i < emptySuggestions.size(); i++)
        {
            if (i > 0)
                cout << ", ";
            cout << emptySuggestions[i];
        }
    }
    cout << " (expected: all words)" << endl;

    // Test 5: Adding more words and retesting
    cout << "\n5. Testing with additional words:" << endl;
    cout << "================================" << endl;

    vector<string> additionalWords = {"application", "appetizer", "banister", "bandana", "oracle", "grapefruit"};
    for (const string &word : additionalWords)
    {
        trie.insert(word);
        cout << "Inserted: " << word << endl;
    }

    // Test search for new words
    for (const string &word : additionalWords)
    {
        bool found = trie.search(word);
        cout << "Search '" << word << "': " << (found ? "FOUND" : "NOT FOUND") << endl;
    }

    // Test autocomplete with new words
    vector<string> newPrefixes = {"app", "ban", "ora", "gra"};
    for (const string &prefix : newPrefixes)
    {
        vector<string> suggestions = trie.autocomplete(prefix);
        cout << "Autocomplete for '" << prefix << "': ";
        if (suggestions.empty())
        {
            cout << "No suggestions found";
        }
        else
        {
            for (size_t i = 0; i < suggestions.size(); i++)
            {
                if (i > 0)
                    cout << ", ";
                cout << suggestions[i];
            }
        }
        cout << endl;
    }

    // Test 6: Case sensitivity (all lowercase expected)
    cout << "\n6. Testing case sensitivity:" << endl;
    cout << "============================" << endl;

    trie.insert("Hello");
    trie.insert("WORLD");

    vector<string> caseWords = {"hello", "Hello", "WORLD", "world"};
    for (const string &word : caseWords)
    {
        bool found = trie.search(word);
        cout << "Search '" << word << "': " << (found ? "FOUND" : "NOT FOUND") << endl;
    }

    cout << "\n=== ALL TESTS COMPLETED ===" << endl;

    return 0;
}
