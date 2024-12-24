#pragma once
#include "TmxLevel.h"

#include <SFML/Graphics.hpp>

struct GameView;

struct GameScene
{
    TmxLevel level;
    TmxObject player;
    std::vector<TmxObject> enemies;
    std::vector<TmxObject> coins;
    std::vector<TmxObject> block;
    sf::Vector2f startLocation;
};

GameScene* NewGameScene();
void UpdateGameScene(void* pData, GameView& view, float deltaSec);
void DrawGameScene(void* pData, GameView& view);
void DestroyGameScene(GameScene * &pScene); 
