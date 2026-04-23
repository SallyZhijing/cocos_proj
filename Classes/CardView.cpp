#include "CardView.h"

USING_NS_CC;

CardView* CardView::create(const CardData& data)
{
    CardView* card = new (std::nothrow) CardView();
    if (card && card->init(data))
    {
        card->autorelease();
        return card;
    }
    CC_SAFE_DELETE(card);
    return nullptr;
}

bool CardView::init(const CardData& data)
{
    if (!Node::init())
    {
        return false;
    }

    _data = data;
    buildView();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [this](Touch* touch, Event* event)
        {
            if (!_clickEnabled || !_clickCallback || !this->isVisible())
            {
                return false;
            }

            if (hitTest(touch->getLocation()))
            {
                _clickCallback(this);
                return true;
            }
            return false;
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void CardView::setData(const CardData& data)
{
    _data = data;
    buildView();
}

const CardData& CardView::getData() const
{
    return _data;
}

void CardView::setZone(CardZone zone)
{
    _data.zone = zone;
}

void CardView::setClickCallback(const std::function<void(CardView*)>& cb)
{
    _clickCallback = cb;
}

void CardView::enableClick(bool enabled)
{
    _clickEnabled = enabled;
}

void CardView::buildView()
{
    this->removeAllChildren();

    const float CARD_SCALE = 0.7f;

    _bg = Sprite::create("card_general.png");
    if (!_bg)
    {
        CCLOG("Failed to load card_general.png");
        return;
    }

    _bg->setScale(CARD_SCALE);
    this->addChild(_bg, 0);

    Size rawSize = _bg->getContentSize();
    Size bgSize = Size(rawSize.width * CARD_SCALE, rawSize.height * CARD_SCALE);

    this->setContentSize(bgSize);

    _bg->setPosition(Vec2(0, 0));
    _bg->setAnchorPoint(Vec2(0.5f, 0.5f));

    // 左小数字
    _smallNumber = Sprite::create(getSmallNumberPath());
    if (_smallNumber)
    {
        _smallNumber->setAnchorPoint(Vec2(0.5f, 0.5f));
        _smallNumber->setPosition(Vec2(-bgSize.width * 0.28f, bgSize.height * 0.33f));
        _smallNumber->setScale(0.48f);
        this->addChild(_smallNumber, 1);
    }
    else
    {
        CCLOG("Failed to load small number image: %s", getSmallNumberPath().c_str());
    }

    // 右上角d花色
    _smallSuit = Sprite::create(getSuitPath());
    if (_smallSuit)
    {
        _smallSuit->setAnchorPoint(Vec2(0.5f, 0.5f));
        _smallSuit->setPosition(Vec2(bgSize.width * 0.25f, bgSize.height * 0.33f));
        _smallSuit->setScale(0.26f);
        this->addChild(_smallSuit, 1);
    }
    else
    {
        CCLOG("Failed to load suit image: %s", getSuitPath().c_str());
    }

    // 中间大数字
    _bigNumber = Sprite::create(getBigNumberPath());
    if (_bigNumber)
    {
        _bigNumber->setAnchorPoint(Vec2(0.5f, 0.5f));
        _bigNumber->setPosition(Vec2(0, -bgSize.height * 0.03f));
        _bigNumber->setScale(0.90f);
        this->addChild(_bigNumber, 1);
    }
    else
    {
        CCLOG("Failed to load big number image: %s", getBigNumberPath().c_str());
    }
}

bool CardView::hitTest(const Vec2& worldPos) const
{
    Vec2 local = this->convertToNodeSpace(worldPos);

    Rect rect(
        -this->getContentSize().width * 0.5f,
        -this->getContentSize().height * 0.5f,
        this->getContentSize().width,
        this->getContentSize().height
    );

    return rect.containsPoint(local);
}

bool CardView::isRedSuit(Suit suit) const
{
    return suit == Suit::Heart || suit == Suit::Diamond;
}

std::string CardView::valueToString(int value) const
{
    switch (value)
    {
    case 1:  return "A";
    case 11: return "J";
    case 12: return "Q";
    case 13: return "K";
    default: return std::to_string(value);
    }
}

std::string CardView::getSmallNumberPath() const
{
    std::string color = isRedSuit(_data.suit) ? "red" : "black";
    return "cards/number/small_" + color + "_" + valueToString(_data.value) + ".png";
}

std::string CardView::getBigNumberPath() const
{
    std::string color = isRedSuit(_data.suit) ? "red" : "black";
    return "cards/number/big_" + color + "_" + valueToString(_data.value) + ".png";
}

std::string CardView::getSuitPath() const
{
    switch (_data.suit)
    {
    case Suit::Club:    return "cards/suits/club.png";
    case Suit::Diamond: return "cards/suits/diamond.png";
    case Suit::Heart:   return "cards/suits/heart.png";
    case Suit::Spade:   return "cards/suits/spade.png";
    default:            return "cards/suits/club.png";
    }
}