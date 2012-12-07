#ifndef _PHYSICSENG_H_
#define _PHYSICSENG_H_

#include "sunsprite.h"
#include "blackholesprite.h"
#include "particlesprite.h"

// PHYSICS ENGINE FUNCTIONS CONTAINED IN A NAMESPACE PHYSICSENG
namespace PhysicsEng 
{
	// Collision detection algorithms
	bool Collision(cBlackholeSprite &Blackhole, cSunSprite &Sun);	
	bool Collision(cBlackholeSprite &Blackhole, cParticleSprite &Particle);	
	// Collision reaction algorithms
	void NoGo(cBlackholeSprite &Blackhole); // Returns sprite to position immediately prior to collision
	void Kill(cParticleSprite &Particle);   // Moves particle off screen and zeros its velocity 
	// Calculate gravity
	void GravityEffect(cSunSprite &Sun, cBlackholeSprite &Blackhole, cParticleSprite &Particle);
}

#endif