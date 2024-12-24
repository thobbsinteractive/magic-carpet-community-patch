#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>

#include "../engine/engine_support.h"

using namespace std;

const int kMaxObservedChangeTimeToLive = 200;

typedef struct {
    string old_value;
    string new_value;
    int time_to_live;
} ObservedChange;

typedef struct {
    type_D41A0_BYTESTR_0 D41A0_0;
} LastStates;

class StateMonitor {
    public:
        StateMonitor();
        ~StateMonitor();

        void Init();
        void Update();

    private:
        void Redraw(const string& text);

        void RegisterChange(const string& key, const string& old_value, const string& new_value);

        void ObserveD41A0();

        bool m_initialized = false;

        TTF_Font *m_font;
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;

        map<string, ObservedChange> m_observed_changes;

        LastStates m_last_states;
};

extern StateMonitor g_state_monitor;
