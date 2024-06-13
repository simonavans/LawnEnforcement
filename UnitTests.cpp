#include "UnitTests.h"

#include <ios>
#include <iostream>
#include <fstream>

#include "SettingsLoader.h"

#ifdef _DEBUG
void UnitTests::runAllTests()
{
	// Clears the file
	std::ofstream tmp("./unit_tests/results.txt");
	tmp << "";
	tmp.close();

	shouldThrowIfGameSettingsFileNotFound();
	shouldThrowIfMinesNegative();
	shouldThrowIfMapSizeSmallerThan4();
	shouldThrowIfMoreMinesThanTiles();
}

void UnitTests::shouldThrowIfGameSettingsFileNotFound()
{
	SettingsLoader sut;
	if (assertReadFileThrows(sut, "config/non_existent_file.txt", std::ios_base::failure("")))
	{
		writeResult("shouldThrowIfGameSettingsFileNotFound", true);
	}
	else
		writeResult("shouldThrowIfGameSettingsFileNotFound", false);
}

void UnitTests::shouldThrowIfMinesNegative()
{
	// Set up
	if (!replaceLine("config/game_settings.txt", "mines: -1", "mines: 15"))
	{
		std::cout << "[UNIT TEST INFO] One or more unit tests have not run due to non-default game setting configuration\n";
		return;
	}

	SettingsLoader sut;
	if (assertReadFileThrows(sut,  "config/game_settings.txt", std::invalid_argument("")))
	{
		writeResult("shouldThrowIfMinesNegative", true);
	}
	else
		writeResult("shouldThrowIfMinesNegative", false);

	// Tear down
	replaceLine("config/game_settings.txt", "mines: 15", "mines: -1");
}

void UnitTests::shouldThrowIfMapSizeSmallerThan4()
{
	// Set up
	if (!replaceLine("config/game_settings.txt", "size: 3", "size: 10"))
	{
		std::cout << "[UNIT TEST INFO] One or more unit tests have not run due to non-default game setting configuration\n";
		return;
	}

	SettingsLoader sut;
	if (assertReadFileThrows(sut, "config/game_settings.txt", std::invalid_argument("")))
	{
		writeResult("shouldThrowIfMapSizeSmallerThan4", true);
	}
	else
		writeResult("shouldThrowIfMapSizeSmallerThan4", false);

	// Tear down
	replaceLine("config/game_settings.txt", "size: 10", "size: 3");
}

void UnitTests::shouldThrowIfMoreMinesThanTiles()
{
	// Set up
	if (!replaceLine("config/game_settings.txt", "mines: 200", "mines: 15"))
	{
		std::cout << "[UNIT TEST INFO] One or more unit tests have not run due to non-default game setting configuration\n";
		return;
	}

	SettingsLoader sut;
	if (assertReadFileThrows(sut, "config/game_settings.txt", std::invalid_argument("")))
	{
		writeResult("shouldThrowIfMoreMinesThanTiles", true);
	}
	else
		writeResult("shouldThrowIfMoreMinesThanTiles", false);

	// Tear down
	replaceLine("config/game_settings.txt", "mines: 15", "mines: 200");
}

template <typename T>
bool UnitTests::assertReadFileThrows(SettingsLoader& sl, const std::string& filePath, const T&)
{
	bool exceptionThrown = false;

	try
	{
		sl.readFile(filePath);
	}
	catch (const T&)
	{
		exceptionThrown = true;
	}

	return exceptionThrown;
}

void UnitTests::writeResult(const std::string& testName, const bool succeeded)
{
	std::ofstream resultFile("./unit_tests/results.txt", std::fstream::app);
	if (succeeded)
		resultFile << "Unit test '" << testName << "' succeeded.\n";
	else
		resultFile << "Unit test '" << testName << "' failed.\n";
	resultFile.close();
}

bool UnitTests::replaceLine(const std::string& fileName, const std::string& replacement, const std::string& toReplace)
{
	std::string copyFileName = fileName + "_copy.txt";
	std::ifstream inFile(fileName);
	std::ofstream outFile(copyFileName);
	std::string line;

	bool replaced = false;
	while (std::getline(inFile, line))
	{
		if (line == toReplace)
		{
			replaced = true;
			outFile << replacement << '\n';
		}
		else
			outFile << line << '\n';
	}
	inFile.close();
	outFile.close();

	if (!replaced)
	{
		std::cout << "[UNIT TEST ERROR] Could find line to replace in file " << fileName << '\n';
		return false;
	}

	if (std::remove(fileName.c_str()))
	{
		std::cout << "[UNIT TEST ERROR] Could not replace line in file " << fileName << '\n';
		return false;
	}

	if (std::rename(copyFileName.c_str(), fileName.c_str()))
	{
		std::cout << "[UNIT TEST ERROR] Could not replace line in file " << fileName << '\n';
		return false;
	}

	return true;
}
#endif
