#pragma once
#include"Framework\GameObject.h"
#include"Framework\GameState.h"
#include<iostream>
#include <SFML/Network.hpp>
#include "GraphicsTools.h"
class Menu : public GameObject
{
public:

	Menu(sf::RenderWindow* hwnd, GameState* gs, Input* in);
	~Menu();
	void Init();
	void handleInput(sf::Event* Ev);
	void update(float dt);
	void render();
	void beginDraw();
	void endDraw();
	void reset();

	sf::IpAddress IpTransmissionToLevel();
	std::string NameTransmissionToLevel();


	bool connect_attempt = false;
	sf::RenderWindow* window;

	sf::Font font;

	sf::Text gameName;
	sf::Text IPaddressEnter;
	std::string IpEnter;
	sf::Text IpEnterDisplay;
	sf::Text nameEnterOrder;
	sf::Text nameEnterText;

	std::string players;
	std::string nameEnter;

	Input* input;
	GameState* gameState;
	sf::IpAddress ipAdress_server;


	GraphicsTools Graphics;
	std::string IPorName;
	
};