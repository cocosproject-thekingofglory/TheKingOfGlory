#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class SettingsScene : public cocos2d::Layer
{
private:
    void menuOkCallback(cocos2d::Ref *pSender);

    cocos2d::ui::CheckBox * createCheckBox(std::function<void(cocos2d::Ref*, cocos2d::ui::CheckBox::EventType)> callback);
    cocos2d::Label * createLabel(const char * text);
    cocos2d::Menu* createText();

    void onEnter();
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SettingsScene);
};
