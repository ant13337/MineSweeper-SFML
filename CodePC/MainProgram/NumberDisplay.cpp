#include "NumberDisplay.h"
bool NumberDisplay::isTexturesLoaded = false;
sf::Texture NumberDisplay::num0, NumberDisplay::num1,
	NumberDisplay::num2, NumberDisplay::num3,
	NumberDisplay::num4, NumberDisplay::num5,
	NumberDisplay::num6, NumberDisplay::num7,
	NumberDisplay::num8, NumberDisplay::num9,
	NumberDisplay::off;
// I should've used an array of textures instead of 10 separate ones but it's too late now and this works fine so :shrug:

NumberDisplay::NumberDisplay()
{
	position = sf::Vector2i(0, 0);
	numberToDisplay = 0;
	loadTextures();
	setPosition(position);
	updateTexture();
}

NumberDisplay::NumberDisplay(sf::Vector2i position)
{
	this->position = position;
	numberToDisplay = 0;
	loadTextures();
	setPosition(position);
	updateTexture();
}

NumberDisplay::~NumberDisplay()
{
	std::cout << "~NumberDisplay()" << std::endl;
}

int NumberDisplay::getNumberToDisplay() const
{
	return numberToDisplay;
}

void NumberDisplay::setNumberToDisplay(int numberToDisplay)
{
	if (numberToDisplay > 1000)
	{
		numberToDisplay = 999;
	}
	else if (numberToDisplay < 0)
	{
		numberToDisplay = 0;
	}
	this->numberToDisplay = numberToDisplay;
	updateTexture();
}

void NumberDisplay::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(this->digit1sprite);
	target.draw(this->digit2sprite);
	target.draw(this->digit3sprite);
}

void NumberDisplay::setPosition(sf::Vector2i position)
{
	this->position = position;
	this->digit1sprite.setPosition(position.x, position.y);
	this->digit2sprite.setPosition(position.x + textureWidth, position.y);
	this->digit3sprite.setPosition(position.x + textureWidth * 2, position.y);
}

void NumberDisplay::loadTextures()
{
	if (!isTexturesLoaded)
	{
		num0.loadFromFile("../Images/numbers/0.png");
		num1.loadFromFile("../Images/numbers/1.png");
		num2.loadFromFile("../Images/numbers/2.png");
		num3.loadFromFile("../Images/numbers/3.png");
		num4.loadFromFile("../Images/numbers/4.png");
		num5.loadFromFile("../Images/numbers/5.png");
		num6.loadFromFile("../Images/numbers/6.png");
		num7.loadFromFile("../Images/numbers/7.png");
		num8.loadFromFile("../Images/numbers/8.png");
		num9.loadFromFile("../Images/numbers/9.png");
		off.loadFromFile("../Images/numbers/off.png");
		isTexturesLoaded = true;
		std::cout << "NumberDisplay textures loaded" << std::endl;
	}
}

void NumberDisplay::updateTexture()
{
	int digit1 = numberToDisplay / 100;
	int digit2 = (numberToDisplay % 100) / 10;
	int digit3 = numberToDisplay % 10;
	changeTexture(digit1sprite, digit1);
	changeTexture(digit2sprite, digit2);
	changeTexture(digit3sprite, digit3);
}

void NumberDisplay::changeTexture(sf::Sprite &digitToChange, int digit)
{
	// Check if the digit is within the valid range
	if (digit >= 0 && digit <= 9)
	{
		// Array of static textures
		static sf::Texture textures[] = {num0, num1, num2, num3, num4, num5, num6, num7, num8, num9};

		// Set the texture for the sprite
		digitToChange.setTexture(textures[digit]);
	}
	else
	{
		// Set default texture (off) if the digit is out of range
		digitToChange.setTexture(off);
	}
}