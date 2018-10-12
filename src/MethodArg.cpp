#include "MethodArg.h"

MethodArg::MethodArg(const char* value, ArgType type)
    : argValue(value), argType(type) {}

std::string MethodArg::GetValue() const {
    return argValue;
}


ArgType MethodArg::GetType() const {
    return argType;
}
