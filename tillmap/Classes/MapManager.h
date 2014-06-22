//
//  MapManager.h
//  tilemap
//
//  Created by king hin on 14-6-19.
//
//

#ifndef __tilemap__MapManager__
#define __tilemap__MapManager__

#include <iostream>
#include "MapLayer.h"
#include "MapInfo.h"
#include "MapLogic.h"
#include "JsonData.h"
#include "MapCache.h"

class MapManager {
    
public:
    static MapManager * getInstance();
    // 构造函数
    MapManager();
    // 析构函数 
    virtual ~MapManager();
    // 初始化地图信息
    void initMap();
    // 释放地图
    void cleareMap();
    //获得地图显示的层
    MapLayer * getLayer();
    // 更新 获取需要显示的tile集合 
    void update(float _dt);
    //初始化地图信息 
    void initMapInfo(JsonData & _jdata);
    
private:
    static MapManager * _instance;// 单例
    MapLayer * _layer; // 地图层
    MapInfo * _info; // 地图基本信息
    MapLogic * _logic; // 地图逻辑
    bool _init_over; // 判断是否经过初始化
};

#endif /* defined(__tilemap__MapManager__) */
