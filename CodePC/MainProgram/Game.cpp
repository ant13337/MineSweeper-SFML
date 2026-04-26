#include "Game.h"
#include <iostream>

//	----------------------------	GAME LOOP	----------------------------
// Initialize the Game object, setting up the window, time parameters, and calling object constructors
Game::Game()
	:window(sf::VideoMode(WIDTH, HEIGHT), "Minesweeper"),
	//"MineSweeper" is the name of the window, see top left corner when Game is running
	timePerFrame(sf::seconds(1.f / 60.f)),
	elapsedTimeSinceLastUpdate(sf::Time::Zero)
	//call object constructors
{
	face = new Face();
}
void Game::handleEvents()
{
	sf::Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->window.close();
		}
		//Can add other events here such as window resizing.
	}
}
// Update function, responsible for updating objects, and performing necessary calculations
void Game::update()
{
	elapsedTimeSinceLastUpdate += clock.restart();
	while (elapsedTimeSinceLastUpdate > timePerFrame)
	{
		elapsedTimeSinceLastUpdate -= timePerFrame;
		sf::Vector2i mouseScreenPosition = sf::Mouse::getPosition(window); 
		// update face		
		face->update(sf::Vector2i(mouseScreenPosition));
		// i dont want to send window as a parameter but i still need the mouseposition relative to the window
	}	
}
// Render function, clears the window, calls objects draw functions and displays the window
void Game::render()
{
	this->window.clear(sf::Color::White);
	//call the objects draw function
	window.draw(*face);
	this->window.display();
}
// Destructor, responsible for cleaning up dynamically allocated objects
Game::~Game()
{
	delete face;
}
//	----------------------------	NERD STUFFIES	----------------------------
//	You probably don't need to touch this stuff ever.
//	This is just where the game does the game loop, very uninteresting
void Game::run()
{
	while (this->window.isOpen())	//Game loop
	{
		handleEvents();
		update();					//Update
		render();					//Render
	}
}									//Call Destructor