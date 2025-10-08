#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema1/gameLogic.h"

namespace m1
{

    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        // Useful functions
    

    public:
        //Spawners:
        HexFactory enemySpawner;
        DiamondFactory allySpawner;
        ProjectileFactory projectileSpawner;

        //Timing & game mechanics related:
        float nextEnemyTimer = 0.0f;
        float nextCollectablesTimer = 0.0f;
        float timeUntilNextCollectables = 7.0f;
        float timeUntilNextEnemy = 1.0f;
        int nextRowEnemyComes = 0;
        TypeColor nextEnemyColor = BLUE;

        //Randomizer:
        int randomizerLowerLimit = 400;
        int randomizerUpperLimit = 600;

        //Drag and Drop:
        bool leftMouseIsPressed = false;
        TypeColor dndDiamondColor = BLUE;
        float dndDiamondX = 0.0f;
        float dndDiamondY = 0.0f;
        int priceToPay = 0;

    };

}   // namespace m1