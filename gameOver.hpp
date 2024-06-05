#pragma once

#include <memory>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"

class GameOver : public Engine::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_gameOverTitle;
	sf::Text m_retryButton;
	sf::Text m_exitButton;

	bool m_isRetryButtonPressed;
	bool m_isRetryButtonSelected;

	bool m_isExitButtonPressed;
	bool m_isExitButtonSelected;

public:
	GameOver(std::shared_ptr<Context> &context);
	~GameOver();
	void Init() override;
	void ProcessInput() override;
	void Update(const sf::Time& deltaTime);
	void Draw() override;
};