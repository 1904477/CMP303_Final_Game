#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string>
#include <sstream>      // std::stringstream
#include <iostream>
#include <stdlib.h>
#include "Framework/GameObject.h"
class Player : public GameObject
{
public:
	Player();
	void Init();
	void Update();
	void Render(sf::RenderWindow* window);
	void HandleInput(Input* input, float dt);
	//void setID(int id) { m_id = id; m_isReady = true; }
	//int getID() { return m_id; }
	void setDirection(sf::Vector2f direction) { m_direction = direction; }
	sf::Vector2f getDirection() { return m_direction; }
	sf::CircleShape shape;
	sf::Vector2f m_direction;
	sf::Vector2f Player_start_pos;
	sf::Vector2f next_pos = sf::Vector2f(0, 0);
	float temp_time;
	int score;
	int m_id;
	//bool arrived = false;
private:
	bool m_isReady;


};

