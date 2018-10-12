//
// Created by olegk on 5/28/18.
//

#ifndef CORBA_PERF_METHODINFO_H
#define CORBA_PERF_METHODINFO_H

#include "IMethodArg.h"
#include "IMethodInfo.h"

class MethodInfo: public IMethodInfo
{
public:

    MethodInfo(const char* methodName, const std::vector<std::shared_ptr<IMethodArg>>& arguments);

    std::string GetMethodName() const override;

    std::vector<std::shared_ptr<IMethodArg>> GetArguments() const override;

private:

    std::string name;
    std::vector<std::shared_ptr<IMethodArg>> args;
};

#endif //CORBA_PERF_METHODINFO_H
