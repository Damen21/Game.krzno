#include "player.h"
#include "window.h"
#include "activist.h"
#include <SDL_image.h>
#include <iostream>
using namespace std;

Activist::Activist(int w, int h, int x, int y, const std::string& image_path) : a_w(w), a_h(h), a_x(x), a_y(y) {
	auto surface = IMG_Load(image_path.c_str());
	if (!surface) {
		cerr << "Failed to load farm surface.\n";
	}
	activist_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	if (!activist_texture) {
		cerr << "Failed to create farm texture.\n";
	}
	SDL_FreeSurface(surface);
}

Activist::~Activist() {
	SDL_DestroyTexture(activist_texture);
}

void Activist::draw() const {
	SDL_Rect aktivist = { a_x, a_y, a_w, a_h };
		SDL_RenderCopy(Window::renderer, activist_texture, nullptr, &aktivist);
}

SDL_bool Activist::hitE(Enemy* a) {
	SDL_Rect ac = { this->GetX(), this->GetY(), this->GetW(), this->GetH() };
	SDL_Rect e = { a->GetX(), a->GetY(), a->GetW(), a->GetH() };

	SDL_bool collision = SDL_HasIntersection(&ac, &e);

	return collision;
}
SDL_bool Activist::hitFarm(Farm* a) {
	SDL_Rect e = { this->GetX(), this->GetY(), this->GetW(), this->GetH() };
	SDL_Rect f = { a->GetX(), a->GetY(), a->GetW(), a->GetH() };

	SDL_bool collision = SDL_HasIntersection(&e, &f);

	return collision;
}
SDL_bool Activist::hitAnimal(Animal* a) {
	SDL_Rect e = { this->GetX(), this->GetY(), this->GetW(), this->GetH() };
	SDL_Rect z = { a->GetX(), a->GetY(), a->GetW(), a->GetH() };

	SDL_bool collision = SDL_HasIntersection(&e, &z);

	return collision;
}

void Activist::activistMovement() {
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
			a_y = 600 - a_h;
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

int Activist::GetX() {
	return a_x;
}
int Activist::GetY() {
	return a_y;
}
int Activist::GetW() {
	return a_w;
}
int Activist::GetH() {
	return a_h;
}