#include "Square.h"
bool Square::isTexturesLoaded = false;
sf::Texture Square::flaggedTexture, Square::normal;
Square::Square()
{
    if (!isTexturesLoaded)
    {
        flaggedTexture.loadFromFile("../Images/squares/flag.png");
        normal.loadFromFile("../Images/squares/normal.png");
        std::cout << "Square textures loaded" << std::endl;
        isTexturesLoaded = true;
    }
}
Square::~Square()
{
}
void Square::dig(Board* board)
{
    dug = true;
}
int Square::getIndex() const
{
    return index;
}
sf::Texture& Square::getFlaggedTexture() const
{
    return flaggedTexture;
}
sf::Texture& Square::getNormalTexture() const
{
    return normal;
}
sf::Sprite& Square::getSprite()
{
    return sprite;
}
bool Square::flag()
{
    if (!getDug() && getFlagged())
    {
        sprite.setTexture(getNormalTexture());
        setFlagged(false);
    }
    else if (!getDug() && !getFlagged())
    {
        sprite.setTexture(getFlaggedTexture());
        setFlagged(true);
    }
    return getFlagged();
}
void Square::revealSquare()
{
}
void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite);
}
bool Square::getDug() const
{
    return dug;
}
bool Square::getFlagged() const
{
    return flagged;
}
void Square::setIndex(int index) 
{
    this->index = index;
}
void Square::setDug(bool value)
{
    dug = value;
}
void Square::setFlagged(bool value)
{
    flagged = value;
}