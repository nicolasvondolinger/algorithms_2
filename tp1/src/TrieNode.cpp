#include "../include/TrieNode.hpp"

TrieNode::TrieNode(){
    value = "";
    children.resize(SYMBOLS, nullptr);
}