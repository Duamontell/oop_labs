#include "../include/Engine.h"

bool Engine::IsTurnedOn() const
{
	return m_isTurnedOn;
}

void Engine::EngineOn()
{
	m_isTurnedOn = true;
}

void Engine::EngineOff()
{
	m_isTurnedOn = false;
}
