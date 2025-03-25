#ifndef CARCONTROLLER_H
#define CARCONTROLLER_H
#include <string>
#include "Car.h"

class CarController
{
public:
	explicit CarController(Car& car) : m_car(car) {}

	void HandleCommand(const std::string &command);

private:
	Car& m_car;

	void Info();
	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(int gear);
	void SetSpeed(int speed);
	void HandleSetGearCommand(std::istringstream &iss);
	void HandleSetSpeedCommand(std::istringstream &iss);
};


#endif // CARCONTROLLER_H
