#include "window.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
using namespace std;

SDL_Renderer* Window::renderer = nullptr;

Window::Window(const std::string& title, int width, int height) {
	w_title = title;
	w_width = width;
	w_height = height;
	w_closed = !init();
}

Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(w_window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Failed to initialize SDL.\n";
		return false;
	}

	w_window = SDL_CreateWindow(w_title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w_width, w_height,0);

	if (w_window == nullptr) {
		std::cerr << "Failed to create window.\n";
		return false;
	}

	renderer = SDL_CreateRenderer(w_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr) {
		std::cerr << "Failed to create renderer.\n";
		return false;
	}

	return true;
}

void Window::pollEvents(SDL_Event& event, bool& ecs) {
	switch (event.type) {
	case SDL_QUIT:
		ecs = true;
		w_closed = true;
		break;

	case SDL_KEYDOWN: 
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			ecs = true;
			w_closed = true;
			break;
			break;
		}
	default:
		break;
	}
}
void Window::clear() const {
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100); 
	SDL_RenderClear(renderer);
}