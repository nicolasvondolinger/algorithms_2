#ifndef TRIE_HPP
#define TRIE_HPP

#include <bits/stdc++.h>
#include "TrieNode.hpp"

using namespace std;

class Trie{
    private:
        TrieNode* root;
        string strCopy(string str, int index);
        void printUntil(TrieNode* node, string str);
    public:
        vector<string> words;
        Trie();
        void insert(string word);
        void print();
        pair<bool, int> search(string word);
        bool startsWith(string prefix);
        int insertCount = 0;
};

#endif 