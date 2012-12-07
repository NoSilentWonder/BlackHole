#ifndef _MENUSCENE_H_
#define _MENUSCENE_H_

#include "scene.h"

class cMenuScene : public cScene
{
public:
	cMenuScene();
	virtual ~cMenuScene();
	virtual void setup();
	virtual void update();
	virtual void render();
	
private:
	virtual void cleanup();

};

#endif