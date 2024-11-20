#include "../include/Trie.hpp"
#include "../include/TrieNode.hpp"

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define ff first
#define ss second
#define pb push_back
     
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

string type = "";

vector<int> bitsUsed (4, 0);

void writeBinaryFile(string& binaryData) {
    ofstream file("compressed.bin", std::ios::binary);

    if (!file) {
        cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    for (size_t i = 0; i < binaryData.size(); i += 16) {
        string block;
        if(i+16 < binaryData.size()) block = binaryData.substr(i, 16);
        else block = binaryData.substr(i, binaryData.size()-i);
        int16_t number = stoi(block, nullptr, 2);
        file.write(reinterpret_cast<const char*>(&number), sizeof(number));    
    }

    file.close();
    cout << "Codificação em binário salva em 'compressed.bin'" << endl;
}

string lzw_encoding(vector<string>& inputText, Trie& encodingTrie) { 
    string p = "", ans = "", ans2 = "", ans3 = "";
    int currentId = 256; // Começa após os 256 códigos ASCII.
    int tempNumBits = encodingTrie.numBits; // Número inicial de bits (8 ou 12).
    
    int maxId = pow(2, 12); // Limite máximo de IDs (12 bits).

    for (int i = 0; i < inputText.size(); i++) {
        string c = inputText[i]; // Converte o caractere atual para 8 bits binários.
        
        // Verifica se a combinação p + c já está na árvore trie.
        if (encodingTrie.search(p + c).first) { 
            p += c; // Atualiza o prefixo.
        } else {
            // Obtém o código binário do prefixo p existente na trie.
            string codeStr = encodingTrie.search(p).second; 
            bitset<12> code(stoi(codeStr)); 
            string temp = code.to_string().substr(12 - tempNumBits); // Ajusta para o número atual de bits.

            ans += temp; // Adiciona o código binário à resposta.
            ans3 += codeStr + " "; // Adiciona o código inteiro à string de depuração.

            // Se o ID atual está abaixo do limite máximo, insere a nova sequência na trie.
            if (currentId < maxId) {
                encodingTrie.insert(p + c, to_string(currentId)); // Insere p+c na trie com o novo ID.
                currentId++; // Incrementa o ID atual.
                if(tempNumBits == 9)
                    bitsUsed[0]++;
                else if(tempNumBits == 10)
                    bitsUsed[1]++;
                else if (tempNumBits == 11)
                    bitsUsed[2]++;
                else if (tempNumBits == 12)
                    bitsUsed[3]++;
                // Ajusta o número de bits dinamicamente, se necessário.
                if (currentId > pow(2, tempNumBits) && tempNumBits < 12) {
                    tempNumBits++;
                }
            }

            p = c; // Atualiza p para o caractere atual.
        }
    }

    // Adiciona o código do último prefixo p.
    string codeStr = encodingTrie.search(p).second;
    bitset<12> code(stoi(codeStr)); 
    ans += code.to_string().substr(12 - tempNumBits); 
    ans3 += codeStr + " "; // Adiciona o último código inteiro à string de depuração.
    ans2 += p; // Opcional: Adiciona os últimos caracteres codificados para exibição.

    if(tempNumBits == 9) bitsUsed[0]++;
    else if(tempNumBits == 10) bitsUsed[1]++;
    else if (tempNumBits == 11) bitsUsed[2]++;
    else if (tempNumBits == 12) bitsUsed[3]++;

    return ans; // Retorna a string codificada em binário.
}

string lzw_decoding(string& phrase, Trie& decodingTrie) {
    string ans = "", c = ""; // String decodificada e primeiro caractere.
    int currentId = 256;     // Próximo ID disponível no dicionário.

    // Obtém o primeiro código usando o número inicial de bits (bitsUsed[0]).
    int bitIndex = 0; // Índice no vetor bitsUsed.
    if(bitsUsed[0] == 0) bitIndex = 3;
    int numBits; 
    if(bitIndex == 0) numBits = 9;
    else numBits = 12;
    bitsUsed[bitIndex]--; // Número de bits inicial.
    string old = phrase.substr(0, numBits); 
    phrase = phrase.substr(numBits); // Remove o prefixo processado da frase.

    // Procura o código na Trie. Se não encontrar, o dado inicial está incorreto.
    string oldStr = decodingTrie.search(old).second;
    if (oldStr.empty()) throw runtime_error("Erro: Código inicial não encontrado na Trie.");
    
    ans += oldStr; // Adiciona a string decodificada ao resultado.
    c = oldStr[0]; // Define o primeiro caractere para referência.

    // Processa o restante da frase.
    while (!phrase.empty()) {

        // Incrementa o índice no vetor bitsUsed e ajusta o número de bits atual.
        while(bitsUsed[bitIndex] == 0) {
            bitIndex++;
            if(bitIndex == 1) numBits = 10;
            else if(bitIndex == 2) numBits = 11;
            else numBits = 12;
        }

        // Obtém o próximo código da entrada.
        if (phrase.size() < numBits) {
            throw runtime_error("Erro: Número de bits insuficiente na string de entrada.");
        }

        string atual = phrase.substr(0, numBits);
        phrase = phrase.substr(numBits); // Remove o prefixo processado.

        string entry = ""; // Sequência correspondente ao código atual.

        // Verifica se o código existe na Trie.
        if (decodingTrie.search(atual).first) {
            entry = decodingTrie.search(atual).second; // Recupera a sequência.
        } else {
            // Caso especial: código não encontrado, segue a regra do LZW.
            entry = oldStr + c;
        }

        ans += entry; // Adiciona a sequência decodificada ao resultado.

        // Atualiza o dicionário com a nova entrada.
        if (currentId < pow(2, 12)) { // Garante que não ultrapassamos 12 bits.
            string aux = bitset<12>(currentId).to_string(); // Converte ID atual para binário.
            aux = aux.substr(12 - numBits); // Ajusta para o número atual de bits.
            bitsUsed[bitIndex]--;
            decodingTrie.insert(aux, oldStr + entry[0]); // Insere o novo código.
            currentId++; // Incrementa o próximo ID disponível.
        }

        // Atualiza oldStr e c para a próxima iteração.
        oldStr = entry;
        c = entry[0];
    }

    return ans; // Retorna a string decodificada.
}

int main(int argc, char *argv[]) {
    Trie encodingTrie, decodingTrie; 
    string inputFile;
    bool verboseMode = false;

    if (argc < 2) {
        cerr << "Erro: Caminho do arquivo de entrada é obrigatório." << endl;
        return 1; 
    }

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-v") verboseMode = true;
        else inputFile = arg;
    }

    if (inputFile.empty()) {
        cerr << "Erro: Caminho do arquivo de entrada é obrigatório." << endl;
        return 1; 
    }

    if (!verboseMode) {
        encodingTrie.increaseNumBits(12);
        decodingTrie.increaseNumBits(12);
    }

    encodingTrie.setUpTrie(0); 
    decodingTrie.setUpTrie(1); 

    string type;
    for (int i = inputFile.size() - 1; i >= 0; i--) {
        if (inputFile[i] == '.') break;
        type += inputFile[i];
    }
    reverse(type.begin(), type.end());

    ifstream inFile(inputFile);
    if (!inFile) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    string inputText, aux, ans = "";

    while (getline(inFile, aux)) inputText += aux + '\n';
    if (!inputText.empty() && inputText.back() == '\n') inputText.pop_back();

    vector<string> temp;
    if (encodingTrie.numBits == 9) {
        for (auto c : inputText) {
            temp.push_back(bitset<9>(c).to_string());
        }
    } else {
        for (auto c : inputText) {
            temp.push_back(bitset<12>(c).to_string());
        }
    }

    ans = lzw_encoding(temp, encodingTrie); writeBinaryFile(ans);
    
    ans = lzw_decoding(ans, decodingTrie);

    ofstream outFile("decompressed." + type);
    if (outFile) {
        outFile << ans;
        outFile.close();
    } else {
        cerr << "Erro ao abrir o arquivo para escrita." << endl;
    }

    cout << "Decodificação salva em 'decompressed." << type << "'" << endl; 
    return 0;
}