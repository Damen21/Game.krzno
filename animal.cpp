#include "player.h"
#include "window.h"
#include "animal.h"
#include <SDL_image.h>
#include <iostream>
using namespace std;

Animal::Animal(int w, int h, int x, int y, const std::string& image_path) : a_w(w), a_h(h), a_x(x), a_y(y) {
	auto surface = IMG_Load(image_path.c_str());
	if (!surface) {
		cerr << "Failed to load farm surface.\n";
	}
	animal_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	if (!animal_texture) {
		cerr << "Failed to create farm texture.\n";
	}
	SDL_FreeSurface(surface);
}

Animal::~Animal() {
	SDL_DestroyTexture(animal_texture);
}

void Animal::draw() const {
	SDL_Rect aktivist = { a_x, a_y, a_w, a_h };
		SDL_RenderCopy(Window::renderer, animal_texture, nullptr, &aktivist);
	
}

void Animal::AnimalMovement() {
	if (stDir >= rand() % (50 - 20) + 20 || smer == 0) {
		stDir = 0;
		smer = rand() % (5 - 1) + 1;   
	}

	switch (smer) {
	case 1:
		if (a_x >= 1000 - a_w)
			a_x = 1000 - a_w;
		else
			a_x += 2;
		stDir++;
		break;
	case 2:
		if (a_x <= 0)
			a_x = 0;
		else
			a_x -= 2;
		stDir++;
		break;
	case 3:
		if (a_y >= 600 - a_h)
			a_y = 600 -a_h;
		else
			a_y += 2;
		stDir++;
		break;
	case 4:
		if (a_y <= 0)
			a_y = 0;
		else
			a_y -= 2;
		stDir++;
		break;
	}
}

int Animal::GetX() {
	return a_x;
}
int Animal::GetY() {
	return a_y;
}
int Animal::GetW() {
	return a_w;
}
int Animal::GetH() {
	return a_h;
}