#pragma once
#include <string>

struct Settings
{
	int mapSize;
	int mines;
};

class SettingsLoader
{
	Settings settings_;
public:
	SettingsLoader(const std::string& fileName);
	SettingsLoader() = default;
	~SettingsLoader() = default;

	Settings get() const;
private:
	/// Reads the game settings from a file and extracts the settings.
	/// @param fileName The file name of the game settings folder
	void readFile(const std::string& fileName);

#ifdef _DEBUG
	friend class UnitTests;
#endif
};

