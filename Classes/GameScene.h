#pragma once
#ifndef GAME_SCENE
#define GAME_SCENE

#include "cocos2d.h"
USING_NS_CC;

class GameScene: public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameScene);
	static Scene* createScene();
	void moveBackground(float t);    //背景滚动
	virtual bool OnTouchBegan(Touch* touch, Event* event);
	virtual void OnTouchMoved(Touch* touch, Event* event);
	virtual void OnTouchEnded(Touch* touch, Event* event);

	//控制子弹
	void newBullet(float t);
	void moveBullet(float t);
	//控制敌机
	void newEnemy(float t);
	void moveEnemy(float t);
	//处理碰撞检测和游戏逻辑
	void update(float t);
	//爆炸效果
	void newBomb(int x, int y);    //爆炸效果
	void killMe(Ref* pSender);    //删除自己
	void jumptoMenu();    //跳转主菜单
public:
	float px, py;    //飞机坐标
	Vector<Sprite*> allBullet;    //保存所有子弹
	Vector<Sprite*>	allEnemy;    //保存敌机
	int score = 0;
};


#endif
