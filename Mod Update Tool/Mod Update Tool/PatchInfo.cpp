#include "PatchInfo.h"

#include <fstream>

#include <curl.h>

PatchInfo::PatchInfo(std::string versionFile) {
	std::fstream versionStream(versionFile);
	if (versionStream.good()) {

	}
}

PatchInfo::~PatchInfo() {}
