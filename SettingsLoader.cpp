#include "SettingsLoader.h"

#include <fstream>
#include <iostream>

SettingsLoader::SettingsLoader(const std::string& fileName)
{
	constexpr Settings defaultSettings{ 10, 15 };
	try
	{
		readFile(fileName);
	}
	catch (const std::ios_base::failure& e)
	{
		settings_ = defaultSettings;
		std::cout << "[GAME SETTINGS ERROR] " << e.what() << '\n';
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "[GAME SETTINGS ERROR] " << e.what() << '\n';
	}
}

Settings SettingsLoader::get() const
{
	return settings_;
}

void SettingsLoader::readFile(const std::string& fileName)
{
	Settings settings{10, 15};
	std::ifstream ifs;

	ifs.open(fileName);
	if (!ifs.is_open())
		throw std::ios_base::failure("Could not load game settings file '" + fileName + "'. Falling back to default settings.");

	std::string line;
	while (std::getline(ifs, line))
	{
		const size_t delimIndex = line.find(": " );
		if (line.substr(0, 2) == "//" || delimIndex == std::string::npos)
			continue;

		std::string settingData = line.substr(delimIndex + 2);
		if (line.find("size: ") != std::string::npos)
		{
			settings.mapSize = std::stoi(settingData);
		}
		else if (line.find("mines: ") != std::string::npos)
		{
			settings.mines = std::stoi(settingData);
		}
	}

	if (settings.mapSize <= 0)
	{
		settings.mapSize = 10;
		settings_ = settings;
		throw std::invalid_argument("Map size cannot be <= 0, resetting map size to default value of 10");
	}

	if (settings.mines <= 0)
	{
		settings.mines = 15;
		settings_ = settings;
		throw std::invalid_argument("Mines amount cannot be <= 0, resetting mines amount to default value of 15");
	}

	if (settings.mapSize <= 4)
	{
		settings.mapSize = 10;
		settings_ = settings;
		throw std::invalid_argument("Map size must be > 4, resetting map size to default value of 10");
	}

	if (settings.mapSize * settings.mapSize - 21 < settings.mines)
	{
		settings.mines = 15;
		settings_ = settings;
		throw std::invalid_argument("Attempted to add more mines than available tiles, resetting mines amount to default value of 15");
	}

	settings_ = settings;
}
