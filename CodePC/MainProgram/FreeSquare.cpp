#include "FreeSquare.h"
#include "Board.h"

bool FreeSquare::isTexturesLoaded = false;
sf::Texture FreeSquare::mines0, FreeSquare::mines1,
	FreeSquare::mines2, FreeSquare::mines3,
	FreeSquare::mines4, FreeSquare::mines5,
	FreeSquare::mines6, FreeSquare::mines7,
	FreeSquare::mines8, FreeSquare::incorrectlyFlagged;
// realized i should've used an array but its too late now and this works so :shrug:

FreeSquare::FreeSquare()
{
	// cant be bothered defining something i wont use
}

FreeSquare::FreeSquare(int minesNearby, sf::Vector2i position, int index) : minesNearby(minesNearby), position(position)
{
	if (!isTexturesLoaded)
	{
		mines0.loadFromFile("../Images/squares/0.png");
		mines1.loadFromFile("../Images/squares/1.png");
		mines2.loadFromFile("../Images/squares/2.png");
		mines3.loadFromFile("../Images/squares/3.png");
		mines4.loadFromFile("../Images/squares/4.png");
		mines5.loadFromFile("../Images/squares/5.png");
		mines6.loadFromFile("../Images/squares/6.png");
		mines7.loadFromFile("../Images/squares/7.png");
		mines8.loadFromFile("../Images/squares/8.png");
		incorrectlyFlagged.loadFromFile("../Images/squares/incorrectlyFlagged.png");
		isTexturesLoaded = true;
		std::cout << "FreeSquare textures loaded" << std::endl;
	}

	// Set texture for the sprite
	getSprite().setTexture(getNormalTexture());
	setIndex(index);
	this->getSprite().setPosition(position.x, position.y);
}

FreeSquare::~FreeSquare()
{
}

void FreeSquare::dig(Board *board)
{
	setDug(true);
	switch (minesNearby)
	{
	case 0:
		board->digNearbySquares(getIndex());
		getSprite().setTexture(mines0);
		break;
	case 1:
		getSprite().setTexture(mines1);
		break;
	case 2:
		getSprite().setTexture(mines2);
		break;
	case 3:
		getSprite().setTexture(mines3);
		break;
	case 4:
		getSprite().setTexture(mines4);
		break;
	case 5:
		getSprite().setTexture(mines5);
		break;
	case 6:
		getSprite().setTexture(mines6);
		break;
	case 7:
		getSprite().setTexture(mines7);
		break;
	case 8:
		getSprite().setTexture(mines8);
		break;
	default:
		// Wont happen but just in case
		getSprite().setTexture(getNormalTexture());
		break;
	}
}

bool FreeSquare::isCorrect() const
{
	return getDug(); // win condition is actually: are all free squares dug?
}

void FreeSquare::revealSquare()
{
	if (getFlagged())
	{
		getSprite().setTexture(incorrectlyFlagged);
	}
}

int FreeSquare::getMinesNearby() const
{
	return minesNearby;
}