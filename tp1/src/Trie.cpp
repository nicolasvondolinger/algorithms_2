#include "../include/Trie.hpp"

string Trie::strCopy(string str, int index){
    return str.substr(index, str.size());
}

void Trie::printUntil(TrieNode* node, string str){
    if(node->isEnd) cout << str << endl;

    for(int i = 0; i < node->edgeLabel.size(); i++){
        if(!node->edgeLabel[i].empty()){
            string temp = str + node->edgeLabel[i];
            printUntil(node->children[i], temp);
        }
    }
}

Trie::Trie(){
    CASE = 'a';
    root = new TrieNode(false);
}

void Trie::insert(string word){
    TrieNode* trav = root;
    int i = 0;

    while (i < word.size() && !trav->edgeLabel[word[i] - CASE].empty()){
        int index = word[i] - CASE;
        int j = 0;
        string label = trav->edgeLabel[index];
        while(j < label.size() && i < word.size() && label[j] == word[i]){
            i++, j++;
        }
        if(j == label.size()) trav = trav->children[index];
        else {
            if(i == word.size()){
                TrieNode* existingChild = trav->children[index];
                TrieNode* newChild = new TrieNode(true);
                string remainingLabel = label.substr(j);
                trav->children[index] = newChild;
                newChild->children[remainingLabel[0] - CASE] = existingChild;
                newChild->edgeLabel[remainingLabel[0] - CASE] = remainingLabel;
            } else {
                string remainingLabel = label.substr(j);
                TrieNode* newChild = new TrieNode(false);
                string remainingWord = word.substr(i);
                TrieNode* temp = trav->children[index];
                trav->children[index] = newChild;
                newChild->edgeLabel[remainingLabel[0] - CASE] = remainingLabel;
                newChild->children[remainingLabel[0] - CASE] = temp;
                newChild->edgeLabel[remainingWord[0] - CASE] = remainingWord;
                newChild->children[remainingWord[0] - CASE] = new TrieNode(true);
            }
            return;
        }
        if(i < word.size()){
            trav->edgeLabel[word[i] - CASE] = strCopy(word, i);
            trav->children[word[i] - CASE] = new TrieNode(true);
        } else {
            trav->isEnd = true;
        }
    }
    
}

void Trie::print(){
    printUntil(root, "");
}

bool Trie::search(string word){
    int i = 0; TrieNode* trav = root;

    while (i < word.size() && !trav->edgeLabel[word[i] - CASE].empty())
    {
        int index = word[i] - CASE;
        string label = trav->edgeLabel[index];
        int j = 0;
        while(i < word.size() && j < label.size()){
            if(word[i] != label[j]) return false;
            i++; j++;
        }

        if(j == label.size() && i <= word.size()){
            trav = trav->children[index];
        } else return false;

        return i == word.size() && trav->isEnd;
    }
}

bool Trie::startsWith(string prefix){
    int i = 0; TrieNode* trav = root;
    while(i < prefix.size() && trav->edgeLabel[prefix[i] - CASE].empty()){
        int index = prefix[i] - CASE;
        string label = trav->edgeLabel[index];
        int j = 0;
        while(i < prefix.size() && j < label.size()){
            if(prefix[i] != label[j]) return false;

            i++; j++;
        }

        if(j == label.size() && i <= prefix.size()){
            trav = trav-> children[index];
        } else {
            return true;
        }
    }
    return i == prefix.size();
}