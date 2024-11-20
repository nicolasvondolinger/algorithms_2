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
        void deleteTrie(TrieNode* node);
    public:
        int numBits;
        Trie();
        ~Trie();
        void increaseNumBits(int num);
        void insert(string word, string id);
        void print(int choice);
        void remove(string word);
        void setUpTrie(int choice);
        pair<bool, string> search(string word);
};

#endif