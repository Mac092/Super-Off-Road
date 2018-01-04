#include "ModuleIntro.h"
#include "Application.h"
#include "ModuleRender.h"


ModuleIntro::ModuleIntro(bool start_enabled) : Module(start_enabled)
{
	Attach(App);

	//First intro of the game
	introRect.x = 0;
	introRect.y = 0;
	introRect.h = 192;
	introRect.w = 320;

	// Second itnroduction screen
	intro2Rect.x = 0;
	intro2Rect.y = 0;
	intro2Rect.h = 199;
	intro2Rect.w = 320;

}

ModuleIntro::~ModuleIntro()
{
}

bool ModuleIntro::Start()
{
	LOG("Loading Intro");

	graphics = App->textures->Load("Game/intro1.png");
	graphics2 = App->textures->Load("Game/intro2.png");
	//set up a timer to control how much does the intro lasts
	
	start = timer.now();

	return true;
}

update_status ModuleIntro::Update()
{
	if (currentIntroNumber == first) {
		App->renderer->Blit(graphics, 0, 0, &introRect, 3.0f);
	}
	else {
		App->renderer->Blit(graphics2, 0, 0, &intro2Rect, 3.0f);
	}
	
	auto now = timer.now();
	auto duration = now -  start;
	auto d = std::chrono::duration_cast<std::chrono::seconds>(duration);
	if (d.count() >=  3){
		if (currentIntroNumber == first) {
			currentIntroNumber = second;
			start = timer.now();
		}
		else if (currentIntroNumber == second) {
			isIntroOver = true;
		}	
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

std::string ModuleIntro::getIntroNumber()
{
	switch (currentIntroNumber) {
	case first:
		return "first";
		break;
	case second:
		return "second";
		break;
	default:
		break;
	}
	return "first";
}

