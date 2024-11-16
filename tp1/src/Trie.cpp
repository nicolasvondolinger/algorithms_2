#include "../include/Trie.hpp"

Trie::Trie(){
    root = new TrieNode();
}

Trie::~Trie(){
    deleteTrie(root);
}

void Trie::deleteTrie(TrieNode* node){        
    if (node == nullptr) return;
    
    for (TrieNode* child : node->children) {
        deleteTrie(child);
    }
            
    delete node;       
}

void Trie::setUpTrieEncoding(){
    for(int i = 0; i < 256; i++){
        this->insertEncoding(string(1, static_cast<char>(i)));
    }
}

void Trie::setUpTrieDecoding(){
    for(int i = 0; i < 256; i++){
        this->insertDecoding(to_string(i), string(1, static_cast<char>(i)));
    }
}

void Trie::increaseInsertCount(){
    int numTemp = stoi(this->insertCount); numTemp++; 
    this->insertCount = to_string(numTemp);
}

void Trie::printEachWord(TrieNode* node, string str){
    for(int i = 0; i < 2; i++){
        if(node->children[i] != nullptr) {
            string temp = str + node->children[i]->value;
            printEachWord(node->children[i], temp);
        }
    }
    if(str != "" && node->id != "-1") cout << str << endl;
}

void Trie::printEachNode(TrieNode* node, int level){
    /* stack<TrieNode*> stack;
    stack.push(node);
    while(!stack.empty()){

    } */
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
        ans += bitset<12>(c).to_string();
    }
    return ans;
}

void Trie::insertEncoding(string word) {
    word = stringToBinary(word);
    TrieNode* node = root; int i = 0;
    while (i < word.size()) {
        int inicial = i, index = (word[i] == '0') ? 0 : 1;
        
        if(node->children[index] == nullptr){
            TrieNode* aux = new TrieNode();
            aux->value = word.substr(i); aux->id = this->insertCount; 
            increaseInsertCount();
            node->children[index] = aux;
            return;
        }
        
        int j = 0; string label = node->children[index]->value; 
        
        if(label == word.substr(inicial)) {
            if(node->children[index]->id == "-1"){
                node->children[index]->id = this->insertCount; 
                increaseInsertCount();
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
            node->children[index]->id = this->insertCount; increaseInsertCount(); 
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
                aux2->id = this->insertCount; increaseInsertCount();
                node->children[index]->children[1] = aux2;
            }else {
                TrieNode* aux = new TrieNode(); aux->value = label.substr(j); 
                aux->children = node->children[index]->children; aux->id = node->children[index]->id;
                node->children[index]->children[1] = aux;

                TrieNode* aux2 = new TrieNode(); aux2->value = word.substr(i);
                aux2->id = this->insertCount; increaseInsertCount();
                node->children[index]->children[0] = aux2;
            }

            node->children[index]->value = label.substr(0, j); node->children[index]->id = -1;
            return;
        } else if(i < word.size() && j == label.size()) node = node->children[index];
    }
}

void Trie::insertDecoding(string word, string id){
    word = stringToBinary(word);
    TrieNode* node = root; int i = 0;
    while (i < word.size()) {
        int inicial = i, index = (word[i] == '0') ? 0 : 1;
        
        if(node->children[index] == nullptr){
            TrieNode* aux = new TrieNode();
            aux->value = word.substr(i); aux->id = id;
            node->children[index] = aux;
            return;
        }
        
        int j = 0; string label = node->children[index]->value; 
        
        if(label == word.substr(inicial)) {
            if(node->children[index]->id == "-1"){
                node->children[index]->id = id;
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
            node->children[index]->id = id;  
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
                aux2->id = id; 
                node->children[index]->children[1] = aux2;
            }else {
                TrieNode* aux = new TrieNode(); aux->value = label.substr(j); 
                aux->children = node->children[index]->children; aux->id = node->children[index]->id;
                node->children[index]->children[1] = aux;

                TrieNode* aux2 = new TrieNode(); aux2->value = word.substr(i);
                aux2->id = id; 
                node->children[index]->children[0] = aux2;
            }

            node->children[index]->value = label.substr(0, j); node->children[index]->id = "-1";
            return;
        } else if(i < word.size() && j == label.size()) node = node->children[index];
    }
}

void Trie::remove(string word){
    word = stringToBinary(word);
    TrieNode* node = root; int i = 0;
    while (i < word.size()) {
        int inicial = i, index = (word[i] == '0') ? 0 : 1;
        
        if(node->children[index] == nullptr){
            cout << "Palavra não encontrada." << endl;
            return;
        }
        
        int j = 0; string label = node->children[index]->value; 
        
        if(label == word.substr(inicial)) {
            if(node->children[index]->id == "-1"){
                cout << "Palavra não encontrada." << endl; return;
            }
            node->children[index]->id = "-1";
            if(node->children[index]->children[0] == nullptr && 
            node->children[index]->children[1] == nullptr) node->children[index] = nullptr;
            cout << "Palavra removida" << endl; return;
        }

        while (i < word.size() && j < label.size() && word[i] == label[j]) {i++; j++;}
        
        if (i == word.size() && j < label.size()) {
            cout << "Palavra não encontrada." << endl; return;
        } else if(i < word.size() && j < label.size()){    
            cout << "Palavra não encontrada." << endl; return;
        } else if(i < word.size() && j == label.size()) node = node->children[index];
    }
}

void Trie::print(int choice){
    if(choice == 0) printEachWord(root, "");
    else printEachNode(root, 1);
}

pair<bool, string> Trie::search(string word) {
    TrieNode* node = root; int i = 0;
    word = stringToBinary(word);
    while (i < word.size()) {
        int index = (word[i] == '0') ? 0 : 1;
        if(node->children[index] == nullptr) return {false, "-1"};
        
        string label = node->children[index]->value;
        
        int j = 0;
        while (i < word.size() && j < label.size()) {
            if (word[i] != label[j]) return {false, "-1"};
            i++; j++;
        }
        
        if (j == label.size() && i < word.size()) node = node->children[index];
        else if(j == label.size() && i == word.size()){    
            if(node->children[index]->id != "-1") return {true, node->children[index]->id};
            return {false, "-1"};
        } else return {false, "-1"};
    }
    return {false, "-1"};
}