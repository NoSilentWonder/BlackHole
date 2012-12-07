#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

#include "scene.h"

class cTitleScene : public cScene
{
public:
	cTitleScene();
	virtual ~cTitleScene();
	virtual void setup();
	virtual void update();
	virtual void render();
	
private:
	virtual void cleanup();

};

#endif