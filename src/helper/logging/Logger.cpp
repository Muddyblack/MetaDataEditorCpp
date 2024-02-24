#include <iostream>
#include "Logger.h"

Logger::Logger(const char* file, int line, const std::string& level) {
    std::filesystem::path filePath(file);
    std::string fileName = filePath.filename().string();
    std::cout << "[" << level << "] [" << fileName << "] [" << line << "] ";
}

Logger::~Logger() {
    std::cout << std::endl;
}