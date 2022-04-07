#include "Internal/LoggingSystem.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

void LoggingSystem::Init(){
    spdlog::set_pattern("%^[%T] [%l] %v%$");
    auto logger = spdlog::stdout_color_mt("Logger");
    logger->set_level(spdlog::level::trace);
}

void LoggingSystem::ShutDown(){
    spdlog::shutdown();
}