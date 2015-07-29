//
//  MozaicTo.h
//  Sansbox3.7
//
//  Created by kuwabara yuki on 2015/07/24.
//
//

#ifndef __Sansbox3_7__MozaicTo__
#define __Sansbox3_7__MozaicTo__

#include "cocos2d.h"
#include "FilterMozaic.h"

using namespace cocos2d;

/**
 * !! tagetをinvisibleにするので非推奨です。
 */
class MozaicTo : public ActionInterval
{
public:
    MozaicTo();
    
    static MozaicTo* create(float duration, cocos2d::Size mozaicSize);
    
    bool initWithDuration(float duration, cocos2d::Size mozaicSize);
    
    MozaicTo* clone() const;
    
    MozaicTo* reverse() const;
    
    virtual void startWithTarget(Node *target);
    virtual void update(float timeRate);
    virtual void stop();
    
protected:
    cocos2d::Size _mozaicSize;
    
private:
    FilterMozaic* _mozaicNode = nullptr;
    bool _targetIsVisible = true;
};

#endif /* defined(__Sansbox3_7__MozaicTo__) */
