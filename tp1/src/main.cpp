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

vector<int> bitsUsed(4, 0);

/*!
 * @brief       Writes the binary data into a binary file.
 * @param       binaryData  String containing binary data to be saved.
 * @return      None.
 */
void writeBinaryFile(string& binaryData) {
    ofstream file("compressed.bin", std::ios::binary);

    if (!file) {
        cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    for (size_t i = 0; i < binaryData.size(); i += 16) {
        string block;
        if (i + 16 < binaryData.size()) block = binaryData.substr(i, 16);
        else block = binaryData.substr(i, binaryData.size() - i);
        int16_t number = stoi(block, nullptr, 2);
        file.write(reinterpret_cast<const char*>(&number), sizeof(number));
    }

    file.close();
    cout << "Codificação em binário salva em 'compressed.bin'" << endl;
}

/*!
 * @brief       Encodes the input text using the LZW algorithm.
 * @param       inputText   Vector containing the input text as strings of bits.
 * @param       encodingTrie Trie used for encoding the input.
 * @return      Encoded binary string.
 */
string lzw_encoding(vector<string>& inputText, Trie& encodingTrie) { 
    string p = "", ans = "", ans2 = "", ans3 = "";
    int currentId = 256; // Starts after ASCII codes.
    int tempNumBits = encodingTrie.numBits; 
    int maxId = pow(2, 12);

    for (int i = 0; i < inputText.size(); i++) {
        string c = inputText[i];
        
        if (encodingTrie.search(p + c).first) { 
            p += c; 
        } else {
            string codeStr = encodingTrie.search(p).second; 
            bitset<12> code(stoi(codeStr)); 
            string temp = code.to_string().substr(12 - tempNumBits); 
            ans += temp;

            if (currentId < maxId) {
                encodingTrie.insert(p + c, to_string(currentId));
                currentId++;
                bitsUsed[tempNumBits - 9]++;
                if (currentId > pow(2, tempNumBits) && tempNumBits < 12) {
                    tempNumBits++;
                }
            }
            p = c;
        }
    }

    string codeStr = encodingTrie.search(p).second;
    bitset<12> code(stoi(codeStr)); 
    ans += code.to_string().substr(12 - tempNumBits); 
    bitsUsed[tempNumBits - 9]++;
    return ans;
}

/*!
 * @brief       Decodes a binary string using the LZW algorithm.
 * @param       phrase       Encoded binary string.
 * @param       decodingTrie Trie used for decoding.
 * @return      Decoded text.
 */
string lzw_decoding(string& phrase, Trie& decodingTrie) {
    string ans = "", c = ""; 
    int currentId = 256;
    int bitIndex = 0; 
    if (bitsUsed[0] == 0) bitIndex = 3;
    int numBits = (bitIndex == 0) ? 9 : 12;
    bitsUsed[bitIndex]--;

    string old = phrase.substr(0, numBits); 
    phrase = phrase.substr(numBits);
    string oldStr = decodingTrie.search(old).second;
    if (oldStr.empty()) throw runtime_error("Erro: Código inicial não encontrado na Trie.");
    ans += oldStr;
    c = oldStr[0];

    while (!phrase.empty()) {
        while (bitsUsed[bitIndex] == 0) {
            bitIndex++;
            numBits = (bitIndex == 1) ? 10 : (bitIndex == 2) ? 11 : 12;
        }

        if (phrase.size() < numBits) throw runtime_error("Erro: Número de bits insuficiente na string de entrada.");
        string atual = phrase.substr(0, numBits);
        phrase = phrase.substr(numBits);

        string entry = decodingTrie.search(atual).first ? decodingTrie.search(atual).second : oldStr + c;
        ans += entry;

        if (currentId < pow(2, 12)) {
            string aux = bitset<12>(currentId).to_string().substr(12 - numBits);
            bitsUsed[bitIndex]--;
            decodingTrie.insert(aux, oldStr + entry[0]);
            currentId++;
        }

        oldStr = entry;
        c = entry[0];
    }

    return ans;
}

/*!
 * @brief       Saves compression statistics to a CSV file.
 * @param       inputFile      Name of the input file.
 * @param       outputFile     Name of the output file.
 * @param       bitsUsedCopy   Vector of bits used for encoding.
 * @param       dictionarySize Size of the encoding dictionary.
 * @param       compressionRatio Compression ratio achieved.
 * @param       executionTime  Total time taken for encoding and decoding.
 * @return      None.
 */
void saveStatsToCSV(const string& inputFile, const string& outputFile, const vector<int>& bitsUsedCopy, 
                    int dictionarySize, double compressionRatio, double executionTime) {
    ofstream csvFile("stats.csv", ios::app);

    if (!csvFile) {
        cerr << "Erro ao criar o arquivo CSV de estatísticas." << endl;
        return;
    }

    csvFile << fixed << setprecision(6); 
    csvFile << inputFile << "," << outputFile << ","
            << compressionRatio << "," 
            << executionTime << ","
            << dictionarySize << ","
            << bitsUsedCopy[0] << ","
            << bitsUsedCopy[1] << ","
            << bitsUsedCopy[2] << ","
            << bitsUsedCopy[3] << "\n";

    csvFile.close();
    cout << "Estatísticas salvas no arquivo 'stats.csv'" << endl;
}

int main(int argc, char *argv[]) {
    Trie encodingTrie, decodingTrie;
    string inputFile;
    bool verboseMode = false, statsMode = false;

    if (argc < 2) {
        cerr << "Erro: Caminho do arquivo de entrada é obrigatório." << endl;
        return 1; 
    }

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-v") {
            verboseMode = true;
        } else if (arg == "-s") {
            statsMode = true;
        } else if (arg[0] == '-') { // Caso de flag desconhecida
            cerr << "Erro: Flag desconhecida '" << arg << "'." << endl;
            return 1;
        } else {
            inputFile = arg; // Assume que é o arquivo de entrada
        }
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
    for (auto c : inputText) {
        temp.push_back(bitset<8>(c).to_string());
    }

    auto start = chrono::high_resolution_clock::now(); // Tempo inicial

    ans = lzw_encoding(temp, encodingTrie);
    vector<int> bitsUsedCopy = bitsUsed;
    writeBinaryFile(ans);
    int ansSize = ans.size();

    auto endEncoding = chrono::high_resolution_clock::now();
    string decoded = lzw_decoding(ans, decodingTrie);

    auto endDecoding = chrono::high_resolution_clock::now(); // Tempo final

    ofstream outFile("decompressed." + type);
    if (outFile) {
        outFile << decoded;
        outFile.close();
    } else {
        cerr << "Erro ao abrir o arquivo para escrita." << endl;
    }

    // Cálculo das estatísticas
    double originalSize = inputText.size() * 8;  // Tamanho em bits
    double compressedSize = ansSize;
    double compressionRatio = (originalSize - compressedSize) / originalSize;

    int dictionarySize = encodingTrie.numBits; // Aproximação para o tamanho do dicionário
    double executionTime = chrono::duration<double>(endDecoding - start).count();

    if(statsMode) saveStatsToCSV(inputFile, "decompressed." + type, bitsUsedCopy, accumulate(bitsUsedCopy.begin(), bitsUsedCopy.end(), 0), compressionRatio, executionTime);

    cout << "Decodificação salva em 'decompressed." << type << "'" << endl;
    return 0;
}
