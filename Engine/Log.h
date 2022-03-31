#pragma once
#include <spdlog/spdlog.h>

#define CONSOLE_LOG_INFO(...)       if (spdlog::get("Logger") != nullptr) {spdlog::get("Logger")->info(__VA_ARGS__);}
#define CONSOLE_LOG_WARNING(...)    if (spdlog::get("Logger") != nullptr) {spdlog::get("Logger")->warn(__VA_ARGS__);}
#define CONSOLE_LOG_ERROR(...)      if (spdlog::get("Logger") != nullptr) {spdlog::get("Logger")->error(__VA_ARGS__);}