cmake_minimum_required(VERSION 3.20)

project(lualib C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(C:/ProgramData/Anaconda3/Library/include C:/ProgramData/Anaconda3/include)
link_directories(C:/ProgramData/Anaconda3/Library/lib C:/ProgramData/Anaconda3/libs)

add_library(test SHARED src/library.c)
target_link_libraries(test lua)

add_executable(luamain src/luamain.c)
target_link_libraries(luamain lua)


message(STATUS fuck you pythonpath)

add_executable(pymain src/pyembeed.c)

target_link_libraries(pymain python3)

add_library(_test SHARED src/testmodule.c)
target_link_libraries(_test python3)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set_target_properties(_test PROPERTIES SUFFIX .pyd)
endif ()