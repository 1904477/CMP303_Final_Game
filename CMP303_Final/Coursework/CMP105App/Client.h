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
class Client
{
public:
	Client(sf::IpAddress& ip, unsigned short& port, Player& p,Player& enemy, std::string& name,sf::TcpSocket*sock);
	~Client();
	void HandleInput(sf::Event* Ev,Input* input, sf::RenderWindow* window, Player* p);
	void Update(Input* input,sf::Event * Ev, sf::RenderWindow* window, Player* p, Player* enemy, float dt);
	void Render( sf::RenderWindow* window);

	void sendMessageTCP(Player* p);
	void UDP_sendPosition(Player* p, Input* input, float dt);
	void TCPReceive();
	void Name_Sending_TCP(sf::TcpSocket* sock, std::string& name);
	void ID_And_Positions_Getter();
	void CheckCollision(Player* p);
	void textSetup(sf::RenderWindow* window);
	void disconnect(Player* p, Input* input, sf::RenderWindow* window);
	void UDPReceive(Player* p, Player* enemy);
	void Setup(Player* p, Player* enemy);
	bool getConnectedStatus();
	bool renderEnemy();
	void interpolateEnemyPos(Player* enemy, float dt);


	sf::Text drawText;
protected:
	std::string name;
	std::string userText;
	sf::Font font;
	sf::TcpSocket* socket;
	sf::UdpSocket udp_socket;
	sf::Clock clock;
	std::vector<sf::Text>chat;
	sf::IpAddress server_address;
	GraphicsTools Tools;

	const unsigned short udp_port=1111;

	int id_getter;
	bool connected_;
	bool render_enemy;
	float speed;
	bool open_chat;		//Bool for knowing if the chat is open
	bool chat_empty_on_open;	//Bool for properly switch vars
	bool is_chat_open;
	sf::Vector2f enemy_received = sf::Vector2f(0, 0);
	float enemy_interpolated_x;
	float enemy_interpolated_y;
	float Player_Starting_posX;
	float Player_Starting_posY;
	float Enemy_Starting_posX;
	float Enemy_Starting_posY;
	sf::Vector2f coinPos[10];

	bool canMove=false;
};

