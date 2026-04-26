#pragma once
#include "FreeSquare.h"
#include "MineSquare.h"
#include "Square.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include "Timer.h"
class Board : public sf::Drawable
{
public:
	Board();
	Board(int sizeX, int sizeY, int mines);
	~Board();
	//update/draw
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateBoard(sf::Vector2i& mousePosition);
	//board management
	void resetBoard();
	void explodeBoard(); //loose
	//square management
	void digNearbySquares(int index);
	//getters
	sf::Vector2i getBoardSize() const;
	sf::Vector2i getPosition() const;
	int getSquareSize() const;
	bool getMinesPlaced() const;
	//gamestate
	enum GameState { normal, clicking, victory, loss };
	GameState getCurrentGameState() const;
private:
	//functions
	//board management
	bool checkBoard(); //win?
	void newBoard(sf::Vector2i startposition); //startsquare should have 0 mines
	//index/vector2i math
	sf::Vector2i indexToVector(int index) const;
	int vectorToIndex(sf::Vector2i coords) const;
	std::vector<int>  getSurroundingSquareIndices(int index) const;
	//square management
	void digAt(int index);
	void flagAt(int index);
	//member variables
	//board info
	sf::Vector2i boardPosition = sf::Vector2i(0,64);
	Square** squares = nullptr;	//30 * 16 = 480 
	int boardSizeX = 30;		//30
	int boardSizeY = 16;		//16
	int nrOfMines = 99;			//99 // 99/480=0.20625 mine-density = 20.625 %
	//texture size
	int squareSize = 32;
	//
	int placedFlags = 0;
	bool minesPlaced = false;
	//input management
	bool wasLeftButtonPressed = false;
	bool wasRightButtonPressed = false;
	//gamestate
	GameState currentState;
	std::shared_ptr<NumberDisplay> minesLeftToFlag;
	std::shared_ptr<Timer> timer;
};
