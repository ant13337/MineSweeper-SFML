#include "Board.h"
#include "ElementPicker.h"

Board::Board()
{
	int x = 0;
	int y = 0;
	squares = new Square * [boardSizeX * boardSizeY] {nullptr};
	for (int i = 0; i < boardSizeX * boardSizeY; i++)
	{
		squares[i] = new FreeSquare(0, sf::Vector2i(x, y) + boardPosition, i);	//create temporary board

		x += squareSize;
		if (i % boardSizeX == boardSizeX - 1)
		{
			x = 0;
			y += squareSize;
		}
	}
	currentState = GameState::normal;
	srand((int)time(0));//seed set by time
	minesLeftToFlag = std::make_shared<NumberDisplay>(sf::Vector2i(0, 0));
	timer = std::make_shared<Timer>(sf::Vector2i(boardPosition.x - 64*3 + boardSizeX * squareSize, 0)); // timer
}

Board::Board(int sizeX, int sizeY, int nrOfMines) : boardSizeX(sizeX), boardSizeY(sizeY), nrOfMines(nrOfMines)
{
	int x = 0;
	int y = 0;
 	squares = new Square * [boardSizeX * boardSizeY] {nullptr};
	for (int i = 0; i < boardSizeX * boardSizeY; i++)
	{
		squares[i] = new FreeSquare(0,sf::Vector2i(x,y) + boardPosition,i);	//create temporary board

		x += squareSize;
		if (i % boardSizeX == boardSizeX - 1)
		{
			x = 0;
			y += squareSize;
		}
	}
	currentState = GameState::normal;
	srand((int)time(0));//seed set by time
	minesLeftToFlag = std::make_shared<NumberDisplay>(sf::Vector2i(0, 0));
	timer = std::make_shared<Timer>(sf::Vector2i(boardPosition.x - 64*3 + boardSizeX * squareSize, 0)); // timer 
}

Board::~Board()
{
	std::cout << "~Board()" << std::endl;
	if (squares != nullptr) //monkey brain code to not delete a nullptr but it works :shrug:, kinda ugly tho
	{
		std::cout << "\tBoard::~squares()" << std::endl;
		for (int i = 0; i < boardSizeX * boardSizeY; i++)
		{
			if (squares[i] != nullptr) //not sure if i need this one but better safe than sorry ig, probably dont tho idk
			{
				delete squares[i];
			}
		}
		delete[] squares;
	}
}

void Board::digAt(int index)
{
	if (minesPlaced)
	{
		if (!squares[index]->getDug() && !squares[index]->getFlagged()) // if allowed to dig square
		{
			squares[index]->dig(this); //dig it
		}
		else if (squares[index]->getDug()) //if its already dug
		{
			//check the sorrounding squares 
			std::vector<int> surroundingSquareIndices = getSurroundingSquareIndices(index);
			int flaggedNearbySquares = 0;
			for (int index2 : surroundingSquareIndices)
			{
				//count flagged nearby squares
				if (squares[index2]->getFlagged())
				{
					flaggedNearbySquares++;
				}
			}
			//if the mines nearby == the amount of flagged squares sorrounding the square
			FreeSquare* freeSquarePtr = dynamic_cast<FreeSquare*>(squares[index]);
			if (flaggedNearbySquares == freeSquarePtr->getMinesNearby())
			{
				digNearbySquares(index); //dig the nearby squares
			}
		}
	}
	else
	{
		newBoard(indexToVector(index));
	}
}

void Board::flagAt(int index)
{
	if (!squares[index]->getDug())
	{
		if (squares[index]->flag())
		{
			placedFlags++; //if flag() returns true that means the square was flagged
		}
		else
		{
			placedFlags--; //if flag() returns flase that means the flag was removed from tha square
		}

		minesLeftToFlag->setNumberToDisplay(nrOfMines-placedFlags);
	}
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < boardSizeX * boardSizeY; i++)
	{
		target.draw(*squares[i]);
	}

	target.draw(*timer);
	target.draw(*minesLeftToFlag);
}

