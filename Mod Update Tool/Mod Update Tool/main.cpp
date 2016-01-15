#include <memory>

#include "ModUpdater.h"

int main() {
	auto modUpdater = std::make_unique<ModUpdater>("config.ini");
	modUpdater->updateMods();

	return (0);
}