//
//  CCProgressLayer.cpp
//  HelloCpp
//
//  Created by CK on 14-6-5.
//
//

#include "CCProgressLayer.h"

CCProgressLayer::CCProgressLayer():
_progress_rate(0.f),
_progress_sp(NULL),
_res_index(0),
_success_func(NULL),
_success_target(NULL)
{
    
}

CCProgressLayer::~CCProgressLayer()
{
    reset();
}

CCProgressLayer * CCProgressLayer::createWithResouceList(vector<LoadableObj*> resouce_list){
    CCProgressLayer * layer = new CCProgressLayer();
    if (layer && layer->init()) {
        layer->_resouce_list = resouce_list;
        layer->autorelease();
    }
    else{
        CC_SAFE_DELETE(layer);
    }
    return layer;
}

void CCProgressLayer::reset(){
    
    vector<LoadableObj*>::iterator _it = _resouce_list.begin();
    while (_it != _resouce_list.end()) {
        delete  (*_it);
        ++_it;
    }
    _resouce_list.clear();
    _res_index = 0;
}

void CCProgressLayer::startLoad(){
//    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    _res_index = 0;
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CCProgressLayer::loadOneResource), this, 0, false);
}

bool CCProgressLayer::init(){
    bool res = CCLayer::init();
    if (res) {
        CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
        
        CCSprite* loadBg = CCSprite::create("vs_loading_bg.png");//进程条的底图
        loadBg->setPosition(CCPoint(visibleSize.width * 0.5,visibleSize.height * 0.3));
        this->addChild(loadBg,1);

        
        _progress_sp = CCProgressTimer::create(CCSprite::create("vs_loading_blood.png"));
        _progress_sp->setBarChangeRate(CCPoint(1,0));//设置进程条的变化速率
        _progress_sp->setType(kCCProgressTimerTypeBar);//设置进程条的类型
        _progress_sp->setMidpoint(CCPoint(0,1));//设置进度的运动方向
        _progress_sp->setPosition(CCPoint(visibleSize.width * 0.5,visibleSize.height * 0.3));
        _progress_sp->setPercentage(0.0f);//设置初始值为0
        this->addChild(_progress_sp,2);
        

        CCSprite * loadStrBg = CCSprite::create("loading_3.png");
        loadStrBg->setPosition(CCPoint(visibleSize.width * 0.5,visibleSize.height * 0.2));
        this->addChild(loadStrBg,3);
        
        _progress_str = CCProgressTimer::create(CCSprite::create("loading_2.png"));
        _progress_str->setBarChangeRate(CCPoint(1,0));//设置进程条的变化速率
        _progress_str->setType(kCCProgressTimerTypeBar);//设置进程条的类型
        _progress_str->setMidpoint(CCPoint(0,1));//设置进度的运动方向
        _progress_str->setPosition(CCPoint(visibleSize.width * 0.5,visibleSize.height * 0.2));
        _progress_str->setPercentage(0.0f);//设置初始值为0
        this->addChild(_progress_str,4);
        
        
        m_bg = CCMenuItemSprite::create(CCSprite::create("kakao_loading_bk.jpg"), NULL) ;
        m_bg->setPosition(CCPoint(visibleSize.width * 0.5,visibleSize.height * 0.5));
        this->addChild(m_bg,0);

    }
    return res;
}

void CCProgressLayer::setProgressRate(float progress_rate){
    
    _progress_sp->stopAllActions();
    _progress_sp->runAction(CCProgressFromTo::create(1, _progress_rate, progress_rate));
    
    _progress_str->stopAllActions();
    _progress_str->runAction(CCProgressFromTo::create(1, _progress_rate, progress_rate));
    
    _progress_rate = progress_rate;
    
}

float CCProgressLayer::getProgressRate(){
    return _progress_rate;
}

void CCProgressLayer::loadOneResource( float dt ){
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(CCProgressLayer::loadOneResource), this);
    if (_res_index >= _resouce_list.size()) {
        LoadingFinished();
    }
    else{
        _resouce_list[_res_index]->setCallBackFunc(this, callfuncO_selector(CCProgressLayer::loadingCallBack));
        _resouce_list[_res_index]->load();
    }
    
}

void CCProgressLayer::LoadingFinished(){
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CCProgressLayer::LoadingFinishedThread), this, 0, false);
}

void CCProgressLayer::LoadingFinishedThread( float dt ){
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(CCProgressLayer::LoadingFinishedThread), this);
    reset();
    if (_success_func && _success_target) {
        (_success_target->*_success_func)();
    }
}

void CCProgressLayer::LoadingErr(bool ignore){
    reset();
}

void CCProgressLayer::setSuccessCallBack(cocos2d::CCObject *target, SEL_CallFunc func){
    this->_success_target = target;
    this->_success_func = func;
}

void CCProgressLayer::loadingCallBack(cocos2d::CCObject *obj){
    ++_res_index;
    this->setProgressRate( (float)_res_index / (float)_resouce_list.size() * 100.f);
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CCProgressLayer::loadOneResource), this, 0, false);
//    loadOneResource();
}