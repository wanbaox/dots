#ifndef __DataController_SCENE_H__
#define __DataController_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;


class DataController : public cocos2d::CCObject
{
    
private:
    
    static DataController * _sharedDataController;
    
    CCString * m_filePath;
    
    CCDictionary * m_dataDic;
    
public:
    
    virtual bool init();
    
    CREATE_FUNC(DataController);
    
    
    
    static DataController* getSharedDataController();
    
    static void releaseSharedDataController();
    
    void savePlayerTemplateData(int score);
    
    CCArray * readLoaclScoreTopList();
    
    CCDictionary * readWorldScpreTopList();
    
    CCArray * readPlayerDefaultProperty();
    
    int getHighScore();
    
    void saveUserName(CCString name);

};

#endif // __DataController_SCENE_H__
