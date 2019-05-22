#include "SettingsScene.h"
#include "Util/GameAudio.h"

USING_NS_CC;

Scene* SettingsScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SettingsScene::create();
    scene->addChild(layer);
    return scene;
}

bool SettingsScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();

    Sprite * bg = Sprite::create("Pictures/Background/SettingBackground.png");
    bg->setPosition(Vec2( visibleSize.width / 2,visibleSize.height / 2));
    this->addChild(bg, -1);

    auto musicLabel = createLabel("Background Music");
    auto musicCheckBox = createCheckBox([=](Ref*, ui::CheckBox::EventType type) {
        GameAudio::getInstance()->setBgmOn(type == ui::CheckBox::EventType::SELECTED);
    });
    musicLabel->setPosition(Vec2(visibleSize.width *0.3 , visibleSize.height * 0.6f));
    musicCheckBox->setPosition(Vec2(visibleSize.width / 2 + 200, visibleSize.height * 0.6f));
    musicCheckBox->setSelected(GameAudio::getInstance()->getBgmOn());
    addChild(musicLabel);
    addChild(musicCheckBox);

    auto effectLabel = createLabel("Effect Music");
    auto effectCheckBox = createCheckBox([=](Ref*, ui::CheckBox::EventType type)
    {
        GameAudio::getInstance()->setEffectOn(type == ui::CheckBox::EventType::SELECTED);
    });
    effectLabel->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height * 0.5f));
    effectCheckBox->setPosition(Vec2(visibleSize.width / 2 + 200, visibleSize.height * 0.5f));
    effectCheckBox->setSelected(GameAudio::getInstance()->getEffectOn());
    addChild(effectLabel);
    addChild(effectCheckBox);

    addChild(createText());

    return true;
}

cocos2d::Menu* SettingsScene::createText()
{
    const auto buttons = Menu::create();

    const auto backButton = MenuItemLabel::create(
        Label::createWithTTF("OK",  "fonts/UnifrakturCook-Bold.ttf",64),
        CC_CALLBACK_1(SettingsScene::menuOkCallback, this));

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto baseY = visibleSize.height * 0.85f;

    backButton->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.2f);
    static_cast<Label*>(backButton->getLabel())->enableGlow(Color4B(0, 0, 0, 255 * 0.6f));

    buttons->addChild(backButton, 1);

    buttons->setPosition(0, 0);

    return buttons;
}

void SettingsScene::onEnter()
{
    Layer::onEnter();
   // GameAudio::getInstance()->playBgm("Sound/mainScene.mp3");
}

void SettingsScene::menuOkCallback(cocos2d::Ref * pSender)
{
    Director::getInstance()->popScene();
}

cocos2d::ui::CheckBox * SettingsScene::createCheckBox(std::function<void(Ref*, ui::CheckBox::EventType)> callback)
{
    auto checkBox = ui::CheckBox::create("Pictures/UI/checkbox_normal.png", "Pictures/UI/checkbox_active.png");
    checkBox->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    checkBox->addEventListener(callback);
    return checkBox;
}

cocos2d::Label * SettingsScene::createLabel(const char * text)
{
    auto label = Label::createWithTTF(text,"fonts/UnifrakturCook-Bold.ttf", 48);
    label->enableShadow(Color4B(0, 0, 0, 255 * 0.15f), Size(2, -2), 2);
    label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    return label;
}
