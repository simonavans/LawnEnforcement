#pragma once
#include <memory>
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
	~SettingsLoader() = default;

	Settings get() const;
private:
	Settings readFile(const std::string& fileName) const;
};

