#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
//#include "Board.h"
class Board;	// this include dependency thing took like 1-2 hour to fix and i was miserable during the whole thing
				// thanks chatgpt, 
				// if you're reading this then include this in the lectures please
				// it's just a couple lines of code 
					// just declare the class then include it in the .cpp file where you actually need access to its functions 
					// instead of including it in the .h file
class Square : public sf::Drawable
{
public:
	Square();
	virtual ~Square();
	//virtual functions
	virtual void dig(Board* board);
	virtual bool isCorrect() const = 0;
	virtual bool flag();
	virtual void revealSquare();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//getters
	bool getDug() const;
	bool getFlagged() const;
	int getIndex() const;

	sf::Texture& getFlaggedTexture() const;
	sf::Texture& getNormalTexture() const;
	sf::Sprite& getSprite();
	//setters
	void setDug(bool value);
	void setFlagged(bool value);
	void setIndex(int index);
private:
	bool dug = false;
	bool flagged = false;
	int index = 0;
	static sf::Texture flaggedTexture, normal;
	static bool isTexturesLoaded;
	sf::Sprite sprite;
};
