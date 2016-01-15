#include <fstream>

#include <dirent.h>

int main() {
	std::ofstream mods;
	mods.open("latestMods.txt");

	DIR* directory;
	dirent *entry;
	if ((directory = opendir("./Mods")) != nullptr) {
		while ((entry = readdir(directory)) != nullptr) {
			std::string fileName(entry->d_name);
			if (!(fileName.substr(fileName.find_last_of(".") + 1) == "jar")) continue;
			mods << entry->d_name << std::endl;
		}
	}
	mods.close();

	return (0);
}