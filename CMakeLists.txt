cmake_minimum_required(VERSION 3.31)
set(CMAKE_CXX_STANDARD 20)

project(TwitterTrendsOOPLab)
set(PROJECT_NAME TwitterTrendsOOPLab)

include_directories(include)

# Добавляем исполняемый файл
add_executable(${PROJECT_NAME}
        main.cpp
        parsers/ParsersJSON.cpp
        parsers/ParsersJSON.h
        entity/State.cpp
        entity/State.h
        entity/Polygon.h
        include/csv2.hpp
        renders/Render.h
        renders/Render.cpp
        parsers/ParserTxt.cpp
        parsers/ParserTxt.h
)

# OpenCV
find_package(OpenCV REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

# Boost
find_package(Boost REQUIRED COMPONENTS json)

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::json)


file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/resources)
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR}/)
