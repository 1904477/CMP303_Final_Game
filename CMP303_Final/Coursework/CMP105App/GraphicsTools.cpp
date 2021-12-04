#include "GraphicsTools.h"

void GraphicsTools::setup(sf::RenderWindow* hwnd)
{
	font.loadFromFile("font/arial.ttf");

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

	renderPlay.push_back(sf::RectangleShape());
	renderPlay.back().setSize(sf::Vector2f(450, 30));
	renderPlay.back().setPosition(hwnd->getSize().x / 3.3 , hwnd->getSize().y / 1.2 );
	renderPlay.back().setFillColor(sf::Color::Black);
	renderPlay.back().setOutlineColor(sf::Color::Cyan);
	renderPlay.back().setOutlineThickness(3);

	//gameStartTimerText.setFont(font);
	//gameStartTimerText.setString("Game is starting in: ");
	//gameStartTimerText.setCharacterSize(50);
	//gameStartTimerText.setFillColor(sf::Color::White);
	//gameStartTimerText.setPosition(hwnd->getSize().x / 2.5, hwnd->getSize().y / 4);

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
		Coin coin;
		coin.setPosition(coinPos_->x,coinPos_->y);
		coin.Update();
		coins.push_back(coin);
}

void GraphicsTools::renderCoin(sf::RenderWindow* hwnd)
{
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i].Render(hwnd);
	}

}

void GraphicsTools::renderPlayButton(sf::RenderWindow* hwnd)
{
	for (int i = 0; i < renderPlay.size(); i++)
	{
		hwnd->draw(renderPlay[i]);
	}
}

//void GraphicsTools::renderGameElements(sf::RenderWindow* hwnd, bool renderElementsStartGame)
//{
//	if (renderElementsStartGame == true)
//	{
//		hwnd->draw(gameStartTimerText);
//	}
//}
