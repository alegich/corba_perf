//
// Created by olegk on 5/25/18.
//

#ifndef CORBA_PERF_IMETHODARG_H
#define CORBA_PERF_IMETHODARG_H

#include <string>

enum ArgType
{
    atString = 1,
    atLong = 2
};

class IMethodArg
{
public:
    virtual ~IMethodArg() {};

    virtual std::string GetValue() const = 0;

    virtual ArgType GetType() const = 0;
};

#endif //CORBA_PERF_IMETHODARG_H
