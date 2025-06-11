cmake_minimum_required(VERSION 3.21)
project(QtTestApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Qt6组件
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# 自动处理Qt的MOC、UIC、RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 源文件
set(SOURCES
    main.cpp
    notepad.cpp
)

set(HEADERS
    notepad.h
)

# 创建可执行文件
add_executable(QtTestApp ${SOURCES} ${HEADERS})

# 链接Qt库
target_link_libraries(QtTestApp Qt6::Core Qt6::Widgets)

# 为Linux设置一些编译选项
if(UNIX AND NOT APPLE)
    set_target_properties(QtTestApp PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()