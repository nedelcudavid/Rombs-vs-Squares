#include <vector>
#include <iostream>
#include "lab_m1/Tema1/Tema1.h"
#include "lab_m1/Tema1/helpers2D.h"
#include "lab_m1/Tema1/objectGenerator2D.h"
#include "lab_m1/Tema1/gameLogic.h"
#include <random>

using namespace std;
using namespace m1;
using namespace helpers2D;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
    //Sets camers
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    
    //Load meshes
    Mesh* fullSquare = objectGenerator2D::CreateSquare("tile", glm::vec3(0,0,0), tileSideLength, zTile, tileColor, true);
    AddMeshToList(fullSquare);

    Mesh* lifeHeart = objectGenerator2D::CreateHeart("lifeHeart", glm::vec3(0, 0, 0), lifeUnitSize, zLifes, lifeColor);
    AddMeshToList(lifeHeart);

    Mesh* emptySquare = objectGenerator2D::CreateSquare("displayTile", glm::vec3(0, 0, 0), tileSideLength, zDisplayFrame,  displayFrameColor, false);
    AddMeshToList(emptySquare);

    Mesh* rectangle = objectGenerator2D::CreateRectangle("barrier", glm::vec3(0, 0, 0), barrierWidth, barrierHeight, zBarrier,  barrierColor, true);
    AddMeshToList(rectangle);

    Mesh* blueDiamond = objectGenerator2D::CreateShootingDiamond("blueDiamond", glm::vec3(0, 0, 0), diamondWidth, diamondHeight, zDiamonds, blueColor);
    AddMeshToList(blueDiamond);

    Mesh* goldenDiamond = objectGenerator2D::CreateShootingDiamond("yellowDiamond", glm::vec3(0, 0, 0), diamondWidth, diamondHeight, zDiamonds, goldenColor);
    AddMeshToList(goldenDiamond);

    Mesh* darkGreenDiamond = objectGenerator2D::CreateShootingDiamond("greenDiamond", glm::vec3(0, 0, 0), diamondWidth, diamondHeight, zDiamonds, darkGreenColor);
    AddMeshToList(darkGreenDiamond);

    Mesh* pinkDiamond = objectGenerator2D::CreateShootingDiamond("pinkDiamond", glm::vec3(0, 0, 0), diamondWidth, diamondHeight, zDiamonds, pinkColor);
    AddMeshToList(pinkDiamond);

    Mesh* curencyStar = objectGenerator2D::CreateStar("curencyStar", glm::vec3(0, 0, 0), curencyStarRadius, zCurencyStar, curencyColor);
    AddMeshToList(curencyStar);

    Mesh* blueHex = objectGenerator2D::CreateHex("blueHex", glm::vec3(0, 0, 0), hexRadius, zHexIn, zHexOut, inHexColour, blueColor);
    AddMeshToList(blueHex);

    Mesh* greenHex = objectGenerator2D::CreateHex("greenHex", glm::vec3(0, 0, 0), hexRadius, zHexIn, zHexOut, inHexColour, darkGreenColor);
    AddMeshToList(greenHex);

    Mesh* yellowHex = objectGenerator2D::CreateHex("yellowHex", glm::vec3(0, 0, 0), hexRadius, zHexIn, zHexOut, inHexColour, goldenColor);
    AddMeshToList(yellowHex);

    Mesh* pinkHex = objectGenerator2D::CreateHex("pinkHex", glm::vec3(0, 0, 0), hexRadius, zHexIn, zHexOut, inHexColour, pinkColor);
    AddMeshToList(pinkHex);

    Mesh* blueProjectile = objectGenerator2D::CreateStar("blueProjectile", glm::vec3(0, 0, 0), projectileStarRadius, zProjectile, blueColor);
    AddMeshToList(blueProjectile);

    Mesh* greenProjectile = objectGenerator2D::CreateStar("greenProjectile", glm::vec3(0, 0, 0), projectileStarRadius, zProjectile, darkGreenColor);
    AddMeshToList(greenProjectile);

    Mesh* yellowProjectile = objectGenerator2D::CreateStar("yellowProjectile", glm::vec3(0, 0, 0), projectileStarRadius, zProjectile, goldenColor);
    AddMeshToList(yellowProjectile);

    Mesh* pinkProjectile = objectGenerator2D::CreateStar("pinkProjectile", glm::vec3(0, 0, 0), projectileStarRadius, zProjectile, pinkColor);
    AddMeshToList(pinkProjectile);

    Mesh* collectableStar = objectGenerator2D::CreateStar("collectableStar", glm::vec3(0, 0, 0), collectableStarRadius, zApearingStar, collectableStarColor);
    AddMeshToList(collectableStar);
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.04f, 0.05f, 0.09f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    glm::mat3 modelMatrix(1);

    //Condition to stop the game at 0 lifes
    if (GameInterface::GetInstance()->getLives() > 0) {

        //Renders barrier and tiles
        modelMatrix = helpers2D::resetModelMatrix(BarrierX, BarrierY);
        RenderMesh2D(meshes["barrier"], shaders["VertexColor"], modelMatrix);

        for (int i = 0; i <= maxIdxMatrix; i++)
        {
            for (int j = 0; j <= maxIdxMatrix; j++)
            {
                modelMatrix = helpers2D::resetModelMatrix(firstTileX + i * (distanceBetweenTiles + tileSideLength), firstTileY + j * (distanceBetweenTiles + tileSideLength));
                RenderMesh2D(meshes["tile"], shaders["VertexColor"], modelMatrix);
            }
        }

        //Renders display tiles with every diamond and prices
        for (int i = 0; i <= maxIdxOfColors; i++)
        {
            float currentDisplayTileX = firstDisplayTileX + i * (distanceBetweenDisplayTiles + tileSideLength);
            float currentDisplayTileY = firstDisplayTileY;

            modelMatrix = helpers2D::resetModelMatrix(currentDisplayTileX, currentDisplayTileY);
            RenderMesh2D(meshes["displayTile"], shaders["VertexColor"], modelMatrix);



            float firstPriceStarPerDisplayTile = currentDisplayTileX + curencyStarRadius - distanceBetweenPriceStars;
            float priceStarsY = currentDisplayTileY - distanceBetweenDisplayTilesAndPriceStars;

            switch (i) {
            case 0:
                modelMatrix = helpers2D::resetModelMatrix(currentDisplayTileX + (tileSideLength - diamondWidth) / 2, currentDisplayTileY + (tileSideLength - diamondHeight) / 2);
                RenderMesh2D(meshes["greenDiamond"], shaders["VertexColor"], modelMatrix);

                for (int k = 0; k < greenDiamondPrice; k++) {
                    modelMatrix = helpers2D::resetModelMatrix(firstPriceStarPerDisplayTile + k * (curencyStarRadius * 2 + distanceBetweenPriceStars), priceStarsY);
                    RenderMesh2D(meshes["curencyStar"], shaders["VertexColor"], modelMatrix);
                }  
                break;
            case 1:
                modelMatrix = helpers2D::resetModelMatrix(currentDisplayTileX + (tileSideLength - diamondWidth) / 2, currentDisplayTileY + (tileSideLength - diamondHeight) / 2);
                RenderMesh2D(meshes["blueDiamond"], shaders["VertexColor"], modelMatrix);

                for (int k = 0; k < blueDiamondPrice; k++) {
                    modelMatrix = helpers2D::resetModelMatrix(firstPriceStarPerDisplayTile + k * (curencyStarRadius * 2 + distanceBetweenPriceStars), priceStarsY);
                    RenderMesh2D(meshes["curencyStar"], shaders["VertexColor"], modelMatrix);
                }
                break;
            case 2:
                modelMatrix = helpers2D::resetModelMatrix(currentDisplayTileX + (tileSideLength - diamondWidth) / 2, currentDisplayTileY + (tileSideLength - diamondHeight) / 2);
                RenderMesh2D(meshes["yellowDiamond"], shaders["VertexColor"], modelMatrix);

                for (int k = 0; k < yellowDiamondPrice; k++) {
                    modelMatrix = helpers2D::resetModelMatrix(firstPriceStarPerDisplayTile + k * (curencyStarRadius * 2 + distanceBetweenPriceStars), priceStarsY);
                    RenderMesh2D(meshes["curencyStar"], shaders["VertexColor"], modelMatrix);
                }
                break;
            case 3:
                modelMatrix = helpers2D::resetModelMatrix(currentDisplayTileX + (tileSideLength - diamondWidth) / 2, currentDisplayTileY + (tileSideLength - diamondHeight) / 2);
                RenderMesh2D(meshes["pinkDiamond"], shaders["VertexColor"], modelMatrix);

                for (int k = 0; k < pinkDiamondPrice; k++) {
                    modelMatrix = helpers2D::resetModelMatrix(firstPriceStarPerDisplayTile + k * (curencyStarRadius * 2 + distanceBetweenPriceStars), priceStarsY);
                    RenderMesh2D(meshes["curencyStar"], shaders["VertexColor"], modelMatrix);
                }
                break;
            default:
                break;
            }
        }
    }
}

