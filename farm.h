#pragma once
#include <string>
#include "player.h"
#include "window.h"
using namespace std;

class Farm {
private:
	int f_w,f_h,f_x,f_y,st_zivali;
	SDL_Texture* farm_texture = nullptr;

public:
	Farm(int w, int h, int x, int y, const std::string& image_path);
	~Farm();

	void draw() const;
	void del();
	void vpisZ();
	int st();

	

	int GetX();
	int GetY();
	int GetW();
	int GetH();
};