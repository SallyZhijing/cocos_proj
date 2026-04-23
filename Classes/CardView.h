#pragma once
#include "cocos2d.h"
#include "CardData.h"
#include <functional>
#include <string>

class CardView : public cocos2d::Node
{
public:
    static CardView* create(const CardData& data);

    bool init(const CardData& data);

    void setData(const CardData& data);
    const CardData& getData() const;

    void setZone(CardZone zone);
    void setClickCallback(const std::function<void(CardView*)>& cb);
    void enableClick(bool enabled);

private:
    void buildView();
    bool hitTest(const cocos2d::Vec2& worldPos) const;

    bool isRedSuit(Suit suit) const;
    std::string valueToString(int value) const;
    std::string getSmallNumberPath() const;
    std::string getBigNumberPath() const;
    std::string getSuitPath() const;

private:
    CardData _data;

    cocos2d::Sprite* _bg = nullptr;
    cocos2d::Sprite* _smallNumber = nullptr;
    cocos2d::Sprite* _smallSuit = nullptr;
    cocos2d::Sprite* _bigNumber = nullptr;

    std::function<void(CardView*)> _clickCallback;
    bool _clickEnabled = true;
};