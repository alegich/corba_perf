//
// Created by olegk on 5/25/18.
//

#ifndef CORBA_PERF_METHODARG_H
#define CORBA_PERF_METHODARG_H

#include "IMethodArg.h"

class MethodArg: public IMethodArg
{
public:

    MethodArg(const char* value, ArgType type);

    std::string GetValue() const override;

    ArgType GetType() const override;

private:

    std::string argValue;
    ArgType argType;
};

#endif //CORBA_PERF_METHODARG_H
