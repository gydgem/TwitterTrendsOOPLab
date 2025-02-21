cmake_minimum_required(VERSION 3.31)
set(CMAKE_CXX_STANDARD 20)

project(TwitterTrendsOOPLab)
set(PROJECT_NAME TwitterTrendsOOPLab)

add_executable(${PROJECT_NAME} main.cpp
        Parsers/JSONMapParser.cpp
        Parsers/JSONMapParser.h)

# OpenCV
set(OPENCV_USE_STATIC_LIBS OFF)
find_package(OpenCV REQUIRED)

if (OpenCV_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
else ()
    message(FATAL_ERROR "OpenCV not found")
endif ()

# Boost
set(BOOST_USE_STATIC_LIBS OFF)
find_package(Boost REQUIRED COMPONENTS system filesystem)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
else ()
    message(FATAL_ERROR "Boost not found")
endif ()

# resources
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR}/resources)
