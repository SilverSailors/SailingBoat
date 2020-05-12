#include "doctest.h"
#include "../include/logger.h"
#include <iostream>

TEST_CASE("Test Logger") {
    time_t raw_time = std::time(nullptr);
    char timeiso[20];
    strftime(timeiso, sizeof(timeiso), "%Y-%m-%d-%H-%M-%S", localtime(&raw_time));

    Logger logger(std::string("test/data_") + timeiso + ".json");
    Log log;

    log.entry_id = 1;

    logger.LogData(log);
    logger.Publish();
    logger.LogData(log);
    logger.Publish();

    // Check if file exists
}
