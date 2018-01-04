#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"
#include <vector>
#include "Observer.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModulePlayer;
class ModuleTrack;
class ModuleFadeToBlack;
class ModuleIntro;


class Application  : public Observer
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	void Update(Subject *subject);
	bool CleanUp();


public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModulePlayer* player;
	ModuleTrack* track;
	ModuleFadeToBlack* fade;
	ModuleIntro * intro;

private:

	std::list<Module*> modules;

};


extern Application* App;

#endif // __APPLICATION_CPP__