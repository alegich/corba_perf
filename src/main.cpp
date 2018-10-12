//#include "test_dsi.h"
#include "ace/Get_Opt.h"
#include "ace/Task.h"
#include <iostream>
#include <chrono>
#include <memory>
#include <sstream>

#include "tao/DynamicInterface/Server_Request.h"
#include "tao/DynamicInterface/Dynamic_Implementation.h"
#include "tao/DynamicInterface/AMH_DSI_Response_Handler.h"
#include "tao/PortableServer/PortableServer.h"
#include "tao/ORB.h"

#include "CmdParser.h"
#include "IMethodArg.h"
#include "IMethodInfo.h"
#include "RequestRunner.h"

std::string typeToStr(ArgType type)
{
    std::string retVal("<unknown>");

    switch (type)
    {
        case atLong:
            retVal = "long"; break;
        case atString:
            retVal = "string"; break;
        default:
            break;
    }

    return retVal;
}

std::string printMetodInfo(std::shared_ptr<IMethodInfo> method)
{
    std::stringstream retVal;
    retVal << method->GetMethodName() << "(";
    for (auto&& arg : method->GetArguments())
    {
        if (arg != method->GetArguments().front())
        {
            retVal << ", ";
        }

        retVal << typeToStr(arg->GetType()) << " " << arg->GetValue();
    }

    retVal << ")";

    return retVal.str();
}

//////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    try {
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
        std::shared_ptr<int> x(NULL, [&](int *) { orb->destroy(); });

        CmdParser parser;
        parser.Parse(argc, argv);

        std::cout << "Invoking function " << printMetodInfo(parser.GetMethodInfo()) << std::endl;

        CORBA::Object_var obj = orb->string_to_object(parser.GetObjectRef().c_str());

        std::shared_ptr<IMethodInfo> method = parser.GetMethodInfo();

        RequestRunner runner(obj, method);

        auto warmDuration = runner.Run();

        std::chrono::microseconds duration(0);

        for (int i = 0; i < parser.GetIterationsCount(); ++i)
        {
            auto iterDuration = runner.Run();
            duration += iterDuration;
        }

        std::cout << "Overall duration: " << (warmDuration + duration).count() << " μs, including warming up "
              << warmDuration.count() << " μs and " << parser.GetIterationsCount() << " iterations during "
              << duration.count() << " μs." << std::endl;
        std::cout << "Average duration: " << duration.count() / parser.GetIterationsCount() << " μs" << std::endl;
    }
    catch(CORBA::TRANSIENT&) {
        std::cerr << "Caught system exception TRANSIENT -- unable to contact the "
             << "server." << std::endl;
    }
    catch(CORBA::SystemException& ex) {
        std::cerr << "Caught a CORBA::" << ex._name() << std::endl;
    }
    catch(CORBA::Exception& ex) {
        std::cerr << "Caught CORBA::Exception: " << ex._name() << std::endl;
    }
    catch(std::exception& e) {
        std::cerr << "Caught std::exception: " << e.what() << std::endl;
    }
    return 0;
}
