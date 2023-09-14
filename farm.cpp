#include "player.h"
#include "window.h"
#include "farm.h"
#include <SDL_image.h>
#include <iostream>
using namespace std;

Farm::Farm(int w, int h, int x, int y, const std::string& image_path) : f_w(w), f_h(h), f_x(x), f_y(y) {
	auto surface = IMG_Load(image_path.c_str());
	if (!surface) {
		cerr << "Failed to load farm surface.\n";
	}
	farm_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	if (!farm_texture) {
		cerr << "Failed to create farm texture.\n";
	}
	SDL_FreeSurface(surface);
}

Farm::~Farm() {
	SDL_DestroyTexture(farm_texture);
}

void Farm::draw() const {
	SDL_Rect farma = { f_x, f_y, f_w, f_h };
		SDL_RenderCopy(Window::renderer, farm_texture, nullptr, &farma);
}

void Farm::vpisZ() {
	this->st_zivali = rand() % 15 + 5;
}

void Farm::del() {
	this->st_zivali -= 1;
}

int Farm::st() {
	return st_zivali;

}

int Farm::GetX() {
	return f_x;
}
int Farm::GetY() {
	return f_y;
}
int Farm::GetW() {
	return f_w;
}
int Farm::GetH() {
	return f_h;
}