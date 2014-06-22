//
//  LoadingScene.cpp
//  tillmap
//
//  Created by king hin on 14-6-18.
//
//

#include "LoadingScene.h"
#include "HelloWorldScene.h"
#include "GameScene.h"

LoadingScene::LoadingScene():
_layer(NULL)
{
    
}

LoadingScene::~LoadingScene()
{

}

LoadingScene * LoadingScene::create(){
    LoadingScene * scene = new LoadingScene();
    if (scene && scene->init()) {
        scene->autorelease();
    }
    else{
        CC_SAFE_DELETE(scene);
    }
    return scene;
}

bool LoadingScene::init()
{
    bool res = cocos2d::Scene::init();
    if (res) {
        CCLOG("LoadingScene::init");
        std::vector<LoadableObj*> res_list; // 需要加载的对象列表
        // 添加图片加载对象
//        res_list.push_back(IMGLoadableObj::createWithFileName("HelloWorld.png"));
        
        char file_name[256];
        for (int a = 1; a <=9; ++a) {
            for (int f = 1; f <= 16; ++f) {
                memset(file_name, 0, 256);
                sprintf(file_name, "map_%d_%d.png",a,f);
                cout << file_name << endl;
                res_list.push_back(MapLoadable::createWithFileName(file_name));
            }
        }
        
        CCLOG("LoadingScene::init::startLoad");
        _layer = CCProgressLayer::createWithResouceList(res_list);
        _layer->setSuccessCallBack(this,callfunc_selector(LoadingScene::LoadedFinish));
        this->addChild(_layer);
    }
    return res;

}

void LoadingScene::onEnter(){
    cocos2d::Scene::onEnter();
    CCLOG("LoadingScene::init::startLoad::onEnter");
    _layer->startLoad();
}

void LoadingScene::LoadedFinish(){
    CCLOG("LoadingScene::LoadedFinish");
    auto next_scene = GameScene::create();
    CCLOG("GameScene::create");
    Director::getInstance()->replaceScene(next_scene);
    CCLOG("replaceScene");
}