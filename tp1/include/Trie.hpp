#ifndef TRIE_HPP
#define TRIE_HPP

#include <bits/stdc++.h>
#include "TrieNode.hpp"

using namespace std;

class Trie{
    private:
        TrieNode* root;
        char CASE;
        string strCopy(string str, int index);
        void printUntil(TrieNode* node, string str);
    public:
        Trie();
        void insert(string word);
        void print();
        bool search(string word);
        bool startsWith(string prefix);
};

#endif // TRIE_HPP