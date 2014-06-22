//
//  MapManager.cpp
//  tilemap
//
//  Created by king hin on 14-6-19.
//
//

#include "MapManager.h"

MapManager * MapManager::_instance = NULL;

MapManager * MapManager::getInstance()
{
    if (MapManager::_instance == NULL) {
        MapManager::_instance = new MapManager();
    }
    return MapManager::_instance;
}

MapManager::MapManager():
_layer(NULL),
_init_over(false),
_info(NULL),
_logic(NULL)
{

}

MapManager::~MapManager()
{
    
}

void MapManager::initMapInfo(JsonData & _jdata){
    // 创建地图信息 并使用地图信息生成逻辑对象和
    _info = MapInfo::createWithData(_jdata);
    _logic = MapLogic::createWithInfo(_info);
    _layer = MapLayer::createWithInfo(_info);
    _layer->retain();
    
    // 为缓存设置大小并绑定显示对象
    MapCache::getInstance()->initWithSize(4096);
    MapCache::getInstance()->bindMapInfo(_info);
    MapCache::getInstance()->bindLayer(_layer);
    
}

void MapManager::initMap()
{
    // 判断是否已有地图信息，如果有就释放旧的
    cleareMap();
    JsonData _jdata;
    _jdata << "{\"map_info\":{\"tile_width\":\"32\",\"tile_height\":\"32\",\"tile_count_x\":\"96\",\"tile_count_y\":\"96\",\"area_count\":\"3\",\"feild_count\":\"4\"}}";
    initMapInfo(_jdata);
}

void MapManager::cleareMap()
{
    // 判断如果有地图层 就减少一次引用计数 并释放
    if (_layer) {
        _layer->release();
        _layer->removeFromParentAndCleanup(true);
    }
}

MapLayer * MapManager::getLayer()
{
    return _layer;
}

void MapManager::update(float _dt)
{
    if ( ( _layer && _layer->isMoving() == true ) || !_init_over) {
        //    vector<MapIndex> vec = _logic->getVisitingList(_layer->getPosition(), Director::getInstance()->getWinSize());
        NeedList list = _logic->getNeedList(_layer->getPosition(), Director::getInstance()->getWinSize(), Vec2(_info->getMapWidth(), _info->getMapHeight()), 480*1.5);
//        for (int i = 0; i < list.size; ++i) {
//            CCLOG(" need list %d (%f,%f)\n" , i , list.need_list[i].x ,list.need_list[i].y);
//        }
        
        MapCache::getInstance()->updateWithNeedList(list.need_list,list.size);
        free(list.need_list);
        cout << "wwwww" << endl;
        if (!_init_over) {
            _init_over = true;
        }
    }

}