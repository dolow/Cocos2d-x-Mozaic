//
//  MozaicTo.cpp
//  Sansbox3.7
//
//  Created by kuwabara yuki on 2015/07/24.
//
//

#include "MozaicTo.h"

MozaicTo::MozaicTo()
: _mozaicSize(Size(5.0f, 5.0f))
{ }

MozaicTo* MozaicTo::create(float duration, Size mozaicSize)
{
    MozaicTo *mozaic = new (std::nothrow) MozaicTo();
    mozaic->initWithDuration(duration, mozaicSize);
    mozaic->autorelease();
    
    return mozaic;
}

bool MozaicTo::initWithDuration(float duration, Size mozaicSize)
{
    if (ActionInterval::initWithDuration(duration)) {
        _mozaicSize = mozaicSize;
        
        return true;
    }
    
    return false;
}

MozaicTo* MozaicTo::clone() const
{
    // no copy constructor
    auto copy = new (std::nothrow) MozaicTo();
    copy->initWithDuration(_duration, _mozaicSize);
    copy->autorelease();
    return copy;
}

MozaicTo* MozaicTo::reverse() const
{
    CCASSERT(false, "reverse() not supported in MozaicTo");
    return nullptr;
}

void MozaicTo::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    
    _targetIsVisible = target->isVisible();
    
    _target->setVisible(false);
}

void MozaicTo::update(float timeRate)
{
    if (_target == nullptr) return;
    
    Node* parent = _target->getParent();
    if (parent == nullptr) return;
    
    Size currentMozaicSize = Size(timeRate * _mozaicSize.width, timeRate * _mozaicSize.height);
    
    if (_mozaicNode == nullptr) {
        _mozaicNode = FilterMozaic::createWithTarget(_target, currentMozaicSize);
        parent->addChild(_mozaicNode, _target->getZOrder() + 1);
    }
    else {
        _mozaicNode->clear();
        _mozaicNode->refreshWithTarget(_target, currentMozaicSize);
    }
    
    _mozaicNode->ignoreAnchorPointForPosition(_target->isIgnoreAnchorPointForPosition());
    _mozaicNode->setPosition(_target->getPosition());
    _mozaicNode->setAnchorPoint(_target->getAnchorPoint());
    _mozaicNode->setScaleX(_target->getScaleX());
    _mozaicNode->setScaleY(_target->getScaleY());
}

void MozaicTo::stop()
{
    _target->setVisible(_targetIsVisible);
    
    ActionInterval::stop();
    
    if (_mozaicNode != nullptr && _mozaicNode->getParent() != nullptr)
        _mozaicNode->removeFromParent();
}