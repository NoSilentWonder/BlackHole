#include "sundestroyedscene.h"
#include "blackhole.h"

// ***************************************************************************************************************
// ***************************************************************************************************************
// **************************************** cSunDestroyedScene Class Functions ***********************************
// ***************************************************************************************************************
// ***************************************************************************************************************

// CONSTRUCTOR ///////////////////////////////////////////////////////////////////////////////////////////////////
cSunDestroyedScene::cSunDestroyedScene()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// DESTRUCTOR ////////////////////////////////////////////////////////////////////////////////////////////////////
cSunDestroyedScene::~cSunDestroyedScene()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// SETUP FUNCTION ////////////////////////////////////////////////////////////////////////////////////////////////
void cSunDestroyedScene::setup()
{
	g_game.m_background_sprite.SetDisplayBitmap("Images/sundestroyed.bmp");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//UPDATE FUNCTION ////////////////////////////////////////////////////////////////////////////////////////////////
void cSunDestroyedScene::update()
{
	if(g_game.m_keys[13])
	{
		g_game.m_keys[13] = false;
		g_game.m_sceneManager.pop();
		g_game.m_sceneManager.pop();
		g_game.m_sceneManager.pop();
		g_game.m_sceneManager.m_activeScene->setup();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//RENDER FUNCTION ////////////////////////////////////////////////////////////////////////////////////////////////
void cSunDestroyedScene::render()
{
	g_game.m_background_sprite.Render();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CLEANUP FUNCTION //////////////////////////////////////////////////////////////////////////////////////////////
void cSunDestroyedScene::cleanup()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////