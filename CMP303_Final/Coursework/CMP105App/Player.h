#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string>
#include <sstream>      // std::stringstream
#include <iostream>
#include <stdlib.h>
#include <time.h>       /* time */
#include "Framework/GameObject.h"
class Player : public GameObject
{
public:				//PLAYER CLASS AND VARIABLES, SOME NOT USED BUT CAN BE EASILY IMPLEMENTED.
	Player();
	void Init();
	void Update();
	void Render(sf::RenderWindow* window);
	void HandleInput(Input* input, float dt);
	//void setID(int id) { m_id = id; m_isReady = true; }
	//int getID() { return m_id; }
	void setDirection(sf::Vector2f direction) { m_direction = direction; }
	sf::Vector2f getDirection() { return m_direction; }
	sf::Color colorGen();
	sf::CircleShape shape;		//Players are circles for now, can be changed.

	sf::Vector2f m_direction;
	sf::Vector2f Player_start_pos;			//Determines the player starting positions

	sf::Vector2f next_pos = sf::Vector2f(0, 0);		//Determines the player updated positions (will be updated in client.cpp)

	float temp_time;				//Time at which received positions (updated in client.cpp);
	int score;
	int m_id;
	//bool arrived = false;
private:
	bool m_isReady;


};

