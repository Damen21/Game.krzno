#pragma once

#include "window.h"
#include "SDL.h"
#include <iostream>
#include <vector>
#include <string>
class Button {
private:
	int b_w, b_h, b_x, b_y, b_mx, b_my;
    SDL_Texture* button_texture;
public:
    Button(int x, int y, int w, int h, const string&);
    bool options(SDL_Event, Window);
    void show();
};