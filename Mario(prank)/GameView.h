#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

struct GameView
{
    sf::RenderWindow window;
    sf::View camera;
    sf::Vector2i windowSize;
    sf::Clock clock;
};

using OnUpdate = void (*)(void* pData, GameView& view, float deltaSec);
using OnDraw = void (*)(void* pData, GameView& view);

GameView* NewGameView(const sf::Vector2i& windowSize);

void EnterGameLoop(GameView& view, OnUpdate onUpdate, OnDraw onDraw, void* pData);

void SetCameraCenter(GameView& view, const sf::Vector2f& center);

void DestroyGameView(GameView * &pView); 
