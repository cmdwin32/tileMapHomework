//
//  MapLayer.h
//  tilemap
//
//  Created by king hin on 14-6-19.
//
//

#ifndef __tilemap__MapLayer__
#define __tilemap__MapLayer__

#include <iostream>
#include "cocos2d.h"
#include "MapInfo.h"
using namespace cocos2d;

class MapLayer : public Layer {
    
public:
    static MapLayer * createWithInfo(MapInfo * info);
    
    // 初始化
    bool initWithInfo(MapInfo * info);
    // 构造函数
    MapLayer();
    // 析构函数
    virtual ~MapLayer();
    // 获得地图的宽度
    float getMapWidth();
    // 获得地图的高度 
    float getMapHeight();
    // 获取地图移动状态 
    bool isMoving();
    
    // Layer
    // 处理点击事件
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);

private:
    // 地图的宽度
    float _map_width;
    // 地图的高度
    float _map_height;
    // 屏幕宽度 
    float _win_width;
    // 屏幕高度
    float _win_height;
    // 开始点击的x坐标
    float _position_x_begin;
    // 开始点击的y坐标
    float _position_y_begin;
    // x最远点
    float _limit_x;
    // y最远点
    float _limit_y;
    // 地图正在被拖拽 
    bool _is_moving;
};

#endif /* defined(__tilemap__MapLayer__) */
