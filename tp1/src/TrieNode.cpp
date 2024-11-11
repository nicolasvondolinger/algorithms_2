#include "../include/TrieNode.hpp"

TrieNode::TrieNode(){
    id = -1;
    value = "";
    children.resize(SYMBOLS, nullptr);
}