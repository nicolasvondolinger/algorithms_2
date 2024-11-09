#include "../include/TrieNode.hpp"

TrieNode::TrieNode(bool isEnd){
    children.resize(SYMBOLS, nullptr);
    edgeLabel.resize(SYMBOLS);
}