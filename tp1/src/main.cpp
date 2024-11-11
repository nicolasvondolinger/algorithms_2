#include "../include/Trie.hpp"
#include "../include/TrieNode.hpp"

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define ff first
#define ss second
#define pb push_back
     
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int main(){

    Trie trie;
    // Insert words
    trie.insert("facebook");
    trie.insert("facelook");
    trie.insert("this");
    trie.insert("then");
    trie.insert("there");
    

    // Print inserted words
    trie.print();

    // Check if these words
    // are present or not
    cout << boolalpha;
    cout << trie.search("facebook").second << endl;
    cout << trie.search("facelook").second << endl;
    cout << trie.search("this").second << endl;
    cout << trie.search("face").second << endl;
    cout << trie.search("there").second << endl;

    return 0;
}