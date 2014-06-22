//
//  MapCache.cpp
//  tilemap
//
//  Created by king hin on 14-6-21.
//
//

#include "MapCache.h"

MapCache * MapCache::_instance = NULL;

MapCache::MapCache():
_layer(NULL),
_info(NULL),
_last_index(-1),
_cache_size(0),
_visiting_rect({-1,-1,-1,-1})
{
    for (int i=0; i<128; ++i) {
        for (int j=0; j<128; ++j) {
            _show_type[i][j] = false;
        }
    }
}

MapCache::~MapCache()
{
    
}

MapCache * MapCache::getInstance()
{
    if ( MapCache::_instance == NULL) {
        MapCache::_instance = new MapCache();
    }
    return MapCache::_instance;
}

void MapCache::initWithSize(int size){
    _cache_size = size;
    _visite_cache.resize(size);
    for (int i=0; i < size; ++i) {
        _visite_cache[i] = MapObj::create();
    }
}

void MapCache::bindMapInfo(MapInfo *info){
    _info = info;
}

void MapCache::bindLayer(cocos2d::Layer *layer){
    if (_layer) {
        assert("bindLayer while there is another layer");
    }
    _layer = layer;
    // 把已经存在的batchnode都加在layer上面
    hash_map<string,SpriteBatchNode*>::iterator _it_hm = _batchNodeCache.begin();
    while (_it_hm != _batchNodeCache.end()) {
        _layer->addChild(_it_hm->second);
        ++_it_hm;
    }
    auto * _tp = Sprite::createWithSpriteFrameName("map_09_10_57.png");
    cout << _tp->getTexture()->getName() << endl;
    _layer->addChild(_tp);
}

void  MapCache::addBatchNode(string node_name, cocos2d::SpriteBatchNode *batch_node)
{
    // 关闭去锯齿 不然会出缝隙 
    batch_node->getTexture()->setAliasTexParameters();
    _batchNodeCache[node_name] = batch_node;
    batch_node->retain();
    if (_layer) {
        _layer->addChild(batch_node);
    }
}

void MapCache::updateWithNeedList(Vec2 * need_list,int size){
    
    if(size > _cache_size)
    {
        // 缓存大小设计为四倍的最大需求尺寸，所以不应该走到这里 
        assert("you need too much");
        return;
    }
    
    CCLOG("needList size-%d",size);
    Vec4 old_rect = _visiting_rect;
    // 更新缓存
    _visiting_rect.x = (need_list)[0].x;
    _visiting_rect.y = (need_list)[0].y;
    _visiting_rect.z = (need_list)[size-1].x;
    _visiting_rect.w = (need_list)[size-1].y;
    
    cout <<"_visiting_rect:"<<  _visiting_rect.x << ":" << _visiting_rect.y << ":" << _visiting_rect.z << ":" << _visiting_rect.w <<":"<<endl;
    
    int _need_index = 0;
    
    // 环行遍历，从上次的结尾开始，保证下一次检查的对象是较早添加的
    int _t_index = _last_index;
    ++_last_index;
    
    int un_seem_count = 0;
    int same = 0;
    // 循环列表结束或者需求列表结束
    while (_t_index != _last_index && _need_index < size) {
        // 剔除和上一次显示重复的区域
        if ( _show_type[(int)((need_list)[_need_index].x)][(int)((need_list)[_need_index].y)] == true ) {
            ++same;
            ++_need_index;
            continue;
        }
        if (_last_index >= _cache_size) {
            _last_index = 0;
        }
        printf("_visite_cache[_last_index]:%d",_visite_cache[_last_index]);
        if (_visite_cache[_last_index]->isUsing(_visiting_rect) != true) {
            _show_type[(int)(_visite_cache[_last_index]->getIndex().x)][(int)(_visite_cache[_last_index]->getIndex().y)] = false;
            _visite_cache[_last_index]->unUse(true);
            _visite_cache[_last_index]->use((need_list)[_need_index],_info);
            if( _visite_cache[_last_index]->getNode()->getParent() == NULL ){     
                _batchNodeCache[_visite_cache[_last_index]->getBatchNodeName()]->addChild(_visite_cache[_last_index]->getNode());
            }
            _show_type[(int)((need_list)[_need_index].x)][(int)((need_list)[_need_index].y)] = true;
            ++_need_index;
            ++un_seem_count;
        }
        
        ++_last_index;
        cout << "_last_index: " << _last_index << endl;
    }
    
    cout << "un_seem_count:" << un_seem_count <<endl;
    
}

void MapCache::reset(){
    vector<MapObj*>::iterator _it_vm = _visite_cache.begin();
    while (_it_vm != _visite_cache.end()) {
        (*_it_vm)->unUse(true);
        delete (*_it_vm);
        ++_it_vm;
    }
    _visite_cache.clear();
    hash_map<string,SpriteBatchNode*>::iterator _it_hm = _batchNodeCache.begin();
    while (_it_hm != _batchNodeCache.end()) {
        _it_hm->second->release();
        ++_it_hm;
    }
    _batchNodeCache.clear();
    _last_index = 0;
}

void MapCache::cleanUnUsed(){
    vector<MapObj*>::iterator _it = _visite_cache.begin();
    while (_it != _visite_cache.end()) {
        if ((*_it)->isUsing(_visiting_rect) != true) {
            (*_it)->unUse(true);
        }
        ++_it;
    }
}

