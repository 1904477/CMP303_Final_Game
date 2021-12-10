#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include <string>
#include <iostream>
#include "Client.h"
#include "Player.h"
#include "Menu.h"
class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs,sf::TcpSocket *sock);
	~Level();
	void handleInput(float dt);
	void update(float dt,sf::Event*Ev);
	void clientInput(sf::Event* Ev);
	void render();
	void Init( Menu* menu_);
	bool get_connected() { return connected_succesfully; };
private:

	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager* audio;
	//Client client_;
	Player player_;
	std::vector<Player>enemies;

	bool connected_succesfully;
	Menu* menu;
	std::unique_ptr<Client> client_;

	unsigned short port;
	sf::IpAddress IP_ADDRESS;
	std::string name;
	sf::TcpSocket* Tcp;

};