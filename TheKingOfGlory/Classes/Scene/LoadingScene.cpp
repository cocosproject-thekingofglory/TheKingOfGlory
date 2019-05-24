#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "LoginScene.h"
#include "GameScene.h"

USING_NS_CC;
using namespace CocosDenshion;


cocos2d::Scene * LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init())
		return false;
	visible_Size = Director::getInstance()->getVisibleSize();
	
	createBackground();
	createProgressBar();

	return true;
}

void LoadingScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	

	//将游戏资源文件名放入ValueVector中
	ValueVector spriteSheets, effects, musics;

	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_move_down.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_move_left.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_move_right.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_move_up.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_move_leftdown.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_move_leftup.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_move_rightdown.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_move_rightup.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_attack_down.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_attack_left.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_attack_right.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_attack_up.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_attack_leftdown.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_attack_leftup.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_attack_rightdown.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_attack_rightup.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_dead_down.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_dead_left.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_dead_right.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_dead_up.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_dead_leftdown.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_dead_leftup.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_dead_rightdown.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_dead_rightup.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_down.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_left.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_right.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_up.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_leftdown.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_leftup.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_rightdown.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_rightup.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_behit_down.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_behit_left.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_behit_right.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_behit_up.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_behit_leftdown.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_behit_leftup.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_behit_rightdown.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_behit_rightup.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_down.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_left.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_right.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_up.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_leftdown.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_leftup.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_rightdown.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_skill_rightup.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_stand_down.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_stand_left.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_stand_right.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_stand_up.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_stand_leftdown.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_stand_leftup.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_stand_rightdown.plist"));
	spriteSheets.push_back(Value("Pictures/Player/warrior/warrior_stand_rightup.plist"));
	spriteSheets.push_back(Value("Pictures/Soldier/soldierAttack.plist"));
	spriteSheets.push_back(Value("Pictures/Soldier/soldierMove.plist"));
	spriteSheets.push_back(Value("Pictures/Tower/towerItem.plist"));
	spriteSheets.push_back(Value("Pictures/Tower/blast.plist"));
	spriteSheets.push_back(Value("Pictures/Store/equipment.plist"));

	musics.push_back(Value("Sounds/StartBgm.mp3"));
	musics.push_back(Value("Sounds/GameBgm.mp3"));
	musics.push_back(Value("Sounds/LoginBgm.mp3"));

	effects.push_back(Value("Sounds/LoginClick.wav"));
	effects.push_back(Value("Sounds/ButtonClick.wav"));
	effects.push_back(Value("Sounds/Win.wav"));
	effects.push_back(Value("Sounds/Lose.wav"));

	sourceCount = spriteSheets.size() + effects.size() + musics.size();

	progress_Interval = 100 / sourceCount;
	
	loadSpriteSheets(spriteSheets);
	loadMusic(musics);
	loadEffect(effects);
	

}

void LoadingScene::createBackground()
{
	//添加背景图
	auto background = Sprite::create("Pictures/Background/LoadingBackground.png");
	background->setPosition(Vec2(visible_Size.width / 2, visible_Size.height / 2));
	this->addChild(background, -1);
}

void LoadingScene::createProgressBar()
{
	//创建进度条
	auto barSprite = Sprite::create("Pictures/UI/Bar.png");
	progress = ProgressTimer::create(barSprite);
	progress->setPercentage(0.0f);
	progress->setMidpoint(Point(0.0f, 0.5f));
	progress->setBarChangeRate(Point(1.0f, 0.0f));
	progress->setType(ProgressTimer::Type::BAR);
	progress->setPosition(Vec2(visible_Size.width / 2, visible_Size.height / 2));
	this->addChild(progress);
}

void LoadingScene::loadMusic(ValueVector musicFiles)
{
	//加载音乐
	for (Value& v : musicFiles)
	{
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic(v.asString().c_str());
		progressUpdate();
	}
}

void LoadingScene::loadEffect(ValueVector effectFiles)
{
	//加载音效
	for (Value &v : effectFiles) {
		SimpleAudioEngine::getInstance()->preloadEffect(v.asString().c_str());
		progressUpdate();
	}
}

void LoadingScene::loadSpriteSheets(ValueVector spriteFiles)
{
	//加载精灵表单
	for (Value &v : spriteFiles) {
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(v.asString().c_str());
		progressUpdate();
	}
}

void LoadingScene::progressUpdate()
{
	if (--sourceCount) {
		//根据剩余的资源数设置进度条进度
		progress->setPercentage(100.0f - (progress_Interval * sourceCount));
	}
	else {
		//游戏资源加载完毕，切换场景
		auto pft = ProgressFromTo::create(0.5f, progress->getPercentage(), 100);

		auto callFunc = CallFunc::create([=] {

			auto delay = DelayTime::create(2.0f);
			//const auto transition = TransitionFade::create(1, LoginScene::createScene());
			const auto transition = TransitionFade::create(1, GameScene::createScene());
			auto action = Sequence::create(delay, transition, NULL);
			Director::getInstance()->replaceScene(transition);
		});
		auto action = Sequence::create(pft, callFunc, NULL);

		progress->runAction(action);
	}
}
