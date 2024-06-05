#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

#include "assetMan.hpp"
#include "stateMan.hpp"

enum AssetID
{
	MAIN_FONT = 0,
	GRASS,
	FOOD,
	WALL,
	SNAKE
};

/* Struct used since these variables are going to be commonly embedded in
	other objects eg.MainMenu, Game, GamePlay, GameOver */
struct Context
{
	/*Declaring object pointers for each manager class 
	  making it easy to access all of these classes and their methods through a variable 
	  instead of creating a new object of the class each time it's called*/
	std::unique_ptr<Engine::AssetMan> m_assets;
	std::unique_ptr<Engine::StateMan> m_states;
	std::unique_ptr<sf::RenderWindow> m_window;
	
	/*Method used to "initialize" these manager pointers*/
	Context()
	{
		m_assets = std::make_unique<Engine::AssetMan>();
		m_states = std::make_unique<Engine::StateMan>();
		m_window = std::make_unique<sf::RenderWindow>();
	}
};

class Game
{
private:
	/*needs to be initialised in constructor 
	  shared_ptr used to create a smart pointer of Context struct*/
	std::shared_ptr<Context> m_context;
	
	/*How much time each frame occupies per second allowing for window to 
	be updated at each given time*/
	const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);

public:
	Game();
	~Game();
	void Run(); 
};