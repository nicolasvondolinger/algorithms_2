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
        void increaseInsertCount();
        void deleteTrie(TrieNode* node);
    public:
        Trie();
        ~Trie();
        string insertCount = "0";
        void insertEncoding(string word);
        void insertDecoding(string word, string id);
        void print(int choice);
        void remove(string word);
        void setUpTrieEncoding();
        void setUpTrieDecoding();
        pair<bool, string> search(string word);
        bool startsWith(string prefix);
};

#endif 