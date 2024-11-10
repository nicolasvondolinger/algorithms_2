#ifndef TRIENODE_HPP
#define TRIENODE_HPP

#include <bits/stdc++.h>

using namespace std;

class TrieNode{
    private: 
        static const int SYMBOLS = 26;
    public:
        int key;
        string value;
        vector<TrieNode*> children;
        TrieNode();
};

#endif // TRIENODE_HPP