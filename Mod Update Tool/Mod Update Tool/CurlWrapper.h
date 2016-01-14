#pragma once

#include <memory>
#include <string>

#include <curl.h>

class CurlWrapper {
public:
	CurlWrapper();
	virtual ~CurlWrapper();

	void get(std::string name, std::string url);

	static std::unique_ptr<CurlWrapper>& getCurl();
private:

	CURL* curlHandle_;

	static size_t writeData(void* pointer, size_t size, size_t nmemb, char* fileName);

	static std::unique_ptr<CurlWrapper> singletonCurl;
};