void Tema1::Update(float deltaTimeSeconds)
{
    //Condition to stop the game at 0 lifes
    if (GameInterface::GetInstance()->getLives() > 0) {
            
        glm::mat3 modelMatrix;

        //Renders lives
        for (int i = 0; i < GameInterface::GetInstance()->getLives(); i++) {
            float x = firstLifeX + i * (distanceBetweenLives + lifeSideLenght);
            float y = firstLifeY;
            modelMatrix = helpers2D::resetModelMatrix(x, y);
            RenderMesh2D(meshes["lifeHeart"], shaders["VertexColor"], modelMatrix);
        }

        //Renders curency stars
        for (int i = 0; i < GameInterface::GetInstance()->getCurencyStars(); i++) {
            float x = firstCurencyStarX + i * (distanceBetweenCurencyStars + 2 * curencyStarRadius);
            float y = firstCurencyStarY;
            modelMatrix = helpers2D::resetModelMatrix(x, y);
            RenderMesh2D(meshes["curencyStar"], shaders["VertexColor"], modelMatrix);
        }

        //Mechanics for Diamonds(allys)
        for (int i = 0; i <= maxIdxMatrix; i++)
        {
            for (int j = 0; j <= maxIdxMatrix; j++)
            {
                if (GameInterface::GetInstance()->getMap()[i][j] == 1)
                {
                    for (Diamond* ally : GameInterface::GetInstance()->getAllAlies())
                    {
                        if (ally->getMapRow() == i && ally->getMapColumn() == j)
                        {

                            //Changes modelMatrix depending on whether ally is alive or not 
                            //and mechanics for shooting
                            if (ally->isAlive() == true)
                            {
                                modelMatrix = helpers2D::resetModelMatrix(ally->getX(), ally->getY());

                                if (ally->getCooldown() >= 0) {
                                    ally->lowerCooldown(deltaTimeSeconds, shootingCooldownPassingSpeed);
                                }
                                else {
                                    for (Hex* enemy : GameInterface::GetInstance()->getAllEnemies()) {
                                        if (enemy->getRow() == ally->getMapRow() && enemy->getX() < 1280 &&
                                            enemy->color() == ally->color()) {
                                            ally->shoot();
                                            ally->setCooldown(shootingCooldown);
                                        }
                                    }
                                }

                            }
                            else
                            {
                                ally->setXScale(ally->getXScale() - deltaTimeSeconds * dyingSpeed);
                                ally->setYScale(ally->getYScale() - deltaTimeSeconds * dyingSpeed);
                                modelMatrix = glm::mat3(1);
                                glm::mat3 shrinkMat = helpers2D::Translate(ally->getX(), ally->getY()) * helpers2D::Translate(diamondWidth / 2, diamondHeight / 2) * helpers2D::Scale(ally->getXScale(), ally->getYScale()) * helpers2D::Translate(-(diamondWidth / 2), -(diamondHeight / 2));
                                modelMatrix *= shrinkMat;

                            }

                            //Renders the allys
                            switch (ally->color())
                            {
                            case BLUE:
                                RenderMesh2D(meshes["blueDiamond"], shaders["VertexColor"], modelMatrix);
                                break;
                            case YELLOW:
                                RenderMesh2D(meshes["yellowDiamond"], shaders["VertexColor"], modelMatrix);
                                break;
                            case GREEN:
                                RenderMesh2D(meshes["greenDiamond"], shaders["VertexColor"], modelMatrix);
                                break;
                            case PINK:
                                RenderMesh2D(meshes["pinkDiamond"], shaders["VertexColor"], modelMatrix);
                                break;
                            default:
                                break;
                            }

                            //If ally was killed and the scaling is complete remove it from the game/matrix/memory
                            if (ally->getXScale() <= 0 && ally->getXScale() <= 0) {
                                ally->die();
                                delete ally;
                            }
                        }
                    }
                }
            }
        }

        //Mechanics for Hexes(enemys)
        for (Hex* enemy : GameInterface::GetInstance()->getAllEnemies())
        {
            //Changes modelMatrix (+moving) depending on whether enemy is alive or not
            if (enemy->getLives() > 0)
            {
                modelMatrix = helpers2D::resetModelMatrix(enemy->getX(), enemy->getY());
                enemy->setX(enemy->getX() - deltaTimeSeconds * enemySpeed);

            }
            else
            {
                enemy->setXScale(enemy->getXScale() - deltaTimeSeconds * dyingSpeed);
                enemy->setYScale(enemy->getYScale() - deltaTimeSeconds * dyingSpeed);
                modelMatrix = glm::mat3(1);
                glm::mat3 shrinkMat = helpers2D::Translate(enemy->getX(), enemy->getY()) * helpers2D::Scale(enemy->getXScale(), enemy->getYScale());
                modelMatrix *= shrinkMat;

            }

            //Render enemys
            switch (enemy->color())
            {
            case BLUE:
                RenderMesh2D(meshes["blueHex"], shaders["VertexColor"], modelMatrix);
                break;
            case YELLOW:
                RenderMesh2D(meshes["yellowHex"], shaders["VertexColor"], modelMatrix);
                break;
            case GREEN:
                RenderMesh2D(meshes["greenHex"], shaders["VertexColor"], modelMatrix);
                break;
            case PINK:
                RenderMesh2D(meshes["pinkHex"], shaders["VertexColor"], modelMatrix);
                break;
            default:
                break;
            }

            //Mechanic to lose life
            if (enemy->getX() <= enemyFinishX) {
                GameInterface::GetInstance()->loseLife();
            }

            //If enemy was killed and the scaling is complete remove it from the game/matrix/memory
            if ((enemy->getXScale() <= 0 && enemy->getXScale() <= 0) || enemy->getX() <= enemyFinishX) {
                enemy->die();
                delete enemy;
            }
        }

        //Mechanics for projectiles
        for (Projectile* projectile : GameInterface::GetInstance()->getAllProjectiles()) {

            //Changes modelMatrix(+moving +rotating) depending on whether projectile has hit or not
            if (projectile->didItHit() == false)
            {
                modelMatrix = helpers2D::resetModelMatrix(projectile->getX(), projectile->getY()) * helpers2D::Rotate(projectile->getRotRad());
                projectile->setRotRad(projectile->getRotRad() - deltaTimeSeconds * projectileRotationSpeed);
                projectile->setX(projectile->getX() + deltaTimeSeconds * projectileTranslationSpeed);

                if (projectile->getRotRad() * 180 / M_PI <= -360) { //loop rotation to not go to - infinity
                    projectile->setRotRad(0);
                }
                
            }

            //Renders projetiles
            switch (projectile->color())
            {
            case BLUE:
                RenderMesh2D(meshes["blueProjectile"], shaders["VertexColor"], modelMatrix);
                break;
            case YELLOW:
                RenderMesh2D(meshes["yellowProjectile"], shaders["VertexColor"], modelMatrix);
                break;
            case GREEN:
                RenderMesh2D(meshes["greenProjectile"], shaders["VertexColor"], modelMatrix);
                break;
            case PINK:
                RenderMesh2D(meshes["pinkProjectile"], shaders["VertexColor"], modelMatrix);
                break;
            default:
                break;
            }

            if ((projectile->didItHit() == true) || projectile->getX() >= projectileFinishX) {
                projectile->die();
                delete projectile;
            }
          
        }

        //Manages interaction between enemy and ally/projectile
        //(+mechanics of dying for both of them if conditions are met)
        for (Hex* enemy : GameInterface::GetInstance()->getAllEnemies()) 
        {
            for (Diamond* ally : GameInterface::GetInstance()->getAllAlies())
            {
                if (glm::distance(glm::vec2(ally->getX() + diamondWidth / 2 , ally->getY() + diamondHeight / 2), glm::vec2(enemy->getX(), enemy->getY())) <= diamondHeight / 2 + hexRadius) {
                    ally->setAlive(false);
                }
            }

            for (Projectile* projectile : GameInterface::GetInstance()->getAllProjectiles())
            {
                if (enemy->getRow() == projectile->getRow() && enemy->color() == projectile->color() &&
                    glm::distance(glm::vec2(enemy->getX() , enemy->getY()), glm::vec2(projectile->getX(), projectile->getY())) <= hexRadius + projectileStarRadius) {
                    projectile->setHitStatus(true);
                    enemy->loseLife();
                }
            }
        }

        //Mechanics of collectable stars (renders it if is not collected and erase from matrix/delete it when it is + adds funds)
        for (CollectableStar* collectable : GameInterface::GetInstance()->getAllCollectableStars())
        {
            if (collectable->isCollected()) {
                collectable->collect();
                delete collectable;
            }
            else {
                modelMatrix = helpers2D::resetModelMatrix(collectable->getX(), collectable->getY());
                RenderMesh2D(meshes["collectableStar"], shaders["VertexColor"], modelMatrix);
            }
        }

        //Randomizer mechanics
        random_device rd;
        mt19937 gen(rd());

        //Resets timer for random spawn time for enemys in an interval and spawn time lowered by time (making it harder)
        //~(Mechanics for spawning enemyes)
        nextEnemyTimer += deltaTimeSeconds;
        if (nextEnemyTimer >= timeUntilNextEnemy) {
            nextEnemyTimer = 0;
            if (randomizerLowerLimit > leastTimeUnitsBetweenEnemies) {
                randomizerLowerLimit -= difficultyIncreaserUnit;
                randomizerUpperLimit -= difficultyIncreaserUnit;
            }

            uniform_int_distribution<> disSpawnTime(randomizerLowerLimit, randomizerUpperLimit);
            uniform_int_distribution<> disNextRow(0, maxIdxMatrix);
            uniform_int_distribution<> disNextColor(0, maxIdxOfColors);
            int rndSpawnTime = disSpawnTime(gen);
            int rndNextRow = disNextRow(gen);
            int rndNextColor = disNextColor(gen);
            timeUntilNextEnemy = rndSpawnTime / timeUnitSizeAjuster;

            switch (rndNextColor)
            {
            case 0:
                nextEnemyColor = BLUE;
                break;
            case 1:
                nextEnemyColor = YELLOW;
                break;
            case 2:
                nextEnemyColor = GREEN;
                break;
            case 3:
                nextEnemyColor = PINK;
                break;
            default:
                break;
            };

            enemySpawner.create(nextEnemyColor, rndNextRow);
        }

        //Resets timer for random spawn time for 3 collectable stars at a fixed interval
        //~(Mechanics for spawning collectable stars)
        nextCollectablesTimer += deltaTimeSeconds;
        if (nextCollectablesTimer >= timeUntilNextCollectables) {
            nextCollectablesTimer = 0;

            uniform_int_distribution<> disX(0 + collectableStarRadius, window->GetResolution().x - collectableStarRadius);
            uniform_int_distribution<> disY(0 + collectableStarRadius, window->GetResolution().y - (guiHeight + collectableStarRadius));

            for (int i = 0; i < numOfCollectableStarsToGenerate; i++) {
                float nextStarX = (float)disX(gen);
                float nextStarY = (float)disY(gen);
                CollectableStar* nextStar = new CollectableStar(nextStarX, nextStarY);
                nextStar->addItToVectorr();
            }
        }

        //(Drag&Drop) Renders the diamond mesh when you drag it from the displayed tiles when you keep the mouse clicked
        if (leftMouseIsPressed) {
            modelMatrix = helpers2D::resetModelMatrix(dndDiamondX, dndDiamondY);
            switch (dndDiamondColor)
            {
            case BLUE:
                RenderMesh2D(meshes["blueDiamond"], shaders["VertexColor"], modelMatrix);
                break;
            case YELLOW:
                RenderMesh2D(meshes["yellowDiamond"], shaders["VertexColor"], modelMatrix);
                break;
            case GREEN:
                RenderMesh2D(meshes["greenDiamond"], shaders["VertexColor"], modelMatrix);
                break;
            case PINK:
                RenderMesh2D(meshes["pinkDiamond"], shaders["VertexColor"], modelMatrix);
                break;
            default:
                break;
            };
        }       
    }
}
    

