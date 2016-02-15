#pragma once
#ifndef ABOUT_SCENE
#define ABOUT_SCENE

#include "cocos2d.h"
USING_NS_CC;

class AboutScene:
	public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(AboutScene);
	static Scene* createScene();
};


#endif