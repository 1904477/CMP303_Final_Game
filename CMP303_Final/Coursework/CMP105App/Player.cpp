#include "Player.h"

Player::Player()
{
}

void Player::Init()
{
	shape.setRadius(20);		//Set size of sphere 
	shape.setFillColor(sf::Color(colorGen()));
	shape.setOutlineThickness(10);			
	shape.setOutlineColor(sf::Color(colorGen()));
	setCollisionBox(0, 0, 40, 40);			//Collision box size
	shape.setPosition(Player_start_pos);
	srand(time(NULL));
}

void Player::HandleInput(Input*input,float dt)
{

}

sf::Color Player::colorGen()			//Seeded random enemy color 
{
	int R =  (rand() % 255);
	int G =  (rand() % 255);
	int B =  (rand() % 255);
	return sf::Color(R, G, B);
}

void Player::Update()
{
	shape.setPosition(getPosition().x+4, getPosition().y+4);		//Position of the shape is always updated.
}

void Player::Render(sf::RenderWindow* window)
{
	window->draw(shape);			//Draw shape
}

