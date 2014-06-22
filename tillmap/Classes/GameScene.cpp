//
//  GameScene.cpp
//  tilemap
//
//  Created by king hin on 14-6-19.
//
//

#include "GameScene.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

GameScene * GameScene::create()
{
    auto scene = new GameScene();
    if (scene && scene->init()) {
        scene->autorelease();
    }
    else{
        CC_SAFE_DELETE(scene);
    }
    return scene;
}

bool GameScene::init()
{
    bool res = cocos2d::Scene::init();
    if (res) {
        // 初始化地图层 并加载
        MapManager::getInstance()->initMap();
        this->addChild(MapManager::getInstance()->getLayer());
        
    }
    return res;
}

void GameScene::update(float dt)
{
    cocos2d::Scene::update(dt);
    MapManager::getInstance()->update(dt);
}

void GameScene::onEnter()
{
    cocos2d::Scene::onEnter();
    schedule(schedule_selector(GameScene::update));
}

void GameScene::onExit()
{
    cocos2d::Scene::onExit();
}