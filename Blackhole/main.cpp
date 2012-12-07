#include "globals.h"
#include "blackhole.h"

using namespace std;

#pragma comment(lib, "winmm.lib")

#define SCREENWIDTH  1250
#define SCREENHEIGHT 700

typedef struct Mouse
{
	int x,y;
}Mouse;
bool mleft = false;
bool mright = false;
bool mmiddle = false;

int xpos, ypos;
int ticker =0;

Mouse MousePos;

void RegisterMyWindow(HINSTANCE hInstance);
BOOL InitialiseMyWindow(HINSTANCE hInstance, int nCmdShow);
BOOL WaitFor(unsigned long delay);
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
void setBuffers();
void displayFrame();
void releaseResources();

bool g_bLoop = true;

//MAIN FUNCTION////////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int nCmdShow)			
{									
    MSG msg;	
	HDC	hdcWindow;

	RegisterMyWindow(hInstance);

   	if (!InitialiseMyWindow(hInstance, nCmdShow))
		return FALSE;
	
	setBuffers();

	g_game.GameSetUp();
		
	//GAME LOOP
	while(g_bLoop) 
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
		    if (msg.message==WM_QUIT)
				break;
			TranslateMessage (&msg);							
			DispatchMessage (&msg);
		}

		else
		{	
			g_game.Update();
			g_game.Render();
			displayFrame();
		}
    }

    releaseResources();
	return msg.wParam ;										
}

//FUNCTIONS///
// The RegisterMyWindow function creates and registers an instance of the Windows class
void RegisterMyWindow(HINSTANCE hInstance)
{
    WNDCLASSEX  wcex;									

    wcex.cbSize        = sizeof (wcex);				
    wcex.style         = CS_HREDRAW | CS_VREDRAW;		
    wcex.lpfnWndProc   = WndProc;						
    wcex.cbClsExtra    = 0;								
    wcex.cbWndExtra    = 0;								
    wcex.hInstance     = hInstance;						
    wcex.hIcon         = 0; 
    wcex.hCursor       = LoadCursor (NULL, IDC_ARROW);	
															
    wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
    wcex.lpszMenuName  = NULL;							
    wcex.lpszClassName = "FirstWindowClass";				
    wcex.hIconSm       = 0; 

	RegisterClassEx (&wcex);							
}

// This function initialises the current instance of the windows class and opens a window
BOOL InitialiseMyWindow(HINSTANCE hInstance, int nCmdShow)
{
	HWND        hwnd;
	hwnd = CreateWindow ("FirstWindowClass",					
						 "Black Hole",		  	
						 WS_OVERLAPPEDWINDOW,	
						 CW_USEDEFAULT,			
						 CW_USEDEFAULT,			
						 SCREENWIDTH,			
						 SCREENHEIGHT,			
						 NULL,					
						 NULL,					
						 hInstance,				
						 NULL);								
	if (!hwnd)
	{
		return FALSE;
	}

    ShowWindow (hwnd, nCmdShow);  //opens the window						
    UpdateWindow (hwnd);	
	ghwnd = hwnd;
	return TRUE;

}



BOOL WaitFor(unsigned long delay)
{
	static unsigned long clockStart = 0;
	unsigned long timePassed;
	unsigned long now = timeGetTime();

	timePassed = now - clockStart;
	if (timePassed >  delay)
	{
		clockStart = now;
		return TRUE;
	}
	else
		return FALSE;
}
	
			
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{


    switch (message)											
    {														
		case WM_CREATE:	
			break;

		case WM_SIZE:
			break;	

		case WM_KEYDOWN:
			g_game.m_keys[wParam]=true;
			break;

		case WM_KEYUP:
			g_game.m_keys[wParam]=false;
			break;

		case WM_MOUSEMOVE:
			MousePos.x = LOWORD (lParam);
			MousePos.y = HIWORD (lParam);
			break;

		case WM_LBUTTONDOWN:
			mleft  = true;
			mright = false;
			mmiddle = false;
			break;
			
		case WM_RBUTTONDOWN:
			mright = true;
			mleft  = false;
			mmiddle = false;
			break;

		case WM_MBUTTONDOWN:
			mmiddle = true;
			mleft  = false;
			mright = false;
			break;

		case WM_PAINT:
			
	
		    break;		

		case WM_DESTROY:	
			
			PostQuitMessage(0);	
								
			break;				
	}													

	return DefWindowProc (hwnd, message, wParam, lParam);		
															
}

void setBuffers()
{
	GetClientRect(ghwnd, &screenRect);	//creates rect based on window client area
	frontHDC = GetDC(ghwnd);			// Initialises front buffer device context (window)
	backHDC = CreateCompatibleDC(frontHDC);// sets up Back DC to be compatible with the front
	bitmapHDC=CreateCompatibleDC(backHDC);
	theOldFrontBitMap = CreateCompatibleBitmap(frontHDC, screenRect.right, 
		screenRect.bottom);		//creates bitmap compatible with the front buffer
    theOldBackBitMap = (HBITMAP)SelectObject(backHDC, theOldFrontBitMap);
								//creates bitmap compatible with the back buffer
	FillRect(backHDC, &screenRect, (HBRUSH)GetStockObject(0));	
}

//double buffering function
void displayFrame() //copy back buffer to the front (displayed) buffer
{
		BitBlt(frontHDC, screenRect.left, screenRect.top, screenRect.right, 
		screenRect.bottom, backHDC, 0, 0, SRCCOPY);
		FillRect(backHDC, &screenRect, (HBRUSH)GetStockObject(0));	
}

void releaseResources()
{
	SelectObject(backHDC,theOldBackBitMap);
	DeleteDC(backHDC);
	DeleteDC(bitmapHDC);
	ReleaseDC(ghwnd,frontHDC);
}