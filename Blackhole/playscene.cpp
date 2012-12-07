#include "playscene.h"
#include "sundestroyedscene.h"
#include "supernovascene.h"
#include "blackhole.h"
#include "physicseng.h"
#include "math.h"
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <tchar.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <iostream>

// ***************************************************************************************************************
// ***************************************************************************************************************
// **************************************** cPlayScene Class Functions ******************************************
// ***************************************************************************************************************
// ***************************************************************************************************************

// CONSTRUCTOR ///////////////////////////////////////////////////////////////////////////////////////////////////
cPlayScene::cPlayScene()
{
	m_supernova_timer = 0;
	m_thread_count = 0;
	for(int i = 0; i < 5; ++i)
	{
		m_lightparticles[i].reserve(450);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// DESTRUCTOR ////////////////////////////////////////////////////////////////////////////////////////////////////
cPlayScene::~cPlayScene()
{
	delete m_barrier;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// SETUP FUNCTION ////////////////////////////////////////////////////////////////////////////////////////////////
void cPlayScene::setup()
{
	g_game.m_background_sprite.SetDisplayBitmap("Images/background.bmp");
	while(m_thread_count < (g_game.noofthreads-1))
	{
		m_lightparticles[m_thread_count].push_back(cParticleSprite());
		m_supernova_timer++;
		m_thread_count++;
	}
	m_thread_count = 0;

	m_barrier = new boost::barrier(g_game.noofthreads+1);

	for(int i = 0; i < g_game.noofthreads-1; ++i)
	{
		if(!m_lightparticles[i].empty())
		{
			m_threads.create_thread(boost::bind(&cPlayScene::UpdateLightParticles, this, boost::ref(m_lightparticles[i])));
			//UpdateLightParticles(m_lightparticles[i]);
		}
	}
	m_threads.create_thread(boost::bind(&cPlayScene::UpdateBlackhole, this));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//UPDATE FUNCTION ////////////////////////////////////////////////////////////////////////////////////////////////
void cPlayScene::update()
{
	// Create new light particles
	m_light_counter = rand()%2;
	if(m_light_counter == 0)
	{
		m_lightparticles[m_thread_count].push_back(cParticleSprite());
		m_supernova_timer++;
		m_thread_count++;
		if(m_thread_count == (g_game.noofthreads-1))
			m_thread_count = 0;
	}

	m_lightparticles[0].size();

	m_start = get_time();

	//for(int i = 0; i < g_game.noofthreads-1; ++i)
	//{
	//	if(!m_lightparticles[i].empty())
	//	{

	//		UpdateLightParticles(m_lightparticles[i]);
	//	}
	//}

	//UpdateBlackhole();

	m_barrier->wait();
	m_barrier->wait();

	m_end = get_time();

	g_game.time_taken += (m_end-m_start);

	// Check for end game conditions
	if(m_blackhole.GetSize() == 8)
	{
		g_game.m_sceneManager.push(*new cSunDestroyedScene);
		g_game.m_sceneManager.m_activeScene->setup();
	}

	if(m_supernova_timer == 5000)
	{
		g_game.m_sceneManager.push(*new cSupernovaScene);
		g_game.m_sceneManager.m_activeScene->setup();
		std::cout << "Time taken: " << g_game.time_taken << std::endl << std::endl;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//RENDER FUNCTION ////////////////////////////////////////////////////////////////////////////////////////////////
void cPlayScene::render()
{
	g_game.m_background_sprite.Render();

	for(int i = 0; i < g_game.noofthreads-1; ++i)
	{
		if(!m_lightparticles[i].empty())
		{
			RenderLightParticles(m_lightparticles[i]);
		}
	}
	RenderBlackholeandSun();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CLEANUP FUNCTION //////////////////////////////////////////////////////////////////////////////////////////////
void cPlayScene::cleanup()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// GET TIME FUNCTION /////////////////////////////////////////////////////////////////////////////////////////////
long long int cPlayScene::get_time()
{
	struct _timeb timebuffer;
	_ftime64_s(&timebuffer);
	return (timebuffer.time * 1000LL) + timebuffer.millitm;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// UPDATEBLACKHOLE FUNCTION //////////////////////////////////////////////////////////////////////////////////////
void cPlayScene::UpdateBlackhole()
{

	while(1)
	{
		m_barrier->wait();
		// Move the black hole based on keyboard input
		m_blackhole.Move(g_game.m_keys);


		// Check if black hole collides with the sun
		if(PhysicsEng::Collision(m_blackhole, m_sun))
			PhysicsEng::NoGo(m_blackhole);
		m_barrier->wait();
	}

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// UPDATELIGHTPARTICLES FUNCTION /////////////////////////////////////////////////////////////////////////////////
void cPlayScene::UpdateLightParticles(std::vector<cParticleSprite> &particles)
{

	while(1)
	{
		m_barrier->wait();

		BOOST_FOREACH(cParticleSprite & light, particles)
		{
			// Calculate velocities for all particles based on mass of black hole and position of black hole and light particle
			PhysicsEng::GravityEffect(m_sun, m_blackhole, light); 
			// Update position of light particles using new velocities
			light.Move();

			// Check for collision with the black hole 
			if(PhysicsEng::Collision(m_blackhole, light))
			{
				// Destroy light particle and increase mass of the black hole
				PhysicsEng::Kill(light);
				m_blackhole.IncreaseMass();
			}
		}
		std::vector<cParticleSprite>::iterator it;
		// Delete light particles if they go off the screen
		it = std::remove_if(particles.begin(), particles.end(), boost::bind(&cParticleSprite::GetX, _1) < 0);
		particles.erase(it, particles.end());
		it = std::remove_if(particles.begin(), particles.end(), boost::bind(&cParticleSprite::GetX, _1) > 1250);
		particles.erase(it, particles.end());
		it = std::remove_if(particles.begin(), particles.end(), boost::bind(&cParticleSprite::GetY, _1) < 0);
		particles.erase(it, particles.end());
		it = std::remove_if(particles.begin(), particles.end(), boost::bind(&cParticleSprite::GetY, _1) > 700);
		particles.erase(it, particles.end());

		m_barrier->wait();
	}

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// RENDERBLACHOLEANDSUN FUNCTION /////////////////////////////////////////////////////////////////////////////////
void cPlayScene::RenderBlackholeandSun()
{
	m_sun.Render();
	m_blackhole.Render();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// RENDERLIGHTPARTICLES FUNCTION /////////////////////////////////////////////////////////////////////////////////
void cPlayScene::RenderLightParticles(std::vector<cParticleSprite>& particles)
{
	BOOST_FOREACH( cParticleSprite & light, particles )
	{
		light.Render();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////