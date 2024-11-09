#ifndef TRIENODE_HPP
#define TRIENODE_HPP

#include <bits/stdc++.h>

using namespace std;

class TrieNode{
    private: 
        static const int SYMBOLS = 26;
        /** 
        Número de símbolos e filhos que aquele
        nó pode ter
        **/
    public:
        int key;
        vector<TrieNode*> children;
        vector<string> edgeLabel;
        bool isEnd;
        TrieNode(bool isEnd);
};

#endif // TRIENODE_HPP