#include "GraphicsTools.h"

void GraphicsTools::setup(sf::RenderWindow* hwnd)
{
	rectangles.push_back(sf::RectangleShape());
	rectangles.back().setSize(sf::Vector2f(400, 30));
	rectangles.back().setPosition(0, hwnd->getSize().y / 1.8 + 50); 
	rectangles.back().setFillColor(sf::Color::Black);
	rectangles.back().setOutlineColor(sf::Color::Cyan);
	rectangles.back().setOutlineThickness(3);

	rectangles.push_back(sf::RectangleShape());
	rectangles.back().setSize(sf::Vector2f(400, 30));
	rectangles.back().setPosition(0, hwnd->getSize().y / 3 + 50);
	rectangles.back().setFillColor(sf::Color::Black);
	rectangles.back().setOutlineColor(sf::Color::Cyan);
	rectangles.back().setOutlineThickness(3);
}

void GraphicsTools::render(sf::RenderWindow* hwnd)
{
	for (int i = 0; i < rectangles.size(); i++)
	{
		hwnd->draw(rectangles[i]);
	}
}

void GraphicsTools::coinGenerator(sf::Vector2f coinPos_[10])
{
	for (int i = 0; i < 10; i++)
	{
		Coin coin;
		coin.setPosition(coinPos_->x,coinPos_->y);
		coin.Update();
		coins.push_back(coin);
		
	}
}

void GraphicsTools::renderCoin(sf::RenderWindow* hwnd)
{
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i].Render(hwnd);
	}

}
