#include "Face.h"
bool Face::isTexturesLoaded = false;
Face::Face()
{
	board = new Board;
	position.x = (board->getBoardSize().x * board->getSquareSize() / 2) - faceSize/2;
	position.y = 0;
	loadTextures();
	sprite.setTexture(smile);
	this->sprite.setPosition(position.x, position.y);
}

Face::~Face()
{
	std::cout << "~Face()" << std::endl;
	if (board!=nullptr)
	{
		std::cout << "\tFace::~board()" << std::endl;
		delete board;
	}
}

void Face::update(sf::Vector2i mousePosition)
{
	// update board
	board->updateBoard(mousePosition);
	Board::GameState currentstate = board->getCurrentGameState();
	switch (currentstate)
	{
	case Board::normal:
		sprite.setTexture(smile);
		break;
	case Board::clicking:
		sprite.setTexture(suprised);
		break;
	case Board::victory:
		sprite.setTexture(sunglasses);
		break;
	case Board::loss:
		sprite.setTexture(dead);
		break;
	default:
		break;
	}
	bool isLeftButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if (sprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && isLeftButtonPressed && !wasLeftButtonPressed)
	{
		if (board->getMinesPlaced())
		{
			std::cout << "Resetting Board!" << std::endl;
			board->resetBoard();
		}
	}
	wasLeftButtonPressed = isLeftButtonPressed;
}

void Face::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*board);
	target.draw(this->sprite);
}

void Face::loadTextures()
{
	if (!isTexturesLoaded)
	{
		smile.loadFromFile("../Images/faces/smile.png");
		suprised.loadFromFile("../Images/faces/suprised.png");
		sunglasses.loadFromFile("../Images/faces/sunglasses.png");
		dead.loadFromFile("../Images/faces/dead.png");
		std::cout << "Face textures loaded" << std::endl;
	}
}
