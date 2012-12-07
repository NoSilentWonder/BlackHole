#ifndef _SUNSPRITE_H_
#define _SUNSPRITE_H_

#include "sprite.h"

class cSunSprite : public cSprite
{
public:
	cSunSprite();
	~cSunSprite();
	POINT * GetPoints(void){return & m_points[0];}
	int GetCentreX(void){return m_centre_x;}
	int GetCentreY(void){return m_centre_y;}
	void SetDisplayBitmask(LPSTR szFileName);
	void Render(void);	

private:
	HBITMAP m_bitmask;

	POINT m_points[3];

	int m_centre_x;
	int m_centre_y;
};


#endif