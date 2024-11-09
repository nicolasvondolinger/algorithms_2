#include "../include/Trie.hpp"
#include "../include/TrieNode.hpp"

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define ff first
#define ss second
#define pb push_back
     
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int main(){

    cout << 1 << endl;

    Trie trie;
    // Insert words
    trie.insert("facebook");
    trie.insert("face");
    trie.insert("this");
    trie.insert("there");
    trie.insert("then");

    // Print inserted words
    trie.print();

    // Check if these words
    // are present or not
    cout << boolalpha;
    cout << trie.search("there") << endl;
    cout << trie.search("therein") << endl;
    cout << trie.startsWith("th") << endl;
    cout << trie.startsWith("fab") << endl;

    return 0;
}