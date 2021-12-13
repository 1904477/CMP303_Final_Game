#include "Coin.h"

Coin::Coin()
{
	picked = false;
	shape.setRadius(10);
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(5);
	shape.setOutlineColor(sf::Color::Magenta);
	setCollisionBox(0, 0, 20, 20);
}

void Coin::Render(sf::RenderWindow* window)
{
	if(picked==false)
	window->draw(shape);
}

void Coin::Update()
{
	shape.setPosition(getPosition());
}

