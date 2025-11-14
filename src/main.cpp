// Include
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
// There's only standart library :sunglasses:
using namespace std;

// All English alphabet
string ALPHABET = "abcdefghijklmnopqrstuvwxyz ";


// This shit converts characters to lowercase
void toLowerCase(string& s) {
    for (char &c : s) {
        if (c >= 'A' && c <= 'Z') {
          	// Convert uppercase to lowercase
          	// by adding 32
            c += 32;
        }
    }
}

// This shit finds character position in alphabet
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

// This shit takes the key and adjustes it to the lenght of string
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

// This shit takes the string and the key and encodes it
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

// This shit doeas the main shit. shit.
int main(){
    string penis, key;
    getline(cin, penis);
    getline(cin, key);
    cout << encode(penis, key);
}