/**
 * @file Logger.cpp
 * @brief Implements the Logger class for logging messages with file and line information.
 * @author Muddyblack
 * @date 24.02.2024
 */
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