#pragma once
#include <string>
#include <SDL.h>
using namespace std;

class Window {
private:
	string w_title;

	bool w_closed;

	int w_width,w_height;

	SDL_Window* w_window = nullptr;

public:

	Window(const string& title, int width, int height);
	~Window();

	void pollEvents(SDL_Event& event, bool& ali);
	void pavza(SDL_Event& event);
	void clear() const;

	inline bool isClosed() const { return w_closed; }
	bool init();

	static SDL_Renderer* renderer;
};