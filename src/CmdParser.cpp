#include "CmdParser.h"

#include "ezOptionParser.hpp"

#include "MethodInfo.h"
#include "MethodArg.h"

CmdParser::CmdParser()
        : iterCount(1)
{}

void CmdParser::Usage(ez::ezOptionParser& opt) const {
    std::string usage;
    opt.getUsage(usage);
    std::cout << usage;
};

void CmdParser::CheckArgs(ez::ezOptionParser& opt) const
{
    const char* errMessage = "Parsing of arguments failed";

    std::vector<std::string> badOptions;
    int i;
    if(!opt.gotRequired(badOptions)) {
        for(i=0; i < badOptions.size(); ++i)
            std::cerr << "ERROR: Missing required option " << badOptions[i] << ".\n\n";
        Usage(opt);
        throw std::runtime_error(errMessage);
    }

    if(!opt.gotExpected(badOptions)) {
        for(i=0; i < badOptions.size(); ++i)
            std::cerr << "ERROR: Got unexpected number of arguments for option " << badOptions[i] << ".\n\n";

        Usage(opt);
        throw std::runtime_error(errMessage);
    }
}

std::vector<std::shared_ptr<IMethodArg>> CmdParser::ParseArgs(ez::ezOptionParser& opt)
{
    std::vector<std::shared_ptr<IMethodArg>> retVal;

    std::vector<std::string> args;
    opt.get("-a")->getStrings(args);

    std::vector<int> argTypes;
    opt.get("-t")->getInts(argTypes);

    for (int i = 0; i < args.size(); ++i)
    {
        std::shared_ptr<IMethodArg> arg = std::make_shared<MethodArg>(args[i].c_str(), (ArgType)argTypes[i]);
        retVal.push_back(arg);
    }

    return retVal;
}

void CmdParser::Parse(int argc, char** argv)
{
    ez::ezOptionParser opt;
    opt.overview = "Simple request invocation performance testing program";
    opt.syntax = "corba_perf -r <object reference> -i <iterations> -n <operation_name> [-a arg1[,arg2,...] -t argType1[,argType2,...]]";
    opt.example = "corba_perf IOR:010000001300000049444c3a497373 100 sendAlert -a hello,3 -t 1,2";
    opt.footer = "arg types: 1- string, 2 - long";

    opt.add("", 1, 1, 0, "Object reference", "-r");
    opt.add("1", 0, 1, 0, "Number of iterations", "-i");
    opt.add("sendAlert", 0, 1, 0, "Operation name", "-n");
    opt.add("", 0, -1, ',', "List of operation arguments", "-a");
    opt.add("", 0, -1, ',', "List of argument types", "-t");

    opt.parse(argc, (const char**)argv);

    CheckArgs(opt);

    opt.get("-i")->getInt(iterCount);

    std::string methodName = "sendAlert";
    opt.get("-n")->getString(methodName);
    std::vector<std::shared_ptr<IMethodArg>> args = ParseArgs(opt);

    methodInfo = std::make_shared<MethodInfo>(methodName.c_str(), args);

    opt.get("-r")->getString(ior);
}

std::shared_ptr<IMethodInfo> CmdParser::GetMethodInfo() const
{
    return methodInfo;
}

int CmdParser::GetIterationsCount() const
{
    return iterCount;
}

std::string CmdParser::GetObjectRef() const
{
    return ior;
}
