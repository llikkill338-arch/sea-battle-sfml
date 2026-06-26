cmake_minimum_required(VERSION 3.16)
project(SeaBattleSFML VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSVC UTF-8 FIX: /utf-8 flag ensures Unicode strings compile correctly
if(MSVC)
    add_compile_options(/utf-8)
endif()

# Set SFML path
set(SFML_DIR "C:/Users/User/Desktop/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Board.cpp
    src/Cell.cpp
    src/Ship.cpp
)

set(HEADERS
    include/Game.hpp
    include/Board.hpp
    include/Cell.hpp
    include/Ship.hpp
    include/Constants.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Copy assets to output directory after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)
