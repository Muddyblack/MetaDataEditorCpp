#include <string>
#include <filesystem>
#include <iostream>

class Logger {
public:
    Logger(const char* file, int line, const std::string& level);
    ~Logger();

    template<typename T>
    Logger& operator<<(const T& msg) {
        std::cout << msg;
        return *this;
    }

private:
    std::string getFileName(const char* file);
};

inline Logger logInfo(const char* file = __FILE__, int line = __LINE__) {
    return Logger(file, line, "INFO");
}

inline Logger logDebug(const char* file = __FILE__, int line = __LINE__) {
    return Logger(file, line, "DEBUG");
}

inline Logger logWarning(const char* file = __FILE__, int line = __LINE__) {
    return Logger(file, line, "WARNING");
}

inline Logger logCritical(const char* file = __FILE__, int line = __LINE__) {
    return Logger(file, line, "CRITICAL");
}

inline Logger logFatal(const char* file = __FILE__, int line = __LINE__) {
    return Logger(file, line, "FATAL");
}