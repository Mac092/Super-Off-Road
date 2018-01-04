#include "ModuleIntro.h"
#include "Application.h"
#include "ModuleRender.h"


ModuleIntro::ModuleIntro(bool start_enabled) : Module(start_enabled)
{
	Attach(App);
	introRect.x = 0;
	introRect.y = 0;
	introRect.h = 192;
	introRect.w = 320;
}

ModuleIntro::~ModuleIntro()
{
}

bool ModuleIntro::Start()
{
	LOG("Loading Intro");

	graphics = App->textures->Load("Game/intro1.png");
	//set up a timer to control how much does the intro lasts
	
	start = timer.now();

	return true;
}

update_status ModuleIntro::Update()
{
	App->renderer->Blit(graphics, 0, 0, &introRect, 3.0f);

	auto now = timer.now();
	auto duration = now -  start;
	auto d = std::chrono::duration_cast<std::chrono::seconds>(duration);
	if (d.count() >=  3){
		isIntroOver = true;
	}
	
	if (isIntroOver == true) {
		Notify();
	}


	return UPDATE_CONTINUE;
}

bool ModuleIntro::CleanUp()
{
	return true;
}

bool ModuleIntro::getIsIntroOver()
{
	return isIntroOver;
}