void Board::updateBoard(sf::Vector2i& mousePosition )

{
	minesLeftToFlag->setNumberToDisplay(nrOfMines - placedFlags);
	timer->updateTimer();

	// INPUT LOGIC

	//if inside board
	if(currentState != victory && currentState != loss)
	{
		if (boardPosition.x <= mousePosition.x && mousePosition.x <= boardPosition.x + boardSizeX * squareSize &&
			boardPosition.y <= mousePosition.y && mousePosition.y <= boardPosition.y + boardSizeY * squareSize)
		{
			//DIG
			bool isLeftButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
			// Check for a change in the state of the left mouse button
			if (isLeftButtonPressed && !wasLeftButtonPressed) {
				currentState = clicking;
			}
			else if (!isLeftButtonPressed && wasLeftButtonPressed) 
			{
				currentState = normal;
				digAt(vectorToIndex((mousePosition - boardPosition) / squareSize));
				checkBoard();
			}
			// Update the previous state of the left mouse button
			wasLeftButtonPressed = isLeftButtonPressed;


			// FLAG
			// Get the current state of the right mouse button
			bool isRightButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
			if (!isRightButtonPressed && wasRightButtonPressed) 
			{
				flagAt(vectorToIndex((mousePosition - boardPosition) / squareSize));
				checkBoard();
			}
			// Update the previous state of the right mouse button
			wasRightButtonPressed = isRightButtonPressed;
		}
		else
		{
			wasLeftButtonPressed = false;
			currentState = normal;
		}
	}
}

void Board::resetBoard()
{
	//delete the previous squares

	if (squares != nullptr) //monkey brain code to not delete a nullptr but it works :shrug:, kinda ugly tho
	{
		for (int i = 0; i < boardSizeX * boardSizeY; i++)
		{
			if (squares[i] != nullptr) //not sure if i need this one but better safe than sorry ig, probably dont tho idk
			{
				delete squares[i];
			}
		}
		delete[] squares;
	}
	// create new squares, they are all FreesSquares because startposition is need before placing mines
	int x = 0;
	int y = 0;
	squares = new Square * [boardSizeX * boardSizeY] {nullptr};
	for (int i = 0; i < boardSizeX * boardSizeY; i++)
	{
		squares[i] = new FreeSquare(0, sf::Vector2i(x, y) + boardPosition, i);	//create temporary board
		x += squareSize;
		if (i % boardSizeX == boardSizeX - 1)
		{
			x = 0;
			y += squareSize;
		}
	}
	currentState = GameState::normal;
	minesPlaced = false;
	timer->stopTimer();
	timer->resetTimer();
	placedFlags = 0;
}

void Board::explodeBoard()
{
	std::cout << "gg L" << std::endl;
	currentState = loss;
	for (int i = 0; i < boardSizeX * boardSizeY; i++)
	{
		squares[i]->revealSquare();
	}
	timer->stopTimer();
}

Board::GameState Board::getCurrentGameState() const
{
	return currentState;
}

bool Board::checkBoard() //win???
{
	bool out = true;
	//check all squares
	for (int i = 0; i < boardSizeX * boardSizeY; i++)
	{
		if (!squares[i]->isCorrect()) // if any square not correct
		{
			out = false; //if one of them is incorrect >> game continues
			break;
		}
	}
	if (out) //if all of them passed the check >> win
	{
		std::cout << "gg W" << std::endl;
		currentState = victory;
		timer->stopTimer( std::string(
			"BoardSize: " + std::to_string(boardSizeX) + "x" + std::to_string(boardSizeY) + 
			" Mines: " + std::to_string(nrOfMines) +
			" Time:"
		)); //Save some boarddata along with the time in times.txt
	}
	
	return out;
}

