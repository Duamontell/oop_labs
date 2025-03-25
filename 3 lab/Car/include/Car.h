#ifndef CAR_H
#define CAR_H
#include <string>
#include "Constants.h"
#include "Engine.h"
#include "Transmission.h"

class Car
{
public:
	void Info() const;
	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(int gear);
	void SetSpeed(int speed);

private:
	Engine m_engine;
	Transmission m_transmission;
	int m_speed = 0;
	std::string m_direction = DIRECTION_STANDING_STILL;

	void ValidateSetGear(int gear) const;
	void ValidateSetSpeed(int speed) const;
};

#endif // CAR_H
