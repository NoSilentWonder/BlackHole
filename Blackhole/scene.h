#ifndef _SCENE_H_
#define _SCENE_H_

#include <stack>

class cScene
{
public:
	cScene();
	virtual ~cScene();
	virtual void setup();
	virtual void update();
	virtual void render();
	
protected:
	virtual void cleanup();
};

class cSceneManager
{
public:
	cSceneManager();
	~cSceneManager();	
	void push(cScene &s);
	void pop();
	cScene * m_activeScene;
private:
	std::stack<cScene*> m_scenes;
};

#endif	