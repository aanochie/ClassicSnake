#include "mainMenu.hpp"
#include "gamePlay.hpp"
#include <SFML/Window/Event.hpp>


MainMenu::MainMenu(std::shared_ptr<Context> &context) 
	: m_context(context), m_isPlayButtonSelected(true),
	m_isPlayButtonPressed(false), m_isExitButtonPressed(false),
	m_isExitButtonSelected(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	//Game title
	m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Lato-Regular.ttf");
	m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_gameTitle.setString("Snake Game");
	m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, 
						  m_gameTitle.getLocalBounds().height / 2);
	m_gameTitle.setPosition(m_context->m_window->getSize().x /2,
							m_context->m_window->getSize().y / 2 - 150.f);
	
	

	//Play button
	m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_playButton.setString("Play");
	m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2, 
						   m_playButton.getLocalBounds().height / 2);
	m_playButton.setPosition(m_context->m_window->getSize().x /2,
							 m_context->m_window->getSize().y / 2 - 25.f);
	m_playButton.setCharacterSize(20);

	//Exit button
	m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_exitButton.setString("Exit");
	m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, 
						   m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(m_context->m_window->getSize().x /2,
							m_context->m_window->getSize().y / 2 + 25.f);
	m_exitButton.setCharacterSize(20);
}

void MainMenu::ProcessInput()
{
	sf::Event event;
	while(m_context->m_window->pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
		{
			m_context->m_window->close();
		}
		else if(event.type == sf::Event::KeyPressed)
		{
			switch(event.key.code)
			{
				case sf::Keyboard::Up:
				{
					if(!m_isPlayButtonSelected)
					{
						m_isPlayButtonSelected = true;
						m_isExitButtonSelected = false;
					}
					break;
				}
				case sf::Keyboard::Down:
				{
					if(!m_isExitButtonSelected)
					{
						m_isExitButtonSelected = true;
						m_isPlayButtonSelected = false;
					}
					
					break;
				}
				case sf::Keyboard::Return:
				{
					m_isPlayButtonPressed = false;
					m_isExitButtonPressed = false;

					if(m_isPlayButtonSelected)
					{
						m_isPlayButtonPressed = true;
					}
					else
					{
						m_isExitButtonPressed = true;
					}

					break;
				}
				default:
				{ break; }
			}
		}	
	}
}

void MainMenu::Update(const sf::Time& deltaTime)
{
	if(m_isPlayButtonSelected)
	{
		m_playButton.setFillColor(sf::Color::Green);
		m_exitButton.setFillColor(sf::Color::White); 
	} 
	else
	{
		m_exitButton.setFillColor(sf::Color::Red);
		m_playButton.setFillColor(sf::Color::White);
	}

	if(m_isPlayButtonPressed)
	{
		m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
	}

	else if(m_isExitButtonPressed)
	{
		m_context->m_window->close();
	}
}


void MainMenu::Draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_gameTitle);
	m_context->m_window->draw(m_playButton);
	m_context->m_window->draw(m_exitButton);
	m_context->m_window->display();
}
