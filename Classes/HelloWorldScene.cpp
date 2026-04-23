#include "HelloWorldScene.h"
#include "CardView.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}
// Init the scene
bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    layoutAnchors(visibleSize, origin);
    createBackgroundAreas();
    setupDemoCards();
    createUndoButton();

    return true;
}
//create colored background same as the reference, etc. 
void HelloWorld::createBackgroundAreas()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    float W = visibleSize.width;
    float H = visibleSize.height;

    float pileH = H * 0.28f;          // 底部堆牌区
    float mainH = H - pileH;          // 上方主牌区

    // 主牌区
    auto mainAreaBg = LayerColor::create(Color4B(181, 130, 72, 255), W, mainH);
    mainAreaBg->setAnchorPoint(Vec2::ZERO);
    mainAreaBg->setPosition(Vec2(origin.x, origin.y + pileH));
    this->addChild(mainAreaBg, -2);

    // 堆牌区
    auto pileAreaBg = LayerColor::create(Color4B(156, 33, 166, 255), W, pileH);
    pileAreaBg->setAnchorPoint(Vec2::ZERO);
    pileAreaBg->setPosition(Vec2(origin.x, origin.y));
    this->addChild(pileAreaBg, -2);
}

//calc layout position for elements
void HelloWorld::layoutAnchors(const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin)
{
    float W = visibleSize.width;
    float H = visibleSize.height;

    float pileH = H * 0.28f;
    float mainBottom = origin.y + pileH;

    // bottom  area 
    _reservePos1 = cocos2d::Vec2(origin.x + W * 0.28f, origin.y + pileH * 0.40f);
    _reservePos2 = cocos2d::Vec2(origin.x + W * 0.40f, origin.y + pileH * 0.40f);
    _topPos = cocos2d::Vec2(origin.x + W * 0.65f, origin.y + pileH * 0.40f);
    _undoPos = cocos2d::Vec2(origin.x + W * 0.88f, origin.y + pileH * 0.40f);

    // main area
    float mainH = H - pileH;

    _leftTopPos = cocos2d::Vec2(origin.x + W * 0.30f, mainBottom + mainH * 0.72f);
    _leftMidPos = cocos2d::Vec2(origin.x + W * 0.35f, mainBottom + mainH * 0.55f);
    _leftBottomPos = cocos2d::Vec2(origin.x + W * 0.40f, mainBottom + mainH * 0.38f);

    _rightTopPos = cocos2d::Vec2(origin.x + W * 0.70f, mainBottom + mainH * 0.72f);
    _rightMidPos = cocos2d::Vec2(origin.x + W * 0.65f, mainBottom + mainH * 0.55f);
    _rightBottomPos = cocos2d::Vec2(origin.x + W * 0.60f, mainBottom + mainH * 0.38f);
}
//init the demo start
void HelloWorld::setupDemoCards()
{
    CardData topData;
    topData.id = 1;
    topData.value = 4;
    topData.suit = Suit::Club;
    topData.zone = CardZone::TopPile;

    _startTopCard = CardView::create(topData);
    if (!_startTopCard)
    {
        CCLOG("Failed to create start top card");
        return;
    }
    _startTopCard->setPosition(_topPos);
    this->addChild(_startTopCard, 5);
    _currentTopCard = _startTopCard;

    CardData reserveData1;
    reserveData1.id = 2;
    reserveData1.value = 3;
    reserveData1.suit = Suit::Club;
    reserveData1.zone = CardZone::ReservePile;

    auto reserveCard1 = CardView::create(reserveData1);
    if (!reserveCard1)
    {
        CCLOG("Failed to create reserveCard1");
        return;
    }
    reserveCard1->setPosition(_reservePos1);
    this->addChild(reserveCard1, 2);
    bindCard(reserveCard1);

    CardData reserveData2;
    reserveData2.id = 3;
    reserveData2.value = 1;
    reserveData2.suit = Suit::Heart;
    reserveData2.zone = CardZone::ReservePile;

    _reserveCard = CardView::create(reserveData2);
    if (!_reserveCard)
    {
        CCLOG("Failed to create reserveCard2");
        return;
    }
    _reserveCard->setPosition(_reservePos2);
    this->addChild(_reserveCard, 3);
    bindCard(_reserveCard);

    // 左列
    CardData c1{ 4, 13, Suit::Club, true, false, CardZone::MainPile };
    CardData c2{ 5, 3,  Suit::Club, true, false, CardZone::MainPile };
    CardData c3{ 6, 3,  Suit::Diamond, true, false, CardZone::MainPile };

    auto leftTop = CardView::create(c1);
    auto leftMid = CardView::create(c2);
    auto leftBottom = CardView::create(c3);

    if (leftTop)
    {
        leftTop->setPosition(_leftTopPos);
        this->addChild(leftTop, 1);
        bindCard(leftTop);
    }

    if (leftMid)
    {
        leftMid->setPosition(_leftMidPos);
        this->addChild(leftMid, 2);
        bindCard(leftMid);
    }

    if (leftBottom)
    {
        leftBottom->setPosition(_leftBottomPos);
        this->addChild(leftBottom, 3);
        bindCard(leftBottom);
    }

    // 右列
    CardData c4{ 7, 3, Suit::Club, true, false, CardZone::MainPile };
    CardData c5{ 8, 3, Suit::Club, true, false, CardZone::MainPile };
    CardData c6{ 9, 2, Suit::Spade, true, false, CardZone::MainPile };

    auto rightTop = CardView::create(c4);
    auto rightMid = CardView::create(c5);
    auto rightBottom = CardView::create(c6);

    if (rightTop)
    {
        rightTop->setPosition(_rightTopPos);
        this->addChild(rightTop, 1);
        bindCard(rightTop);
    }

    if (rightMid)
    {
        rightMid->setPosition(_rightMidPos);
        this->addChild(rightMid, 2);
        bindCard(rightMid);
    }

    if (rightBottom)
    {
        rightBottom->setPosition(_rightBottomPos);
        this->addChild(rightBottom, 3);
        bindCard(rightBottom);
    }
}

