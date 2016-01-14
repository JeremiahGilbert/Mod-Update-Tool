#include <fstream>
#include <iostream>
#include <memory>

#include <curl.h>

#include "CurlWrapper.h"

int main() {
	std::unique_ptr<CurlWrapper>& curl = CurlWrapper::getCurl();
	curl->get("aFile.txt", "https://malitia.no-ip.org/test.txt");

	return (0);
}