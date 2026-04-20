#pragma once

typedef struct {
    bool devicesOpen;
    bool fileOpen;
    bool settingsOpen;
} window_states_t;

extern window_states_t window_states;


void RenderWindows();