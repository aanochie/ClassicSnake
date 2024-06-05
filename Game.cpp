#include "Game.hpp"
#include "mainMenu.hpp"
#include <SFML/Window/Event.hpp>

Game::Game() : m_context(std::make_shared<Context>())
{	
	// Renders a new window 
	m_context->m_window->create(sf::VideoMode(640, 352), "Snake", sf::Style::Close);
	// Adds reference to MainMenu to the stack of states
	// Meaning this state will be rendered onto the window  
	m_context->m_states->Add(std::make_unique<MainMenu>(m_context));
}

Game::~Game()
{
}

void Game::Run()
{
 	sf::Clock clock;
	sf::Time timeSinceLastFrame = sf::Time::Zero;

	while(m_context->m_window->isOpen())
	{
	        timeSinceLastFrame += clock.restart();
		
		while(timeSinceLastFrame > TIME_PER_FRAME)
		{	//
			timeSinceLastFrame -= TIME_PER_FRAME;
		
			m_context->m_states->ProcessStateChange();
			m_context->m_states->GetCurrent()->ProcessInput();
			m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
			m_context->m_states->GetCurrent()->Draw();
			
		}
	}	
}
