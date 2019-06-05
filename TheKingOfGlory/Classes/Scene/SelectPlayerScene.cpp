#include"SelectPlayerScene.h"
#include"Util/GameAudio.h" //������Ч
#include"ui/CocosGUI.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* SelectPlayerScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectPlayerScene::create();
	layer->setName("SelectPlayerScene");
	scene->addChild(layer);
	return scene;
}

bool SelectPlayerScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//��ӱ���ͼƬ
	Sprite* bg = Sprite::create("Pictures/Background/SelectPlayerScene.png"); //����ͼƬ
	bg->setPosition(Vec2(visible_Size.width / 2, visible_Size.height / 2));
	this->addChild(bg, -1);


	//�������ѡ��
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/SelectPlayerSound.mp3", true);//��Ч

	auto yaseButton = ui::Button::create("Pictures/UI/yase.png");
	yaseButton->setScale(0.5);//����
	yaseButton->setPosition(Vec2(,));
	yaseButton->addClickEventListener(CC_CALLBACK_1(SelectPlayerScene::yaseCallback, this));
	addChild(yaseButton);
	auto houyiButton = ui::Button::create("Pictures/UI/houyi.png");
	houyiButton->setScale(0.5);
	houyiButton->setPosition(Vec2(, ));
	houyiButton->addClickEventListener(CC_CALLBACK_1(SelectPlayerScene::houyiCallback, this));
	addChild(houyiButton);
	auto dajiButton = ui::Button::create("Pictures/UI/daji.png");
	dajiButton->setScale(0.5);
	dajiButton->setPosition(Vec2(, ));
	dajiButton->addClickEventListener(CC_CALLBACK_1(SelectPlayerScene::dajiCallback, this));
	addChild(dajiButton);

	return true;
}

void SelectPlayerScene::yaseCallback(Ref* pSender)
{
	auto roleName = Player::initWithRole(0, BLUE);//Ӧ����ɾ�̬����?
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/yaseChosen.mp3");
	//����ת����Ϸ��ʼ����
	auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(scene);
}

void SelectPlayerScene::houyiCallback(Ref* pSender)
{
	auto roleName = Player::initWithRole(1, BLUE);
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/houyiChosen.mp3");
	auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(scene);
}

void SelectPlayerScene::dajiCallback(Ref* pSender)
{
	auto roleName = Player::initWithRole(2, BLUE);
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/dajiChosen.mp3");
	auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(scene);
}