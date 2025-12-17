// Include
#define SDL_MAIN_USE_CALLBACKS 1

#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <cmath>
#include <locale>
#include <fstream>
#include <codecvt>
// #include <SDL3/SDL.h>
// #include <SDL3/SDL_main.h>
// #include "imgui.h"
// #include "imgui_stdlib.h"
// #include "imgui_impl_sdl3.h"
// #include "imgui_impl_sdlrenderer3.h"
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
	wstring StUserAlph;
	wstring StMode;
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
	ofile.open("output.txt");
	while (getline(ifile, Word)){
		if (Mode == 0){
			if (Word == L"\n"){
				ofile << Word;
			}else {
				ofile << encode(Word, Key, Alph);
			}
		}else if(Mode == 1){
			if (Word == L"\n"){
				ofile << Word;
			}else {
				ofile << decode(Word, Key, Alph);
			}
		}
	}
	ofile.close();
	ifile.close();

	// wcout << "Welcome to the ENCODER!" << endl;
	// wcout << "Select mode [Encode - 0; Decode - 1] (default - Encode):\n\t";
	// getline(wcin, StMode);
	// if (StMode == L""){}
	// else { Mode = stoi(StMode); }
	// wcout << "Select alphabet [EN - 0; RU - 1] (default - EN):\n\t";
	// getline(wcin, StUserAlph);
	// if (StUserAlph == L""){}
	// else { UserAlph = stoi(StUserAlph); }
	// wcout << "Type your text to operate on (one string):\n\t";
	// getline(wcin, Word);
	// wcout << "Type your key (only alphabet letters and space):\n\t";
	// getline(wcin, Key);
	//
	// switch (UserAlph){
	// 	case 0:
	// 		Alph = "en";
	// 		break;
	// 	case 1:
	// 		Alph = "ru";
	// 		break;
	// 	default:
	// 		Alph = "en";
	// }
	//
	// switch (Mode){
	// 	case 1:
	// 		wcout << "Your decoded string:\n\t" << decode(Word, Key, Alph) << endl;
	// 		break;
	// 	default:
	// 		wcout << "Your encoded string:\n\t" << encode(Word, Key, Alph) << endl;
	// 		break;
	// }

	return 0;
}

// static SDL_Window *window;
// static SDL_Renderer *renderer;
//
//
// SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){
// 	locale::global(locale("ru_RU.UTF-8"));
//     wcin.imbue(locale());
//     wcout.imbue(locale());
//
// 	if(!SDL_Init(SDL_INIT_VIDEO)){
// 		SDL_Log("Couldn initialize SDL: %s", SDL_GetError());
// 		return SDL_APP_FAILURE;
// 	}
//
// 	float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
// 	if(!SDL_CreateWindowAndRenderer("Encoder/Decoder", (int)(640 * main_scale), (int)(480 * main_scale), NULL, &window, &renderer)){
// 		SDL_Log("Couldnt create window/renderer: %s", SDL_GetError());
// 		return SDL_APP_FAILURE;
// 	}
// 	SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);
//
//     IMGUI_CHECKVERSION();
// 	ImGui::CreateContext();
//     ImGuiIO& io = ImGui::GetIO(); (void)io;
//     io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
//
// 	ImGui::StyleColorsDark();
//
//     ImGuiStyle& style = ImGui::GetStyle();
//     style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
//     style.FontScaleDpi = main_scale;        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)
//
// 	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
// 	ImGui_ImplSDLRenderer3_Init(renderer);
//
// 	return SDL_APP_CONTINUE;
// }
//
//
// wstring tempOutput;
//
//
// SDL_AppResult SDL_AppIterate(void *appstate){
// 	SDL_SetRenderDrawColor(renderer, 15, 7, 30, 0);
// 	SDL_RenderClear(renderer);
// 	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
//
// 	ImGui_ImplSDLRenderer3_NewFrame();
// 	ImGui_ImplSDL3_NewFrame();
// 	ImGui::NewFrame();
// 	ImGui::Begin("Encoder/Decoder");
//
// 	ImGui::Button("Button");
// 	// ImGui::Checkbox("Select Mode", &Mode);
// 	//
// 	// ImGui::Checkbox("Select Alphabet", &UserAlph);
// 	//
// 	// string SUserInput = wstringToString(Word);
// 	// if (ImGui::InputText("Input", &SUserInput)){
// 	// 	Word = stringToWstring(SUserInput);
// 	// }
// 	//
// 	// string SUserKey = wstringToString(Key);
// 	// if (ImGui::InputText("Input", &SUserKey)){
// 	// 	Key = stringToWstring(SUserKey);
// 	// }
//
//
// 	// ImGui::Text(tempOutput);
//
// 	ImGui::End();
// 	ImGui::Render();
//
// 	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
// 	SDL_RenderPresent(renderer);
// 	return SDL_APP_CONTINUE;
// }
//
//
// SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){
// 	ImGui_ImplSDL3_ProcessEvent(event);
// 	if(event->type == SDL_EVENT_QUIT){
// 		return SDL_APP_SUCCESS;
// 	}
// 	return SDL_APP_CONTINUE;
// }
//
//
// void SDL_AppQuit(void *appstate, SDL_AppResult result){
//     ImGui_ImplSDLRenderer3_Shutdown();
//     ImGui_ImplSDL3_Shutdown();
//     ImGui::DestroyContext();
//
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();
// }
