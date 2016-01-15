#include "ModUpdater.h"

#include <iostream>
#include <string>

#include <dirent.h>

#include "CurlWrapper.h"

ModUpdater::ModUpdater(std::string configuration) {
	std::ifstream configurationInputStream;
	configurationInputStream.open(configuration);
	if (!configurationInputStream.good()) {
		configurationInputStream.close();
		std::ofstream configurationOutputStream;
		configurationOutputStream.open(configuration);
		configurationOutputStream
			<< "updateHost https://malitia.no-ip.org/" << std::endl
			<< "updateRepository TPPI/" << std::endl
			<< "updateList latestMods.txt" << std::endl
			<< "path ./Mods/" << std::endl
			<< "extension jar";
		configurationOutputStream.close();
		configurationInputStream.open(configuration);
	}
	std::string option, value;
	while (configurationInputStream >> option >> value) {
		configuration_[option] = value;
	}
	configurationInputStream.close();

	auto& curl = CurlWrapper::getCurl();
	curl->get(configuration_["updateList"], configuration_["updateHost"] + configuration_["updateList"]);

	std::fstream mods;
	mods.open(configuration_["updateList"], std::ios::in);

	std::string mod;
	while (std::getline(mods, mod)) {
		modNames_.insert(mod);
	}
	mods.close();
}

ModUpdater::~ModUpdater() {}

void ModUpdater::updateMods() {
	for (auto it = modNames_.begin(); it != modNames_.end(); ++it) {
		if (!fileExists(configuration_["path"] + *it)) {
			auto& curl = CurlWrapper::getCurl();
			std::cout << "Downloading new file " << *it << std::endl;
			curl->get(configuration_["path"] + *it, configuration_["updateHost"] + configuration_["updateRepository"] + curl->escapeURL(*it));
		}
	}

	DIR* directory;
	struct dirent *entry;

	if ((directory = opendir(configuration_["path"].c_str())) != nullptr) {
		while ((entry = readdir(directory)) != nullptr) {
			std::string fileName(entry->d_name);
			if (!(fileName.substr(fileName.find_last_of(".") + 1) == configuration_["extension"])) continue;
			if (modNames_.find(entry->d_name) == modNames_.end()) {
				std::cout << "Removing old file " << entry->d_name << std::endl;
				std::remove((std::string() + configuration_["path"] + entry->d_name).c_str());
			}
		}
	}
}

bool ModUpdater::fileExists(std::string const file) {
	std::ifstream fileStream;
	fileStream.open(file);
	if (fileStream.good()) {
		fileStream.close();
		return (true);
	} else {
		fileStream.close();
		return (false);
	}
}
