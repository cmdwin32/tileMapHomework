//
//  MapObjects.h
//  tilemap
//
//  Created by king hin on 14-6-21.
//
//

#ifndef __tilemap__MapObjects__
#define __tilemap__MapObjects__

#include "cocos2d.h"
#include "MapInfo.h"
#include <iostream>

using namespace cocos2d;

struct NeedList{
    Vec2 * need_list;
    int size;
};

class MapObj {
    
public:
    MapObj();
    ~MapObj();
    // 创建一个空的地图对象
    static MapObj* create();
    // 根据正在显示的区域判断该对象是否正在被使用
    bool isUsing(Vec4 showing_rect);
    // 使用一个缓存 设置地图索引
    Node * use(Vec2 index,MapInfo * info);
    // 该节点不在被使用
    void unUse(bool cleanup);
    // 获得显示用对象
    Node * getNode();
    // 获得所在的batchnode名称
    std::string getBatchNodeName();
    // 获得现在的索引 
    Vec2 getIndex();
    
    
private:
    Vec2 _index; // 地图索引
    Sprite * _sp; // 对应的显示对象
    bool _is_using ; // 是否在被使用
    std::string _batchnode_name; // 所在的batchnode名称
};

#endif /* defined(__tilemap__MapObjects__) */
