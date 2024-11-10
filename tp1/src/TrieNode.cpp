#include "../include/TrieNode.hpp"

TrieNode::TrieNode(bool end){
    isEnd = end;
    value = "";
    children.resize(SYMBOLS, nullptr);
}