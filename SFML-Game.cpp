#include <iostream>
#include "GameView.h"
#include "GameScene.h"

int main() {
    try
    {
        GameView* pGameView = NewGameView({ 800, 600 });
        GameScene* pGameScene = NewGameScene();

        EnterGameLoop(*pGameView, UpdateGameScene, DrawGameScene, pGameScene);
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}