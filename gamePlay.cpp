#include "gamePlay.hpp"
#include "gameOver.hpp"
#include "pause.hpp"
#include <SFML/Window/Event.hpp>
#include <stdlib.h>
#include <time.h>


GamePlay::GamePlay(std::shared_ptr<Context> &context)
    : m_context(context), 
      m_snakeDirection({16.f, 0.f}),
      m_elapasedTime(sf::Time::Zero),
      m_isPauseKey(false),
      m_score(0)
{
    srand(time(nullptr));
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
    m_context->m_assets->AddTexture(GRASS, "assets/textures/grass.png", true);
    m_context->m_assets->AddTexture(FOOD, "assets/textures/food.png");
    m_context->m_assets->AddTexture(WALL, "assets/textures/wall.png", true);
    m_context->m_assets->AddTexture(SNAKE, "assets/textures/snake.png");

    m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
    m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    for(auto& wall : m_walls)
    {
        wall.setTexture(m_context->m_assets->GetTexture(WALL));
    }

    // Horizontal walls
    // 640 is the width of window
    m_walls[0].setTextureRect({0, 0, 640, 16});
    m_walls[1].setTextureRect({0, 0, 640, 16});
    m_walls[1].setPosition(0, m_context->m_window->getSize().y - 16);

    // Vertical walls
    // 352 is the height of the window
    m_walls[2].setTextureRect({0, 0, 16, 352});
    m_walls[3].setTextureRect({0, 0, 16, 352});
    m_walls[3].setPosition(m_context->m_window->getSize().x - 16, 0);

    m_food.setTexture(m_context->m_assets->GetTexture(FOOD));
    m_food.setPosition(m_context->m_window->getSize().x / 2
    , m_context->m_window->getSize().y / 2);

    m_snake.Init(m_context->m_assets->GetTexture(SNAKE));

    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreText.setString("Score: " + std::to_string(m_score));
    m_scoreText.setCharacterSize(10);
    
}


void GamePlay::ProcessInput()
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
            sf::Vector2f newDirection = m_snakeDirection;
            switch(event.key.code)
            {
                case sf::Keyboard::Up:
                    // -16 to move one sprite(16x16) up on y axis
                    newDirection = {0.f, -16.f};
                    break;
                
                case sf::Keyboard::Down:
                    newDirection =  {0.f, 16.f};
                    break;
                
                case sf::Keyboard::Right:
                    newDirection = {16.f, 0.f};
                    break;
                
                case sf::Keyboard::Left:
                    newDirection = {-16.f, 0.f};
                    break;
                
                case sf::Keyboard::Escape:
                    m_isPauseKey = true;
                    m_context->m_states->Add(std::make_unique<PauseGame>(m_context));
                    break;
                
                default:
                    break;
            }
            // Snake can not move backward/180
            if(std::abs(m_snakeDirection.x) != std::abs(newDirection.x) ||
                std::abs(m_snakeDirection.y) != std::abs(newDirection.y))
            {
                m_snakeDirection = newDirection;
            }
        }
    }


}

void GamePlay::Update(const sf::Time& deltaTime)
{
    //Ensures snake doesn't move too fast
    m_elapasedTime += deltaTime;
    // Snake moves every 0.1 seconds
    if(m_elapasedTime.asSeconds() > 0.1)
    {
        bool isOnWall = false;

        for(auto& wall : m_walls)
        {
            if(m_snake.IsOn(wall))
            {
                m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
                break;
            }

        }

        if(m_snake.IsOn(m_food))
        {
            m_snake.Grow(m_snakeDirection);

            int x=0, y=0;
           
            // Sets lower value to be 16 so food is not displayed on the walls
            x = std::clamp(rand() % 640, 16, 640 - 2*16);
            y = std::clamp(rand() % 352, 16, 352 - 2*16);

            m_food.setPosition(x,y);
            m_score++;
            m_scoreText.setString("Score: " + std::to_string(m_score));
            m_scoreText.setCharacterSize(15);
        }
        // Doesn't make snake move while it's growing 
        else
        {
            m_snake.Move(m_snakeDirection);
        }

        m_elapasedTime = sf::Time::Zero;
    }

    if(m_isPauseKey)
    {
        
    }
}

void GamePlay::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_grass);

    for(auto& wall : m_walls)
    {
        m_context->m_window->draw(wall);
    }

    m_context->m_window->draw(m_food);
    m_context->m_window->draw(m_snake);
    m_context->m_window->draw(m_scoreText);
    m_context->m_window->display();
    

}

void GamePlay::Pause()
{

}

void GamePlay::Start() 
{

}