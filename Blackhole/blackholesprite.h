#ifndef _BLACKHOLESPRITE_H_
#define _BLACKHOLESPRITE_H_

#include "sprite.h"
#include <boost/thread/mutex.hpp>

class cBlackholeSprite : public cSprite
{
public:
	cBlackholeSprite();
	~cBlackholeSprite();
	void Move(bool k[256]);
	int GetMass(void){return m_mass;}
	int GetSize(void){return m_size;}
	int GetCentreX(void){return m_centre_x;}
	int GetCentreY(void){return m_centre_y;}
	int GetPrevX(void){return m_prev_x;}
	int GetPrevY(void){return m_prev_y;}
	void IncreaseMass(void);
	POINT * GetPoints(void){return & m_points[0];}
	void SetDisplayBitmask(LPSTR szFileName);
	void Render(void);	

private:
	void IncreaseSize(void);
	HBITMAP m_bitmask;

	POINT m_points[3];
	int m_mass; // Mass of the black hole - this will affect the velocities of the light particles
	int m_size; // From 1 to 11 - 11 = game won
	int m_centre_x;
	int m_centre_y;
	int m_prev_x;
	int m_prev_y;

	boost::mutex m_mass_mutex;
};


#endif