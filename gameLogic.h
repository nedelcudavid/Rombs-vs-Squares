#pragma once
#include "lab_m1/Tema1/helpers2D.h"

#include <string>
#include <iostream>
#include <array>
#include <vector>

using namespace std;
using namespace helpers2D;

enum TypeColor { BLUE, YELLOW, GREEN, PINK };

//-------------------- Base Classes --------------------

class Diamond
{       
protected:
    bool alive = false;
    int map_invRow = 0;
    int map_column = 0;
    float x_pos = 0;
    float y_pos = 0;
    float x_scale = 0;
    float y_scale = 0;
    float shootCooldown = 0;

public:
    Diamond() {
        alive = false;
        map_invRow = 0;
        map_column = 0;
        float x_pos = 0;
        float y_pos = 0;
        float x_scale = 0;
        float y_scale = 0;
        float shootCooldown = 0;
    }

    virtual TypeColor color() = 0;

    void setAlive(bool lifeStatus) {
        alive = lifeStatus;
    }

    float getCooldown() {
        return shootCooldown;
    }

    void setCooldown(float cooldownReset) {
        shootCooldown = cooldownReset;
    }

    void lowerCooldown(float deltatimeSec, float multiplier) {
        shootCooldown -= deltatimeSec * multiplier;
    }

    bool isAlive() {
        return alive;
    }

    void setMapRow(int newIX) {
        map_invRow = newIX;
    }

    int getMapRow() {
        return map_invRow;
    }

    void setMapColumn(int newJY) {
        map_column = newJY;
    }

    int getMapColumn() {
        return map_column;
    }

    float getX() {
        return x_pos;
    }

    float getY() {
        return y_pos;
    }

    float getXScale() {
        return x_scale;
    }

    void setXScale(float newX) {
        x_scale = newX;
    }

    float getYScale() {
        return y_scale;
    }

    void setYScale(float newY) {
        y_scale = newY;
    }

    virtual void shoot() = 0;
    virtual void die() = 0;

};

class Hex
{
protected:
    int lives = 0;
    int row = 0;
    float x_pos = 0;
    float y_pos = 0;
    float x_scale = 0;
    float y_scale = 0;

public:
    Hex() {
        lives = 0;
        int row = 0;
        float x_pos = 0;
        float y_pos = 0;
        float x_scale = 0;
        float y_scale = 0;
    }
    virtual TypeColor color() = 0;

    void setLifes(int lifeStatus) {
        lives = lifeStatus;
    }

    void loseLife() {
        lives--;
    }

    int getLives() {
        return lives;
    }

    int getRow() {
        return row;
    }

    float getX() {
        return x_pos;
    }

    void setX(float newX) {
        x_pos = newX;
    }

    float getY() {
        return y_pos;
    }

    float getXScale() {
        return x_scale;
    }

    void setXScale(float newX) {
        x_scale = newX;
    }

    float getYScale() {
        return y_scale;
    }

    void setYScale(float newY) {
        y_scale = newY;
    }

    virtual void die() = 0;

};

class Projectile
{
protected:
    bool hit = false;
    int row = 0;
    float x_pos = 0;
    float y_pos = 0;
    float rotRadians = 0;

public:
    void setHitStatus(bool hitStatus) {
        hit = hitStatus;
    }

    bool didItHit() {
        return hit;
    }

    int getRow() {
        return row;
    }

    float getX() {
        return x_pos;
    }

    void setX(float newX) {
        x_pos = newX;
    }

    float getY() {
        return y_pos;
    }

    float getRotRad() {
        return rotRadians;
    }

    void setRotRad(float newRotRad) {
        rotRadians = newRotRad;
    }

    virtual void die() = 0;
    virtual TypeColor color() = 0;
};

//-------------------- Factories --------------------

// creates the types of diamonds we need
class DiamondFactory
{
public:
    Diamond* create(TypeColor color, int row, int column);

};

// creates the types of diamonds we need
class HexFactory
{
public:
    Hex* create(TypeColor color, int row);

};

// creates the types of diamonds we need
class ProjectileFactory
{
public:
    Projectile* create(TypeColor color, int cr_row, float cr_X, float cr_Y);

};

//-------------------- CollectableStar Class --------------------

class CollectableStar
{
private:
    bool collected;
    float x;
    float y;
public:
    CollectableStar(float received_x, float received_y) {
        collected = false;
        x = received_x;
        y = received_y;
    }

