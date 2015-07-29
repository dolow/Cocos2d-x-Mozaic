//
//  FilterMozaic.cpp
//  Sansbox3.7
//
//  Created by kuwabara yuki on 2015/07/27.
//
//

#include "FilterMozaic.h"

using namespace cocos2d;

FilterMozaic* FilterMozaic::createWithTarget(Node* target, Size mozaicSize)
{
    FilterMozaic* instance = new FilterMozaic();
    if (instance != nullptr && instance->initWithTarget(target, mozaicSize)) {
        instance->autorelease();
        return instance;
    }
    
    delete instance;
    instance = nullptr;
    return instance;
}

bool FilterMozaic::initWithTarget(Node* target, Size mozaicSize)
{
    if (!DrawNode::init()) return false;
    
    return this->refreshWithTarget(target, mozaicSize);
}

bool FilterMozaic::refreshWithTarget(Node* target, Size mozaicSize)
{
    _mozaicSize = mozaicSize;
    
    float contentScaleFactor = Director::getInstance()->getContentScaleFactor();
    
    float minPix = 1.0f / contentScaleFactor;
    
    if (_mozaicSize.width < minPix)
        _mozaicSize.width = minPix;
    if (_mozaicSize.height < minPix)
        _mozaicSize.height = minPix;
    
    this->clear();
    
    if (target == nullptr) return false;
    
    bool originalVisibility = target->isVisible();
    Vec2 originalScale      = Vec2(target->getScaleX(), target->getScaleY());
    
    this->setContentSize(target->getContentSize());
    
    Director* director = Director::getInstance();
    
    Size contentSize = target->getContentSize();
    Vec2 anchorPoint = target->getAnchorPoint();
    Vec2 leftBottom  = target->getPosition() - Size(contentSize.width * anchorPoint.x, contentSize.height * anchorPoint.y);
    
    target->setVisible(true);
    target->setScale(1.0f);
    
    RenderTexture* rt = RenderTexture::create(director->getVisibleSize().width, director->getVisibleSize().height);
    rt->begin();
    target->draw(director->getRenderer(), target->getNodeToParentTransform(), false);
    director->getRenderer()->render();
    
    for (float x = 0.0f; x <= contentSize.width - _mozaicSize.width; x += _mozaicSize.width) {
        for (float y = 0.0f; y <= contentSize.height - _mozaicSize.height; y += _mozaicSize.height) {
            void* buffer = malloc(sizeof(Color4B)*1);
            glReadPixels((GLint)(int)((leftBottom.x + x) * contentScaleFactor),
                         (GLint)(int)((leftBottom.y + contentSize.height - y) * contentScaleFactor),
                         1, 1, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
            
            Color4B* color = static_cast<Color4B*>(buffer);
            if (color->a <= 0.0f) continue;
            
            Vec2 verts[4] = {
                Vec2(x,                     contentSize.height - y),
                Vec2(x + _mozaicSize.width, contentSize.height - y),
                Vec2(x + _mozaicSize.width, contentSize.height - y - _mozaicSize.height),
                Vec2(x,                     contentSize.height - y - _mozaicSize.height)
            };
            
            this->drawPolygon(verts, 4, Color4F(color->r / 255.0f, color->g / 255.0f, color->b / 255.0f, color->a / 255.0f), 0, Color4F(0.0f, 0.0f, 0.0f, 0.0f));
            
            free(buffer);
        }
    }
    
    rt->end();
    
    target->setVisible(originalVisibility);
    target->setScale(originalScale.x, originalScale.y);
    
    return true;
}