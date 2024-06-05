#pragma once

#include <memory>
#include <array>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Game.hpp"
#include "State.hpp"
#include "snake.hpp"

class GamePlay : public Engine::State
{
    private:
        std::shared_ptr<Context> m_context;
        sf::Sprite m_grass;
        sf::Sprite m_food;
        std::array<sf::Sprite, 4> m_walls;
        Snake m_snake;

        sf::Vector2f m_snakeDirection;
        sf::Time m_elapasedTime;
        sf::Text m_scoreText;
        int m_score;

        bool m_isPauseKey;

    public:
        GamePlay(std::shared_ptr<Context> &context);
        ~GamePlay();

        void Init() override;
	    void ProcessInput() override;
	    void Update(const sf::Time& deltaTime);
	    void Draw() override;
        void Pause() override;
        void Start() override;
};