#include "GameScene.h"
#include <SimpleAudioEngine.h>
#include "HelloWorldScene.h"

using namespace CocosDenshion;

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visible = Director::getInstance()->getVisibleSize();

	auto spbg = Sprite::create("BackGround.png");
	spbg->setAnchorPoint(Point::ZERO);
	spbg->setPosition(Point::ZERO);
	spbg->setTag(10);
	this->addChild(spbg);
	auto spbg2 = Sprite::create("BackGround.png");
	spbg2->setAnchorPoint(Point::ZERO);
	spbg2->setPosition(Point(0,spbg->getPositionY() + spbg->getContentSize().height));
	spbg2->setTag(11);
	this->addChild(spbg2);

	//分数显示
	auto scoreLabel = Label::create("score: 0", "Marker Felt", 20);
	scoreLabel->setPosition(Vec2(10, visible.height - 10));
	scoreLabel->setAnchorPoint(Vec2(0, 1));
	this->addChild(scoreLabel);
	scoreLabel->setTag(120);

	//添加整张飞机图片
	auto spPlane = Sprite::create("plane2.png");
	spPlane->setPosition(Point(visible.width / 2, 0));
	spPlane->setAnchorPoint(Vec2(0.5, 0));
	spPlane->setTag(110);
	this->addChild(spPlane);

	//auto spPlane = Sprite::create();
	//spPlane->setTag(110);
	//spPlane->setPosition(Point(visible.width / 2, 0));
	//spPlane->setAnchorPoint(Vec2(0.5, 0));
	//this->addChild(spPlane);
	//Vector<SpriteFrame*> allFrame;    //保存动画所有帧
	////创建每一帧,循环播放
	//for (int i = 0; i < 4; i++)
	//{
	//	SpriteFrame* sf = SpriteFrame::create("plane4.png", Rect(0, 82 * i, 67, 82));
	//	allFrame.pushBack(sf);
	//}
	//Animation * ani = Animation::createWithSpriteFrames(allFrame, 0.3);
	//spPlane->runAction(RepeatForever::create(Animate::create(ani)));
	//通过触摸事件控制飞机移动
	EventListenerTouchOneByOne* touch = EventListenerTouchOneByOne::create();
	touch->setSwallowTouches(true);
	touch->onTouchBegan = CC_CALLBACK_2(GameScene::OnTouchBegan,this);
	touch->onTouchMoved = CC_CALLBACK_2(GameScene::OnTouchMoved, this);
	touch->onTouchEnded = CC_CALLBACK_2(GameScene::OnTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);
	//计划任务一背景滚动
	this->schedule(schedule_selector(GameScene::moveBackground), 0.01);
	//处理子弹发射
	this->schedule(schedule_selector(GameScene::newBullet), 0.3);
	this->schedule(schedule_selector(GameScene::moveBullet), 0.01);
	//控制敌机
	this->schedule(schedule_selector(GameScene::newEnemy), 0.3);
	this->schedule(schedule_selector(GameScene::moveEnemy), 0.01);
	//调用update方法
	this->scheduleUpdate();
	return true;
}

Scene * GameScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

void GameScene::moveBackground(float t)
{
	auto visiable = Director::getInstance()->getVisibleSize();
	auto spbg1 = this->getChildByTag(10);
	auto spbg2 = this->getChildByTag(11);
	spbg1->setPositionY(spbg1->getPositionY() - 1);
	if (spbg1->getPositionY() < -(spbg1->getContentSize().height))
	{
		spbg1->setPositionY(0);
	}
	spbg2->setPositionY(spbg1->getPositionY()+ spbg1->getContentSize().height);
}

bool GameScene::OnTouchBegan(Touch * touch, Event * event)
{
	px = touch->getLocation().x;
	py = touch->getLocation().y;
	return true;
}

void GameScene::OnTouchMoved(Touch * touch, Event * event)
{
	float nx = touch->getLocation().x - px;
	float ny = touch->getLocation().y - py;
	auto spPlane = this->getChildByTag(110);
	spPlane->runAction(MoveBy::create(0,Point(nx, ny)));
	px = touch->getLocation().x;
	py = touch->getLocation().y;
}

void GameScene::OnTouchEnded(Touch * touch, Event * event)
{
}

void GameScene::newBullet(float t)
{
	auto spPlane = this->getChildByTag(110);
	Sprite* spBullet = Sprite::create("bullet.png");
	spBullet->setPosition(spPlane->getPosition()+Vec2(0,spPlane->getContentSize().height/2));
	this->addChild(spBullet);
	this->allBullet.pushBack(spBullet);
}

