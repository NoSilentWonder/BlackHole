#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include "scene.h"
#include "sunsprite.h"
#include "blackholesprite.h"
#include "particlesprite.h"
#include <vector>
#include <boost/thread.hpp>
#include <boost/thread/barrier.hpp>
#include "blackhole.h"

class cPlayScene : public cScene
{
public:
	cPlayScene();
	virtual ~cPlayScene();
	virtual void setup();
	virtual void update();
	virtual void render();
	
private:
	virtual void cleanup();
	long long int get_time();
	void UpdateBlackhole();
	void UpdateLightParticles(std::vector<cParticleSprite> &particles);
	void RenderBlackholeandSun();
	void RenderLightParticles(std::vector<cParticleSprite> &particles);
	cSunSprite m_sun;									// sun sprite
	cBlackholeSprite m_blackhole;						// black hole sprite
	std::vector<cParticleSprite> m_lightparticles[12];	// Array of vectors to hold light particles
	int m_light_counter;								// used to control generation of new light particles
	long long int m_start, m_end;						//used to hold start and end time
	int m_supernova_timer;
	int m_thread_count;
	boost::thread_group m_threads;
	boost::barrier * m_barrier;
};

#endif	