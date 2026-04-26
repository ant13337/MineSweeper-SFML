#pragma once
#include "Board.h"
#include <SFML/Graphics.hpp>
class Face : public sf::Drawable
{
public:
	Face();
	~Face();
	void update(sf::Vector2i mousePosition);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void loadTextures();
	Board* board;
	int faceSize = 64;
	sf::Vector2i position;
	bool wasLeftButtonPressed = false;
	//texture bs
	static bool isTexturesLoaded;
	sf::Texture smile, suprised, sunglasses, dead;
	//sprite
	sf::Sprite sprite;
};
