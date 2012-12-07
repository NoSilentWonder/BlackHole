#include "physicseng.h"
#include "math.h"

#define gravity_constant 0.0000667
#define PI 3.14159265359

// COLLISION (blackhole and sun) FUNCTION//////////////////////////////////////////////////////////////
bool PhysicsEng::Collision(cBlackholeSprite &Blackhole, cSunSprite &Sun)
{
	if((pow((float)(Blackhole.GetCentreX() - Sun.GetCentreX()), 2) + 
		pow((float)(Blackhole.GetCentreY() - Sun.GetCentreY()), 2)) <
		pow((float)((Blackhole.GetWidth()*0.5f) + (Sun.GetWidth()*0.5f)), 2))
		return true;
	else
	{
		return false;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////

// COLLISION (blackhole and particle) FUNCTION/////////////////////////////////////////////////////////
bool PhysicsEng::Collision(cBlackholeSprite &Blackhole, cParticleSprite &Particle)
{
	if((pow((float)(Blackhole.GetCentreX() - Particle.GetX()), 2) + 
		pow((float)(Blackhole.GetCentreY() - Particle.GetY()), 2)) <
		(float)(Blackhole.GetWidth()*0.5f))
		return true;
	else
	{
		return false;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////

// NOGO FUNCTION///////////////////////////////////////////////////////////////////////////////////////
void PhysicsEng::NoGo(cBlackholeSprite &Blackhole)
{
	Blackhole.MoveTo(Blackhole.GetPrevX(), Blackhole.GetPrevY());
}
///////////////////////////////////////////////////////////////////////////////////////////////////////

// KILL FUNCTION //////////////////////////////////////////////////////////////////////////////////////
void PhysicsEng::Kill(cParticleSprite &Particle)
{
	Particle.MoveTo(-10, -10);
	Particle.SetVelocity(0, 0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////

// GRAVITYEFFECT FUNCTION /////////////////////////////////////////////////////////////////////////////
void PhysicsEng::GravityEffect(cSunSprite &Sun, cBlackholeSprite &Blackhole, cParticleSprite &Particle)
{
	float distance_x;
	float distance_y;
	float distance_squared;
	float distance;
	float gravity_effect;
	float delta_velocity;
	float velocity_x;
	float velocity_y;
	float angle;

	distance_x = (float)(Blackhole.GetCentreX() - Particle.GetTrueX());
	distance_y = (float)(Blackhole.GetCentreY() - Particle.GetTrueY());
	distance_squared = pow(distance_x, 2) + pow(distance_y, 2);
	distance = sqrt(distance_squared);

	//angular_velocity = sqrt(gravity_constant*Blackhole.GetMass()/distance);
	gravity_effect = exp(/*gravity_constant**/Blackhole.GetMass()/distance);
	delta_velocity = gravity_effect/distance_squared;
	angle = atan2(distance_y, (float)(distance_x * 180 / PI));
	velocity_x = Particle.GetVelocityX() + delta_velocity*cos(angle);
	velocity_y = Particle.GetVelocityY() + delta_velocity*sin(angle);

	if(velocity_x < -2)
		velocity_x = -2;
	if(velocity_x > 2)
		velocity_x = 2;
	if(velocity_y < -2)
		velocity_y = -2;
	if(velocity_y > 2)
		velocity_y = 2;

	Particle.SetVelocity(velocity_x, velocity_y);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////

