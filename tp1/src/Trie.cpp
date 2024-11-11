#include "../include/Trie.hpp"

string Trie::strCopy(string str, int index){  
    return str.substr(index, str.size() - index);
}

void Trie::printUntil(TrieNode* node, string str){
    for(int i = 0; i < node->children.size(); i++){
        if(node->children[i] != nullptr) {
            string temp = str + node->children[i]->value;
            //cout << node->children[i]->value << " " << node->children[i]->id << endl;
            printUntil(node->children[i], temp);
        }
    }
    if(str != "" && node->id != -1) cout << str << endl;
}

Trie::Trie(){
    root = new TrieNode();
}


void Trie::insert(string word) {
    words.push_back(word);
    TrieNode* node = root; int i = 0;
    while (i < word.size()) {
        int inicial = i;
        int index = word[i] - 'a';
        
        if(node->children[index] == nullptr){
            TrieNode* aux = new TrieNode();
            aux->value = word; aux->id = this->insertCount; this->insertCount++;
            node->children[index] = aux;
            //cout << "aqui" << word << endl;
            return;
        }
        
        int j = 0; string label = node->children[index]->value; 
        
        if(label == word) return;

        while (i < word.size() && j < label.size() && word[i] == label[j]) {i++; j++;}
        
        if (i == word.size() && j < label.size()) {
            TrieNode* aux = new TrieNode(); 
            string remainingLabel = strCopy(label, j); aux->value = remainingLabel; aux->id = node->children[index]->id;
            node->children[index]->children[remainingLabel[0] - 'a'] = aux;
            node->children[index]->value = word; node->children[index]->id = this->insertCount; this->insertCount++;
            //cout << "aqui" << word << endl;
            return;
        } else if(i < word.size() && j < label.size()){    
            node->children[index]->value = word.substr(inicial, i - inicial); 

            //cout << "aqui2 " <<  word.substr(inicial, i) <<" " << label << endl;

            string remainingLabel = label.substr(j);
            TrieNode* aux = new TrieNode(); aux->value = remainingLabel; aux->id = node->children[index]->id;
            node->children[index]->children[remainingLabel[0] - 'a'] = aux;
            node->children[index]->id = -1;

            string remainingWord = word.substr(i);
            TrieNode* aux2 = new TrieNode(); aux2->value = remainingWord; aux2->id = this->insertCount; this->insertCount++;
            node->children[index]->children[remainingWord[0] - 'a'] = aux2;
            //cout << "aqui" << word << endl;
            return;
        } else if(i < word.size() && j == label.size()) node = node->children[index];
    }
}

void Trie::print(){
    printUntil(root, "");
}

pair<bool, int> Trie::search(string word) {
    int i = 0;
    TrieNode* node = root;

    while (i < word.size() && node->children[word[i] - 'a'] != nullptr) {
        int index = word[i] - 'a';
        string label = node->children[index]->value;
        int j = 0;

        while (i < word.size() && j < label.size()) {
            if (word[i] != label[j]) return {false, -1};
            i++; j++;
        }

        if (j == label.size() && i < word.size()){
            node = node->children[index];
        } else if(j == label.size() && i == word.size()){
            return {true, node->children[index]->id};
        } else return {false, -1};
        
    }
    if(i == word.size()) return {true, node->children[word[i] - 'a']->id};
    return {false, -1};
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
            i++; j++;
        }

        if (j == label.size() && i <= prefix.size()) {
            trav = trav->children[index];
        }
    }

    return i == prefix.size();
}