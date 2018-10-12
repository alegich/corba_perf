//
// Created by olegk on 5/28/18.
//

#ifndef CORBA_PERF_IMETHODINFO_H
#define CORBA_PERF_IMETHODINFO_H

#include <vector>
#include <memory>
#include "IMethodArg.h"

class IMethodInfo
{
public:

    virtual ~IMethodInfo() {}

    virtual std::string GetMethodName() const = 0;

    virtual std::vector<std::shared_ptr<IMethodArg>> GetArguments() const = 0;

};

#endif //CORBA_PERF_IMETHODINFO_H
