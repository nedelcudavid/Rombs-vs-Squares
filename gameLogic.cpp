#include "gameLogic.h"

//-------------------- GUI and Map = Game Interface Class --------------------

GameInterface* GameInterface::singleton_ = nullptr;;

GameInterface* GameInterface::GetInstance()
{
	if (singleton_ == nullptr) {
		singleton_ = new GameInterface();
	}
	return singleton_;
}

void GameInterface::addStar() {
	curencyStars++;
}

void GameInterface::payStars(int cost) {
	curencyStars -= cost;
}

void GameInterface::loseLife() {
	lives--;
}

//-------------------- Diamond Classes --------------------

// BlueDiamond --------------------------------------------

TypeColor BlueDiamond::color()
{
	return BLUE;
}

// YellowDiamond --------------------------------------------

TypeColor YellowDiamond::color()
{
	return YELLOW;
}


// GreenDiamond --------------------------------------------

TypeColor GreenDiamond::color()
{
	return GREEN;
}

// PinkDiamond --------------------------------------------

TypeColor PinkDiamond::color()
{
	return PINK;
}


// Diamond Factory-----------------------------------------
Diamond* DiamondFactory::create(TypeColor color, int row, int column)
{
	switch (color)
	{
	case BLUE:
		return new BlueDiamond(row, column);
		break;
	case YELLOW:
		return new YellowDiamond(row, column);
		break;
	case GREEN:
		return new GreenDiamond(row, column);
		break;
	case PINK:
		return new PinkDiamond(row, column);
		break;
	default:
		break;
	}
}


//-------------------- Hex Classes ------------------------

// BlueHex --------------------------------------------

TypeColor BlueHex::color()
{
	return BLUE;
}

// YellowHex --------------------------------------------

TypeColor YellowHex::color()
{
	return YELLOW;
}

// GreenHex --------------------------------------------

TypeColor GreenHex::color()
{
	return GREEN;
}

// PinkHex --------------------------------------------

TypeColor PinkHex::color()
{
	return PINK;
}

// Hex Factory-----------------------------------------
Hex* HexFactory::create(TypeColor color, int row)
{
	switch (color)
	{
	case BLUE:
		return new BlueHex(row);
		break;
	case YELLOW:
		return new YellowHex(row);
		break;
	case GREEN:
		return new GreenHex(row);
		break;
	case PINK:
		return new PinkHex(row);
		break;
	default:
		break;
	}
}

//-------------------- Projectile Classes ------------------------
// ProjectileHex --------------------------------------------

TypeColor BlueProjectile::color()
{
	return BLUE;
}

// YellowProjectile --------------------------------------------

TypeColor YellowProjectile::color()
{
	return YELLOW;
}

// GreenProjectile --------------------------------------------

TypeColor GreenProjectile::color()
{
	return GREEN;
}


// PinkProjectile --------------------------------------------

TypeColor PinkProjectile::color()
{
	return PINK;
}

// Projectile Factory-----------------------------------------
Projectile* ProjectileFactory::create(TypeColor color, int cr_row, float cr_X, float cr_Y)
{
	switch (color)
	{
	case BLUE:
		return new BlueProjectile(cr_row, cr_X, cr_Y);
		break;
	case YELLOW:
		return new YellowProjectile(cr_row, cr_X, cr_Y);
		break;
	case GREEN:
		return new GreenProjectile(cr_row, cr_X, cr_Y);
		break;
	case PINK:
		return new PinkProjectile(cr_row, cr_X, cr_Y);
		break;
	default:
		break;
	}
}

// CollectableStar --------------------------------------------

void CollectableStar::addItToVectorr() {
	GameInterface::GetInstance()->getAllCollectableStars().push_back(this);
};

void CollectableStar::collect() {
	GameInterface::GetInstance()->addStar();
	auto it = std::find(GameInterface::GetInstance()->getAllCollectableStars().begin(), GameInterface::GetInstance()->getAllCollectableStars().end(), this);
	if (it != GameInterface::GetInstance()->getAllCollectableStars().end()) {
		GameInterface::GetInstance()->getAllCollectableStars().erase(it);
	}
};