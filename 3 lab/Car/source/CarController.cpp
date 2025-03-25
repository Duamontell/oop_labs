#include "../include/CarController.h"
#include <sstream>

enum class CarCommand
{
	Info,
	EngineOn,
	EngineOff,
	SetGear,
	SetSpeed,
	Unknown
};

CarCommand ParseCommand(const std::string &command)
{
	if (command == "Info")
		return CarCommand::Info;
	if (command == "EngineOn")
		return CarCommand::EngineOn;
	if (command == "EngineOff")
		return CarCommand::EngineOff;
	if (command == "SetGear")
		return CarCommand::SetGear;
	if (command == "SetSpeed")
		return CarCommand::SetSpeed;
	return CarCommand::Unknown;
}

void CarController::HandleSetGearCommand(std::istringstream &iss)
{
	int gear;
	if (iss >> gear && !(iss.fail()) && iss.eof())
	{
		CarController::SetGear(gear);
	}
	else
	{
		throw std::invalid_argument("Invalid command argument");
	}
}

void CarController::HandleSetSpeedCommand(std::istringstream &iss)
{
	int speed;
	if (iss >> speed && !(iss.fail()) && iss.eof())
	{
		CarController::SetSpeed(speed);
	}
	else
	{
		throw std::invalid_argument("Invalid command argument");
	}
}

void CarController::HandleCommand(const std::string &command)
{
	std::istringstream iss(command);
	std::string cmd;
	iss >> cmd;

	switch (ParseCommand(cmd))
	{
		case CarCommand::Info:
			CarController::Info();
			break;
		case CarCommand::EngineOn:
			CarController::TurnOnEngine();
			break;
		case CarCommand::EngineOff:
			CarController::TurnOffEngine();
			break;
		case CarCommand::SetGear:
			HandleSetGearCommand(iss);
			break;
		case CarCommand::SetSpeed:
			HandleSetSpeedCommand(iss);
			break;
		case CarCommand::Unknown:
			throw std::invalid_argument("Unknown command");
	}
}

void CarController::Info()
{
	m_car.Info();
}

void CarController::TurnOnEngine()
{
	m_car.TurnOnEngine();
}

void CarController::TurnOffEngine()
{
	m_car.TurnOffEngine();
}

void CarController::SetGear(int gear)
{
	m_car.SetGear(gear);
}

void CarController::SetSpeed(int speed)
{
	m_car.SetSpeed(speed);
}
