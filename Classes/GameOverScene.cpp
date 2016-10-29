//
//  GameOverScene.cpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/4/6.
//
//

#include "GameOverScene.hpp"
#include "MainGameScene.hpp"
USING_NS_CC;

Scene* GameOverScene::createScene(bool success) {
    _success = success;
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameOverScene::init() {
    if (!LayerColor::initWithColor(Color4B::WHITE)) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    std::string message = "Zombie ate your brains!";
    std::string buttonMsg = "Try again";
    if (_success) {
        message = "You successfully defend you house";
        buttonMsg = "One more time";
    }
    auto label = Label::createWithTTF(message, "fonts/Marker Felt.ttf", 30);
    label->setTextColor(Color4B::BLACK);
    label->setPosition(visibleSize.width / 2, visibleSize.height -  label->getContentSize().height - 10);
    addChild(label);
    
    auto retryButton = cocos2d::ui::Button::create();
    retryButton->setTitleText(buttonMsg);
    retryButton->setTitleFontName("fonts/Marker Felt.ttf");
    retryButton->setTitleColor(Color3B::BLACK);
    retryButton->setTitleFontSize(25);
    retryCallback = [](Ref* button){
        Director::getInstance()->replaceScene(MainGameScene::createScene());
    };
    retryButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 20));
    retryButton->addClickEventListener(retryCallback);
    addChild(retryButton);
    
    auto exitButton = cocos2d::ui::Button::create();
    exitButton->setTitleText("Exit");
    exitButton->setPosition(Vec2(visibleSize.width / 2, retryButton->getPositionY() - exitButton->getContentSize().height - 20));
    exitButton->setTitleFontName("fonts/Marker Felt.ttf");
    exitButton->setTitleColor(Color3B::BLACK);
    exitButton->setTitleFontSize(25);
    exitButton->addClickEventListener([](Ref* sender){
        Director::getInstance()->end();
    });
    addChild(exitButton);
    return true;
}