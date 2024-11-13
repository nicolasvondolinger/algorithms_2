#include "../include/Trie.hpp"
#include "../include/TrieNode.hpp"

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define ff first
#define ss second
#define pb push_back
     
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void setUpMap(map<string, int>& mp){
    string str;
    int count = 0;
    for(char c = 'a'; c <= 'z'; c++){
        str = c;
        mp[str] = count; count++;
    }
}

int main(){

    Trie trie; trie.setUpTrie();
    map<string, int> mp; setUpMap(mp);
    string word; vector<string> words;
    while(cin >> word) words.pb(word);
    
    string p = "", ans1 = "", ans2 = "";
    int count = 26;
    cout << words[0] << endl;
    for(int i = 0; i < words.size(); i++){
        for(int j = 0; j < words[i].size(); j++){
            string c = ""; c += words[i][j];
            if(trie.search(p + c).ff){ 
                p += c;
            } else {
                ans1 += to_string(trie.search(p).ss); ans2 += to_string(mp[p]);
                ans1+= '-'; ans2 += '-';
                trie.insert(p + c); mp[p+c] = count; count++; 
                p = c;
            }
        }
        ans1 += to_string(trie.search(p).ss); ans2 += to_string(mp[p]);      
    }

    cout << ans1 << endl;
    cout << ans2 << endl;

    //trie.print(1);

    return 0;
}