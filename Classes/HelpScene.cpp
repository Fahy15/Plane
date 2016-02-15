#include "HelpScene.h"
#include "HelloWorldScene.h"

Scene * HelpScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = HelpScene::create();
	scene->addChild(layer);
	return scene;
}

bool HelpScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Sprite* spbg = Sprite::create("planeBG.jpg");
	spbg->setAnchorPoint(Point::ZERO);
	spbg->setPosition(Point::ZERO);
	this->addChild(spbg);
	auto touchListener = EventListenerTouchOneByOne::create();    //创建监听器
	//监听动作
	touchListener->onTouchBegan = [](Touch* touch, Event* event) {    //必须要touchbegin，才能调用touchmove
		return true;
	};
	touchListener->onTouchMoved = [](Touch* touch, Event* event) {
		Director::getInstance()->popScene();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);    //分发对象

	return true;
}
