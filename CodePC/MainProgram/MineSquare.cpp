#include "MineSquare.h"
#include "Board.h"

bool MineSquare::isTexturesLoaded = false;
sf::Texture MineSquare::mine, MineSquare::mineExploded;


MineSquare::MineSquare()
{
	//cant be bothered defining something i wont use
}

MineSquare::MineSquare(sf::Vector2i position, int index) :  position(position)
{
	if (!isTexturesLoaded) 
	{
		mine.loadFromFile("../Images/squares/mine.png");  
		mineExploded.loadFromFile("../Images/squares/mineExploded.png");
		isTexturesLoaded = true;
		std::cout << "MineSquare textures loaded" << std::endl;
	}

	// Set texture for the sprite
	getSprite().setTexture(getNormalTexture());
	setIndex(index);
	this->getSprite().setPosition(position.x, position.y);
}

MineSquare::~MineSquare()
{
}

void MineSquare::dig(Board* board)
{
	explode(board);
	getSprite().setTexture(mineExploded);
	setDug(true);
}

bool MineSquare::isCorrect() const
{
	return !getDug();
	// Win condition is actually: are all free squares dug? 
	// This means that you don't actually have to flag the mines if you don't want to
}


void MineSquare::revealSquare()
{
	if (!getFlagged())
	{
		getSprite().setTexture(mine);
	}
}

void MineSquare::explode(Board* board)
{
	board->explodeBoard();
}