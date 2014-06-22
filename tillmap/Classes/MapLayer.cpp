//
//  MapLayer.cpp
//  tilemap
//
//  Created by king hin on 14-6-19.
//
//

#include "MapLayer.h"

MapLayer::MapLayer():
_map_height(0.f),
_map_width(0.f),
_position_x_begin(0.f),
_position_y_begin(0.f),
_limit_x(0.f),
_limit_y(0.f),
_is_moving(false)
{

}

MapLayer::~MapLayer()
{
    
}

MapLayer * MapLayer::createWithInfo(MapInfo * info)
{
    MapLayer * layer = new MapLayer();
    if (layer && layer->initWithInfo(info)) {
        layer->autorelease();
    }
    else{
        CC_SAFE_DELETE(layer);
    }
    return layer;
}

bool MapLayer::initWithInfo(MapInfo * info)
{
    bool res = Layer::init();
    if (res) {
        this->setTouchEnabled(true);
        
        _map_height = info->getMapHeight();
        _map_width = info->getMapWidth();
        
        _win_height = Director::getInstance()->getWinSize().height;
        _win_width = Director::getInstance()->getWinSize().width;
        
        _limit_x = (_win_width - _map_width) ;
        _limit_y = (_win_height - _map_height) ;
        
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        
        touchListener->onTouchBegan = CC_CALLBACK_2(MapLayer::onTouchBegan, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(MapLayer::onTouchMoved, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(MapLayer::onTouchEnded, this);
        touchListener->onTouchCancelled = CC_CALLBACK_2(MapLayer::onTouchCancelled, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        this->setPosition(Vec2(0,0));
        
    }
    return res;
}

float MapLayer::getMapHeight()
{
    return _map_height;
}

float MapLayer::getMapWidth()
{
    return _map_width;
}

bool MapLayer::isMoving()
{
   return _is_moving;
}
bool MapLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    CCLOG("onTouchBegan %f x %f",touch->getLocationInView().x,touch->getLocationInView().y);
    _position_x_begin = this->getPosition().x;
    _position_y_begin = this->getPosition().y;
    return true;
}

void MapLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    float _x = _position_x_begin + touch->getLocation().x - touch->getStartLocation().x;
    float _y = _position_y_begin + touch->getLocation().y - touch->getStartLocation().y;
    CCLOG("x , y %f,%f  (max_x %f,max_y %f)",_x,_y,_limit_x,_limit_y);
    if (_x > 0) {
        _x = 0;
    }
    else if(_x < _limit_x ){
        _x = _limit_x;
    }
    if (_y > 0) {
        _y = 0;
    }
    else if(_y < _limit_y){
        _y = _limit_y;
    }
    this->setPosition(Vec2(_x, _y));
    _is_moving = true;
    CCLOG("onTouchMoved");
}

void MapLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    _is_moving = false;
    CCLOG("onTouchEnded");
}

void MapLayer::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    _is_moving = false;
    CCLOG("onTouchCancelled");
}

