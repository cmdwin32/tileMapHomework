//
//  MapLogic.h
//  tilemap
//  地图逻辑处理类
//  Created by king hin on 14-6-21.
//
//

#ifndef __tilemap__MapLogic__
#define __tilemap__MapLogic__

#include <iostream>
#include "MapInfo.h"
#include "MapObjects.h"
#include <vector>
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;

#define CACHE_SIZE 2048

class MapLogic {
    
public:
    
    MapLogic();
    virtual ~MapLogic();
    
    
    // 根据地图信息创建地图逻辑
    static MapLogic * createWithInfo(MapInfo * info);
    
    // 根据地图信息初始化地图逻辑
    bool initWithInfo(MapInfo * info);
    /**
     * 获得当前显示区域内的地块编号
     * @param map_position 地图坐标 
     * @param win_size 显示窗口尺寸 
     */
    vector<Vec2> getVisitingList(cocos2d::Vec2 map_position,cocos2d::Vec2 win_size);
    /**
     * 当前需要的地块编号
     * @param map_position 地图坐标
     * @param need_radius 需要显示的区域半径 
     */
    NeedList getNeedList(cocos2d::Vec2 map_position, cocos2d::Vec2 win_size,cocos2d::Vec2 map_size,float need_size);
    
protected:
    MapInfo * _info; // 地图 信息
    Vec2 _res_cache[CACHE_SIZE]; // 固定缓存减少meme操作
};

#endif /* defined(__tilemap__MapLogic__) */
