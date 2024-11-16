#ifndef TRIENODE_HPP
#define TRIENODE_HPP

#include <bits/stdc++.h>

using namespace std;

class TrieNode{
    public:
        string id;
        string value;
        vector<TrieNode*> children;
        TrieNode();
};

#endif // TRIENODE_HPP