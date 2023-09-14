#pragma once
#include <string>
#include <fstream>
#include "farm.h"
#include "enemy.h"
#include "window.h"
using namespace std;

class Player {
private:
	int p_w, p_h,p_x, p_y;
	SDL_Texture* player_texture = nullptr;

public:
	Player(int w, int h, int x, int y, const std::string& image_path);
	~Player();

	void draw() const;
	void pollEvents(SDL_Event& event);

	SDL_bool hitE(Enemy* a);
	SDL_bool hitF(Farm* a);
	SDL_bool hitZ(Animal* a);

	void replayVpis(ofstream data);
	void replayPremik(int x, int y);

	void no_hitF(Farm* a);

	int GetX();
	int GetY();
	int GetW();
	int GetH();
};