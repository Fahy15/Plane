#include "AboutScene.h"

bool AboutScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Sprite* spbg = Sprite::create("planeBG.jpg");
	spbg->setAnchorPoint(Point::ZERO);
	spbg->setPosition(Point::ZERO);
	this->addChild(spbg);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
	};
	touchListener->onTouchMoved = [](Touch* touch, Event* event) {
		Director::getInstance()->popScene();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

Scene * AboutScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = AboutScene::create();
	scene->addChild(layer);
	return scene;
}
