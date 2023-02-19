cmake_minimum_required(VERSION 3.20)

set(EXEC_NAME "${TARGET}-test")
project(EXEC_NAME)

file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
add_executable(${EXEC_NAME} ${SRC} ${HEADERS})

link_directories(${LIB_DIR})
target_link_libraries(${EXEC_NAME} PUBLIC valor-std)