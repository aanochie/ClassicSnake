#pragma once 
#include <SFML/System/Time.hpp>

// Engine handles State, StateManager, AssetManager
namespace Engine
{
// Represents each state of the game 
// e.g. Menu, GamePlay, GameOver
// each state will have to implement all the methods
class State
{
	public:
		/*
		virtual allows for functions to not be implemented in derived classes
		=0 allows for abstraction therfore functions must be implemented
		*/

		//Constructor initialization 
		State(){};
		virtual ~State(){};

		virtual void Init() = 0; 
		virtual void ProcessInput() = 0;
		virtual void Update(const sf::Time& deltaTime) = 0;
		virtual void Draw() = 0;

		virtual void Pause(){};
		virtual void Start(){};
	};

}
