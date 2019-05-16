#ifndef __UTIL_ANIMATIONLOADER_H__
#define __UTIL_ANIMATIONLOADER_H__

#include "cocos2d.h"

class AnimationLoader
{
public:
    AnimationLoader();

    void runAnimation(const std::string& animationName, cocos2d::Sprite * sprite);

    void stopAnimation(cocos2d::Sprite * sprite);

    void stopAnimation(const std::string& animationName, cocos2d::Sprite * sprite);
    

    cocos2d::Animation * getAnimation(const std::string & animationName);
    
protected:

    void loadAnimation(const std::string& animationName, float delay, int num);
private:

    cocos2d::AnimationCache * animationCache;

    unsigned int getFlag(const std::string & animationName);
};

#endif