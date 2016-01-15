#include "CurlWrapper.h"

#include <fstream>

CurlWrapper::CurlWrapper() {
	curlHandle_ = curl_easy_init();
	curl_easy_setopt(curlHandle_, CURLOPT_WRITEFUNCTION, writeData);
	curl_easy_setopt(curlHandle_, CURLOPT_SSL_VERIFYPEER, false);
}

CurlWrapper::~CurlWrapper() {
	curl_easy_cleanup(curlHandle_);
}

void CurlWrapper::get(std::string name, std::string url) {
	curl_easy_setopt(curlHandle_, CURLOPT_URL, url.c_str());
	fileStream_.open(name, std::fstream::out | std::fstream::binary);
	curl_easy_setopt(curlHandle_, CURLOPT_WRITEDATA, &fileStream_);
	curl_easy_perform(curlHandle_);
	fileStream_.close();
}

std::string CurlWrapper::escapeURL(std::string url) {
	return std::string(curl_easy_escape(curlHandle_, url.c_str(), (int)url.length()));
}

size_t CurlWrapper::writeData(void* pointer, size_t size, size_t nmemb, std::fstream* fileStream) {
	fileStream->write((char*)pointer, size * nmemb);
	return (size * nmemb);
}