#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class NumberDisplay : public sf::Drawable
{
public:
	NumberDisplay();
	NumberDisplay(sf::Vector2i position);
	virtual ~NumberDisplay();
	int getNumberToDisplay() const;
	void setNumberToDisplay(int numberToDisplay);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setPosition(sf::Vector2i position);
private:
	void loadTextures();
	void updateTexture();
	void changeTexture(sf::Sprite& digitToChange, int digit);
	int numberToDisplay;
	static sf::Texture num0, num1, num2, num3, num4, num5, num6, num7, num8, num9, off;
	sf::Vector2i position;
	sf::Sprite digit1sprite;
	sf::Sprite digit2sprite;
	sf::Sprite digit3sprite;
	int textureWidth = 64;
	static bool isTexturesLoaded;
};