    bool isCollected() {
        return collected;
    }

    void setCollected(bool newStatus) {
        collected = newStatus;
    }

    float getX() {
        return x;
    }

    float getY() {
        return y;
    }

    void addItToVectorr();
    void collect();
};

//-------------------- GUI and Map = Game Interface Class --------------------
class GameInterface {

    typedef std::array<int, 3> row_type;
    typedef std::array<row_type, 3> mat3x3_type;

private:
    GameInterface()
    {
        lives = 3;
        curencyStars = 5;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m_map[i][j] = 0;
            }
        }
    }
    static GameInterface* singleton_;

    int lives;
    int curencyStars;
    mat3x3_type m_map; //Map to keep track if a tile si occupied or not (0 - free, 1 - ocupied)
    vector<Diamond*> allAllies;
    vector<Hex*> AllEnemies;
    vector<Projectile*> AllProjectiles;
    vector<CollectableStar*> AllCollectableStars;

public:
    GameInterface(GameInterface& other) = delete;
    void operator=(const GameInterface&) = delete;
    static GameInterface* GetInstance();

    int getLives() {
        return lives;
    }

    int getCurencyStars() {
        return curencyStars;
    }


    mat3x3_type& getMap() { return m_map; }

    void addStar();
    void payStars(int cost);
    void loseLife();

    vector<Diamond*>& getAllAlies() {
        return allAllies;
    }

    vector<Hex*>& getAllEnemies() {
        return AllEnemies;
    }

    vector<Projectile*>& getAllProjectiles() {
        return AllProjectiles;
    }

    vector<CollectableStar*>& getAllCollectableStars() {
        return AllCollectableStars;
    }
};

//-------------------- Diamond Classes --------------------

class BlueDiamond : public Diamond
{
public:
    BlueDiamond(int row, int column) {
        alive = true;
        map_invRow = row;
        map_column = column;
        x_pos = firstTileX + (tileSideLength - diamondWidth) / 2 + map_column * (tileSideLength + distanceBetweenTiles);
        y_pos = firstTileY + (tileSideLength - diamondHeight) / 2 + map_invRow * (tileSideLength + distanceBetweenTiles);
        x_scale = 1;
        y_scale = 1;
        shootCooldown = shootingCooldown;
        GameInterface::GetInstance()->getMap()[row][column] = 1;
        GameInterface::GetInstance()->getAllAlies().push_back(this);
    }

    TypeColor color();

    void shoot() override {
        ProjectileFactory projectileMaker;
        projectileMaker.create(color(), map_invRow, x_pos, y_pos);
    };

    void die() override {
        alive = false;
        GameInterface::GetInstance()->getMap()[this->getMapRow()][this->getMapColumn()] = 0;

        auto it = std::find(GameInterface::GetInstance()->getAllAlies().begin(), GameInterface::GetInstance()->getAllAlies().end(), this);
        if (it != GameInterface::GetInstance()->getAllAlies().end()) {
            GameInterface::GetInstance()->getAllAlies().erase(it);
        }
    };
};

class YellowDiamond : public Diamond
{
public:
    YellowDiamond(int row, int column) {
        alive = true;
        map_invRow = row;
        map_column = column;
        x_pos = firstTileX + (tileSideLength - diamondWidth) / 2 + map_column * (tileSideLength + distanceBetweenTiles);
        y_pos = firstTileY + (tileSideLength - diamondHeight) / 2 + map_invRow * (tileSideLength + distanceBetweenTiles);
        x_scale = 1;
        y_scale = 1;
        shootCooldown = shootingCooldown;
        GameInterface::GetInstance()->getMap()[row][column] = 1;
        GameInterface::GetInstance()->getAllAlies().push_back(this);
    }

    TypeColor color();

    void shoot() override {
        ProjectileFactory projectileMaker;
        projectileMaker.create(color(), map_invRow, x_pos, y_pos);
    };

    void die() override {
        alive = false;
        GameInterface::GetInstance()->getMap()[this->getMapRow()][this->getMapColumn()] = 0;

        auto it = std::find(GameInterface::GetInstance()->getAllAlies().begin(), GameInterface::GetInstance()->getAllAlies().end(), this);
        if (it != GameInterface::GetInstance()->getAllAlies().end()) {
            GameInterface::GetInstance()->getAllAlies().erase(it);
        }
    };
};

