#ifndef __MODULEINTRO_H__
#define __MODULEINTRO_H__

#include "Globals.h"
#include "Module.h"
#include "Subject.h"
#include "ModuleTextures.h"
#include <chrono>
#include <string>

class Application;

struct SDL_Texture;

enum NumOfIntro { first, second };

class ModuleIntro  : public Module, public Subject
{
public:
	ModuleIntro(bool start_enabled = true);
	~ModuleIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool getIsIntroOver();
	std::string getIntroNumber();

private:
	bool isIntroOver = false;
	std::chrono::steady_clock timer;
	std::chrono::steady_clock::time_point start;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Rect introRect;
	SDL_Rect intro2Rect;
	NumOfIntro currentIntroNumber = first;
	

};

#endif // __MODULEINTRO_H__