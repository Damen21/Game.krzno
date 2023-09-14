#include "player.h"
#include "farm.h"
#include "enemy.h"
#include <SDL_image.h>
#include <iostream>
#include <fstream>
using namespace std;

Player::Player(int w, int h, int x, int y, const std::string& image_path) : p_w(w), p_h(h), p_x(x), p_y(y) {
	auto surface = IMG_Load(image_path.c_str());
	if (!surface) {
		cerr << "Failed to load player surface.\n";
	}
	player_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	if (!player_texture) {
		cerr << "Failed to create player texture.\n";
	}
	SDL_FreeSurface(surface);
}

Player::~Player() {
	SDL_DestroyTexture(player_texture);
}

void Player::draw() const {
	SDL_Rect player = { p_x, p_y, p_w, p_h };
		SDL_Rect maska = { p_x - 100, p_y - 100, p_w + 200, p_h + 200 };
		SDL_RenderSetClipRect(Window::renderer, &maska);
		SDL_RenderCopy(Window::renderer, player_texture, nullptr, &player);
}

SDL_bool Player::hitE(Enemy* a) {
	SDL_Rect p = { this->GetX(), this->GetY(), this->GetW(), this->GetH() };
	SDL_Rect e = { a->GetX(), a->GetY(), a->GetW(), a->GetH() };

	SDL_bool collision = SDL_HasIntersection(&p, &e);

	return collision;
}

SDL_bool Player::hitF(Farm* a) {
	SDL_Rect p = { this->GetX(), this->GetY(), this->GetW(), this->GetH() };
	SDL_Rect f = { a->GetX(), a->GetY(), a->GetW(), a->GetH() };

	SDL_bool collision = SDL_HasIntersection(&p, &f);

	return collision;
}

SDL_bool Player::hitZ(Animal* a) {
	SDL_Rect p = { this->GetX(), this->GetY(), this->GetW(), this->GetH() };
	SDL_Rect z = { a->GetX(), a->GetY(), a->GetW(), a->GetH() };

	SDL_bool collision = SDL_HasIntersection(&p, &z);

	return collision;
}

void Player::pollEvents(SDL_Event& event) {
	
	if (event.type == SDL_KEYDOWN)
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			if (p_x <= 0)
				p_x = 0;
			else
				p_x -= 10;
			break;
		case SDLK_RIGHT:
			if (p_x >= 1000 - p_w)
				p_x = 1000 - p_w;
			else
				p_x += 10;
			break;
		case SDLK_UP:
			if (p_y <= 0)
				p_y = 0;
			else
				p_y -= 10;
			break;
		case SDLK_DOWN:
			if (p_y >= 600 - p_h)
				p_y = 600 - p_h;
			else
				p_y += 10;
			break;
		}
}

void Player::replayVpis(ofstream data) {
	data << "X: " << this->GetX() << " - Y" << this->GetY() << ".\n";
}

void Player::replayPremik(int x, int y) {
	p_x = x;
	p_y = y;
}

int Player::GetX() {
	return p_x;
}
int Player::GetY() {
	return p_y;
}
int Player::GetW() {
	return p_w;
}
int Player::GetH() {
	return p_h;
}