class GreenDiamond : public Diamond
{
public:
    GreenDiamond(int row, int column) {
        alive = true;
        map_invRow = row;
        map_column = column;
        x_pos = firstTileX + (tileSideLength - diamondWidth) / 2 + map_column * (tileSideLength + distanceBetweenTiles);
        y_pos = firstTileY + (tileSideLength - diamondHeight) / 2 + map_invRow * (tileSideLength + distanceBetweenTiles);
        x_scale = 1;
        y_scale = 1;
        shootCooldown = shootingCooldown;
        GameInterface::GetInstance()->getMap()[row][column] = 1;
        GameInterface::GetInstance()->getAllAlies().push_back(this);
    }

    TypeColor color();

    void shoot() override {
        ProjectileFactory projectileMaker;
        projectileMaker.create(color(), map_invRow, x_pos, y_pos);
    };

    void die() override {
        alive = false;
        GameInterface::GetInstance()->getMap()[this->getMapRow()][this->getMapColumn()] = 0;

        auto it = std::find(GameInterface::GetInstance()->getAllAlies().begin(), GameInterface::GetInstance()->getAllAlies().end(), this);
        if (it != GameInterface::GetInstance()->getAllAlies().end()) {
            GameInterface::GetInstance()->getAllAlies().erase(it);
        }
    };
};


class PinkDiamond : public Diamond
{
public:
    PinkDiamond(int row, int column) {
        alive = true;
        map_invRow = row;
        map_column = column;
        x_pos = firstTileX + (tileSideLength - diamondWidth) / 2 + map_column * (tileSideLength + distanceBetweenTiles);
        y_pos = firstTileY + (tileSideLength - diamondHeight) / 2 + map_invRow * (tileSideLength + distanceBetweenTiles);
        x_scale = 1;
        y_scale = 1;
        shootCooldown = shootingCooldown;
        GameInterface::GetInstance()->getMap()[row][column] = 1;
        GameInterface::GetInstance()->getAllAlies().push_back(this);
    }

    TypeColor color();

    void shoot() override {
        ProjectileFactory projectileMaker;
        projectileMaker.create(color(), map_invRow, x_pos, y_pos);
    };

    void die() override {
        alive = false;
        GameInterface::GetInstance()->getMap()[this->getMapRow()][this->getMapColumn()] = 0;

        auto it = std::find(GameInterface::GetInstance()->getAllAlies().begin(), GameInterface::GetInstance()->getAllAlies().end(), this);
        if (it != GameInterface::GetInstance()->getAllAlies().end()) {
            GameInterface::GetInstance()->getAllAlies().erase(it);
        }
    };
};

//-------------------- Hex Classes --------------------

class BlueHex : public Hex
{
public:
    BlueHex(int n_row) {
        lives = 3;
        row = n_row;
        x_pos = enemySpawnX;
        y_pos = firstTileY + tileSideLength / 2 + row * (tileSideLength + distanceBetweenTiles);
        x_scale = 1;
        y_scale = 1;
        GameInterface::GetInstance()->getAllEnemies().push_back(this);
    }

    TypeColor color();
    
    void die() override {
        auto it = std::find(GameInterface::GetInstance()->getAllEnemies().begin(), GameInterface::GetInstance()->getAllEnemies().end(), this);
        if (it != GameInterface::GetInstance()->getAllEnemies().end()) {
            GameInterface::GetInstance()->getAllEnemies().erase(it);
        }
    };
};

class YellowHex : public Hex
{
public:
    YellowHex(int n_row) {
        lives = 3;
        row = n_row;
        x_pos = enemySpawnX;
        y_pos = firstTileY + tileSideLength / 2 + row * (tileSideLength + distanceBetweenTiles);
        x_scale = 1;
        y_scale = 1;
        GameInterface::GetInstance()->getAllEnemies().push_back(this);
    }

    TypeColor color();
    
    void die() override {
        auto it = std::find(GameInterface::GetInstance()->getAllEnemies().begin(), GameInterface::GetInstance()->getAllEnemies().end(), this);
        if (it != GameInterface::GetInstance()->getAllEnemies().end()) {
            GameInterface::GetInstance()->getAllEnemies().erase(it);
        }
    };
};

class GreenHex : public Hex
{
public:
    GreenHex(int n_row) {
        lives = 3;
        row = n_row;
        x_pos = enemySpawnX;
        y_pos = firstTileY + tileSideLength / 2 + row * (tileSideLength + distanceBetweenTiles);
        x_scale = 1;
        y_scale = 1;
        GameInterface::GetInstance()->getAllEnemies().push_back(this);
    }

