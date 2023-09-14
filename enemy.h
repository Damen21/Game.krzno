#pragma once
#include <string>
#include "window.h"
#include "animal.h"
#include "player.h"
using namespace std;



class Enemy {
private:

	int e_w, e_h,e_x, e_y;
	SDL_Texture* enemy_texture = nullptr;

	int stDir;
	int smer;

public:
	Enemy(int w, int h, int x, int y, const string& image_path);
	~Enemy();

	void draw();
	void enemyMovement();
	void AI(Farm* a);
	SDL_bool hitAnimal(Animal* a);
	SDL_bool hitFarm(Farm* a);

	int GetX();
	int GetY();
	int GetW();
	int GetH();
};