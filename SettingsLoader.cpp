#include "SettingsLoader.h"

#include <fstream>
#include <iostream>
#include <vector>

SettingsLoader::SettingsLoader(const std::string& fileName)
{
	settings_ = readFile(fileName);
}

Settings SettingsLoader::get() const
{
	return settings_;
}

Settings SettingsLoader::readFile(const std::string& fileName)
{
	Settings settings{10, 15};
	std::ifstream ifs;

	ifs.open(fileName);
	if (!ifs.is_open())
	{
		std::cout << "WARNING: could not load data file '" << fileName << "'. Falling back to default settings.\n";
		return settings;
	}

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
		std::cout << "WARNING: map size cannot be <= 0, resetting map size to default value of 10\n";
		settings.mapSize = 10;
	}

	if (settings.mines <= 0)
	{
		std::cout << "WARNING: mines amount cannot be <= 0, resetting mines amount to default value of 15\n";
		settings.mines = 15;
	}

	if (settings.mapSize <= 4)
	{
		std::cout << "WARNING: map size must be > 4, resetting map size to default value of 10\n";
		settings.mapSize = 10;
	}

	if (settings.mapSize * settings.mapSize - 21 < settings.mines)
	{
		std::cout << "WARNING: attempted to add more mines than available tiles, resetting mines amount to default value of 15\n";
		settings.mines = 15;
	}

	return settings;
}
