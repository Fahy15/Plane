#pragma once
#ifndef HELP_SCENE
#define HELP_SCENE

#include "cocos2d.h"
USING_NS_CC;

class HelpScene :
	public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HelpScene);
};

#endif