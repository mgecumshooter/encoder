// Include
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <cmath>
#include <locale>
#include <fstream>
#include <codecvt>
// There's only standart library :sunglasses:
using namespace std;

// All alphabet
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


// takes character, alphabet, then finds character position in the specified alphabet
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
	if (alph == "en"){
		for (int i = 0; i < word.length(); i++){
			if (alphPos(word[i], alph) == -1){
				enc += word[i];
			}else if (isCap(word[i], alph)){
				enc += capAlph_en[(alphPos(word[i], alph) + alphPos(key[i], alph)) % 27];
			}else if (!isCap(word[i], alph)){
				enc += alph_en[(alphPos(word[i], alph) + alphPos(key[i], alph)) % 27];
			}
		}
	}else if (alph == "ru"){
		for (int i = 0; i < word.length(); i++){
			if (alphPos(word[i], alph) == -1){
				enc += word[i];
			}else if (isCap(word[i], alph) == true){
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
			if (alphPos(word[i], alph) == -1){
				dec += word[i];
			}else if (alphPos(word[i], alph) >= alphPos(key[i], alph)){
				if (isCap(word[i], alph)){
					dec += capAlph_en[(alphPos(word[i], alph) - alphPos(key[i], alph)) % 27];
				}else if (!isCap(word[i], alph)){
					dec += alph_en[(alphPos(word[i], alph) - alphPos(key[i], alph)) % 27];
				}
			}else if (alphPos(word[i], alph) < alphPos(key[i], alph)){
				if (isCap(word[i], alph)){
					dec += capAlph_en[(27 - (alphPos(key[i], alph) - alphPos(word[i], alph))) % 27];
				}else if (!isCap(word[i], alph)){
					dec += alph_en[(27 - (alphPos(key[i], alph) - alphPos(word[i], alph))) % 27];
				}
			}
		}
	}else if (alph == "ru"){
		for (int i = 0; i != word.length(); i++){
			if (alphPos(word[i], alph) == -1){
				dec += word[i];
			}else if (alphPos(word[i], alph) >= alphPos(key[i], alph)){
				if (isCap(word[i], alph) == true){
					dec += capAlph_ru[(alphPos(word[i], alph) - alphPos(key[i], alph)) % 33];
				}else if (isCap(word[i], alph) == false){
					dec += alph_ru[(alphPos(word[i], alph) - alphPos(key[i], alph)) % 33];
				}
			}else if(alphPos(word[i], alph) < alphPos(key[i], alph)){
				if (isCap(word[i], alph) == true){
					dec += capAlph_ru[(33 - (alphPos(key[i], alph) - alphPos(word[i], alph))) % 33];
				}else if (isCap(word[i], alph) == false){
					dec += alph_ru[(33 - (alphPos(key[i], alph) - alphPos(word[i], alph))) % 33];
				}
			}
		}
	}
    return dec;
}

wstring StringToWstring(const string& str){
	wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);
}

// This shit does the main shit. shit.
int main(int argc, char** argv){
	locale::global(locale("ru_RU.UTF-8"));
    wcin.imbue(locale());
    wcout.imbue(locale());

	int Mode = 0;
	int UserAlph = 0;
	string Alph;
	wstring Word;
	wstring Key = StringToWstring(argv[2]);

	cout << "Select alphabet [EN - 0; RU - 1] (defult - EN):" << "\n\t";
	cin >> UserAlph;
	cout << "Select mode [ENCODE - 0; DECODE - 1] (deafult - ENCODE):" << "\n\t";
	cin >> Mode;

	switch (UserAlph){
		case 1:
			Alph = "ru";
			break;
		default:
			Alph = "en";
	}


	wofstream ofile;
	wifstream ifile;

	ifile.open(argv[1]);
	if (!ifile.is_open()){
		cout << "Error opening input file" << endl;
		return 1;
	}

	if(argc > 3){
		ofile.open(argv[3]);
	}else {
		ofile.open("output.txt");
	}

	while (getline(ifile, Word)){
		if (Mode == 0){
				ofile << encode(Word, Key, Alph);
				ofile << "\n";
		}else if(Mode == 1){
				ofile << decode(Word, Key, Alph);
				ofile << "\n";
		}
	}
	ofile.close();
	ifile.close();

	return 0;
}
