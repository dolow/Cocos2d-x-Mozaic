# Cocos2d-x-Mozaic

## Contents

* module converts Sprite to mozaic
* sample action named "MozaicTo"

## Dependency

cocos2d-x 3.7

Cocos2d-x-Mozaic is not tested on other versions.

## Usage

```
// to create mozaic node
Sprite* baseSprite = Sprite::create("sample.png");
Size    mozaicSize = Size(5.0f, 5.0f);

FilterMozaic* mozaic = FilterMozaic::createWithTarget(baseSpirte, mozaicSize);
this->addChild(mozaic);
```

```
// to act MozaicTo
Size  mozaicSize = Size(5.0f, 5.0f);
float duration = 10.0f;

// MozaicTo automatically set visible of target node to false
baseSprite->runAction(MozaicTo::create(duration, mozaicSize));
```
