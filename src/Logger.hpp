#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>

class Logger {
    private:
        std::ofstream file;
        int errorsCnt;
        int warningsCnt;

    public:
        enum class LogType { LOG_ERROR, LOG_WARNING, LOG_INFO };

        Logger(const char *filename = "debug.log");
        ~Logger();

        friend Logger &operator<<(Logger &, const LogType);
        friend Logger &operator<<(Logger &, const char *);

        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;
};

inline Logger::Logger(const char *filename)
  : errorsCnt(0), warningsCnt(0) {
    file.open(filename);
    if (file.is_open()) {
        file << "Log file created" << std::endl << std::endl;
    }
}

inline Logger::~Logger() {
    if (file.is_open()) {
        file << std::endl << std::endl;
        file << "total warnings: " << warningsCnt << ", total errors: " << errorsCnt << std::endl;
        file.close();
    }
}

inline  Logger &operator<<(Logger &logger, const Logger::LogType type) {
    switch (type) {
        case Logger::LogType::LOG_ERROR:
            logger.file << "[ERROR] ";
            ++logger.errorsCnt;
            break;
        case Logger::LogType::LOG_WARNING:
            logger.file << "[WARNING] ";
            ++logger.warningsCnt;
            break;
        default:
            logger.file << "[INFO] ";
            break;
    }
    return logger;
}

inline Logger &operator<<(Logger &logger, const char *text) {
    logger.file << text << std::endl;
    return logger;
}

#endif  // LOGGER_HPP
