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
wstring alph_ru = L"абвгдежзийклмнопрстуфхцчшщъыьэюя ";
wstring capAlph_ru = L"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ ";

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
	}else {
		cap = false;
	}
	return cap;
}


// takes character, alphabet and caps, then finds character position in the specified alphabet
int alphPos(wchar_t c, string alph){
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
	wcout << "\n\t" << word << "\n";
	wcout << "\n\t" << key << "\n";
	cout << "\n\t" << alph << "\n";
	if (alph == "en"){
		for (int i = 0; i < word.length(); i++){
			if (isCap(word[i], alph)){
				enc += capAlph_en[(alphPos(word[i], alph) + alphPos(key[i], alph)) % 27];
			}else if (!isCap(word[i], alph)){
				enc += alph_en[(alphPos(word[i], alph) + alphPos(key[i], alph)) % 27];
			}
		}
	}else if (alph == "ru"){
		for (int i = 0; i <= word.length(); i++){
			if (isCap(word[i], alph) == true){
				enc += capAlph_ru[(alphPos(word[i], alph) + alphPos(key[i], alph)) % 33];
			}else if (isCap(word[i], alph) == false){
				enc += alph_ru[(alphPos(word[i], alph) + alphPos(key[i], alph)) % 33];
			}
		}
	}
    return enc;
}

wstring decode(wstring word, wstring key, string alph){
    doKey(word, key);
    wstring dec;
	if (alph == "en"){
		for (int i = 0; i != word.length(); i++){
			if (alphPos(word[i], alph) >= alphPos(key[i], alph)){
				if (isCap(word[i], alph)){
					dec += capAlph_en[(alphPos(word[i], alph) - alphPos(key[i], alph)) % 27];
				}else if (!isCap(word[i], alph)){
					dec += alph_en[(alphPos(word[i], alph) - alphPos(key[i], alph)) % 27];
				}
			}else {
				if (isCap(word[i], alph)){
					dec += capAlph_en[(27 - alphPos(word[i], alph) - alphPos(key[i], alph)) % 27];
				}else if (!isCap(word[i], alph)){
					dec += alph_en[(27 - alphPos(word[i], alph) - alphPos(key[i], alph)) % 27];
				}
			}
		}
	}else if (alph == "ru"){
		for (int i = 0; i != word.length(); i++){
			if (alphPos(word[i], alph) >= alphPos(key[i], alph)){
				if (isCap(word[i], alph) == true){
					dec += capAlph_ru[(alphPos(word[i], alph) - alphPos(key[i], alph)) % 33];
				}else if (isCap(word[i], alph) == false){
					dec += alph_ru[(alphPos(word[i], alph) - alphPos(key[i], alph)) % 33];
				}
			}else {
				if (isCap(word[i], alph) == true){
					dec += capAlph_ru[(33 - alphPos(word[i], alph) - alphPos(key[i], alph)) % 33];
				}else if (isCap(word[i], alph) == false){
					dec += alph_ru[(33 - alphPos(word[i], alph) - alphPos(key[i], alph)) % 33];
				}
			}
		}
	}
    return dec;
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
	locale::global(locale("ru_RU.UTF-8"));
    wcin.imbue(locale());
    wcout.imbue(locale());

	string alphb = "ru";
	wstring word = L"пенис";
	wstring key = L"хуй";
	wstring penis = encode(word, key, alphb);
	wcout << encode(word, key, alphb) << endl;
	wcout << decode(penis , key, alphb) << endl;
}
