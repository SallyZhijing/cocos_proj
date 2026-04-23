#pragma once

enum class Suit
{
    Club,
    Diamond,
    Heart,
    Spade
};

enum class CardZone
{
    MainPile,     // 主牌区
    ReservePile,  // 备用牌区
    TopPile       // 当前顶部牌区
};

struct CardData
{
    int id = 0;
    int value = 1;               // use A=1, J=11, Q=12, K=13
    Suit suit = Suit::Club;
    bool faceUp = true;
    bool removed = false;
    CardZone zone = CardZone::MainPile;
};