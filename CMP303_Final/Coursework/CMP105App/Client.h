#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string>
#include <sstream>      // std::stringstream
#include <iostream>
#include <stdlib.h>
#include "Player.h"
#include "GraphicsTools.h"
#include "Framework/Collision.h"
#include <queue>
class Client
{
public:
	Client(sf::IpAddress& ip, unsigned short& port, Player& p, std::string& name,sf::TcpSocket*sock,sf::RenderWindow*window);			//Different variables passed from Level.
	~Client();
	void HandleInput(sf::Event* Ev,Input* input, Player* p);		//Handle Input for inputs 
	void Update(Input* input,sf::Event * Ev, Player* p, float dt);
	void Render();
	void disconnect(Player* p, Input* input);		//Disconnect once esc is pressed
	void Setup(Player* p);			

	void sendMessageTCP(Player* p);		//------------------------------------------TCP FUNCTIONS
	void TCPReceive();
	void ID_And_Positions_Getter();
	void textSetup(sf::RenderWindow* window);

	void UDP_sendPosition(Player* p, Input* input, float dt);		//------------------------------------------UDP FUNCTIONS
	void UDPReceive(Player* p);
	void interpolateEnemyPos(Player* Player, float dt);
	void CheckCollision(Player* p);

	sf::Vector2f getClientPos(int idx) {			//Get client position at a certain index
		return enemies.at(idx).getPosition();
	}


	void askSetup();
	void coinPosGetter();
	bool getConnectedStatus();

	Player getLastAddedP() { return enemies.back(); }
	bool someoneJoined = false;
	sf::Vector2f next_pos_pass_to_level;

protected:
	std::string name;
	std::string userText;
	sf::Font font;

	sf::TcpSocket* socket;
	sf::UdpSocket udp_socket;
	std::vector<sf::Text>chat;
	sf::IpAddress Ip_serverAddress;

	GraphicsTools Tools;

	sf::Text drawText;
	sf::Text timerStart;
	sf::Text waitForPlayers;
	sf::Clock clock;
	sf::Clock clockGameStart;
	sf::Time timeGameStart;
	sf::RenderWindow* window_;
	sf::Vector2f final_interp_pos;

	unsigned short udp_port;

	int id_getter;
	bool connected_;
	bool open_chat;		//Bool for knowing if the chat is open
	bool chat_empty_on_open;	//Bool for properly switch vars
	bool is_chat_open;
	bool render_preStart = true;
	bool canMove = false;
	bool renderGameStartedElements = false;
	float lerpAlpha;

	sf::Vector2f coinPos[30];			//How many coins to generate
	enum dataInfo				//Enum to avoid putting only numbers in the different packet types
	{
		askForSetup = 19,
		sendPlayerPos = 3,
		gameTimeReceive = 2,
		receiveEnemyPos = 7,
		coinHasBeenPicked = 9,
		sendDisconnection = 6,
		IdReceived = 1,
		startGameType = 5,
		chatReceived = 8,
		coinPositions = 2
	};

	Player Player1;
	//Player Player2;
	std::vector<Player>enemies;
	float gameTime;
	float speed;
};