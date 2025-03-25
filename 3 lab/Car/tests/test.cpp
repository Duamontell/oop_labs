#include <gtest/gtest.h>
#include "Car.h"
#include "CarController.h"
#include "Engine.h"
#include "Transmission.h"

std::string RunCarCommands(const std::vector<std::string>& commands)
{
	Car car;
	CarController carController(car);
	std::ostringstream outputStream;
	std::streambuf* oldCoutStreamBuf = std::cout.rdbuf(outputStream.rdbuf());

	for (const auto& command : commands)
	{
		try
		{
			carController.HandleCommand(command);
		}
		catch (const std::exception& e)
		{
			outputStream << e.what() << "\n";
		}
	}

	std::cout.rdbuf(oldCoutStreamBuf);
	return outputStream.str();
}

TEST(CarTest, EngineTest)
{
	Engine engine;
	EXPECT_FALSE(engine.IsTurnedOn());

	engine.EngineOn();
	EXPECT_TRUE(engine.IsTurnedOn());

	engine.EngineOff();
	EXPECT_FALSE(engine.IsTurnedOn());
}

TEST(CarTest, TransmissionTest)
{
	Transmission transmission;
	EXPECT_EQ(transmission.GetGear(), 0);

	transmission.SetGear(1);
	EXPECT_EQ(transmission.GetGear(), 1);

	transmission.SetGear(-1);
	EXPECT_EQ(transmission.GetGear(), -1);
}

TEST(CarTest, ValidateCar)
{
	Car car;
	EXPECT_NO_THROW(car.TurnOnEngine());
	EXPECT_NO_THROW(car.SetGear(0));
	EXPECT_NO_THROW(car.SetSpeed(0));
	EXPECT_NO_THROW(car.TurnOffEngine());

	Car car1;
	EXPECT_THROW(car1.SetGear(1), std::runtime_error);

	EXPECT_THROW(car1.SetSpeed(10), std::runtime_error);
}

TEST(CarControllerTest, ValidTest)
{
	std::vector<std::string> input = {
		"EngineOn",
		"SetGear -1",
		"SetSpeed 10",
		"SetGear 0",
		"SetSpeed 0",
		"SetGear 1",
		"SetSpeed 20",
		"SetGear 2",
		"SetSpeed 40",
		"SetGear 3",
		"Info"
	};

	EXPECT_EQ(RunCarCommands(input), "Engine: On\n"
									 "Direction: forward\n"
									 "Speed: 40\n"
									 "Gear: 3\n");
}

TEST(CarControllerTest, UnknownCommand)
{
	std::vector<std::string> input = {
		"Ensss"
	};

	EXPECT_EQ(RunCarCommands(input), "Unknown command\n");
}

TEST(CarControllerTest, EngineOffError)
{
	std::vector<std::string> input = {
		"EngineOn",
		"SetGear 1",
		"SetSpeed 20",
		"EngineOff\n",
	};

	EXPECT_EQ(RunCarCommands(input), "Сar must be stopped and in neutral gear\n");
}

TEST(CarControllerTest, GearArgumentError)
{
	std::vector<std::string> input = {
		"EngineOn",
		"SetGear 1.52",
	};

	EXPECT_EQ(RunCarCommands(input), "Invalid command argument\n");

	input = {
		"EngineOn",
		"SetGear fffffff"
	};

	EXPECT_EQ(RunCarCommands(input), "Invalid command argument\n");

	input = {
		"EngineOn",
		"SetGear 6"
	};

	EXPECT_EQ(RunCarCommands(input), "Invalid gear\n");

	input = {
		"EngineOn",
		"SetGear -2"
	};

	EXPECT_EQ(RunCarCommands(input), "Invalid gear\n");

	input = {
		"SetGear 3"
	};

	EXPECT_EQ(RunCarCommands(input), "Cannot set gear while engine is off\n");

	input = {
		"EngineOn",
		"SetGear 1",
		"SetSpeed 20",
		"SetGear 3"
	};

	EXPECT_EQ(RunCarCommands(input), "Unsuitable current speed\n");

	input = {
		"EngineOn",
		"SetGear 1",
		"SetSpeed 20",
		"SetGear -1"
	};

	EXPECT_EQ(RunCarCommands(input), "Cannot reverse while moving\n");
}

TEST(CarControllerTest, SpeedArgumentError)
{
	std::vector<std::string> input = {
		"EngineOn",
		"SetGear 1",
		"SetSpeed SS"
	};

	EXPECT_EQ(RunCarCommands(input), "Invalid command argument\n");

	input = {
		"EngineOn",
		"SetGear 1",
		"SetSpeed 4.2"
	};

	EXPECT_EQ(RunCarCommands(input), "Invalid command argument\n");

	input = {
		"EngineOn",
		"SetSpeed -1"
	};

	EXPECT_EQ(RunCarCommands(input), "Speed cannot be negative\n");

	input = {
		"SetSpeed 47"
	};

	EXPECT_EQ(RunCarCommands(input), "Cannot set speed while engine is off\n");

	input = {
		"EngineOn",
		"SetSpeed 50"
	};

	EXPECT_EQ(RunCarCommands(input), "Cannot accelerate on neutral\n");

	input = {
		"EngineOn",
		"SetGear 1",
		"SetSpeed 50"
	};

	EXPECT_EQ(RunCarCommands(input), "Speed is out of gear range\n");
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
