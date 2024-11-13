#include "../include/TrieNode.hpp"

TrieNode::TrieNode(){
    id = -1;
    value = "";
    children.resize(2, nullptr);
}