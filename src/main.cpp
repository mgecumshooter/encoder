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
int alphPos(wchar_t c, string alph, int cap){
	cout << "\n\t";
	cout << "DEBUG: c - " << c << "\n\t";
	cout << "DEBUG: alph - " << alph << "\n\t";
	cout << "DEBUG: cap - " << cap << endl;
	int pos = -1;
	// check alph
	if (alph == "en" && cap == 1){ // iterate trough cap en alphabet
		for (int i = 0; i < capAlph_en.length(); i++){
			if (c != capAlph_en[i]){
				continue;
			}else if (c == capAlph_en[i]){
				pos = i;
				break;
			}
		}
	}else if(alph == "en"){ // same as previous, but without caps
		for (int i = 0; i < alph_en.length(); i++){
			if (c != alph_en[i]){
				continue;
			}else if (c == alph_en[i]){
				pos = i;
				break;
			}
		}
	}else if (alph == "ru" && cap == 1){ // iterate trough cap ru alphabet
		for (int i = 0; i < capAlph_ru.length(); i++){
			if (c != capAlph_ru[i]){
				continue;
			}else if (c == capAlph_ru[i]){
				pos = i;
				break;
			}
		}
	}else if(alph == "ru"){ // same as previous, but without caps
		for (int i = 0; i < alph_ru.length(); i++){
			if (c != alph_ru[i]){
				continue;
			}else if (c == alph_ru[i]){
				pos = i;
				break;
			}
		}
	}
	return pos;
}

// // This shit takes the key and adjustes it to the lenght of string
// void doKey(string c, string key){
//     while (c.size() != key.size()){
//         if (c.size() > key.size()){
//             key += key;
//         }else if(c.size() < key.size()){
//             key.pop_back();
//         }else {
//             break;
//         }
//     }
// }

// // This shit takes the string and the key and encodes it
// string encode(string word, string key){
//     toLowerCase(word);
//     toLowerCase(key);
//     doKey(word, key);
//     string enc;
//     for (int i = 0; i < word.size(); i++){
//         enc += ALPHABET[(alphPos(word[i]) + alphPos(key[i])) % 27];
//     }
//     return enc;
// }

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

	wchar_t penis = L'а';
	string alph = "ru";
	wcout << "\n" << penis << "\n";
	wcout << isCap(penis, alph) << "\n";
	wcout << alphPos(penis, alph, isCap(penis, alph)) << "\n";
}
