//
//  MapLogic.cpp
//  tilemap
//
//  Created by king hin on 14-6-21.
//
//

#include "MapLogic.h"
#include <math.h>

MapLogic::MapLogic():
_info(NULL)
{

}

MapLogic::~MapLogic()
{
    
}

MapLogic * MapLogic::createWithInfo(MapInfo *info){
    MapLogic * logic = new MapLogic();
    if (logic && logic->initWithInfo(info)) {
        
    }
    else{
        if (logic) {
            delete logic;
            logic = NULL;
        }
    }
    return logic;
}

bool MapLogic::initWithInfo(MapInfo *info)
{
    _info = info;
    return true;
}

vector<Vec2> MapLogic::getVisitingList(cocos2d::Vec2 map_position, cocos2d::Vec2 win_size)
{
    vector<Vec2> res;
    // 未初始化的地图信息会造成死循环 
    if (_info->getTileWidth() <= 0 || _info->getTileHeight() <= 0) {
        return res;
    }
    // x 轴第一个索引 地图平移除以每个单元格的宽度 下取整
    int _index_x_start = (int)ceil(( -1.f * map_position.x) / (float)_info->getTileWidth());
    // y 轴第一个索引 地图平移除以每个单元格的高度 下取整
    int _index_y_start = (int)ceil(( -1.f * map_position.y) / (float)_info->getTileHeight());
//    res.push_back(MapIndex(_index_x_start, _index_y_start));
    // 统计过的宽度
    float _over_width = -1 * map_position.x - _index_x_start * (float)_info->getTileWidth();
    // 统计过的高度
    float _over_height = -1 * map_position.y - _index_y_start * (float)_info->getTileHeight();
    // 统计过的x索引
    int _over_index_x = 0;
    // 统计过的y索引
    int _over_index_y = 0;
    
    float _last_x = win_size.x ;//+ _info->getTileWidth();
    float _last_y = win_size.y ;//+ _info->getTileHeight();
    float _res_x = 0.f; // 结果 x
    float _res_y = 0.f; // 结果 y
    while (_over_height < _last_y) {
        while (_over_width < _last_x) {
            _res_x = MIN(_index_x_start + _over_index_x, _info->getTileCountX()-1);
            _res_y = MIN(_index_y_start + _over_index_y, _info->getTileCountY() -1);
            res.push_back(Vec2(_res_x,_res_y));
            _over_width += _info->getTileWidth();
            ++_over_index_x;
        }
        _over_width = 0.f;
        _over_index_x = 0;
        _over_height += _info->getTileHeight();
        ++_over_index_y;
    }
    return res;
}

NeedList MapLogic::getNeedList(cocos2d::Vec2 map_position, cocos2d::Vec2 win_size,cocos2d::Vec2 map_size,float need_size  )
{
    NeedList list;
    // 遍历圆形区域所在的外界矩形，筛选出区域内的索引
    
    // 未初始化的地图信息会造成死循环
    if (_info->getTileWidth() <= 0 || _info->getTileHeight() <= 0) {
        return list;
    }
    
    float _end_width = map_position.x * -1 + win_size.x * 0.5 + need_size;
    float _end_height = map_position.y * -1 + win_size.y * 0.5 + need_size;
    
    // x 轴第一个索引 地图平移除以每个单元格的宽度 下取整
    int _index_x_start = (int)ceil(( -1.f * map_position.x - ( need_size - win_size.x * 0.5 ) ) / (float)_info->getTileWidth());
    // y 轴第一个索引 地图平移除以每个单元格的高度 下取整
    int _index_y_start = (int)ceil(( -1.f * map_position.y - ( need_size - win_size.y * 0.5 ) ) / (float)_info->getTileHeight());
    // 裁剪不存在的索引
    
    _end_width = MIN(_end_width, map_size.x);
    _end_height = MIN(_end_height, map_size.y);
    _index_x_start = MAX(_index_x_start,0);
    _index_y_start = MAX(_index_y_start,0);
    
    //    res.push_back(MapIndex(_index_x_start, _index_y_start));
    // 统计过的宽度
    float _over_width = _index_x_start * (float)_info->getTileWidth();
    // 统计过的高度
    float _over_height = _index_y_start * (float)_info->getTileHeight();
    // 统计过的x索引
    int _over_index_x = 0;
    // 统计过的y索引
    int _over_index_y = 0;
    
    float _res_x = 0.f; // 结果 x
    float _res_y = 0.f; // 结果 y
    int _res_index = 0;
    while (_over_height < _end_height) {
        while (_over_width < _end_width) {
            _res_x = _index_x_start + _over_index_x;
            _res_y = _index_y_start + _over_index_y;
            
            _over_width += _info->getTileWidth();
            ++_over_index_x;
            
            if (_res_x >= 0 && _res_y >= 0 && _res_x < _info->getTileCountX() && _res_y < _info->getTileCountY() ) {
                _res_cache[_res_index] = Vec2(_res_x,_res_y);
                ++_res_index;
                if(_res_index >= CACHE_SIZE){
                    // cache size已经大于四倍的屏幕尺寸了，如果还不够就下次再处理
                    break;
                }
            }

        }
        _over_width = 0.f;
        _over_index_x = 0;
        _over_height += _info->getTileHeight();
        ++_over_index_y;
    }
    

    
    list.need_list = (Vec2*)malloc(_res_index*sizeof(Vec2));
    memcpy(list.need_list, _res_cache, _res_index*sizeof(Vec2));
    list.size = _res_index;
    printf("need list size %d obj : %x",_res_index,list.need_list);
    
    return list;
}

