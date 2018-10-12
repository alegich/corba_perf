
#include "MethodInfo.h"

MethodInfo::MethodInfo(const char* methodName, const std::vector<std::shared_ptr<IMethodArg>>& arguments)
        : name(methodName)
        , args(arguments)
{}

std::string MethodInfo::GetMethodName() const
{
    return name;
}

std::vector<std::shared_ptr<IMethodArg>> MethodInfo::GetArguments() const
{
    return args;
}