#ifndef TRANSMISSION_H
#define TRANSMISSION_H

class Transmission
{
public:
	[[nodiscard]] int GetGear() const;
	void SetGear(int gear);

private:
	int m_gear = 0;
};

#endif // TRANSMISSION_H
