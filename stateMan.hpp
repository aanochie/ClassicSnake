#pragma once 

#include <stack>
#include <memory>
#include "State.hpp"

namespace Engine
{
class StateMan
{
private: 
	// unique_ptr: owns and manages object through a pointer
	// object is disposed when u_ptr goes out of scope

	// Stack holding ptr of State
	std::stack<std::unique_ptr<State>> m_stateStack;
	std::unique_ptr<State> m_newState;
	
	// variables that need to be initialized
	bool m_add;
	bool m_replace;
	bool m_remove;

public:
	StateMan();
	~StateMan();

	void Add(std::unique_ptr<State> toAdd, bool replace = false);
	void PopCurrent();
	void ProcessStateChange();
	// returns address of ptr of object State 
	std::unique_ptr<State>& GetCurrent();
};

}
