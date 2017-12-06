#include "Application.h"
#include "ModuleTrack.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "TerrainAlteration.h"



ModuleTrack::ModuleTrack(bool start_enabled) : Module(start_enabled)
{
	//truck terrain
	ground.x = 8;
	ground.y = 1408;
	ground.h = 198;
	ground.w = 319;

	//walls
	wall.x = 336;
	wall.y = 1408;
	wall.h = 198;
	wall.w = 319;

	//poodle1
	poodle1Rect.x = 72;
	poodle1Rect.y = 1459;
	poodle1Rect.h = 23;
	poodle1Rect.w = 20;
}


ModuleTrack::~ModuleTrack()
{
	terrainAlterations.push_back(poodle1 = new TerrainAlteration(poodle1Rect.x,poodle1Rect.y,poodle1Rect.w,poodle1Rect.h));
}

bool ModuleTrack::Start()
{
	LOG("Loading Current Track");
	
	graphics = App->textures->Load("Game/stages.png");
	App->audio->PlayMusic("Game/Off-Road_Fandango.wav", 0);

	App->player->Init();
	App->player->Start();

	return true;
}

update_status ModuleTrack::Update()
{
	App->renderer->Blit(graphics, 10, 10, &ground, 3.0f);
	App->renderer->Blit(graphics, 38, 10, &wall, 3.0f);
	App->player->Update();
	

	return UPDATE_CONTINUE;
}

bool ModuleTrack::CleanUp()
{
	return false;
}
