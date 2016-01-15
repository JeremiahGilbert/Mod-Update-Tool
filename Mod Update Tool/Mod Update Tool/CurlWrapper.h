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

	static std::unique_ptr<CurlWrapper>& getCurl();
private:

	CURL* curlHandle_;

	static size_t writeData(void* pointer, size_t size, size_t nmemb, void* ignore);

	static std::fstream fileStream;
	static std::unique_ptr<CurlWrapper> singletonCurl;
};

