#include <iostream>
#include <vector>
#include "button.h"
#include "window.h"
#include <SDL_image.h>

using namespace std;

Button::Button(int x, int y, int w, int h, const string& image_path) {
    b_x = x;
    b_y = y;
    b_w = w;
    b_h = h;


    auto surface = IMG_Load(image_path.c_str());
    button_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
}

bool Button::options(SDL_Event event, Window window) {
    bool parameter = false;
    SDL_Rect box = { b_x, b_y, b_w, b_h };
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {

            b_mx = event.button.x;
            b_my = event.button.y;

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT && (b_mx > box.x) && (b_mx < box.x + box.w - 100) && (b_my > box.y) && (b_my < box.y + box.h)) {
                    parameter = true;
                    quit = true;
                }
                else if (event.button.button == SDL_BUTTON_LEFT && (b_mx > box.x + 100) && (b_mx < box.x + box.w) && (b_my > box.y) && (b_my < box.y + box.h)) {
                    parameter = false;
                    quit = true;
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                }
            }
            SDL_RenderCopy(Window::renderer,button_texture, nullptr, &box);
            window.clear();
        }
    }
    return parameter;
}

void Button::show() {
    SDL_Rect box = { b_x, b_y, b_w, b_h };
    SDL_RenderCopy(Window::renderer, button_texture, nullptr, &box);
}