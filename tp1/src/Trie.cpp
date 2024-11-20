#include "../include/Trie.hpp"

/*!
 * @brief       Construtor da classe Trie, inicializa a raiz e o número de bits padrão.
 */
Trie::Trie(){
    root = new TrieNode();
    numBits = 9;
}

/*!
 * @brief       Destrutor da classe Trie, limpa a memória alocada para os nós.
 */
Trie::~Trie(){
    deleteTrie(root);
}

/*!
 * @brief       Deleta recursivamente os nós da Trie para liberar memória.
 * @param       node        Ponteiro para o nó atual da Trie.
 */
void Trie::deleteTrie(TrieNode* node){        
    if (node == nullptr) return;
    
    for (TrieNode* child : node->children) {
        deleteTrie(child);
    }
            
    delete node;       
}

/*!
 * @brief       Ajusta o número de bits usado na codificação.
 * @param       num         Novo número de bits.
 */
void Trie::increaseNumBits(int num){
    numBits = num;
}

/*!
 * @brief       Configura a Trie inicial com base na escolha de modo (codificação ou decodificação).
 * @param       choice      0 para codificação, 1 para decodificação.
 */
void Trie::setUpTrie(int choice){
    if(choice == 0){
        for(int i = 0; i < 256; i++){
            string word = "";
            for(char c: string(1, static_cast<char>(i))){
                string aux = bitset<12>(c).to_string();
                word += aux.substr(12-(this->numBits));
            }
            this->insert(word, to_string(i));
        }
    } else {
        for(int i = 0; i < 256; i++){
            string word = ""; 
            string aux = bitset<12>(i).to_string();
            word += aux.substr(12-(this->numBits)); 
            this->insert(word, string(1, static_cast<char>(i)));
        }
    }
}

/*!
 * @brief       Imprime todas as palavras presentes na Trie.
 * @param       node        Nó atual da Trie.
 * @param       str         Prefixo acumulado da palavra.
 */
void Trie::printEachWord(TrieNode* node, string str){
    for(int i = 0; i < 2; i++){
        if(node->children[i] != nullptr) {
            string temp = str + node->children[i]->value;
            printEachWord(node->children[i], temp);
        }
    }
    if(str != "" && node->id != "-1") cout << str << " " << node->id << endl;
}

/*!
 * @brief       Imprime todos os nós da Trie.
 * @param       node        Nó atual da Trie.
 * @param       level       Nível atual na Trie (para debug).
 */
void Trie::printEachNode(TrieNode* node, int level){
    stack<TrieNode*> stack;
    stack.push(node);
    while(!stack.empty()){
        if(node->children[0] != nullptr){
            stack.push(node->children[0]); 
            cout << node->children[0]->value << " " << node->children[0]->id << endl;
        }
        if(node->children[1] != nullptr){
            stack.push(node->children[1]); 
            cout << node->children[1]->value << " " << node->children[1]->id << endl;
        }
    }
}

/*!
 * @brief       Insere uma nova palavra na Trie.
 * @param       word        Palavra binária a ser inserida.
 * @param       id          Identificador associado à palavra.
 */
void Trie::insert(string word, string id) {
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

/*!
 * @brief       Remove uma palavra da Trie.
 * @param       word        Palavra binária a ser removida.
 */
void Trie::remove(string word){
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

/*!
 * @brief       Imprime a estrutura da Trie.
 * @param       choice      0 para imprimir palavras, 1 para imprimir nós.
 */
void Trie::print(int choice){
    if(choice == 0) printEachWord(root, "");
    else printEachNode(root, 1);
}

/*!
 * @brief       Busca uma palavra binária na Trie.
 * @param       word        Palavra a ser buscada.
 * @return      Par indicando se foi encontrada e seu identificador.
 */
pair<bool, string> Trie::search(string word) {
    TrieNode* node = root; int i = 0;
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
