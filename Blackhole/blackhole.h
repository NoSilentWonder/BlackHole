#ifndef _BLACKHOLE_H_
#define _BLACKHOLE_H_

#include "scene.h"
#include "sprite.h"


class cBlackHole
{
public:
	cBlackHole();
	~cBlackHole();
	void GameSetUp();
	void Update();
	void Render();

	cSceneManager m_sceneManager;
	bool m_keys[256];
	cSprite m_background_sprite;
	int noofthreads;
	long long int time_taken;
	
};

extern cBlackHole g_game;

#endif