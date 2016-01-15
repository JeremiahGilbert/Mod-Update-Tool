#include "CurlWrapper.h"

#include <fstream>

std::fstream CurlWrapper::fileStream;
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
	curl_easy_setopt(curlHandle_, CURLOPT_URL, url.c_str());
	fileStream.open(name, std::fstream::out | std::fstream::binary);
	curl_easy_perform(curlHandle_);
	fileStream.close();
}

std::string CurlWrapper::escapeURL(std::string url) {
	return std::string(curl_easy_escape(curlHandle_, url.c_str(), (int)url.length()));
}

size_t CurlWrapper::writeData(void* pointer, size_t size, size_t nmemb, void* ignore) {
	fileStream.write((char*)pointer, size * nmemb);
	return (size * nmemb);
}