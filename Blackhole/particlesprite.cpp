#include "particlesprite.h"
#include "globals.h"

// CONSTRUCTOR /////////////////////////////////////////////////////////////////////////////////
cParticleSprite::cParticleSprite()
{
	m_x = 625;
	m_y = 350;
	m_true_x = (float)m_x;
	m_true_y = (float)m_y;
	m_velocity_x = (rand()%2000 - 1000)*0.001f;
	m_velocity_y = (rand()%2000 - 1000)*0.001f;
	if((m_velocity_x == 0) && (m_velocity_y == 0)) // Make sure all particles are moving initially
		m_velocity_x = 0.1f;
	m_w = 1;
	m_h = 1;
	SetDisplayBitmap("Images/sun.bmp");
}
////////////////////////////////////////////////////////////////////////////////////////////////

// DESTRUCTOR //////////////////////////////////////////////////////////////////////////////////
cParticleSprite::~cParticleSprite()
{
	// Nothing to clean-up
}
////////////////////////////////////////////////////////////////////////////////////////////////

// MOVE FUNCTION ///////////////////////////////////////////////////////////////////////////////
// This function updates the x and y coordinate of 
// the particle using it's current x and y velocities.
// As movement is done in integers, a float is used to
// keep a more accurate position, and then cast as an
// iteger to move the particle.
void cParticleSprite::Move(void)
{
	m_true_x += m_velocity_x;
	m_x = (int)m_true_x;

	m_true_y += m_velocity_y;
	m_y = (int)m_true_y;
}
////////////////////////////////////////////////////////////////////////////////////////////////

// SETVELOCTY FUNCTION /////////////////////////////////////////////////////////////////////////
void cParticleSprite::SetVelocity(float vx, float vy)
{
	m_velocity_x = vx;
	m_velocity_y = vy;
}
////////////////////////////////////////////////////////////////////////////////////////////////