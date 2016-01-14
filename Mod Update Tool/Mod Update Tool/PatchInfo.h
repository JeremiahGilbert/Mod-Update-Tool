#pragma once

#include <string>

class PatchInfo {

public:
	PatchInfo(std::string versionFile);
	virtual ~PatchInfo();

private:
	unsigned lastApplied_;
	unsigned latest_;
};

