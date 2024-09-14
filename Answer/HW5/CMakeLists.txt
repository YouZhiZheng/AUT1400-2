cmake_minimum_required(VERSION 3.13)
project(AP)

set(CMAKE_CXX_STANDARD 20)

# 查找 GTest 和 ncurses 库
find_package(GTest REQUIRED)
find_package(Curses REQUIRED)

# 包含目录
include_directories(include/)

# 可执行文件
add_executable(main
        src/main.cpp
        src/unit_test.cpp
        src/espresso_based.cpp
        src/cappuccino.cpp
        src/mocha.cpp
)

# 链接库
target_link_libraries(main
        GTest::GTest
        GTest::Main
        ${CURSES_LIBRARIES}
)