void GameScene::moveBullet(float t)
{
	auto visible = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < allBullet.size(); i++)
	{
		auto nowbullet = allBullet.at(i);
		nowbullet->setPositionY(nowbullet->getPositionY() + 3);
		if (nowbullet->getPositionY() > visible.height)
		{
			nowbullet->removeFromParent();
			allBullet.eraseObject(nowbullet);
			i--;
		}
	}
}

void GameScene::newEnemy(float t)
{
	auto visible = Director::getInstance()->getVisibleSize();
	Sprite* enemy = nullptr;
	int num = rand() % 3;
	switch (num)
	{
	case 0:
		enemy = Sprite::create("enemy.png");
		enemy->setTag(1000);
		break;
	case 1:
		enemy = Sprite::create("enemy2.png");
		enemy->setTag(2000);
		break;
	case 2:
		enemy = Sprite::create("enemy3.png");
		enemy->setTag(3000);
		break;
	default:
		break;
	}

	enemy->setPosition(Point(rand() % 320, visible.height));
	this->addChild(enemy);
	this->allEnemy.pushBack(enemy);
}

void GameScene::moveEnemy(float t)
{
	for (int i = 0; i < allEnemy.size(); i++)
	{
		auto newEnemy = allEnemy.at(i);
		newEnemy->setPositionY(newEnemy->getPositionY() - 3);
		if (newEnemy->getPositionY() < 0)
		{
			newEnemy->removeFromParent();
			allEnemy.eraseObject(newEnemy);
			i--;
		}
	}
}

void GameScene::update(float t)
{
	auto spPlane = this->getChildByTag(110);
	Rect rp(spPlane->getPositionX(), 
		    spPlane->getPositionY(), 
			spPlane->getContentSize().width, 
			spPlane->getContentSize().height);
	for (int i = 0; i < allEnemy.size(); i++)
	{
		auto nowenemy = allEnemy.at(i);
		Rect er(nowenemy->getPositionX(), nowenemy->getPositionY(), nowenemy->getContentSize().width, nowenemy->getContentSize().height);
		CCLOG("%f,%f", nowenemy->getContentSize().width, nowenemy->getContentSize().height);
		//敌机与我机碰撞检测
		if (rp.intersectsRect(er))
		{
			//敌机消失
			nowenemy->removeFromParent();
			allEnemy.eraseObject(nowenemy);
			i--;
			//粒子效果
			auto ps = ParticleSystemQuad::create("bomb.plist");
			ps->setPosition(spPlane->getPositionX(), spPlane->getPositionY());
			this->addChild(ps);
			//我机消失
			//spPlane->removeFromParent();
			//音效
			SimpleAudioEngine::getInstance()->playEffect("eat.wav");
			//gameover
			//Director::getInstance()->getActionManager()->pauseAllRunningActions();    //暂停动作
			this->pauseSchedulerAndActions();
			auto spover = Sprite::create("gameover.png");
			spover->setScaleX(1.2);
			spover->setAnchorPoint(Point::ZERO);
			spover->setPosition(Point::ZERO);
			this->addChild(spover);
			auto act = Sequence::create(DelayTime::create(2),
				                        CallFunc::create(this,callfunc_selector(GameScene::jumptoMenu)),
				                        NULL);
			this->runAction(act);
		}
		//子弹与敌机碰撞检测
		for (int j = 0; j < allBullet.size(); j++)
		{
			auto nowbullet = allBullet.at(j);
			Rect br(nowbullet->getPositionX(), nowbullet->getPositionY(), nowbullet->getContentSize().width, nowbullet->getContentSize().height);
			if (br.intersectsRect(er))
			{
				//子弹碰到敌机
				Label* labScore = (Label*)this->getChildByTag(120);
				score += nowenemy->getTag();
				//爆炸效果
				newBomb(nowbullet->getPositionX(), nowbullet->getPositionY());
				//粒子效果
				auto ps = ParticleSystemQuad::create("bomb.plist");
				ps->setPosition(nowbullet->getPositionX(), nowbullet->getPositionY());
				this->addChild(ps);
				//音效
				SimpleAudioEngine::getInstance()->playEffect("eat.wav");
				//加分
				labScore->setString(String::createWithFormat("score: %d", score)->getCString());
				//子弹消失
				nowbullet->removeFromParent();
				allBullet.eraseObject(nowbullet);
				//敌机消失
				nowenemy->removeFromParent();
				allEnemy.eraseObject(nowenemy);
				i--;
				break;
				
			}
		}
	}
}

void GameScene::newBomb(int x, int y)
{
}

void GameScene::killMe(Ref * pSender)
{
}

void GameScene::jumptoMenu()
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
