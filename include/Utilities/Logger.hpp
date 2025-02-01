#pragma once

#include <iostream>
#include <string>

// Define logging macros here
#define DEFINE_CLASS_NAME(name) static constexpr const char* __CLASS_NAME__ = #name;

// Function to get the logging location
inline std::string GetLoggerLocation(const char* functionName, const char* className = nullptr) {
    return className ? (std::string(className) + "::" + functionName) : std::string(functionName);
}

// Logging function
inline void LogMessage(const std::string& level, const std::string& location, const std::string& message) {
    std::cout << "[" << level << "] " << location << " - " << message << std::endl;
}

// Logging macros that work for both class methods and free functions
#ifdef LOG_ENABLED
    #ifdef __CLASS_NAME__
        #define LOG(message) LogMessage("INFO", GetLoggerLocation(__func__, __CLASS_NAME__), message)
        #define LOGWARN(message) LogMessage("WARN", GetLoggerLocation(__func__, __CLASS_NAME__), message)
        #define LOGERR(message) LogMessage("ERROR", GetLoggerLocation(__func__, __CLASS_NAME__), message)
    #else
        #define LOG(message) LogMessage("INFO", GetLoggerLocation(__func__), message)
        #define LOGWARN(message) LogMessage("WARN", GetLoggerLocation(__func__), message)
        #define LOGERR(message) LogMessage("ERROR", GetLoggerLocation(__func__), message)
    #endif
#else
    // No-op when logging is disabled
    #define LOG(message) ((void)0)
    #define LOGWARN(message) ((void)0)
    #define LOGERR(message) ((void)0)
#endif


