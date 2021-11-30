#include "Coin.h"

Coin::Coin()
{
	picked = false;
	shape.setRadius(10);
	shape.setFillColor(sf::Color(100, 250, 50));
	shape.setOutlineThickness(5);
	shape.setOutlineColor(sf::Color(250, 150, 100));
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

