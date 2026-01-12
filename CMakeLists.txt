cmake_minimum_required(VERSION 4.0)
project(Typoglycemia)
set(CMAKE_CXX_STANDARD 20)

add_library(typoglycemia STATIC typoglycemia.cpp)

target_include_directories(typoglycemia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (MINGW)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif()

add_executable(Typoglycemia standalone.cpp)

target_link_libraries(Typoglycemia PRIVATE typoglycemia)