//
//  MapCache.h
//  tilemap
//
//  Created by king hin on 14-6-21.
//
//

#ifndef __tilemap__MapCache__
#define __tilemap__MapCache__

#include <iostream>
#include "cocos2d.h"
#include "MapObjects.h"
#include <vector>
#include "ckHashMap.h"
#include "MapInfo.h"
using namespace std;
using namespace cocos2d;
class MapCache {
    
public:
    // 地图缓存是一个单利
    static MapCache * getInstance();
    
    MapCache();
    virtual ~MapCache();
    // 根据缓存尺寸初始化缓存
    void initWithSize(int size);
    // 为缓存绑定一个层 缓存的显示对象将刷新这个层
    void bindLayer(Layer * layer);
    // 为缓存绑定一个地图信息
    void bindMapInfo(MapInfo * info);
    // 添加一个batchNode到缓存
    void addBatchNode(string node_name,SpriteBatchNode * batch_node);
    // 根据期望列表刷新缓存
    void updateWithNeedList(Vec2 * need_list,int size);
    // 清空所有的batchNode 和显示对象缓存
    void reset();
    // 删除不在使用的显示对象缓存 
    void cleanUnUsed();
    
private:
    static MapCache * _instance; //单利
    Layer * _layer; // 缓存绑定的地图层
    MapInfo * _info; // 缓存绑定的地图信息
    vector<MapObj*> _visite_cache; // 显示对象缓存
    hash_map<string,cocos2d::SpriteBatchNode*> _batchNodeCache; // 所有合并渲染的
    int _last_index; // 上一次加载的最后索引
    Vec4 _visiting_rect; // 显示区域
    int _cache_size; // 缓存大小
    
    bool _show_type[128][128];

    
};

#endif /* defined(__tilemap__MapCache__) */
