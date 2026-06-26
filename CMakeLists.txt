cmake_minimum_required(VERSION 3.16)
project(SeaBattleSFML VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === ПУТЬ К SFML ===
set(SFML_DIR "C:/Users/User/Desktop/SFML-2.6.1/lib/cmake/SFML" CACHE PATH "Path to SFML cmake config")

find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

# Исходные файлы
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

# Создаём .exe
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Копируем assets в папку сборки
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)

# Windows: копируем SFML DLLs
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SFML_DIR}/../../bin $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
