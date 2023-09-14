#pragma once
#include <string>
#include "player.h"
#include "window.h"
#include "enemy.h"
using namespace std;

class Activist {
private:
	int a_w, a_h, a_x, a_y;
	SDL_Texture* activist_texture = nullptr;

	int stDir = 0;
	int smer = 0;

public:
	Activist(int w, int h, int x, int y, const std::string& image_path);
	~Activist();

	void draw() const;
	void activistMovement();
	SDL_bool hitE(Enemy* a);
	SDL_bool hitFarm(Farm* a);
	SDL_bool hitAnimal(Animal* a);
	int GetX();
	int GetY();
	int GetW();
	int GetH();
};