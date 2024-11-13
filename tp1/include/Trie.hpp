#ifndef TRIE_HPP
#define TRIE_HPP

#include <bits/stdc++.h>
#include "TrieNode.hpp"

using namespace std;

class Trie{
    private:
        TrieNode* root;
        void printEachWord(TrieNode* node, string str);
        void printEachNode(TrieNode* node, int level);
        string stringToBinary(string word);
        string binaryToString(string word);
    public:
        Trie();
        int insertCount = 0;
        void insert(string word);
        void print(int choice);
        void remove(string word);
        void setUpTrie();
        pair<bool, int> search(string word);
        bool startsWith(string prefix);
};

#endif 