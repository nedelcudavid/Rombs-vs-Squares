#pragma once

#include "utils/glm_utils.h"



namespace helpers2D
{
    //Sizes:
    static const float hexRadius = 45.0f;
    static const float curencyStarRadius = 20.0f;
    static const float diamondWidth = 60.0f;
    static const float diamondHeight = 100.0f;
    static const float barrierWidth = 60.0f;
    static const float barrierHeight = 430.0f;
    static const float tileSideLength = 120.0f;
    static const float lifeUnitSize = 12.0f;
    static const float lifeSideLenght = 6 * lifeUnitSize;
    static const float projectileStarRadius = 30.0f;  
    static const float collectableStarRadius = 35.0f;


    //Colors:
    static const glm::vec3 tileColor = glm::vec3(0.19f, 0.91f, 0.59f);
    static const glm::vec3 barrierColor = glm::vec3(0.64f, 0.08f, 0.08f);
    static const glm::vec3 blueColor = glm::vec3(0.18f, 0.26f, 0.52f);
    static const glm::vec3 goldenColor = glm::vec3(0.99f, 0.84f, 0.00f);
    static const glm::vec3 darkGreenColor = glm::vec3(0.06f, 0.31f, 0.02f);
    static const glm::vec3 pinkColor = glm::vec3(0.90f, 0.33f, 0.50f);
    static const glm::vec3 curencyColor = glm::vec3(0.94f, 0.96f, 0.44f);
    static const glm::vec3 inHexColour = glm::vec3(0.71f, 0.24f, 0.24f);
    static const glm::vec3 lifeColor = glm::vec3(0.99f, 0.05f, 0.01f);
    static const glm::vec3 displayFrameColor = glm::vec3(0.27f, 0.44f, 0.31f);
    static const glm::vec3 collectableStarColor = glm::vec3(0.62f, 0.11f, 0.62f);

    //Overlay (Z of the visuals):
    static const float zTile = 0.1f;
    static const float zBarrier = 0.2f;
    static const float zDisplayFrame = 0.1f;
    static const float zDiamonds = 0.2f;
    static const float zCurencyStar = 0.1f;
    static const float zApearingStar = 0.3f;
    static const float zProjectile = 0.13f;
    static const float zHexOut = 0.15f;
    static const float zHexIn = 0.25f;
    static const float zLifes = 0.1f;

    //Randomizer:
    static const int leastTimeUnitsBetweenEnemies = 100;
    static const int difficultyIncreaserUnit = 10;

    //Coordonates and randering info:
    static const float firstCurencyStarX = 845.0f;
    static const float firstCurencyStarY = 580.0f;
    static const float distanceBetweenCurencyStars = 1.0f;

    static const float firstLifeX = 830.0f;
    static const float firstLifeY = 615.0f;
    static const float distanceBetweenLives = 38.0f;

    static const float firstTileX = 100.0f;
    static const float firstTileY = 25.0f;
    static const float distanceBetweenTiles = 35.0f;

    static const float BarrierX = 10.0f;
    static const float BarrierY = 25.0f;

    static const float firstDisplayTileX = 70.0f;
    static const float firstDisplayTileY = 580.0f;
    static const float distanceBetweenDisplayTiles = 70.0f;

    static const float distanceBetweenDisplayTilesAndPriceStars = 22.0f;
    static const float distanceBetweenPriceStars = 1.0f;
    static const int greenDiamondPrice = 1;
    static const int blueDiamondPrice = 2;
    static const int yellowDiamondPrice = 2;
    static const int pinkDiamondPrice = 3;

    //Others:
    static const int maxIdxMatrix = 2;
    static const int maxIdxOfColors = 3;
    static const float timeUnitSizeAjuster = 100.0f;

    static const float enemySpawnX = 1326.0f;
    static const float enemyFinishX = 40.0f;
    static const float enemySpeed = 60.0f;
    static const float dyingSpeed = 2.0f;

    static const float projectileFinishX = 1400.0f;
    static const float projectileRotationSpeed = 3.0f;
    static const float projectileTranslationSpeed = 200.0f;

    static const float shootingCooldownPassingSpeed = 3.0f;
    static const float shootingCooldown = 7.0f;

    static const int numOfCollectableStarsToGenerate = 3;
    static const int guiHeight = tileSideLength + distanceBetweenDisplayTilesAndPriceStars + 2 * curencyStarRadius + firstTileY;

    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        return glm::transpose(
            glm::mat3(1, 0, translateX,
                0, 1, translateY,
                0, 0, 1)
        );

    }

    // Scale matrix
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
        return glm::transpose(
            glm::mat3(scaleX, 0, 0,
                      0, scaleY, 0,
                      0, 0, 1)
        );

    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        return glm::transpose(
            glm::mat3(cos(radians), -sin(radians), 0,
                      sin(radians), cos(radians), 0,
                      0, 0, 1)
        );

    }

    inline glm::mat3 Rotate3D(float radians)
    {
        return glm::transpose(
            glm::mat3(cos(radians), -sin(radians), 0,
                sin(radians), sin(radians), 0,
                0, 0, 1)
        );

    }

    //Reset modelMatrix
    inline glm::mat3 resetModelMatrix(float newX, float newY)
    {
        glm::mat3 modelMatrix = glm::mat3(1);
        modelMatrix *= Translate(newX, newY);
        return modelMatrix;

    }

} 