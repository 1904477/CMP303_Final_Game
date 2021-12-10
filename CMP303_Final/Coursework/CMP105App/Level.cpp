#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs,sf::TcpSocket *sock)
{
	window = hwnd;
	input = in;
	gameState = gs;
	connected_succesfully = false;
	Tcp = sock;
}

Level::~Level()
{
}

void Level::Init(Menu*menu_)
{
	port = 53000;
	menu=menu_;
	name = menu->NameTransmissionToLevel();
	//std::cout << "Enter the ip address you wanna connect to: \n";
	IP_ADDRESS = menu->IpTransmissionToLevel();
	client_ = std::make_unique<Client>(IP_ADDRESS, port, player_, name, Tcp, window);
	connected_succesfully = client_->getConnectedStatus();

	if (connected_succesfully == true)
	{
		player_.Init();
	}

	else if(connected_succesfully == false)
	{
		menu_->Init();
		gameState->setCurrentState(State::MENU);
	}

}

// handle user input
void Level::handleInput(float dt)
{
	if (connected_succesfully == true)
	{
		player_.HandleInput(input, dt);
	}
}

// Update game objects
void Level::update(float dt, sf::Event* Ev)
{

	if (client_->someoneJoined) {
		client_->someoneJoined = false;
		enemies.push_back(client_->getLastAddedP());
	}

	if (connected_succesfully == true)
	{
		client_->Update(input, Ev, &player_,dt);
		player_.Update();
		for (int i = 0; i < enemies.size(); i++) {

			enemies.at(i).Update();
			enemies.at(i).setPosition(client_->getClientPos(i));
		//	enemies.at(i).setPosition(client_->next_pos_pass_to_level);
		}
	}
}

void Level::clientInput(sf::Event* Ev)
{
	client_->HandleInput(Ev, input, &player_);
}

// Render level
void Level::render()
{
	beginDraw();
	
	
	client_->Render();
	player_.Render(window);
	for (int i = 0; i < enemies.size(); i++) {
		enemies.at(i).Render(window);
	}
	endDraw();
}
// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(0,114,160));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}