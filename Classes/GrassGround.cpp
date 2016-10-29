//
//  GrassGround.cpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/3/31.
//
//

#include "GrassGround.hpp"

USING_NS_CC;
//bool GrassGround::init() {
//    if (!Node::init()) {
//        return false;
//    }
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    
//    setContentSize(Size(visibleSize.width, visibleSize.height / 3));
//    setPhysicsBody(PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height / 3)));
//    return true;
//}
GrassGround* GrassGround::create(const std::string& filename) {
    GrassGround *pRet = new(std::nothrow) GrassGround();
    if (pRet && pRet->initWithFile(filename)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}


bool GrassGround::initWithFile(const std::string& fileName) {
    if(!Sprite::initWithFile(fileName)) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    setAnchorPoint(Vec2(0, 0));
    setScale(0.5);
    setPosition(0,0);
    setContentSize(visibleSize);
    return true;
}