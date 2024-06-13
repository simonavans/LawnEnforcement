#pragma once
#include <functional>
#include <string>

class SettingsLoader;

class UnitTests
{
public:
	static void runAllTests();
	static void shouldThrowIfGameSettingsFileNotFound();
	static void shouldThrowIfMinesNegative();
	static void shouldThrowIfMapSizeSmallerThan4();
	static void shouldThrowIfMoreMinesThanTiles();

private:
	/// Returns whether the readFile method on SettingsLoader threw an exception.
	/// @tparam T Type of exception to look for
	/// @param sl SettingsLoader to run test on
	/// @param filePath File path to the game settings
	/// @return Whether an exception was thrown or not
	template<typename T>
	static bool assertReadFileThrows(SettingsLoader& sl, const std::string& filePath, const T&);

	/// Writes the result of a unit test to the unit test results file.
	/// @param testName The name of the unit test, the name of the function
	/// @param succeeded Whether the test succeeded or failed
	static void writeResult(const std::string& testName, bool succeeded);

	/// Replaces a line in a certain file.
	/// @param fileName The name of the file
	/// @param replacement The string to replace the line with
	/// @param toReplace The string to look for
	/// @return Whether or not the replacement could complete
	static bool replaceLine(const std::string& fileName, const std::string& replacement, const std::string& toReplace);
};
