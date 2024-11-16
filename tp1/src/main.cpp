#include "../include/Trie.hpp"
#include "../include/TrieNode.hpp"

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define ff first
#define ss second
#define pb push_back
     
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

Trie encodingTrie, decodingTrie;
int binaryQuant = 9;

void writeBinaryFile(const string& filename, const string& binaryData) {
    ofstream file(filename, std::ios::binary);

    if (!file) {
        cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    // Processa a string binária em blocos de 12 bits
    for (size_t i = 0; i < binaryData.size(); i += 12) {
        string block = binaryData.substr(i, 12); // Pega 12 bits
        int number = stoi(block, nullptr, 2);    // Converte o bloco binário para inteiro
        file.write(reinterpret_cast<const char*>(&number), sizeof(number)); // Escreve no arquivo
    }

    file.close();
    cout << "Codificação em binário salva em 'compressed.bin'" << endl;
}

string lzw_encoding(string& inputLine) {
    string p = "", ans1 = "";
    ll count = pow(2, 12) - 256;  // Número máximo de códigos disponíveis

    for (unsigned int i = 0; i < inputLine.size(); i++) {
        string c = ""; 
        c += inputLine[i];  // Obtém o próximo caractere

        // Se o prefixo p + c já existe na trie
        if (encodingTrie.search(p + c).ff) {
            p += c;  // Expande o prefixo
        } else {
            // Caso contrário, insere o código correspondente e escreve o código binário
            ans1 += bitset<12>(stoi(encodingTrie.search(p).ss)).to_string(); 

            // Verifica se ainda podemos inserir novos códigos
            if (count > 0) {
                encodingTrie.insertEncoding(p + c);  // Insere o novo prefixo
                count--;  // Decrementa o contador
            }

            // Atualiza o prefixo para o caractere atual
            p = c;
        }
    }

    // Adiciona o último prefixo codificado
    ans1 += bitset<12>(stoi(encodingTrie.search(p).ss)).to_string(); 
    return ans1;
}


string lzw_decoding(string& phrase){
    string s = "", ans = "", c = "";
    int count = 256;
    string old = phrase.substr(0, 12); 
    int oldInt = stoi(old, nullptr, 2);
    old = to_string(oldInt);

    ans += decodingTrie.search(old).second;

    for (unsigned int i = 1; i < phrase.size()/12; i++) {
        string atual = phrase.substr(i*12, 12);
        oldInt = stoi(atual, nullptr, 2); atual = to_string(oldInt);
    
        string entry = "";

        if (decodingTrie.search(atual).first) {
            entry = decodingTrie.search(atual).second;
        } else {
            entry = decodingTrie.search(old).second + c;
        }

        ans += entry; c = entry[0];

        decodingTrie.insertDecoding(to_string(count), decodingTrie.search(old).second + c);
        
        count++; old = atual;
    }

    return ans;
}

int main() {
    encodingTrie.setUpTrieEncoding(); 
    decodingTrie.setUpTrieDecoding();

    string inputText, aux, ans = "";

    // Lê todas as linhas da entrada, preservando as quebras de linha
    while (getline(cin, aux)) {
        inputText += aux + '\n'; // Adiciona a quebra de linha explicitamente
    }

    // Remove o último '\n' para evitar problemas no final do texto
    if (!inputText.empty() && inputText.back() == '\n') {
        inputText.pop_back();
    }

    // Codifica a string inteira
    ans = lzw_encoding(inputText); writeBinaryFile("compressed.bin", ans);  // Escreve o arquivo binário

    // Decodifica a string codificada
    ans = lzw_decoding(ans);

    // Escreve o resultado da decodificação em um arquivo de texto
    ofstream outFile("decompressed.txt");  // Abre o arquivo de saída para escrita

    if (outFile) {
        outFile << ans;  // Escreve o conteúdo de ans no arquivo de texto
        outFile.close();  // Fecha o arquivo
    } else cerr << "Erro ao abrir o arquivo para escrita." << endl;
    
    // Imprime mensagem indicando sucesso
    cout << "Decodificação salva em 'decompressed.txt'" << endl;

    return 0;
}
