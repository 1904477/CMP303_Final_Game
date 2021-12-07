#include "Player.h"

Player::Player()
{
}

void Player::Init()
{
	shape.setRadius(20);
	// set the shape color to green
	shape.setFillColor(sf::Color(100, 250, 50));
	shape.setOutlineThickness(10);
	shape.setOutlineColor(sf::Color(250, 150, 100));
	setCollisionBox(0, 0, 40, 40);
	shape.setPosition(Player_start_pos);
}

void Player::HandleInput(Input*input,float dt)
{

}

void Player::Update()
{
	shape.setPosition(getPosition().x+4, getPosition().y+4);
}

void Player::Render(sf::RenderWindow* window)
{
	window->draw(shape);
}
