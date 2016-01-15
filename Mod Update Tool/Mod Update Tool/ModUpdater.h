#pragma once

#include <map>
#include <set>
#include <string>

class ModUpdater {

public:
	ModUpdater(std::string configurationFile);
	virtual ~ModUpdater();

	void updateMods();

private:
	static bool fileExists(std::string const file);

	std::map<std::string, std::string> configuration_;
	std::set<std::string> modNames_;
};
