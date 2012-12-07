#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <windows.h>

class cSprite 
{
public:
	cSprite();
	virtual ~cSprite();
	void SetDimensions(const int w, const int h);
	int GetX(void){return m_x;}
	int GetY(void){return m_y;}
	int GetWidth(void){return m_w;}
	int GetHeight(void){return m_h;}
	HBITMAP GetBitmap(void){return m_bitmap;}
	void MoveTo(const int x, const int y);
	void SetDisplayBitmap(LPSTR szFileName);
	virtual void Render(void);	

protected:
	int m_x, m_y;	//position on screen
	int m_w, m_h;	//width and height
	
	HBITMAP m_bitmap;
};

#endif