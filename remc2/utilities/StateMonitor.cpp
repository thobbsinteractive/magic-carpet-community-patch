#include "StateMonitor.h"

#include <vector>
#include <algorithm>
#include <fmt/core.h>

#include "../portability/port_filesystem.h"

StateMonitor g_state_monitor;

StateMonitor::StateMonitor() {
}

StateMonitor::~StateMonitor() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    m_renderer = nullptr;
    m_window = nullptr;
}

// Comparator function to sort pairs 
bool cmp(pair<string, ObservedChange>& a, pair<string, ObservedChange>& b) 
{ 
    return a.second.time_to_live < b.second.time_to_live; 
} 
 
void StateMonitor::Init() {
    m_window = SDL_CreateWindow("StateMonitor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 800, 0);
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    TTF_Init();
    m_font = TTF_OpenFont(GetSubDirectoryPath("font/UbuntuMono-B.ttf").c_str(), 18);

    m_initialized = true;
}

void StateMonitor::Update() {
    if (!m_initialized) {
        return;
    }

    // reduce time to live for all observed changes
    for (auto& change : m_observed_changes) {
        change.second.time_to_live--;
        if (change.second.time_to_live <= 0) {
            m_observed_changes.erase(change.first);
        }
    }

    // check for changes
    ObserveD41A0();

    // create string of all changes sorted by time to live
    vector<pair<string, ObservedChange> > sorter; 
    for (auto& change : m_observed_changes) {
        sorter.push_back(change);
    } 
    sort(sorter.begin(), sorter.end(), cmp); 
    string changes;
    for (auto& change : sorter) {
        changes += change.first + ": " + change.second.old_value + " -> " + change.second.new_value + " TTL" + to_string(change.second.time_to_live) + "\n";
    }

    // redraw
    Redraw(changes);
}

void StateMonitor::Redraw(const string& text) {
    SDL_SetRenderDrawColor(m_renderer, 255,255,255,250);
    SDL_RenderClear(m_renderer);
    SDL_Surface *surface = TTF_RenderText_Solid_Wrapped(m_font, text.c_str(), {0, 0, 0}, 0);
    if (!surface) { 
        return; 
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    if (!texture) { 
        SDL_FreeSurface(surface);
        return; 
    }

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_RenderCopy(m_renderer, texture, nullptr, &rect);
    SDL_RenderPresent(m_renderer);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void StateMonitor::RegisterChange(const string& key, const string& old_value, const string& new_value) {
    m_observed_changes[key] = {old_value, new_value, 100};
}

// macro to compare and register changes
#define COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(struct, key) \
    if (m_last_states.struct.key != struct.key) { RegisterChange(#struct ": " #key, fmt::format("{:x}", m_last_states.struct.key), fmt::format("{:x}", struct.key)); }


void StateMonitor::ObserveD41A0() {
    // compare D41A0_0 with with last state if different, add to observed changes
	// uint8_t stub0[4];
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, dword_0x4);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, LevelIndex_0xc);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0xe);
	// uint8_t array_0x10[29]; //0x10, next 0x2d(45)
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, dword_0x2d);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0x31);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0x33);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, dword_0x35); // entity counter(max 1000 entity changes per step)
	// uint8_t array_0x39[508];//57
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, maptypeMusic_0x235);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, byte_0x239);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, dword_0x23a);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, dword_0x23e);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, dword_0x242);
	// type_event_0x6E8E* pointers_0x246[1000];//pointers
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, dword_0x11e6); // second entity counter
	// type_event_0x6E8E* dword_0x11EA[1000];//??4586
	// GameSettingsStruct_t m_GameSettings;
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, dword_0x219A);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, dword_0x219E);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, dword_0x21A2);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, dword_0x21A6);
	// type_str_0x21AA str_0x21AA;
	// type_str_0x21AE str_0x21AE;
	// type_str_0x21B2 str_0x21B2;
	// type_str_0x21B6 str_0x21B6;
	// uint8_t stub3b[424];
	// axis_3d array_0x2362[8];
	// uint8_t stub3c[333];
	// uint8_t stub3d[1791];
	// type_str_0x2BDE array_0x2BDE[8];
	// type_str_0x6E3E array_0x6E3E[8];//28222	lenght 0xa size 0x8// game events
	// type_event_0x6E8E struct_0x6E8E[1000];//28302 a8*3e8
	// Type_Level_2FECE terrain_2FECE;// a1 = &x_D41A0_BYTEARRAY_0[0x2FECE/*196302*/];//fix - size 0x6604u//compress level
	// type_str_0x364D2 str_0x364D2;//lenght 108
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0x3653E);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0x36540);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0x36542);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0x36544);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0x36546);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0x36548);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0x3654A);
	// type_str_3654C stages_0x3654C[8];//size 10 count 8
	// type_str_3659C struct_0x3659C[8];//size 11 count 8 C-0 D-1 E-2 F-3
	// type_str_0x3647Ac StageVars2_0x365F4[11];//8x11	//set 0x58 // end 0x3664c
	// type_str_0x3664C str_0x3664C[50];// lenght 0x79e//39x50 (end-0x36dea)
	// int8_t byte_0x36DEA_fly_asistant;
	// int8_t byte_0x36DEB_xx;
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0x36DEC_mousex);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0x36DEE_mousey);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0x36DF0_mousexx);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, dword_0x36DF2);
	// type_str_160* dword_0x36DF6;//pointer
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0x36DFA);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0x36DFC);
    COMPARE_AND_REGISTER_CHANGE_VARIABLE_HEX(D41A0_0, word_0x36DFE);
	// uint8_t countStageVars_0x36E00;
	// uint8_t stageIndex_0x36E01;//count objectives
	// int8_t byte_0x36E02;//temp objective
	// int8_t byte_0x36E03;
	// int8_t byte_0x36E04;
	// uint8_t stub3k[6];
	// int8_t byte_0x36E0B;
	// uint8_t stubend[11];

    // shallow copy of D41A0_0
    m_last_states.D41A0_0 = D41A0_0;
}