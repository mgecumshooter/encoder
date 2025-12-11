// Include
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <cmath>
#include <locale>
// #include <codecvt>
// There's only standart library :sunglasses:
using namespace std;

// All English alphabet
wstring alph_en = L"abcdefghijklmnopqrstuvwxyz ";
wstring capAlph_en = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ " ;
wstring alph_ru = L"абвгдежзтклмнопрстуфхйчшщыэюя ";
wstring capAlph_ru = L"АБВГДЕЖЗТКЛМНОПРСТУФХЙЧШЩЫЕЭЮЯ ";

bool isCap (wchar_t c, string alph){
	bool cap;
	if (c != ' '){
		if (alph == "en"){
			for(wchar_t x: capAlph_en){
				if(c == x){
					cap = true;
					break;
				}else {
					cap = false;
				}
			}
		}else if (alph == "ru"){
			for(wchar_t x: capAlph_ru){
				if(c == x){
					cap = true;
					break;
				}else {
					cap = false;
				}
			}
		}
	}
	return cap;
}


// takes character, alphabet and caps, then finds character position in the specified alphabet
int alphPos(wchar_t c, string alph){
	cout << "\n\t";
	cout << "DEBUG: c - " << c << "\n\t";
	cout << "DEBUG: alph - " << alph << "\n\t";
	int pos = -1;
	// check alph
	if (alph == "en"){ // iterate trough cap en alphabet
		for (int i = 0; i < capAlph_en.length(); i++){
			if (i == capAlph_en.length()-1 && c != capAlph_en[i]){
				for (int b = 0; b < alph_en.length(); b++){
					if (c != alph_en[b]){
						continue;
					}else if (c == alph_en[b]){
						pos = b;
						break;
					}
				}
			}else if (c == capAlph_en[i]){
				pos = i;
				break;
			}else if (c != capAlph_en[i]){
				continue;
			}
		}
	}

	if (alph == "ru"){ // iterate trough cap ru alphabet
		for (int i = 0; i < capAlph_ru.length(); i++){
			if (i == capAlph_ru.length()-1 && c != capAlph_ru[i]){
				for (int b = 0; b < alph_ru.length(); b++){
					if (c != alph_ru[b]){
						continue;
					}else if (c == alph_ru[b]){
						pos = b;
						break;
					}
				}
			}else if (c == capAlph_ru[i]){
				pos = i;
				break;
			}else if (c != capAlph_ru[i]){
				continue;
			}
		}
	}
	return pos;
}

// // This shit takes the key and adjustes it to the lenght of string
void doKey(wstring c, wstring& key){
    while (c.length() != key.length()){
        if (c.length() > key.length()){
            key += key;
        }else if(c.length() < key.length()){
            key.pop_back();
        }else {
            break;
        }
    }
}

// // This shit takes the string and the key and encodes it
wstring encode(wstring word, wstring key, string alph){
    doKey(word, key);
    wstring enc;
	if (alph == "en"){
		for (int i = 0; i < word.length(); i++){
			if (isCap(word[i], alph)){
				enc += capAlph_en[(alphPos(word[i], alph) + alphPos(key[i], alph)) % 27];
			}
		}
	}
    return enc;
}

// // This Shit takes encoded string and dekodes it
// string decode(string word, string key){
//     string dec;
//     toLowerCase(word);
//     toLowerCase(key);
//     doKey(word, key);
//     for (int i = 0; i != word.length(); i++){
//         if (alphPos(word[i]) >= alphPos(key[i])){
//             dec += ALPHABET[(alphPos(word[i]) - alphPos(key[i])) % 27];
//         } else {
//             dec += ALPHABET[(27 - (alphPos(key[i]) - alphPos(word[i]))) % 27];
//         }
//     }
//     return dec;
// }

// void encode (char c, char key){

// }

// string alph(char c){
//     if (c == ' '){
//         return "en";
//     }else {
//         for (char b: ALPHABET){
//             if (b == c){
//                 return "en";
//             }else if (alphPos(c, "en") >= 26 && c != b){
//                 return "ru";
//             }
//         }
//     }
// }

// This shit does the main shit. shit.
int main(){
	locale::global(locale("en_US.UTF-8"));
    wcin.imbue(locale());
    wcout.imbue(locale());

	cout << alphPos(L'б', "ru") << endl;
}
