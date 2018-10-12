#ifndef CORBA_PERF_REQUESTRUNNER_H
#define CORBA_PERF_REQUESTRUNNER_H

#include <memory>
#include "IRequestRunner.h"
#include "IMethodInfo.h"

#include "tao/ORB.h"


class RequestRunner: public IRequestRunner
{
public:

    RequestRunner(CORBA::Object_ptr obj, std::shared_ptr<IMethodInfo> method);

    std::chrono::microseconds Run() override;

protected:

    std::chrono::microseconds InvokeMethod(CORBA::Request_var req);

    void AddInputArg(CORBA::Request_var req, std::shared_ptr<IMethodArg> arg);

    std::chrono::microseconds PrepareAndInvoke(CORBA::Object_ptr obj, std::shared_ptr<IMethodInfo> method);

private:

    CORBA::Object_ptr obj;

    std::shared_ptr<IMethodInfo> methodInfo;
};

#endif //CORBA_PERF_REQUESTRUNNER_H
