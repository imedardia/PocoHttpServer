cmake_minimum_required(VERSION 2.6)
project (httpserver)

set (SRV_SRC   poco.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-varargs")

find_library(POCO_FOUNDATION PocoFoundation)
find_library(POCO_UTIL PocoUtil)
find_library(POCO_NET PocoNet)

#compiling step
add_executable(httpserver ${SRV_SRC} ${POCO_FOUNDATION_INCLUDE_DIRS} ${POCO_UTIL_INCLUDE_DIRS} ${POCO_NET_INCLUDE_DIRS})

#Link step
target_link_libraries(httpserver -lPocoFoundation -lPocoXML -lPocoUtil -lPocoNet -lcrypto -lssl)
