#include "../include/Trie.hpp"

string Trie::strCopy(string str, int index){
    
    return str.substr(index, str.size() - index);
}

void Trie::printUntil(TrieNode* node, string str){
    for(int i = 0; i < node->children.size(); i++){
        if(node->children[i] != nullptr) {
            string temp = str + node->children[i]->value;
            printUntil(node->children[i], temp);
        }
    }
    if(str != "") cout << str << endl;
}

Trie::Trie(){
    root = new TrieNode();
}

void Trie::insert(string word) {
    TrieNode* trav = root; int i = 0;

    while (i < word.size()) {
        int index = word[i] - 'a';
        
        if(trav->children[index] == nullptr){
            trav->children[index] = new TrieNode();
            trav->children[index]->value = word;
            return;
        }
        
        int j = 0;
        string label = trav->children[index]->value; if(label == word) return;

        while (j < label.size() && i < word.size() && label[j] == word[i]) {
            i++; j++;
        }
        
        if(trav->children[word.substr(i)[0] - 'a'] != nullptr){
            trav = trav->children[word.substr(i)[0] - 'a'];
            continue;
        }
        if (i == word.size() && j < label.size()) {
            string remainingLabel = label.substr(j);
            trav->children[index]->value = word;
            TrieNode* aux = new TrieNode();
            aux->value = remainingLabel;
            trav->children[index]->children[remainingLabel[0] - 'a'] = aux;
            return;
        } else if(i < word.size() && j < label.size()){
            trav->children[index]->value = word.substr(0, i);
                
            string remainingLabel = label.substr(j);
            TrieNode* aux = new TrieNode(); aux->value = remainingLabel;
            trav->children[index]->children[remainingLabel[0] - 'a'] = aux;

            string remainingWord = word.substr(i);
            TrieNode* aux2 = new TrieNode(); aux2->value = remainingWord;
            trav->children[index]->children[remainingWord[0] - 'a'] = aux2;
            return;
        }
    }
    
    // Inserção final se não houver rótulos conflitantes
    if (i < word.size()) {
        TrieNode* temp = new TrieNode();
        temp->value = strCopy(word, i);
        trav->children[word[i] - 'a'] = temp;
    } 
}

void Trie::print(){
    printUntil(root, "");
}

bool Trie::search(string word) {
    int i = 0;
    TrieNode* trav = root;

    while (i < word.size() && trav->children[word[i] - 'a'] != nullptr) {
        int index = word[i] - 'a';
        string label = trav->children[index]->value;
        int j = 0;

        while (i < word.size() && j < label.size()) {
            if (word[i] != label[j]) return false;
            i++;
            j++;
        }

        if (j == label.size() && i < word.size()) {
            trav = trav->children[index];
        } else {
            return false;
        }
    }

    return i == word.size();
}

bool Trie::startsWith(string prefix) {
    int i = 0;
    TrieNode* trav = root;

    while (i < prefix.size() && !trav->children[prefix[i] - 'a']->value.empty()) {
        int index = prefix[i] - 'a';
        string label = trav->children[index]->value;
        int j = 0;

        while (i < prefix.size() && j < label.size()) {
            if (prefix[i] != label[j]) return false;
            i++;
            j++;
        }

        if (j == label.size() && i <= prefix.size()) {
            trav = trav->children[index];
        }
    }

    return i == prefix.size(); // Correção
}