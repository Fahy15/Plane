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
	void moveBackground(float t);    //��������
	virtual bool OnTouchBegan(Touch* touch, Event* event);
	virtual void OnTouchMoved(Touch* touch, Event* event);
	virtual void OnTouchEnded(Touch* touch, Event* event);

	//�����ӵ�
	void newBullet(float t);
	void moveBullet(float t);
	//���Ƶл�
	void newEnemy(float t);
	void moveEnemy(float t);
	//������ײ������Ϸ�߼�
	void update(float t);
	//��ըЧ��
	void newBomb(int x, int y);    //��ըЧ��
	void killMe(Ref* pSender);    //ɾ���Լ�
	void jumptoMenu();    //��ת���˵�
public:
	float px, py;    //�ɻ�����
	Vector<Sprite*> allBullet;    //���������ӵ�
	Vector<Sprite*>	allEnemy;    //����л�
	int score = 0;
};


#endif
