#ifndef _SUPERNOVASCENE_H_
#define _SUPERNOVASCENE_H_

#include "scene.h"

class cSupernovaScene : public cScene
{
public:
	cSupernovaScene();
	virtual ~cSupernovaScene();
	virtual void setup();
	virtual void update();
	virtual void render();
	
private:
	virtual void cleanup();

};

#endif