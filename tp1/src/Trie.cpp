#include "../include/Trie.hpp"

Trie::Trie(){
    root = new TrieNode();
}

void Trie::setUpTrie(){
    string str;
    for(char c = 'a'; c <= 'z'; c++){
        str = c;
        this->insert(str);
    }
}

void Trie::printEachWord(TrieNode* node, string str){
    for(int i = 0; i < 2; i++){
        if(node->children[i] != nullptr) {
            string temp = str + node->children[i]->value;
            printEachWord(node->children[i], temp);
        }
    }
    if(str != "" && node->id != -1) cout << str << endl;
}

void Trie::printEachNode(TrieNode* node, int level){
    for(int i = 0; i < 2; i++){
        cout << "LEVEL " << level << endl;
        if(node->children[i] != nullptr) {
            cout << node->children[i]->value << " " << node->children[i]->id << endl;
            printEachNode(node->children[i], level+1);
        }
    }
}

string Trie::stringToBinary(string word){
    string ans = "";
    for(char c: word){
        ans += bitset<8>(c).to_string();
    }
    return ans;
}

void Trie::insert(string word) {
    word = stringToBinary(word);
    TrieNode* node = root; int i = 0;
    while (i < word.size()) {
        int inicial = i, index = (word[i] == '0') ? 0 : 1;
        
        if(node->children[index] == nullptr){
            TrieNode* aux = new TrieNode();
            aux->value = word.substr(i); aux->id = this->insertCount; this->insertCount++;
            node->children[index] = aux;
            return;
        }
        
        int j = 0; string label = node->children[index]->value; 
        
        if(label == word.substr(inicial)) {
            if(node->children[index]->id == -1){
                node->children[index]->id = this->insertCount; this->insertCount++;
                return;
            }
            cout << "Palavra já inserida" << endl;
            return;
        }

        while (i < word.size() && j < label.size() && word[i] == label[j]) {i++; j++;}
        
        if (i == word.size() && j < label.size()) {
            TrieNode* aux = new TrieNode(); aux->value = label.substr(j);
            aux->children = node->children[index]->children; aux->id = node->children[index]->id;

            node->children[index]->value = word.substr(inicial); 
            node->children[index]->id = this->insertCount; this->insertCount++; 
            node->children[index]->children[0] = nullptr; node->children[index]->children[1] = nullptr;
            
            if(label[j] == '0') node->children[index]->children[0] = aux;
            else node->children[index]->children[1] = aux; 

            return;
        } else if(i < word.size() && j < label.size()){    
            if(label[j] == '0'){
                TrieNode* aux = new TrieNode(); aux->value = label.substr(j); 
                aux->children = node->children[index]->children; aux->id = node->children[index]->id; 
                node->children[index]->children[0] = aux;

                TrieNode* aux2 = new TrieNode(); aux2->value = word.substr(i);
                aux2->id = this->insertCount; this->insertCount++;
                node->children[index]->children[1] = aux2;
            }else {
                TrieNode* aux = new TrieNode(); aux->value = label.substr(j); 
                aux->children = node->children[index]->children; aux->id = node->children[index]->id;
                node->children[index]->children[1] = aux;

                TrieNode* aux2 = new TrieNode(); aux2->value = word.substr(i);
                aux2->id = this->insertCount; this->insertCount++;
                node->children[index]->children[0] = aux2;
            }

            node->children[index]->value = label.substr(0, j); node->children[index]->id = -1;
            return;
        } else if(i < word.size() && j == label.size()) node = node->children[index];
    }

}

void Trie::print(int choice){
    if(choice == 0) printEachWord(root, "");
    else printEachNode(root, 1);
}

pair<bool, int> Trie::search(string word) {
    TrieNode* node = root; int i = 0;
    word = stringToBinary(word);
    while (i < word.size()) {
        int index = (word[i] == '0') ? 0 : 1;
        if(node->children[index] == nullptr) return {false, -1};
        
        string label = node->children[index]->value;
        
        int j = 0;
        while (i < word.size() && j < label.size()) {
            if (word[i] != label[j]) return {false, -1};
            i++; j++;
        }
        
        if (j == label.size() && i < word.size()) node = node->children[index];
        else if(j == label.size() && i == word.size()){    
            if(node->children[index]->id != -1) return {true, node->children[index]->id};
            return {false, -1};
        } else return {false, -1};
    }
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