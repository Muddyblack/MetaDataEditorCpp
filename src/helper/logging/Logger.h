/**
 * @file Logger.h
 * @brief Defines the Logger class and convenience functions for logging.
 * @author Muddyblack
 * @date 24.02.2024
 */
#include <string>
#include <filesystem>
#include <iostream>

/**
 * @class Logger
 * @brief A simple logging class.
 *
 * This class provides a simple way to log messages with different log levels.
 * It outputs log messages to the console with additional data.
 */
class Logger {
public:
    /**
     * @brief Constructs a Logger object.
     *
     * @param file The name of the file where the log message originated.
     * @param line The line number where the log message originated.
     * @param level The log level of the message.
     */
    Logger(const char* file, int line, const std::string& level);

    
    /**
     * @brief Destroys the Logger object.
     *
     * This function is called when the Logger object is destroyed. It outputs a newline character to the console.
     */
    ~Logger();


    /**
     * @brief Outputs a log message to the console.
     *
     * @param msg The message to log.
     * @return A reference to the Logger object, allowing for chain calls.
     */
    template<typename T>
    Logger& operator<<(const T& msg) {
        std::cout << msg;
        return *this;
    }

private:
    /**
     * @brief Extracts the file name from a file path.
     *
     * @param file The file path.
     * @return The file name.
     */
    std::string getFileName(const char* file);
};


/**
 * @name Logging Convenience Functions
 * 
 * These functions create a Logger object with a specific log level.
 * 
 * @param file The name of the file where the log message originated.
 * @param line The line number where the log message originated.
 * @return A Logger object.
 * @{
 */
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
/** @} */ // end of Logging Convenience Functions