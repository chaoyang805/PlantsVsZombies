//
//  GrassGround.hpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/3/31.
//
//

#ifndef GrassGround_hpp
#define GrassGround_hpp

#include <stdio.h>
#include "cocos2d.h"
class GrassGround: public cocos2d::Sprite {
public:
    virtual bool initWithFile(const std::string& filename);
    static GrassGround* create(const std::string& filename);
};


#endif /* GrassGround_hpp */
