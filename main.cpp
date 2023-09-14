#include <iostream>
#include <fstream>
#include <vector>
#include <SDL_image.h>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include "window.h"
#include "player.h"
#include "activist.h"
#include "enemy.h"
#include "farm.h"
#include "animal.h"
#include "button.h"
using namespace std;

void pollEventsW(Window& window, Player& igralec, bool &esc) {
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		window.pollEvents(event, esc);
		igralec.pollEvents(event);
	}
}

bool EventOption(Button a, Window window) {
	SDL_Event event;
	bool left = false;

	if (SDL_PollEvent(&event)) {
		if (a.options(event, window)) {
			left = true;
		}
		else {
			left = false;
		}
	}

	return left;
}

int main(int argc, char** argv) {
	char ime[20];
	cout << "vpisite ime" << endl;
	cin >> ime;
	int personscore;
	ofstream data("replay.txt");
	int score = 0;
	int level = 1;
	vector<bool> temp;
	int st1 = 0, st2 = 0;
	bool Player_alive = true;
	bool esc = false;
	do {
		cout << "LEVEL: " << level <<endl;

		srand((unsigned int)time(NULL));


		Window window("Game", 1000, 600);
		Button start_gumb(350, 200, 300, 100, "slike/start.png");
		if (level == 1) {																				
			start_gumb.show();
			if(EventOption(start_gumb, window))
			{
				 st1 = rand() % (950),st2 = rand() % (550);
			}
			else
			{
				int ran = rand() % (4);
				switch (ran)
				{
				case 0:
					 st1 = 0,st2 = 0;
					break;
				case 1:
					 st1 = 950,st2 = 0;
					break;
				case 2:
					 st1 = 0,st2 = 550;
					break;
				case 3:
					st1 = 950,st2 = 550;
					break;
				}
			}
			
		}
		if(level == 1)
			window.init();
		
		Player player(50, 50, st1, st2, "slike/player.png");
		vector<Enemy*> hunter;
		vector<Farm*> farm;
		vector<Activist*> activist;
		vector<Animal*> animal;
		vector<Farm*> farmaiD;
		vector<Enemy*> nasprotnikiD;

		bool Player_alive = true;
		bool esc = false;


		for (int i = 0; i < (2 + (level * 1.5)); i++) {
			Enemy* n = new Enemy(50, 50, rand() % (970), rand() % (570), "slike/hunter.PNG");
			hunter.push_back(n);
		}

		for (int i = 0; i < (level+1); i++) {
			Farm* f = new Farm(100, 100, rand() % (950), rand() % (550), "slike/farm.PNG");
			f->vpisZ();
			farm.push_back(f);
		}

		for (int i = 0; i < (level+2); i++) {
			Activist* a = new Activist(50, 50, rand() % (970), rand() % (570), "slike/aktivist.PNG");
			activist.push_back(a);
		}

		for (int i = 0; i < (level*2); i++) {
			Animal* z = new Animal(40, 40, rand() % (980), rand() % (580), "slike/zivali.png");
			animal.push_back(z);
		}

		for (int i = 0; i < hunter.size(); i++) {
			temp.push_back(0);
			farmaiD.push_back(0);
		}

		int fps = 30;
		int count = 0;
		Uint32 frameStart;
		int frameTime;
		int frameDelay = 1000 / fps;

		while (!window.isClosed()) {

			frameStart = SDL_GetTicks();
			pollEventsW(window, player, esc);
			if (esc)
			{
				Player_alive = false;
			}
			data << player.GetX() << " " << player.GetY() << endl;

			if (count %(20-level*2) == 0) {																		
				for (unsigned int i = 0; i < farm.size(); i++) {
					if (player.hitF(farm[i]))
						if (farm[i]->st() != 0) {
							farm[i]->del();
							score++;
						}
						else {
							farm.erase(farm.begin() + i);
						}
				}
			}

			for (unsigned int i = 0; i < animal.size(); i++) {
				if (player.hitZ(animal[i])) {
					animal.erase(animal.begin() + i);
					score += 5;
				}
			}

			if (count %(25-level*3) == 0) {																		
				for (unsigned int i = 0; i < hunter.size(); i++) {
					for (unsigned int j = 0; j < farm.size(); j++) {
						if (hunter[i]->hitFarm(farm[j])) {

							if (farm[j]->st() != 0) {
								farm[j]->del();
								score--;
							}
							else {
								farm.erase(farm.begin() + j);
							}
						}
					}
				}
			}
			if (count % (25 - level * 3) == 0) {																		
				for (unsigned int i = 0; i < activist.size(); i++) {
					for (unsigned int j = 0; j < farm.size(); j++) {
						if (activist[i]->hitFarm(farm[j])) {

							if (farm[j]->st() != 0) {
								farm[j]->del();
								score++;
							}
							else {
								farm.erase(farm.begin() + j);
							}
						}
					}
				}
			}

			for (int i = 0; i < hunter.size(); i++) {												
				if (player.hitE(hunter[i])) {
					int c = 0;
					for (int j = 0; j < hunter.size(); j++) {
						if (player.hitE(hunter[j]) && &hunter[i] != &hunter[j]) {
							Player_alive = false;
							score=0;
							c++;
							break;
						}
					}
					if (c == 0) {
						hunter.erase(hunter.begin() + i);
						score+=10;
						break;
					}
				}
			}


			for (unsigned int i = 0; i < hunter.size(); i++) {										
				for (unsigned int j = 0; j < activist.size(); j++) {
					if (activist[j]->hitE(hunter[i])) {
						int c = 0;
						for (unsigned int p = 0; p < hunter.size(); p++) {
							if (activist[j]->hitE(hunter[i]) && activist[j]->hitE(hunter[p]) && &hunter[i] != &hunter[p]) {
								activist.erase(activist.begin() + j);
								score-=10;
								c++;
								break;
							}
						}
						if (c == 0) {
							hunter.erase(hunter.begin() + i);
							score+=2;
							break;
						}
					}
				}
			}

			for (unsigned int i = 0; i < hunter.size(); i++) {										
				for (unsigned int j = 0; j < animal.size(); j++) {
					if (hunter[i]->hitAnimal(animal[j])) {
						if (animal.size() != 0) {
							animal.erase(animal.begin() + j);
							score-=5;
						}
					}
				}
			}						

			for (unsigned int i = 0; i < hunter.size(); i++) {										
				for (unsigned int j = 0; j < farm.size(); j++) {
					if (hunter[i]->hitFarm(farm[j])) {
						farmaiD[i] = farm[j];
						temp[i] = true;
						break;
					}
				}
			}

			for (unsigned int i = 0; i < hunter.size(); i++) {										
				if (temp[i] ==true) {
					if (hunter[i]->hitFarm(farmaiD[i])) {
						hunter[i]->draw();
					}
				}
				else if (temp[i] == false) {
					hunter[i]->enemyMovement();
					hunter[i]->draw();
				}
				temp[i] = false;
			}

			for (unsigned int i = 0; i < activist.size(); i++) {
				for (unsigned int j = 0; j < animal.size(); j++) {
					if (activist[i]->hitAnimal(animal[j])) {
						if (animal.size() != 0) {
							animal.erase(animal.begin() + j);
							score += 5;
						}
					}
				}
			}
			for (unsigned int i = 0; i < activist.size(); i++) {										
				for (unsigned int j = 0; j < farm.size(); j++) {
					if (activist[i]->hitFarm(farm[j])) {
						farmaiD[i] = farm[j];
						temp[i] = true;
						break;
					}
				}
			}
			for (unsigned int i = 0; i < activist.size(); i++) {										
				if (temp[i] == true) {
					if (activist[i]->hitFarm(farmaiD[i])) {
						activist[i]->draw();
					}
				}
				else if (temp[i] == false) {
					activist[i]->activistMovement();
					activist[i]->draw();
				}
				temp[i] = false;
			}

			for (unsigned int i = 0; i < farm.size(); i++) {											
				farm[i]->draw();
			}

			for (unsigned int i = 0; i < animal.size(); i++) {											
				animal[i]->AnimalMovement();
				animal[i]->draw();
			}
		
			player.draw();																				

																			

			if (farm.size() == 0 && animal.size() == 0) {																	
				if (score > 0)
				{
					level++;
					
				}
				else
				{
					cout << "premalo tock" << endl;
					Player_alive = false;
					cout << "score: " << score << endl;
				
				}
				break;
			}	
			else if (hunter.size() == 0) {															
				if (score > 0)
				{
					level++;
					
				}
				else
				{
					cout << "premalo tock" << endl;
					Player_alive = false;
					cout << "score: " << score << endl;
					
				}
				break;
			}

			window.clear();

			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime)
				SDL_Delay(frameDelay - frameTime);
			count++;
		}

	}while (Player_alive==true && level<5);                               //konec gejma
	personscore = score;
	ofstream data1("leaderboard.txt",ios::app);
	data1 << "ime: " << ime << "  score: " << personscore << endl;
	data1.close();
	data.close();

	bool da = false;
	int s;

	Window Iwindow("replay", 1000, 600);
	Button ButtonReplay(400, 250, 200, 100, "slike/replay.PNG");
	ButtonReplay.show();

	if (EventOption(ButtonReplay, Iwindow) == true) {
		Iwindow.init();
		da = true;
	}
	else {
		da = false;
	}

	if (da == true) {
		Player Dummy(50, 50, 0, 0, "slike/player.png");
		ifstream data("replay.txt");
		int px, py;
		if (data.is_open()) {
			while (data >> px >> py) {
				Dummy.replayPremik(px, py);
				Dummy.draw();
				Iwindow.clear();
			}
			data.close();
		}
	}
	cout << "leaderboard:" << endl;
	ifstream data2("leaderboard.txt");
	string curr;
	int count = 1;
	if (data2.is_open())
	{
		while (data2 >> curr)
		{
			cout << curr<<" ";
			if (count % 4 == 0)
				cout << endl;
			count++;
		}
	}
	return 0;
}