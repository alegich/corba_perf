#include "RequestRunner.h"

#include "tao/DynamicInterface/Request.h"

RequestRunner::RequestRunner(CORBA::Object_ptr obj, std::shared_ptr<IMethodInfo> method)
    : obj(obj), methodInfo(method)
{}

std::chrono::microseconds RequestRunner::InvokeMethod(CORBA::Request_var req)
{
    std::chrono::microseconds retVal;

    std::string methodName(req->operation());

    try {
        std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
        req->invoke();
        std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
        retVal = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    }
    catch (const CORBA::TRANSIENT&)
    {
        std::cerr << "CORBA::TRANSIENT during invoking method [" << methodName << "]" <<std::endl;
        throw;
    }
    catch (const CORBA::UserException& e)
    {
        std::cerr << "CORBA::UserException during invoking method [" << methodName << "]" <<std::endl;
        throw;
    }
    catch (const CORBA::Exception& e)
    {
        std::cerr << "CORBA::Exception during invoking method [" << methodName << "]" <<std::endl;
        throw;
    }
    catch (const std::exception& e)
    {
        std::cerr << "std::exception [" << e.what() << "] during invoking method [" << methodName << "]" <<std::endl;
        throw;
    }
    catch (...)
    {
        std::cerr << "Unknown exception during invoking method [" << methodName << "]" <<std::endl;
        throw;
    }

    return retVal;
}

void RequestRunner::AddInputArg(CORBA::Request_var req, std::shared_ptr<IMethodArg> arg)
{
    switch (arg->GetType())
    {
        case atString: req->add_in_arg() <<= arg->GetValue().c_str(); break;
        case atLong: req->add_in_arg() <<= atoi(arg->GetValue().c_str()); break;
        default: req->add_in_arg() <<= arg->GetValue().c_str(); break;
    }
}

std::chrono::microseconds RequestRunner::PrepareAndInvoke(CORBA::Object_ptr obj, std::shared_ptr<IMethodInfo> method)
{
    CORBA::Request_var req = obj->_request(method->GetMethodName().c_str());

    for (auto&& item : method->GetArguments()) {
        AddInputArg(req, item);
    }

    std::chrono::microseconds retVal = InvokeMethod(req);

    const char* ret = nullptr;
    req->return_value() >>= ret;

    return retVal;
}

std::chrono::microseconds RequestRunner::Run()
{
    return PrepareAndInvoke(obj, methodInfo);
}
