cmake_minimum_required(VERSION 3.25)

set(main C CXX)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME}
    main.cpp
)

include_directories(${PROJECT_NAME}
    .
)