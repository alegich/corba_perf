#ifndef CORBA_PERF_IREQUESTRUNNER_H
#define CORBA_PERF_IREQUESTRUNNER_H

#include <chrono>

class IRequestRunner
{
public:

    virtual ~IRequestRunner() {}

    virtual std::chrono::microseconds Run() = 0;
};

#endif //CORBA_PERF_IREQUESTRUNNER_H