void HelloWorld::bindCard(CardView* card)
{
    if (!card)
    {
        return;
    }

    card->setClickCallback([this](CardView* clicked)
        {
            this->onCardClicked(clicked);
        });

    card->enableClick(true);
}
// check if top and mian card are matched(dff is 1)
bool HelloWorld::canMatchMainCard(CardView* card) const
{
    if (!card || !_currentTopCard)
    {
        return false;
    }

    int clickedValue = card->getData().value;
    int topValue = _currentTopCard->getData().value;

    return std::abs(clickedValue - topValue) == 1;
}

//handle card click
void HelloWorld::onCardClicked(CardView* card)
{
    if (!card || !card->isVisible())
    {
        return;
    }

    if (card == _currentTopCard)
    {
        return;
    }

    CardZone zone = card->getData().zone;

    // 手牌区，点击自动替换
    if (zone == CardZone::ReservePile)
    {
        moveCardToTop(card);
        return;
    }

    // 桌面牌，only change when diff is 1
    if (zone == CardZone::MainPile)
    {
        if (canMatchMainCard(card))
        {
            moveCardToTop(card);
        }
        else
        {
            CCLOG("cannot match current top card.");
        }
    }
}
// move a card to the top
void HelloWorld::moveCardToTop(CardView* card)
{
    if (!card)
    {
        return;
    }

    MoveRecord record;
    record.movedCard = card;
    record.fromPos = card->getPosition();
    record.fromZone = card->getData().zone;
    record.previousTop = _currentTopCard;
    record.previousTopVisible = (_currentTopCard != nullptr) ? _currentTopCard->isVisible() : false;

    _undoStack.push_back(record);

    if (_currentTopCard)
    {
        _currentTopCard->setVisible(false);
    }

    card->setZone(CardZone::TopPile);
    _currentTopCard = card;
    card->stopAllActions();
    card->runAction(MoveTo::create(0.25f, _topPos));
}

void HelloWorld::undoLastMove(Ref* sender)
{
    if (_undoStack.empty())
    {
        CCLOG("Undo stack is empty.");
        return;
    }

    MoveRecord record = _undoStack.back();
    _undoStack.pop_back();

    if (!record.movedCard)
    {
        return;
    }

    // 当前顶部牌 move to 原位置
    record.movedCard->stopAllActions();
    record.movedCard->runAction(MoveTo::create(0.25f, record.fromPos));
    record.movedCard->setZone(record.fromZone);

    // show prev top card
    if (record.previousTop)
    {
        record.previousTop->setVisible(record.previousTopVisible);
        _currentTopCard = record.previousTop;
    }
    else
    {
        _currentTopCard = nullptr;
    }
}

void HelloWorld::createUndoButton()
{
    auto label = Label::createWithSystemFont("back", "Arial", 20);
    label->setColor(Color3B::WHITE);

    auto undoItem = MenuItemLabel::create(label, CC_CALLBACK_1(HelloWorld::undoLastMove, this));
    undoItem->setPosition(_undoPos);

    auto menu = Menu::create(undoItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 20);
}