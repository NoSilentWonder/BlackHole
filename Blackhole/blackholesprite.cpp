#include "blackholesprite.h"
#include "globals.h"
#include <math.h>

// CONSTRUCTOR /////////////////////////////////////////////////////////////////////////////////
cBlackholeSprite::cBlackholeSprite()
{
	m_x = 400;
	m_y = 100;

	m_w = 13;
	m_h = 13;

	m_mass = 1;
	m_size = 1;

	m_centre_x = (int)(m_x + m_w*0.5f);
	m_centre_y = (int)(m_y + m_h*0.5f);

	m_points[0].x = m_x;			// Upper left
	m_points[0].y = m_y;
	m_points[1].x = m_x + m_w;		// Upper right	
	m_points[1].y = m_y;
	m_points[2].x = m_x;			// Lower left
	m_points[2].y = m_y + m_h;

	SetDisplayBitmap("Images/blackhole.bmp");
	SetDisplayBitmask("Images/holemask0.bmp");
}
////////////////////////////////////////////////////////////////////////////////////////////////

// DESTRUCTOR //////////////////////////////////////////////////////////////////////////////////
cBlackholeSprite::~cBlackholeSprite()
{
	// Nothing to clean-up
}
////////////////////////////////////////////////////////////////////////////////////////////////

// MOVE FUNCTION ///////////////////////////////////////////////////////////////////////////////
// Move function uses keyboard inputs for the arrowkeys
// to move the black hole around the game area.
// There are controls included to prevent the hole being
// moved off-screen.
void cBlackholeSprite::Move(bool k[256])
{
	m_prev_x = m_x;
	m_prev_y = m_y;
	// Move up when Up arrowkey pressed
	if(k[38])
	{
		m_y -= 2;
		if(m_y < 0)
			m_y = 0;
	}
	// Move down when Down arrowkey pressed
	if(k[40])
	{
		m_y += 2;
		if((m_y + m_h) > 662)
			m_y = 662 - m_h;
	}
	// Move left when Left arrowkey pressed
	if(k[37])
	{
		m_x -= 2;
		if(m_x < 0)
			m_x = 0;
	}
	// Move right when Right arrowkey pressed
	if(k[39])
	{
		m_x += 2;
		if((m_x + m_w) > 1233)
			m_x = 1233 - m_w;
	}

	m_centre_x = (int)(m_x + m_w*0.5f);
	m_centre_y = (int)(m_y + m_h*0.5f);

	m_points[0].x = m_x;			// Upper left
	m_points[0].y = m_y;
	m_points[1].x = m_x + m_w;		// Upper right	
	m_points[1].y = m_y;
	m_points[2].x = m_x;			// Lower left
	m_points[2].y = m_y + m_h;
}
////////////////////////////////////////////////////////////////////////////////////////////////

// INCREASEMASS FUNCTION ///////////////////////////////////////////////////////////////////////
// Function called when light particles collide with the black hole
// This function will be protected by a mutex to ensure the mass
// of the black hole is increased correctly.
void cBlackholeSprite::IncreaseMass(void)
{
	boost::mutex::scoped_lock lock(m_mass_mutex);
	m_mass += 1;
	if((m_mass%100) == 0)
		IncreaseSize();
}
////////////////////////////////////////////////////////////////////////////////////////////////

// SETDISPLAYBITMASK FUNCTION //////////////////////////////////////////////////////////////////
void cBlackholeSprite::SetDisplayBitmask(LPSTR szFileName)
{
	this->m_bitmask = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}
////////////////////////////////////////////////////////////////////////////////////////////////

// RENDER FUNCTION /////////////////////////////////////////////////////////////////////////////
void cBlackholeSprite::Render(void)
{
	HBITMAP originalBitMap;
	originalBitMap = (HBITMAP)SelectObject(bitmapHDC, m_bitmap);
	PlgBlt(backHDC, m_points, bitmapHDC, 0, 0, m_w,
		m_h, m_bitmask, 0, 0);
	SelectObject(bitmapHDC,originalBitMap); 
}
////////////////////////////////////////////////////////////////////////////////////////////////

// INCREASESIZE FUNCTION ///////////////////////////////////////////////////////////////////////
void cBlackholeSprite::IncreaseSize(void)
{
	m_size += 1;
	switch(m_size)
	{
	case 1:
		m_w = 13;
		m_h = 13;
		SetDisplayBitmap("Images/blackhole.bmp");
		SetDisplayBitmask("Images/holemask0.bmp");
		break;
	case 2:
		m_w = 25;
		m_h = 25;
		m_x -= 6;
		m_y -= 6;
		SetDisplayBitmask("Images/holemask1.bmp");
		break;
	case 3:
		m_w = 50;
		m_h = 50;
		m_x -= 12;
		m_y -= 12;
		SetDisplayBitmask("Images/holemask2.bmp");
		break;
	case 4:
		m_w = 75;
		m_h = 75;
		m_x -= 12;
		m_y -= 12;
		SetDisplayBitmask("Images/holemask3.bmp");
		break;
	case 5:
		m_w = 100;
		m_h = 100;
		m_x -= 12;
		m_y -= 12;
		SetDisplayBitmask("Images/holemask4.bmp");
		break;
	case 6:
		m_w = 125;
		m_h = 125;
		m_x -= 12;
		m_y -= 12;
		SetDisplayBitmask("Images/holemask5.bmp");
		break;
	case 7:
		m_w = 150;
		m_h = 150;
		m_x -= 12;
		m_y -= 12;
		SetDisplayBitmask("Images/holemask6.bmp");
		break;
	case 8:
		m_w = 175;
		m_h = 175;
		m_x -= 12;
		m_y -= 12;
		SetDisplayBitmask("Images/holemask7.bmp");
		break;
	case 9:
		m_w = 200;
		m_h = 200;
		m_x -= 12;
		m_y -= 12;
		SetDisplayBitmask("Images/holemask8.bmp");
		break;
	case 10:
		m_w = 225;
		m_h = 225;
		m_x -= 12;
		m_y -= 12;
		SetDisplayBitmask("Images/holemask9.bmp");
		break;
	case 11:
		m_w = 250;
		m_h = 250;
		m_x -= 12;
		m_y -= 12;
		SetDisplayBitmask("Images/holemask10.bmp");
		break;
	case 12:
		break;
	}	
}
////////////////////////////////////////////////////////////////////////////////////////////////