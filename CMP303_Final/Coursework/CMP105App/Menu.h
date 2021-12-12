#pragma once
#include"Framework\GameObject.h"
#include"Framework\GameState.h"
#include<iostream>
#include <SFML/Network.hpp>
#include "GraphicsTools.h"
class Menu : public GameObject
{
public:

	Menu(sf::RenderWindow* hwnd, GameState* gs, Input* in, sf::TcpSocket *sock);
	~Menu();
	void Init();
	void handleInput(sf::Event* Ev);
	void update(float dt);
	void render();
	void beginDraw();
	void endDraw();
	void reset();
	void nameEnterFunction(sf::Event* Event_);
	void IpEnterFunction(sf::Event* Event_);
	void Name_Sending_TCP();
	sf::IpAddress IpTransmissionToLevel();
	std::string NameTransmissionToLevel();
private:			//----------------DIFFERENT TEXTS TO DISPLAY IN THE MENU
	bool connect_attempt = false;
	sf::RenderWindow* window;

	sf::Font font;

	sf::Text gameName;
	sf::Text IPaddressEnter;
	std::string IpEnter;
	sf::Text IpEnterDisplay;
	sf::Text nameEnterOrder;
	sf::Text nameEnterText;
	sf::Text joinLobbyDisplay;

	bool renderJoinGame=false;

	std::string players;
	std::string nameEnter;

	Input* input;
	GameState* gameState;
	sf::IpAddress ipAdress_server;
	sf::TcpSocket* Tcp;

	GraphicsTools Graphics;
	std::string IPorName;

	enum typeVariables
	{
		sendName = 1,
	};
};