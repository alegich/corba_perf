cmake_minimum_required(VERSION 3.6)
project(corba_perf)

if(MSVC)
    SET(TAO_SUFFIX "d")
else()
    SET(TAO_SUFFIX "")
endif()

add_definitions(-DACE_LACKS_AUTO_PTR)
include_directories($ENV{ACE_ROOT} $ENV{TAO_ROOT} "$ENV{TAO_ROOT}/orbsvcs")
link_directories( "$ENV{ACE_ROOT}/lib" )

set(CMAKE_CXX_STANDARD 14)

add_executable(corba_perf main.cpp MethodArg.cpp MethodInfo.cpp CmdParser.cpp RequestRunner.cpp)
target_link_libraries(corba_perf
        ACE${TAO_SUFFIX}
        TAO${TAO_SUFFIX}
        TAO_IORInterceptor${TAO_SUFFIX}
        TAO_Valuetype${TAO_SUFFIX}
        TAO_PortableServer${TAO_SUFFIX}
        TAO_AnyTypeCode${TAO_SUFFIX}
        TAO_Messaging${TAO_SUFFIX}
        TAO_DynamicInterface${TAO_SUFFIX}
        )
