#include <iostream>
#include <string>
#include <sstream>
#include <stack>
using namespace std;

string ALPHABET = "abcdefghijklmnopqrstuvwxyz ";

void toLowerCase(string& s) {
    for (char &c : s) {
        if (c >= 'A' && c <= 'Z') {
          	// Convert uppercase to lowercase
          	// by adding 32
            c += 32;
        }
    }
}

int alphPos (char c){
    int pos;

    for (int i = 0; i <= ALPHABET.size(); i++){
        if (c != ALPHABET[i]){
            continue;
        }else {
            pos = i;
            break;
        }
    }
    return pos;
}

void doKey(string c, string& key){
    while (c.size() != key.size()){
        if (c.size() > key.size()){
            key += key;
        }else if(c.size() < key.size()){
            key.pop_back();
        }else {
            break;
        }
    }
}
string encode(string word, string key){
    toLowerCase(word);
    toLowerCase(key);
    doKey(word, key);
    string enc = "";
    for (int i = 0; i < word.size(); i++){
        enc += ALPHABET[(alphPos(word[i]) + alphPos(key[i])) % 26];
    }
    return enc;
}

int main(){
    string penis, key;
    getline(cin, penis);
    getline(cin, key);
    cout << encode(penis, key);
}