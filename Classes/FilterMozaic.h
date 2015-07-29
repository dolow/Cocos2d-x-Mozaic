//
//  FilterMozaic.h
//  Sansbox3.7
//
//  Created by kuwabara yuki on 2015/07/27.
//
//

#ifndef __Sansbox3_7__FilterMozaic__
#define __Sansbox3_7__FilterMozaic__

#include "cocos2d.h"

/**
 * ネストされたNodeには非対応
 * glReadPixelsを利用しているので、対象のNodeが大きいと負荷も大きいです
 */
class FilterMozaic : public cocos2d::DrawNode
{
public:
    static FilterMozaic* createWithTarget(cocos2d::Node* target, cocos2d::Size mozaicSize);
    bool initWithTarget(cocos2d::Node* target, cocos2d::Size mozaicSize);
    bool refreshWithTarget(cocos2d::Node* target, cocos2d::Size mozaicSize);
    
protected:
    cocos2d::Size _mozaicSize;
};

#endif /* defined(__Sansbox3_7__FilterMozaic__) */
