#pragma once
#include "Framework/GameObject.h"
class Coin : public GameObject
{
public:
	Coin();			//Pickable object class (coins)
	void Render(sf::RenderWindow* window);
	void Update();
	void setPicked(bool picky) { picked = picky;  };
	bool getPicked() { return picked; };
private:
	sf::CircleShape shape;
	bool picked;			//var to determine if the coin is picked.

};

