//
//  Sun.hpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/4/2.
//
//

#ifndef Sun_hpp
#define Sun_hpp
#include "cocos2d.h"
#include <stdio.h>
class Sun: public cocos2d::Sprite {
public:
    virtual bool init();
    
    CREATE_FUNC(Sun);
    
private:
    float _velocityY = 2;
    float _velocityX = 0;
    cocos2d::Size _visibleSize;
    void scheduleMove(float delta);
};
#endif /* Sun_hpp */
