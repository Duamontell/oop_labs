#include "../include/Car.h"
#include <iostream>
#include <stdexcept>

void Car::Info() const
{
	std::cout << "Engine: " << (m_engine.IsTurnedOn() ? "On" : "Off") << "\n";
	std::cout << "Direction: " << m_direction << "\n";
	std::cout << "Speed: " << m_speed << "\n";
	std::cout << "Gear: " << m_transmission.GetGear() << std::endl;
}

void Car::TurnOnEngine()
{
	m_engine.EngineOn();
}

void Car::TurnOffEngine()
{
	if (m_speed != 0 || m_transmission.GetGear() != 0)
	{
		throw std::runtime_error("Сar must be stopped and in neutral gear");
	}
	if (!m_engine.IsTurnedOn())
	{
		throw std::runtime_error("Car is already turned off");
	}
	m_engine.EngineOff();
}

void Car::ValidateSetGear(int gear) const
{
	if (gear < -1 || gear > 5)
	{
		throw std::runtime_error("Invalid gear");
	}
	if (!m_engine.IsTurnedOn())
	{
		throw std::runtime_error("Cannot set gear while engine is off");
	}
	std::pair<int, int> speedLimit = GEARS[gear + 1].second;
	if (speedLimit.first > m_speed || speedLimit.second < m_speed)
	{
		throw std::runtime_error("Unsuitable current speed");
	}
	if (gear == -1 && m_speed != 0)
	{
		throw std::runtime_error("Cannot reverse while moving");
	}
}

void Car::SetGear(int gear)
{
	ValidateSetGear(gear);
	m_transmission.SetGear(gear);
}

void Car::ValidateSetSpeed(int speed) const
{
	if (speed < 0)
	{
		throw std::runtime_error("Speed cannot be negative");
	}
	if (!m_engine.IsTurnedOn())
	{
		throw std::runtime_error("Cannot set speed while engine is off");
	}
	if (m_transmission.GetGear() == 0 && speed > m_speed)
	{
		throw std::runtime_error("Cannot accelerate on neutral");
	}
	std::pair<int, int> speedLimit = GEARS[m_transmission.GetGear() + 1].second;
	if (speedLimit.first > speed || speedLimit.second < speed)
	{
		throw std::runtime_error("Speed is out of gear range");
	}
}

void Car::SetSpeed(int speed)
{
	ValidateSetSpeed(speed);
	m_speed = speed;
	if (m_speed == 0)
	{
		m_direction = DIRECTION_STANDING_STILL;
	}
	else if (m_transmission.GetGear() < 0)
	{
		m_direction = DIRECTION_BACKWARD;
	}
	else if (m_transmission.GetGear() > 0)
	{
		m_direction = DIRECTION_FORWARD;
	}
}