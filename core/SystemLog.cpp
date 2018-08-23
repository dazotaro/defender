/*
 * SystemLog.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: jusabiaga
 */

// Local Includes
#include "SystemLog.hpp"

// Global Includes
#include <cstdio>           // std::printf

namespace JU
{

SystemLog::LogMap SystemLog::log_map_;

/**
 * Log a message for a given tag
 *
 * @param tag 		Tag of the log
 * @param message	Message to log
 * @param abort		Abort execution?
 */
void SystemLog::logMessage(const char* tag, const char* message, bool abort)
{
    LogMapIter iter = log_map_.find(tag);
    if (iter == log_map_.end())     // new tag
    {
        Log new_log;
        new_log.addMessage(message);
        log_map_[tag] = new_log;
    }
    log_map_[tag].addMessage(message);

    if (abort)
    {
        printAllLogs();
        exit(EXIT_FAILURE);
    }
}


/**
 * Clear a log for an specific tag
 *
 * @param tag Tag
 */
void SystemLog::clearLog(const char* tag)
{
    log_map_.erase(tag);
}


/**
 * Clear all logs
 */
void SystemLog::clarAllLogs()
{
    log_map_.clear();
}


/**
 * Print a log for an specific tag
 *
 * @param tag Tag of log to print
 */
bool SystemLog::printLog(const char* tag)
{
    std::string output_string;

    LogMapConsIter iter = log_map_.find(tag);
    if (iter == log_map_.end())
    {
        return false;
    }

    iter->second.print(output_string);
    std::printf("%s\n", output_string.c_str());

    return true;
}


/**
 * Print all logs
 */
void SystemLog::printAllLogs()
{
    for (LogMapConsIter iter = log_map_.begin(); iter != log_map_.end(); iter++)
        printLog(iter->first.c_str());
}


} /* namespace JU */
