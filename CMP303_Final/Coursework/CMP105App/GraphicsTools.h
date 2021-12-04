#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/GameObject.h"
#include "Coin.h"
class GraphicsTools
{

public: 


	void setup(sf::RenderWindow* hwnd);
	void render(sf::RenderWindow* hwnd);
	void coinGenerator(sf::Vector2f coinPos_[10]);
	void renderCoin(sf::RenderWindow* hwnd);
	void renderPlayButton(sf::RenderWindow* hwnd);
	//void renderGameElements(sf::RenderWindow* hwnd,bool renderElementsStartGame);

	std::vector<sf::RectangleShape>rectangles;
	std::vector<sf::RectangleShape>renderPlay;
	std::vector<Coin>coins;
	sf::Font font;

	sf::Text gameStartTimerText;

};