void Tema1::FrameEnd()
{  
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}

void Tema1::OnKeyPress(int key, int mods)
{  
}

void Tema1::OnKeyRelease(int key, int mods)
{
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    //(Drag&Drop) Keeps the coordonates of mouse in order to move mesh with it
    dndDiamondX = mouseX - diamondWidth / 2;
    dndDiamondY = window->GetResolution().y - mouseY - diamondHeight / 2;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    //Mechanic of deleting an ally on right mouse
    if (button == 2) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if ((mouseX >= firstTileX + j * (tileSideLength + distanceBetweenTiles) && mouseX <= firstTileX + j * distanceBetweenTiles + (j + 1) * tileSideLength)
                    && (mouseY <= (window->GetResolution().y - firstTileY) - i * (tileSideLength + distanceBetweenTiles) && mouseY >= (window->GetResolution().y - firstTileY) - i * distanceBetweenTiles - (i + 1) * tileSideLength)) {
                    for (Diamond* ally : GameInterface::GetInstance()->getAllAlies())
                    {
                        if (ally->getMapRow() == i && ally->getMapColumn() == j &&
                            GameInterface::GetInstance()->getMap()[i][j] == 1)
                        {
                            ally->setAlive(false);
                        }
                    }
                }
            }
        }
    }
  
    //(Drag&Drop) Sets all the info needed for Update in order to make drag and drop look right
    for (int i = 0; i <= maxIdxOfColors; i++)
    {
        float currentDisplayTileX = firstDisplayTileX + i * (distanceBetweenDisplayTiles + tileSideLength);
        float currentDisplayTileY = firstDisplayTileY;
        if (mouseX >= currentDisplayTileX && mouseX <= currentDisplayTileX + tileSideLength
            && mouseY <= window->GetResolution().y - currentDisplayTileY && mouseY >= window->GetResolution().y - currentDisplayTileY - tileSideLength) {
            if (button == 1) {
                leftMouseIsPressed = true;
                switch (i)
                {
                case 0:
                    dndDiamondColor = GREEN;
                    priceToPay = greenDiamondPrice;
                    break;
                case 1:
                    dndDiamondColor = BLUE;
                    priceToPay = blueDiamondPrice;
                    break;
                case 2:
                    dndDiamondColor = YELLOW;
                    priceToPay = yellowDiamondPrice;
                    break;
                case 3:
                    dndDiamondColor = PINK;
                    priceToPay = pinkDiamondPrice;
                    break;
                default:
                    break;
                };
            }
        }
    }

    //Mechanic for when you click the star to collect it
    for (CollectableStar* collectable : GameInterface::GetInstance()->getAllCollectableStars())
    {
        if (mouseX >= collectable->getX() - collectableStarRadius && mouseX <= collectable->getX() + collectableStarRadius
            && mouseY >= window->GetResolution().y - (collectable->getY() + collectableStarRadius)
            && mouseY <= window->GetResolution().y - (collectable->getY() - collectableStarRadius)
            && button == 1) {
            collectable->setCollected(true);
        }
    }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    //(Drag&Drop) Final step in drag and drop, the drop :)) , and also if it's not on tile to not count
    if (button == 1) {
        for (int i = 0; i <= maxIdxMatrix; i++)
        {
            for (int j = 0; j <= maxIdxMatrix; j++)
            {
                if (mouseX >= firstTileX + j * (distanceBetweenTiles + tileSideLength) &&
                    mouseX <= firstTileX + j * (distanceBetweenTiles + tileSideLength) + tileSideLength &&
                    mouseY <= window->GetResolution().y - (firstTileY + i * (distanceBetweenTiles + tileSideLength)) &&
                    mouseY >= window->GetResolution().y - (firstTileY + i * (distanceBetweenTiles + tileSideLength)) - tileSideLength &&
                    GameInterface::GetInstance()->getMap()[i][j] == 0 && leftMouseIsPressed 
                    && GameInterface::GetInstance()->getCurencyStars() >= priceToPay) {
                    GameInterface::GetInstance()->payStars(priceToPay);
                    allySpawner.create(dndDiamondColor, i, j);
                }               
            }
        }
        leftMouseIsPressed = false;
    }
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
