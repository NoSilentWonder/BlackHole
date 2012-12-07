#ifndef _PARTICLESPRITE_H_
#define _PARTICLESPRITE_H_

#include "sprite.h"

class cParticleSprite : public cSprite 
{
public:
	cParticleSprite();
	virtual ~cParticleSprite();
	void Move(void);
	void SetVelocity(float vx, float vy);
	float GetVelocityX(void){return m_velocity_x;}
	float GetVelocityY(void){return m_velocity_y;}
	float GetTrueX(void){return m_true_x;}
	float GetTrueY(void){return m_true_y;}

private:
	float m_velocity_x;
	float m_velocity_y;
	float m_true_x;
	float m_true_y;
};


#endif