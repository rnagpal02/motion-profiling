cmake_minimum_required(VERSION 3.0.0)
project(MotionProfiling VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(setup)
include_directories(lib)    
include_directories(graphing)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(MotionProfiling main.cpp setup/parse-args.cpp lib/path.cpp lib/spline.cpp)

target_link_libraries(MotionProfiling ${PYTHON_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
