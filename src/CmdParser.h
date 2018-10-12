//
// Created by olegk on 5/28/18.
//

#ifndef CORBA_PERF_CMDPARSER_H
#define CORBA_PERF_CMDPARSER_H

#include "IMethodInfo.h"

namespace ez {
    class ezOptionParser;
}

class CmdParser
{
public:

    CmdParser();

    void Parse(int argc, char** argv);

    std::shared_ptr<IMethodInfo> GetMethodInfo() const;

    int GetIterationsCount() const;

    std::string GetObjectRef() const;

protected:

    void Usage(ez::ezOptionParser& opt) const;
    void CheckArgs(ez::ezOptionParser& opt) const;

    std::vector<std::shared_ptr<IMethodArg>> ParseArgs(ez::ezOptionParser& opt);

private:

    std::shared_ptr<IMethodInfo> methodInfo;
    int iterCount;
    std::string ior;
};

#endif //CORBA_PERF_CMDPARSER_H
