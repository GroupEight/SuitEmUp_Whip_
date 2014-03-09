#pragma once

class StateManager
{
public:
	enum States
	{
		InGame,
		Paused,
		Quit
	};

	StateManager(StateManager::States state);

	StateManager::States				State;
};