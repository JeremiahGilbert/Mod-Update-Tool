#pragma once

#include <fstream>
#include <memory>
#include <string>

#include <curl.h>

class CurlWrapper {
public:
	CurlWrapper();
	virtual ~CurlWrapper();

	void get(std::string name, std::string url);
	std::string escapeURL(std::string url);
private:
	CURL* curlHandle_;
	std::fstream fileStream_;

	static size_t writeData(void* pointer, size_t size, size_t nmemb, std::fstream* ignore);
};

