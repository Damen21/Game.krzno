#include <iostream>
#include <SDL_image.h>
#include <string>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include "player.h"
#include "enemy.h"

Enemy::Enemy(int w, int h, int x, int y, const string& image_path) : e_w(w), e_h(h), e_x(x), e_y(y) {
	stDir = 0;
	smer = 0;

	auto surface = IMG_Load(image_path.c_str());
	if (!surface) {
		std::cerr << "Failed to create surface for enemy.\n";
	}
	enemy_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	if (!enemy_texture) {
		std::cerr << "Failed to create texture for enemy.\n";
	}
	SDL_FreeSurface(surface);
}

Enemy::~Enemy() {
	SDL_DestroyTexture(enemy_texture);
}

void Enemy::draw() {
	SDL_Rect nasprotnik = { e_x, e_y, e_w, e_h };
		SDL_RenderCopy(Window::renderer, enemy_texture, nullptr, &nasprotnik);
}

void Enemy::enemyMovement() {
	if (stDir >= rand() % (50 - 20) + 20 || smer == 0) {
		stDir = 0;
		smer = rand() % (4) + 1;    
	}

	switch (smer) {
	case 1:
		if (e_x >= 1000 - e_w)
			e_x = 1000 - e_w;
		else
			e_x += 2;
		stDir++;
		break;
	case 2:
		if (e_x <= 0)
			e_x = 0;
		else
			e_x -= 2;
		stDir++;
		break;
	case 3:
		if (e_y >= 600 -e_h)
			e_y = 600 - e_h;
		else
			e_y += 2;
		stDir++;
		break;
	case 4:
		if (e_y <= 0)
			e_y = 0;
		else
			e_y -= 2;
		stDir++;
		break;
	}
}

SDL_bool Enemy::hitAnimal(Animal* a) {
	SDL_Rect e = { this->GetX(), this->GetY(), this->GetW(), this->GetH() };
	SDL_Rect z = { a->GetX(), a->GetY(), a->GetW(), a->GetH() };

	SDL_bool collision = SDL_HasIntersection(&e, &z);

	return collision;
}

SDL_bool Enemy::hitFarm(Farm* a) {
	SDL_Rect e = { this->GetX(), this->GetY(), this->GetW(), this->GetH() };
	SDL_Rect f = { a->GetX(), a->GetY(), a->GetW(), a->GetH() };

	SDL_bool collision = SDL_HasIntersection(&e, &f);

	return collision;
}




int Enemy::GetX() {
	return e_x;
}
int Enemy::GetY() {
	return e_y;
}
int Enemy::GetW() {
	return e_w;
}
int Enemy::GetH() {
	return e_h;
}