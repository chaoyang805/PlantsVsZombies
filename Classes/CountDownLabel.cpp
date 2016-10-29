//
//  CountDownLabel.cpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/4/8.
//
//

#include "CountDownLabel.hpp"
USING_NS_CC;

CountDownLabel* CountDownLabel::create(int totalTime) {
    CountDownLabel *pRet = new(std::nothrow) CountDownLabel();
    if (pRet && pRet->init(totalTime)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}
bool CountDownLabel::init(int totalTime) {
    if(!Label::init()) {
        return false;
    }
    _totalTime = totalTime;
    _restTime = _totalTime;
    std::stringstream text;
    text << "time left:" << _restTime;
    setTextColor(Color4B::BLACK);
    setSystemFontSize(30);
    setString(text.str());
    setAnchorPoint(Vec2(0, 1));
    return true;
}

void CountDownLabel::startCountDown() {
    _restTime = _totalTime;
    schedule(schedule_selector(CountDownLabel::countDown), 1);
}

void CountDownLabel::countDown(float delta) {
    _restTime--;
    if (onPreTimesUp && _restTime == 15) {
        onPreTimesUp();
        setTextColor(Color4B::RED);
    }
    if (onTimesUp && _restTime == 0) {
        onTimesUp();
        unschedule(schedule_selector(CountDownLabel::countDown));
        return;
    }
    std::stringstream text;
    text << "time left:" << _restTime;
    setString(text.str());
}