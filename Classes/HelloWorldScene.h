#pragma once

#include "cocos2d.h"
#include "CardData.h"
#include <vector>

class CardView;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;

    CREATE_FUNC(HelloWorld);

private:
    struct MoveRecord
    {
        CardView* movedCard = nullptr;
        cocos2d::Vec2 fromPos;
        CardZone fromZone = CardZone::MainPile;

        CardView* previousTop = nullptr;
        bool previousTopVisible = true;
    };

    void createBackgroundAreas();
    void layoutAnchors(const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin);
    void setupDemoCards();
    void createUndoButton();

    void bindCard(CardView* card);
    void onCardClicked(CardView* card);
    bool canMatchMainCard(CardView* card) const;
    void moveCardToTop(CardView* card);
    void undoLastMove(cocos2d::Ref* sender);

private:
    // bottom region
    cocos2d::Vec2 _topPos;
    cocos2d::Vec2 _reservePos1;
    cocos2d::Vec2 _reservePos2;
    cocos2d::Vec2 _undoPos;

    // main card area
    cocos2d::Vec2 _leftTopPos;
    cocos2d::Vec2 _leftMidPos;
    cocos2d::Vec2 _leftBottomPos;

    cocos2d::Vec2 _rightTopPos;
    cocos2d::Vec2 _rightMidPos;
    cocos2d::Vec2 _rightBottomPos;

    CardView* _currentTopCard = nullptr;
    CardView* _startTopCard = nullptr;
    CardView* _reserveCard = nullptr;

    std::vector<MoveRecord> _undoStack;
};