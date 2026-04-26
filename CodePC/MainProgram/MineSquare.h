#pragma once
#include "Square.h"
class MineSquare : public Square
{
public:
	MineSquare();
	MineSquare(sf::Vector2i position, int index);
	~MineSquare();
	//override
	void dig(Board* board) override;
	bool isCorrect() const override;
	void revealSquare() override;	//if loose -> reveal if not yet flagged mine
	//functions
	void explode(Board* board);			//loose
private:
	sf::Vector2i position;
	//texture bs
	static sf::Texture mine, mineExploded;
	static bool isTexturesLoaded;
};