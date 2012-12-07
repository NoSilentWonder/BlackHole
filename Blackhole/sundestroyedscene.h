#ifndef _SUNDESTROYEDSCENE_H_
#define _SUNDESTROYEDSCENE_H_

#include "scene.h"

class cSunDestroyedScene : public cScene
{
public:
	cSunDestroyedScene();
	virtual ~cSunDestroyedScene();
	virtual void setup();
	virtual void update();
	virtual void render();
	
private:
	virtual void cleanup();

};

#endif