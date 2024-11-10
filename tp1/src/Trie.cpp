#include "../include/Trie.hpp"

string Trie::strCopy(string str, int index){
    
    return str.substr(index, str.size() - index);
}

void Trie::printUntil(TrieNode* node, string str){
    if(node->isEnd){
        cout << str << endl;
        return;
    }

    for(int i = 0; i < node->children.size(); i++){
        if(!node->children[i]->value.empty()){
            string temp = str + node->children[i]->value;
            printUntil(node->children[i], temp);
        }
    }
}

Trie::Trie(){
    CASE = 'a';
    root = new TrieNode(false);
}

void Trie::insert(string word) {
    TrieNode* trav = root;
    int i = 0;

    while (i < word.size() && !trav->children[word[i] - CASE]->value.empty()) {
        int index = word[i] - CASE;
        int j = 0;
        string label = trav->children[index]->value;
        cout << i << " " << index <<  " " << word << " " << label <<  endl;

        // Avança até onde os caracteres coincidem
        while (j < label.size() && i < word.size() && label[j] == word[i]) {
            i++;
            j++;
        }
        
        if (j == label.size()) {
            // Se todo o rótulo coincide, mova-se para o próximo nó filho
            trav = trav->children[index];
            continue;
        } else {
            // Divisão da aresta
            if (i == word.size()) {
                // Caso em que a palavra terminou, mas o rótulo ainda tem partes
                TrieNode* existingChild = trav->children[index];
                TrieNode* newChild = new TrieNode(true);
                trav->children[index] = newChild;

                string remainingLabel = label.substr(j);
                
                newChild->children[remainingLabel[0] - CASE] = existingChild;
                newChild->children[remainingLabel[0] - CASE]->value = remainingLabel;
            } else {
                // Caso em que tanto a palavra quanto o rótulo ainda têm partes restantes
                string remainingLabel = label.substr(j);
                string remainingWord = word.substr(i);
                //Pega as duas substrings
                TrieNode* newChild = new TrieNode(false);
                TrieNode* temp = trav->children[index];
                trav->children[index] = newChild;
                newChild->children[remainingLabel[0] - CASE]->value = remainingLabel;
                newChild->children[remainingLabel[0] - CASE] = temp;
                newChild->children[remainingWord[0] - CASE]->value = remainingWord;
                newChild->children[remainingWord[0] - CASE] = new TrieNode(true);
            }
            return;
        }
    }

    // Inserção final se não houver rótulos conflitantes
    if (i < word.size()) {
        trav->children[word[i] - CASE]->value = strCopy(word, i);
        trav->children[word[i] - CASE] = new TrieNode(true);
    } else {
        trav->isEnd = true;
    }
}

void Trie::print(){
    printUntil(root, "");
}

bool Trie::search(string word) {
    int i = 0;
    TrieNode* trav = root;

    while (i < word.size() && !trav->children[word[i] - CASE]->value.empty()) {
        int index = word[i] - CASE;
        string label = trav->children[index]->value;
        int j = 0;

        while (i < word.size() && j < label.size()) {
            if (word[i] != label[j]) return false;
            i++;
            j++;
        }

        if (j == label.size() && i <= word.size()) {
            trav = trav->children[index];
        } else {
            return false;
        }
    }

    return i == word.size() && trav->isEnd;
}

bool Trie::startsWith(string prefix) {
    int i = 0;
    TrieNode* trav = root;

    while (i < prefix.size() && !trav->children[prefix[i] - CASE]->value.empty()) {
        int index = prefix[i] - CASE;
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