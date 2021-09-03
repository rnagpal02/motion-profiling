cmake_minimum_required(VERSION 3.0.0)
project(MotionProfiling VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(setup)
include_directories(lib)    

add_executable(MotionProfiling main.cpp setup/parse-args.cpp lib/path.cpp lib/spline.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
