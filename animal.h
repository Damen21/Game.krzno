#pragma once
#include <string>
#include "player.h"
#include "window.h"
using namespace std;

class Animal {
private:
	int a_w, a_h,a_x, a_y;
	SDL_Texture*animal_texture = nullptr;
	int stDir = 0;
	int smer = 0;

public:
	Animal(int w, int h, int x, int y, const std::string& image_path);
	~Animal();

	void draw() const;
	void AnimalMovement();

	int GetX();
	int GetY();
	int GetW();
	int GetH();
};
