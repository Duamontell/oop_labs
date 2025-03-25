#ifndef ENGINE_H
#define ENGINE_H

class Engine {
public:
	[[nodiscard]] bool IsTurnedOn() const;
	void EngineOn();
	void EngineOff();

private:
	bool m_isTurnedOn = false;
};

#endif // ENGINE_H
