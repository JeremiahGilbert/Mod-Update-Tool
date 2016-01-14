#include "CurlWrapper.h"

#include <fstream>

std::unique_ptr<CurlWrapper> CurlWrapper::singletonCurl = std::make_unique<CurlWrapper>();

CurlWrapper::CurlWrapper() {
	curlHandle_ = curl_easy_init();
	curl_easy_setopt(curlHandle_, CURLOPT_WRITEFUNCTION, writeData);
	curl_easy_setopt(curlHandle_, CURLOPT_SSL_VERIFYPEER, false);
}

CurlWrapper::~CurlWrapper() {
	curl_easy_cleanup(curlHandle_);
}

std::unique_ptr<CurlWrapper>& CurlWrapper::getCurl() {
	return (singletonCurl);
}

void CurlWrapper::get(std::string name, std::string url) {
	curl_easy_setopt(curlHandle_, CURLOPT_WRITEDATA, name.c_str());
	curl_easy_setopt(curlHandle_, CURLOPT_URL, url.c_str());
	curl_easy_perform(curlHandle_);
}

size_t CurlWrapper::writeData(void* pointer, size_t size, size_t nmemb, char* fileName) {
	std::fstream fs;
	fs.open(fileName, std::fstream::out | std::fstream::binary);
	fs.write((char*)pointer, size * nmemb);
	fs.close();
	return (size * nmemb);
}