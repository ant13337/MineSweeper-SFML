#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Face.h"

class Game
{
private:
	static const int WIDTH = 960;//30*32
	static const int HEIGHT = 576;//64+16*32
private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;

	//declare objects
	Face* face;
	//
	
	void handleEvents();
	void update();
	void render();
public:
	Game();
	~Game();
	void run(); 
};
