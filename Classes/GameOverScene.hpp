//
//  GameOverScene.hpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/4/6.
//
//

#ifndef GameOverScene_hpp
#define GameOverScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"

static bool _success = false;
class GameOverScene: public cocos2d::LayerColor {
    
public:
    static cocos2d::Scene* createScene(bool success);
    
    virtual bool init();
    
    CREATE_FUNC(GameOverScene);
    
    cocos2d::ui::AbstractCheckButton::ccWidgetClickCallback retryCallback;
    cocos2d::ui::AbstractCheckButton::ccWidgetClickCallback exitCallback;
    
};

#endif /* GameOverScene_hpp */
