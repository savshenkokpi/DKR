#include "Logger.h"
#include <fstream>
#include <ctime>

void Logger::log(const std::string& message) {
    std::ofstream logFile("log.txt", std::ios::app);
    std::time_t now = std::time(nullptr);
    logFile << std::ctime(&now) << ": " << message << std::endl;
    logFile.close();
}
