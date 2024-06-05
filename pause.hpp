// make class for pause state
#pragma once
#include <memory>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"

class PauseGame : public Engine::State
{
    private:
        std::shared_ptr<Context> m_context;
        sf::Text m_pauseTitle;
        sf::Text m_playButton;
        sf::Text m_exitButton;

        bool m_isPlayButtonSelected;
        bool m_isPlayButtonPressed;
        bool m_isExitButtonSelected;
        bool m_isExitButtonPressed;

    public:
        PauseGame(std::shared_ptr<Context> &context);
        ~PauseGame();
        void Init() override;
        void ProcessInput() override;
        void Update(const sf::Time& delataTime);
        void Draw() override;
        
};