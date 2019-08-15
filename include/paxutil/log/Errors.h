//
// Created by Paul on 02.06.2017.
//

#ifndef PAXENGINE3_ERRORS_H
#define PAXENGINE3_ERRORS_H

#include <sstream>
#include <stdexcept>
#include "Log.h"

#define PAX_ASSERT_NOT_NULL(value, ...) do { \
if (value == nullptr) { \
    std::stringstream s; \
    s << __VA_ARGS__; \
    PAX_LOG(PAX::Log::Level::Error, s.str()); \
    throw std::invalid_argument(s.str()); \
}} while(0)

#define PAX_THROW_RUNTIME_ERROR(...) do { \
    std::stringstream s; \
    s << __VA_ARGS__; \
    PAX_LOG(PAX::Log::Level::Error, s.str()); \
    throw std::runtime_error(s.str()); \
} while(0)

#define PAX_NOT_IMPLEMENTED() PAX_LOG(PAX::Log::Level::Warn, "not implemented")
#define PAX_NOT_IMPLEMENTED_EXCEPTION() PAX_THROW_RUNTIME_ERROR("not implemented")

#endif //PAXENGINE3_ERRORS_H
