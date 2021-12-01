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


	std::vector<sf::RectangleShape>rectangles;
	std::vector<Coin>coins;

};

