project(jampi)
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_COMPILER "icpc")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall ")
#set(CMAKE_CXX_FLAGS_DEBUG "-prof-gen=srcpos -g")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

include_directories(include)

set(SOURCE_FILES_TIMER
  common/timer.cpp
  common/timer.h)

# =-=-=-=-=-=-=-=-=-= EXAMPLES =-=-=-=-=-=-=-=-=-= #

set(SOURCE_FILES_REDUCE examples/vector_reduce.cpp)
add_executable(vector_reduce ${SOURCE_FILES_REDUCE})
target_link_libraries(vector_reduce -pthread)

set(SOURCE_FILES_FOR examples/parallel_for.cpp)
add_executable(parallel_for ${SOURCE_FILES_FOR} ${SOURCE_FILES_TIMER})
target_link_libraries(parallel_for -pthread)

set(SOURCE_FILES_FIBONACCI examples/fibonacci.cpp)
add_executable(fibonacci ${SOURCE_FILES_FIBONACCI} ${SOURCE_FILES_TIMER})
target_link_libraries(fibonacci -pthread)
