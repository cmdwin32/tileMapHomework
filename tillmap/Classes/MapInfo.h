//
//  MapInfo.h
//  tilemap
//  地图基本信息 包括地图的tile尺寸和数量 
//  Created by king hin on 14-6-21.
//
//

#ifndef __tilemap__MapInfo__
#define __tilemap__MapInfo__

#include <iostream>
#include "JsonData.h"
class MapInfo {
    
public:
    // 根据json生成一个地图基本信息
    static MapInfo * createWithData(JsonData & _jdata);
    
    MapInfo();
    virtual ~MapInfo();
    // 初始化
    bool initWithData(JsonData & _jdata);
    
    // 获得数据
    int getTileWidth();
    int getTileHeight();
    int getTileCountX();
    int getTileCountY();
    int getMapWidth();
    int getMapHeight();
    // 区域内的tile数量
    int getTilePerArea();
    int getTilePerFeild();
    int getTileAreaCount();
    int getTileFeildCount();
    int getTileIndexCount();
private:
    // 每一个tile的宽度
    int _tile_width;
    // 每一个tile的高度
    int _tile_height;
    // 在x轴上的tile总数
    int _tile_count_x;
    // 在y轴上的tile总数
    int _tile_count_y;
    // 地图宽度
    int _map_width;
    // 地图高度
    int _map_height;
    
    
    // 地图每个区域包含的tile数
    int _map_tile_per_area;
    // 地图每个二级区域包含的tile数
    int _map_tile_per_feild;
    // 每个方向上一级区域总数
    int _map_tile_area_count;
    // 每个方向上二级区域总数
    int _map_tile_feild_count;
    // 每个方向上索引总数
    int _map_tile_index_count;
};

#endif /* defined(__tilemap__MapInfo__) */
