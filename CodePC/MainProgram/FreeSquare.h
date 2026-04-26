#pragma once
#include "Square.h"
class FreeSquare : public Square
{
public:
	FreeSquare();
	FreeSquare(int minesNearby, sf::Vector2i position, int index);
	~FreeSquare();
	//override
	void dig(Board* board) override;
	bool isCorrect() const override;
	void revealSquare() override;
	//getters
	int getMinesNearby() const;
private:
	int minesNearby = 0;
	sf::Vector2i position;
	//texture bs
	static sf::Texture mines0, mines1, mines2, mines3, mines4, mines5, mines6, mines7, mines8, incorrectlyFlagged;
	static bool isTexturesLoaded;
};
