#include "HelloWorldScene.h"
#include "GameScene.h"
#include "HelpScene.h"
#include "AboutScene.h"

USING_NS_CC;

enum ButtonTag
{
	CLOSETAG = 1,
	STARTTAG = 2,
	HELPTAG = 3,
	ABOUTTAG =4
};

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
	closeItem->setTag(ButtonTag::CLOSETAG);
	//新增菜单条目
	auto gameItem = MenuItemFont::create("Start Game", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	auto helpItem = MenuItemFont::create("Help", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	auto aboutItem = MenuItemFont::create("About", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	
	gameItem->setPosition(Vec2(origin.x + visibleSize.width /2, origin.y + visibleSize.height /2));
	helpItem->setPosition(Vec2(origin.x + visibleSize.width /2,
								origin.y + visibleSize.height /2 - gameItem->getContentSize().height));
	aboutItem->setPosition(Vec2(origin.x + visibleSize.width /2,
								origin.y + visibleSize.height /2
								- gameItem->getContentSize().height - helpItem->getContentSize().height));
	gameItem->setTag(ButtonTag::STARTTAG);
	helpItem->setTag(ButtonTag::HELPTAG);
	aboutItem->setTag(ButtonTag::ABOUTTAG);


    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, gameItem, helpItem, aboutItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("plane.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	MenuItem* pressItem = (MenuItem*)pSender;
	Scene* scene = nullptr;
	switch (pressItem->getTag())
	{
	case ButtonTag::CLOSETAG:
	{
		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}
	break;
	case ButtonTag::STARTTAG:
	{
		scene = GameScene::createScene();
	}
		break;
	case ButtonTag::HELPTAG:
	{
		scene = HelpScene::createScene();
	}
		break;
	case ButtonTag::ABOUTTAG:
	{
		scene = AboutScene::createScene();
	}
		break;
	default:
		break;
	}

	if (scene!=nullptr)
	{
		Director::getInstance()->pushScene(scene);
	}

}