void Board::newBoard(sf::Vector2i startposition)
{
	// Board starts as a Board filled with FreeSquares
	int nrOfMinesPlaced = 0;
	placedFlags = 0;

	std::vector<int> forbiddenSquares = getSurroundingSquareIndices(vectorToIndex(startposition));
	forbiddenSquares.push_back(vectorToIndex(startposition));

	std::vector<int> allIndexesVector;
	// Populate allIndexesVector with all valid indexes in the squares array
	for (int i = 0; i < boardSizeX * boardSizeY; i++) 
	{
		allIndexesVector.push_back(i);
	}

	// Lamda function for populating array
	auto placeMine = [&]() 
	{
		// Make an element picker with int for T
		ElementPicker<int> indexPicker(allIndexesVector, forbiddenSquares);
		// Pick a random int in the first vector except if its in the other vector
		int mineIndex = indexPicker.pickRandomElement(); 

		delete squares[mineIndex]; // delete what was there previously
		squares[mineIndex] = new MineSquare(indexToVector(mineIndex) * squareSize + boardPosition, mineIndex);// replace it with a new mine
		nrOfMinesPlaced++;
		forbiddenSquares.push_back(mineIndex); // make sure we don't place a mine in the same spot
	};
	
	for (int i = 0; i < nrOfMines; i++)
	{
		try 
		{
			placeMine();
		}
		catch (const std::invalid_argument & e)	// if there are too many mines to fit on the board
		{
			std::cout << "Error: " << e.what() << std::endl;
			break;
		}
	}
	minesPlaced = true;

	//Fill the rest of the board with FreeSquares
	for (int i = 0; i < boardSizeX * boardSizeY; i++)
	{
		MineSquare* mineSquarePtr = dynamic_cast<MineSquare *>(squares[i]); //get square
		if (mineSquarePtr == nullptr) //if not a mine
		{
			int minesCount = 0; 
			std::vector<int> surroundingSquareIndices = getSurroundingSquareIndices(i); //get surrounding squares
			for (int index : surroundingSquareIndices)//count the mines
			{
				mineSquarePtr = dynamic_cast<MineSquare*>(squares[index]);
				if (mineSquarePtr != nullptr)//if a mine
				{
					minesCount++;
				}
			}
			delete squares[i]; //this is probably the last line im gonna write for this project, im tired
			squares[i] = new FreeSquare(minesCount, indexToVector(i) * squareSize + boardPosition, i); //new square
		}
	}
	
	//start the game
	digAt(vectorToIndex(startposition));
	timer->startTimer(); // timer 
}

void Board::digNearbySquares(int index)
{
	std::vector<int> surroundingSquareIndices = getSurroundingSquareIndices(index); //get surrounding squares
	for (int index2 : surroundingSquareIndices)
	{
		if (!squares[index2]->getFlagged() && !squares[index2]->getDug()) //if not flagged or dug
		{
			squares[index2]->dig(this);
		}
	}
}

sf::Vector2i Board::getBoardSize() const
{
	return sf::Vector2i(boardSizeX,boardSizeY);
}

sf::Vector2i Board::getPosition() const
{
	return boardPosition;
}

int Board::getSquareSize() const
{
	return squareSize;
}

bool Board::getMinesPlaced() const
{
	return minesPlaced;
}

sf::Vector2i Board::indexToVector(int index) const
{
	int x = index % boardSizeX;
	int y = index / boardSizeX;
	return sf::Vector2i(x, y);
}

int Board::vectorToIndex(sf::Vector2i coords) const
{
	int x = coords.x;
	int y = coords.y;
	int index = y * boardSizeX + x;
	return index;
}

std::vector<int> Board::getSurroundingSquareIndices(int index) const
{
	std::vector<int> surroundingSquareIndices;
	sf::Vector2i center = indexToVector(index);

	// Iterate through the 3x3 grid around the center
	for (int y = center.y - 1; y <= center.y + 1; ++y) {
		for (int x = center.x - 1; x <= center.x + 1; ++x) {
			// Check if the coordinates are within the board
			if (x >= 0 && x < boardSizeX && y >= 0 && y < boardSizeY) {
				// Calculate the index and add it to the vector
				int i = y * boardSizeX + x;
				surroundingSquareIndices.push_back(i);
			}
		}
	}

	return surroundingSquareIndices;
}