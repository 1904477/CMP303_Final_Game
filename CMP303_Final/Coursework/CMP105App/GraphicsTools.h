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
	void preGameElementsRender(sf::RenderWindow* hwnd);
	void inLevelElements(sf::RenderWindow* hwnd);
	void postGameElementsRender(sf::RenderWindow* hwnd , float scoreP1, float scoreP2);

	//void renderGameElements(sf::RenderWindow* hwnd,bool renderElementsStartGame);

	std::vector<sf::RectangleShape>rectangles;
	std::vector<sf::RectangleShape>renderPlay;



	std::vector<sf::RectangleShape>InGameBox;
	std::vector<sf::Text>PreGameText;
	std::vector<sf::Text>PostGameText;
	std::vector<Coin>coins;
	sf::Font font;

	sf::Text gameStartTimerText;

	sf::Text player1Score;
	sf::Text player2Score;

};