    TypeColor color();
    
    void die() override {
        auto it = std::find(GameInterface::GetInstance()->getAllEnemies().begin(), GameInterface::GetInstance()->getAllEnemies().end(), this);
        if (it != GameInterface::GetInstance()->getAllEnemies().end()) {
            GameInterface::GetInstance()->getAllEnemies().erase(it);
        }
    };
};


class PinkHex : public Hex
{
public:
    PinkHex(int n_row) {
        lives = 3;
        row = n_row;
        x_pos = enemySpawnX;
        y_pos = firstTileY + tileSideLength / 2 + row * (tileSideLength + distanceBetweenTiles);
        x_scale = 1;
        y_scale = 1;
        GameInterface::GetInstance()->getAllEnemies().push_back(this);
    }

    TypeColor color();
    
    void die() override {
        auto it = std::find(GameInterface::GetInstance()->getAllEnemies().begin(), GameInterface::GetInstance()->getAllEnemies().end(), this);
        if (it != GameInterface::GetInstance()->getAllEnemies().end()) {
            GameInterface::GetInstance()->getAllEnemies().erase(it);
        }
    };
};

//-------------------- Projectile Classes --------------------

class BlueProjectile : public Projectile
{
public:
    BlueProjectile(int cr_row, float cr_X, float cr_Y) {
        hit = false;
        row = cr_row;
        x_pos = cr_X + diamondHeight / 2 + diamondHeight / 2;
        y_pos = cr_Y + diamondHeight / 2;
        rotRadians = 0;
       
        GameInterface::GetInstance()->getAllProjectiles().push_back(this);
    }

    TypeColor color();

    void die() override {
        auto it = std::find(GameInterface::GetInstance()->getAllProjectiles().begin(), GameInterface::GetInstance()->getAllProjectiles().end(), this);
        if (it != GameInterface::GetInstance()->getAllProjectiles().end()) {
            GameInterface::GetInstance()->getAllProjectiles().erase(it);
        }
    };
  
};

class YellowProjectile : public Projectile
{
public:
    YellowProjectile(int cr_row, float cr_X, float cr_Y) {
        hit = false;
        row = cr_row;
        x_pos = cr_X + diamondHeight / 2 + diamondHeight / 2;
        y_pos = cr_Y + diamondHeight / 2;
        rotRadians = 0;

        GameInterface::GetInstance()->getAllProjectiles().push_back(this);
    }

    TypeColor color();

    void die() override {
        auto it = std::find(GameInterface::GetInstance()->getAllProjectiles().begin(), GameInterface::GetInstance()->getAllProjectiles().end(), this);
        if (it != GameInterface::GetInstance()->getAllProjectiles().end()) {
            GameInterface::GetInstance()->getAllProjectiles().erase(it);
        }
    };

};

class GreenProjectile : public Projectile
{
public:
    GreenProjectile(int cr_row, float cr_X, float cr_Y) {
        hit = false;
        row = cr_row;
        x_pos = cr_X + diamondHeight / 2 + diamondHeight / 2;
        y_pos = cr_Y + diamondHeight / 2;
        rotRadians = 0;

        GameInterface::GetInstance()->getAllProjectiles().push_back(this);
    }

    TypeColor color();

    void die() override {
        auto it = std::find(GameInterface::GetInstance()->getAllProjectiles().begin(), GameInterface::GetInstance()->getAllProjectiles().end(), this);
        if (it != GameInterface::GetInstance()->getAllProjectiles().end()) {
            GameInterface::GetInstance()->getAllProjectiles().erase(it);
        }
    };
  
};


class PinkProjectile : public Projectile
{
public:
    PinkProjectile(int cr_row, float cr_X, float cr_Y) {
        hit = false;
        row = cr_row;
        x_pos = cr_X + diamondHeight / 2 + diamondHeight / 2;
        y_pos = cr_Y + diamondHeight / 2;
        rotRadians = 0;

        GameInterface::GetInstance()->getAllProjectiles().push_back(this);
    }

    TypeColor color();

    void die() override {
        auto it = std::find(GameInterface::GetInstance()->getAllProjectiles().begin(), GameInterface::GetInstance()->getAllProjectiles().end(), this);
        if (it != GameInterface::GetInstance()->getAllProjectiles().end()) {
            GameInterface::GetInstance()->getAllProjectiles().erase(it);
        }
    };
};



